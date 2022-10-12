#include "stdafx.h"
#include "Scenario.h"

Scenario::Scenario(void)
{
	LaneLength = 5000;
	LaneWidth = 3;
	NbLane = 4;

	Nodes = NULL;
	NodeDensity = 100;
	UnitDisBtwNode = 5;

	F1 = fopen("beaconingLoad.txt", "w");
	Time = 0;
}

Scenario::~Scenario(void)
{
	if (Nodes)
	{
		delete[] Nodes;
		Nodes = NULL;
	}
	fclose(F1);
}

void Scenario::draw()
{
	float margin = 1;
	glColor3f(0.5, 0.5, 0.5);
	glRectf(-LaneLength/2, -LaneWidth*NbLane-2, LaneLength/2, LaneWidth*NbLane+2);

	//Centerline
	glColor3f(251.0/256.0, 175.0 / 256.0, 65.0 / 256.0);
	float width = 0.3;
	glPushMatrix();
	glTranslatef(0, 0, 1.0);
	glRectf(-LaneLength / 2, -width/2, LaneLength / 2, width / 2);
	glPopMatrix();

	//Lane
	glColor3f(1, 1, 1);
	float laneSeg = 1.5;
	float laneSegGap = 0.5;
	float dis = -LaneLength / 2;

	glPushMatrix();
	glTranslatef(0, 0, 1.0);
	glRectf(-LaneLength / 2, -LaneWidth*NbLane -width / 2, LaneLength / 2, -LaneWidth*NbLane+width / 2);
	glRectf(-LaneLength / 2, LaneWidth*NbLane - width / 2, LaneLength / 2, LaneWidth*NbLane + width / 2);

	while (1)
	{
		if (dis > LaneLength / 2)
			break;
		dis += (laneSeg + laneSegGap);
		for (int i = 1; i < NbLane; i++)
		{
			glRectf(dis, -LaneWidth*i - width / 2, dis+laneSeg, -LaneWidth*i + width / 2);
			glRectf(dis, LaneWidth*i - width / 2, dis + laneSeg, LaneWidth*i + width / 2);
		}

	}
	glPopMatrix();
}

void Scenario::drawNodes()
{
	for (int i = 0; i < NbNodes; i++)
	{
		Nodes[i].draw();
		//Nodes[i].drawCR();
	}
		
}

void Scenario::initNodes1()
{
	int nbLaneSeg = LaneLength / 1000;
	int nbNodePerSeg = 1000 / UnitDisBtwNode;
	NbNodes = NodeDensity * nbLaneSeg;
	Nodes = new Node[NbNodes];
	
	int nodeIdx = 0;
	srand(time(NULL));
	for (int i = 0; i < nbLaneSeg; i++)
	{
		for (int j = 0; j < NodeDensity; j++)
		{
			// 1. 차량간 최소거리 50m, 1km내에 20 포인트
			float posX = -LaneLength / 2 + i * 1000 + (rand() % nbNodePerSeg)*UnitDisBtwNode;
			int laneSel = rand() % (NbLane * 2) - NbLane;
			float posY = LaneWidth*laneSel + LaneWidth / 2.0;
			Nodes[nodeIdx].setPos(Vec3f(posX, posY, 0));
			if (laneSel > 0)
			{
				Nodes[nodeIdx].setDirec(1);
				Nodes[nodeIdx].setSpeed(10);
			}
			else
			{
				Nodes[nodeIdx].setDirec(-1);
				Nodes[nodeIdx].setSpeed(10);
			}
			nodeIdx++;
		}
	}
}

void Scenario::initNodes2()
{
	int nbLaneSeg = LaneLength / 1000;
	int nbNodePerSeg = 1000 / UnitDisBtwNode;
	NbNodes = NodeDensity * nbLaneSeg;
	Nodes = new Node[NbNodes];

	int nbNode[5];
	nbNode[0] = NbNodes*0.15;
	nbNode[1] = NbNodes*0.3;
	nbNode[2] = NbNodes*0.15;
	nbNode[3] = NbNodes*0.3;
	nbNode[4] = NbNodes - (nbNode[0]+ nbNode[1] + nbNode[2] + nbNode[3]);

	int nodeIdx = 0;
	srand(time(NULL));
	for (int i = 0; i < nbLaneSeg; i++)
	{
		for (int j = 0; j < nbNode[i]; j++)
		{
			// 1. 차량간 최소거리 50m, 1km내에 20 포인트
			float posX = -LaneLength / 2 + i * 1000 + (rand() % nbNodePerSeg)*UnitDisBtwNode;
			int laneSel = rand() % (NbLane * 2) - NbLane;
			float posY = LaneWidth*laneSel + LaneWidth / 2.0;
			Nodes[nodeIdx].setPos(Vec3f(posX, posY, 0));
			if (laneSel > 0)
			{
				Nodes[nodeIdx].setDirec(1);
				Nodes[nodeIdx].setSpeed(10);
			}
			else
			{
				Nodes[nodeIdx].setDirec(-1);
				Nodes[nodeIdx].setSpeed(10);
			}
			nodeIdx++;
		}
	}
}

void Scenario::simulation(float dt)
{
	fprintf(F1, "%f\t", Time);
	for (int i = 0; i < NbNodes; i++)
	{
		Nodes[i].transmitBeaconMessage(Nodes, NbNodes, 500);
		Nodes[i].transmitDistressMessage(Nodes, NbNodes, 1);
		//Nodes[i].move(dt);
		Nodes[i].computeTransmissionRate(dt);
		//fprintf(F1, "%.2f ", Nodes[i].beaconLoad());
	}
	fprintf(F1, "%.2f\n", Nodes[5].beaconLoad());
	//fprintf(F1, "\n");
	Time += dt;
}