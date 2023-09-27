#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H
#include "olcPixelGameEngine.h"
#include "Physics.h"
#include "Raycast.h"




class Object
{
public:
	Object();
	~Object();

	void Update(float deltatime);
	void Projection(olc::PixelGameEngine *pge, Player& player, Raycast& ray);
	void Input(olc::PixelGameEngine* pge);
	void Movement(float deltatime, Map& map);

public:
	float x, y;

	int texture;
	float scale;
	bool stationary;
	olc::vf2d size;
	float distance;
	float angle;
	bool visible;
	bool inSight;
	int width;
	int height;
	bool pickedup;
	float liftup = 0.0f;

	//movement 
	float rotationangle = 0;
	int turndirection = 0;
	int movedirection = 0;
	float movespeed = 100;
	float turnspeed = 45 * (PI / 180);

	Physics physics;
};

class ObjectManager
{

};

#endif // !OBJECTMANAGER_H



