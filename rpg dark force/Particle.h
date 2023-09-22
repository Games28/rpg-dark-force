#ifndef PARTICLE_H
#define PARTICLE_H
#include "Vec2.h"
#include "defs.h"

class Particle
{
public:
	Particle() = default;
	void integrate(float& deltatime);
	void physicsconstants();
	void physicobjectlift(float& deltatime, bool& isfalling);
	void physicssetup(float& lift);
	

public:
	bool isfalling;
	bool iscaught;
	float gravity;
	int pixels_per_meter;;
	float* pos = nullptr;
	float vel;
	float accelerate;
	float deltatime;
};


#endif // !PARTICLE_H


