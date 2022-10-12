#include "stdafx.h"
#include "Node.h"

Node::Node(void)
{
	Color = Vec3f(1, 1, 1);
	CR = 100;
	RecievedBeaconMessage = 0;
	RecievedExtBeaconMessage = 0;
	SentMessage = 0;
	DistressRecieved = false;
	Distress = false;
	Count = 0;
}

Node::~Node(void)
{
}

void Node::transmitBeaconMessage(Node* node, int nbNode, float byte)
{
	SentMessage += byte;
	for (int i = 0; i < nbNode; i++)
	{
		float dis = (node[i].Pos - Pos).norm();
		if (dis < CR)
		{
			if(nakagami(dis))
				node[i].recieveBeaconMessage(byte);
		}
	}
}

void Node::transmitDistressMessage(Node* node, int nbNode, float byte)
{
	if (Distress)
	{
		SentMessage += byte;
		for (int i = 0; i < nbNode; i++)
		{
			float dis = (node[i].Pos - Pos).norm();
			if (dis < CR)
			{
				node[i].recieveDistressMessage(byte);
			}
		}
	}
}
void Node::transmitExtBeaconMessage(Node* node, int nbNode, float byte)
{
	SentMessage += byte;
	for (int i = 0; i < nbNode; i++)
	{
		float dis = (node[i].Pos - Pos).norm();
		if (dis < CR)
		{
			if (nakagami(dis))
				node[i].recieveExtBeaconMessage(byte);
		}
	}
}

void Node::recieveBeaconMessage(float byte)
{
	RecievedBeaconMessage += byte;
}

void Node::recieveDistressMessage(float byte)
{
	DistressRecieved = true;
	//Color = Vec3f(0, 0, 1);
	RecievedExtBeaconMessage += byte;
}

void Node::recieveExtBeaconMessage(float byte)
{
	RecievedExtBeaconMessage += byte;
}

void Node::move(float dt)
{
	//Pos += Vel*dt;
	Pos[0] += Direc*Speed*dt;
}

void Node::draw()
{
	GLUquadricObj *qobj = 0;
	qobj = gluNewQuadric();

	glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LIGHTING_BIT);
	glPushMatrix();
	glColor3f(Color[0], Color[1], Color[2]);
	glTranslatef(Pos[0], Pos[1], Pos[2]);
	gluSphere(qobj, RADIUS, 20, 20);
	glPopMatrix();
	glPopAttrib();
}

void Node::setCR(float cr)
{
	CR = cr;
}

void Node::setPos(Vec3f pos)
{
	Pos = pos;
}

void Node::setVel(Vec3f vel)
{
	Vel = vel;
}

void Node::increaseCR(float eps)
{
	if (CR >= CR_MAX)
		CR = CR_MAX;
	else CR += eps;	
}

void Node::setDirec(int d)
{
	Direc = d;
}

void Node::setSpeed(float s)
{
	Speed = s;
}

void Node::decreaseCR(float eps)
{
	if (CR <= CR_MIN)
		CR = CR_MIN;
	else CR -= eps;	
}

void Node::drawCR()
{
	drawCircleStipple(Pos, CR);
}

void Node::drawCircle(float r)
{
	Vec3f v1(r, 0, 0);
	int nbSeg = 100;
	float dAngle = 2 * PI / nbSeg;

	glBegin(GL_LINES);
	Mat3x3f rot; rot.setRotationMatrix(Vec3d(0, 0, 1), dAngle);
	for (int i = 0; i < nbSeg; i++)
	{
		Vec3f v2 = rot*v1;
		glVertex3f(v1[0], v1[1], v1[2]+1.0);
		glVertex3f(v2[0], v2[1], v2[2]+1.0);
		v1 = v2;
	}
	glEnd();
}

void Node::drawCircle(Vec3f pos, float r)
{
	Vec3f v1(r, 0, 0);
	int nbSeg = 100;
	float dAngle = 2 * PI / nbSeg;

	glBegin(GL_LINES);
	Mat3x3f rot; rot.setRotationMatrix(Vec3d(0, 0, 1), dAngle);
	for (int i = 0; i < nbSeg; i++)
	{
		Vec3f v2 = rot*v1;
		glVertex3f(pos[0] + v1[0], pos[1] + v1[1], pos[2] + v1[2] + 1.0);
		glVertex3f(pos[0] + v2[0], pos[1] + v2[1], pos[2] + v2[2] + 1.0);
		v1 = v2;
	}
	glEnd();
}

void Node::drawCircleStipple(float r)
{
	Vec3f v1(r, 0, 0);
	int nbSeg = 500;
	float dAngle = 2 * PI / nbSeg;

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	Mat3x3f rot; rot.setRotationMatrix(Vec3d(0, 0, 1), dAngle);
	for (int i = 0; i < nbSeg; i++)
	{
			Vec3f v2 = rot*v1;
			if (i % 2 == 0)
			{
				glVertex3f(v1[0], v1[1], v1[2] + 1.0);
				glVertex3f(v2[0], v2[1], v2[2] + 1.0);
			}
			v1 = v2;
	}
	glEnd();
}

void Node::drawCircleStipple(Vec3f pos, float r)
{
	Vec3f v1(r, 0, 0);
	int nbSeg = 500;
	float dAngle = 2 * PI / nbSeg;

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	Mat3x3f rot; rot.setRotationMatrix(Vec3d(0, 0, 1), dAngle);
	for (int i = 0; i < nbSeg; i++)
	{
		Vec3f v2 = rot*v1;
		if (i % 2 == 0)
		{
			glVertex3f(pos[0] + v1[0], pos[1] + v1[1], pos[2] + v1[2] + 1.0);
			glVertex3f(pos[0] + v2[0], pos[1] + v2[1], pos[2] + v2[2] + 1.0);
		}
		v1 = v2;
	}
	glEnd();
}

void Node::computeTransmissionRate(float dt)
{
	// Beacon load
	BeaconLoad = RecievedBeaconMessage/dt*8/1000000;

	// Channel occupancy
	ChannelOccupancy = (RecievedBeaconMessage + RecievedExtBeaconMessage + SentMessage)/dt * 8 / 1000000;

	if ((Count%CR_ADJ_FREQ) == 0)
	{
		if (BeaconLoad >= MABL)
		{
			Distress = true;
			Color = Vec3f(1, 0, 0);
		}
		else
		{ 
			Distress = false;
			Color = Vec3f(1, 1, 1);
		}
	}

	if (DistressRecieved)
	{
		decreaseCR(CR_D_EPS);
		DistressRecieved = false;
	}
	else
		increaseCR(CR_I_EPS);

	RecievedBeaconMessage = RecievedExtBeaconMessage = SentMessage = 0;
	Count++;
}

bool Node::nakagami(float dis)
{
	srand(time(NULL));
	int randNum = rand() % 100;
	if (NAKAGAMIM == 5)
	{
		if (dis < 100)
			return true;
		else if (dis < 200)
			return true;
		else if (dis < 300)
		{
			if (randNum < 95)
				return true;
			else
				return false;
		}
		else if (dis < 400)
		{
			if (randNum < 80)
				return true;
			else
				return false;
		}
		else if (dis < 500)
		{
			if (randNum < 40)
				return true;
			else
				return false;
		}
		else if (dis < 600)
		{
			if (randNum < 10)
				return true;
			else
				return false;
		}
		else
			return false;
	}

	if (NAKAGAMIM == 3)
	{
		if (dis < 100)
			return true;
		else if (dis < 200)
			return true;
		else if (dis < 300)
		{
			if (randNum < 90)
				return true;
			else
				return false;
		}
		else if (dis < 400)
		{
			if (randNum < 70)
				return true;
			else
				return false;
		}
		else if (dis < 500)
		{
			if (randNum < 40)
				return true;
			else
				return false;
		}
		else if (dis < 600)
		{
			if (randNum < 10)
				return true;
			else
				return false;
		}
		else
			return false;
	}

	if (NAKAGAMIM == 1)
	{
		if (dis < 100)
		{
			if (randNum < 95)
				return true;
			else
				return false;
		}
		else if (dis < 200)
		{
			if (randNum << 85)
				return true;
			else
				return false;
		}
		else if (dis < 300)
		{
			if (randNum < 70)
				return true;
			else
				return false;
		}
		else if (dis < 400)
		{
			if (randNum < 50)
				return true;
			else
				return false;
		}
		else if (dis < 500)
		{
			if (randNum < 40)
				return true;
			else
				return false;
		}
		else if (dis < 600)
		{
			if (randNum < 20)
				return true;
			else
				return false;
		}
		else
			return false;
	}
}

float Node::beaconLoad()
{
	return BeaconLoad;
}
float Node::channelOccupancy()
{
	return ChannelOccupancy;
}

