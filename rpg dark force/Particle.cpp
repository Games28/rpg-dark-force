#include "Particle.h"

void Particle::integrate(float& deltatime)
{
	vel += accelerate * deltatime;
	*pos += vel * deltatime;
}

void Particle::physicsconstants()
{
	gravity = 9.8f;
	pixels_per_meter = 50;
	accelerate = gravity * pixels_per_meter;
}

void Particle::physicobjectlift(float& deltatime, bool& isfalling)
{
	if (isfalling)
	{
		integrate(deltatime);

	}

	if (*pos >= 0)
	{
		*pos = 0;

		vel *= -0.9f;
	}
}

void Particle::physicssetup(float& lift)
{
	pos = &lift;
}
