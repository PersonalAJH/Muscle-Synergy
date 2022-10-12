#ifndef SCENARIO
#define SCENARIO

#include "DataTypes/Vec.h"
#include "DataTypes/Mat.h"
#include <afxwin.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <vector>
#include "Modules\Node.h"

class Scenario
{
public:
	Scenario(void);
	~Scenario(void);

//functions
public:
	void draw();
	void drawNodes();
	void initNodes1();
	void initNodes2();
	void simulation(float dt);

//variables
public:
	FILE* F1;
	float Time;

	int NbLane;
	float LaneWidth;
	float LaneLength;

	// Nodes
	int NbNodes;
	int NodeDensity;	// nbNodes/km
	int UnitDisBtwNode;
	Node *Nodes;
};

#endif