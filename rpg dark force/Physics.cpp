#include "Physics.h"

Physics::Physics()
{
	gravity = 9.8f;
    pixels_per_meter = 50;
    accelerate = gravity * pixels_per_meter;
}

void Physics::integrate(float& deltatime)
{
	vel += accelerate * deltatime;
	pos += vel * deltatime;
}

void Physics::physicsconstants()
{
	gravity = 9.8f;
	pixels_per_meter = 50;
	accelerate = gravity * pixels_per_meter;
}

float Physics::physicobjectlift(float& deltatime)
{
	
	integrate(deltatime);

	

	if (pos >= 0)
	{
		pos = 0;

		vel *= -0.9f;
	}

	return pos;
}

void Physics::physicssetup(float lift)
{
	pos = lift;
}
