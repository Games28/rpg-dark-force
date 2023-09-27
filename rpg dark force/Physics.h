#ifndef PARTICLE_H
#define PARTICLE_H
#include "Vec2.h"
#include "defs.h"

class Physics
{
public:
	Physics();
	void integrate(float& deltatime);
	void physicsconstants();
	float physicobjectlift(float& deltatime);
	void physicssetup(float lift);
	

public:
	bool isfalling;
	bool iscaught;
	float gravity;
	int pixels_per_meter;;
	float pos;
	float vel;
	float accelerate;
	float deltatime;
};


#endif // !PARTICLE_H


