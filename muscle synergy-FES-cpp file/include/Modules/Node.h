#ifndef NODE
#define NODE

#include "DataTypes/Vec.h"
#include "DataTypes/Mat.h"
#include <afxwin.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <vector>

#define RADIUS 0.5
#define PI 3.141592
#define CR_MAX 500
#define CR_MIN 100
#define CR_D_EPS 10
#define CR_I_EPS 10
#define NAKAGAMIM 1
#define MABL 0.1 //Mbps
#define CR_ADJ_FREQ 1

class Node
{
public:
	Node(void);
	~Node(void);

//functions
public:
	void transmitBeaconMessage(Node* node, int nbNode, float byte);
	void transmitDistressMessage(Node* node, int nbNode, float byte);
	void transmitExtBeaconMessage(Node* node, int nbNode, float byte);

	void recieveBeaconMessage(float byte);
	void recieveDistressMessage(float byte);
	void recieveExtBeaconMessage(float byte);
	void increaseCR(float eps);
	void decreaseCR(float eps);
	void draw();
	void drawCR();
	void move(float dt);

	void setCR(float cr);
	void setPos(Vec3f pos);
	void setVel(Vec3f vel);
	void setDirec(int d);
	void setSpeed(float s);

	float beaconLoad();
	float channelOccupancy();

	void computeTransmissionRate(float dt);
	bool nakagami(float dis);

private:
	void drawCircle(float r);
	void drawCircle(Vec3f pos, float r);
	void drawCircleStipple(float r);
	void drawCircleStipple(Vec3f pos, float r);

//variables
private:
	bool	Distress;
	bool	DistressRecieved;

	Vec3f	Pos;
	Vec3f	Color;
	Vec3f	Vel;
	int		Direc;
	float	Speed;

	float	CR;
	float	RecievedBeaconMessage;
	float	RecievedExtBeaconMessage;
	float	SentMessage;

	float	BeaconLoad;
	float	ChannelOccupancy;

	int		Count;

};

#endif