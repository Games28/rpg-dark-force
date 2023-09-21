#include "Particle.h"



void Particle::InitVert(float& vert, float mass)
{
	objectVertPos = &vert;
}

void Particle::integrateVert(float& deltatime)
{
	VertAccelerate = VertSumForces * VertinvMass;
	VertVel += VertAccelerate * deltatime;
	*objectVertPos += VertVel * deltatime;
}

void Particle::addVertForce(const float& force)
{
	VertSumForces += force;
}

void Particle::InitHorz(Vec2& pos, float mass)
{
}

void Particle::integrateHorz(float& deltatime)
{
}

void Particle::addHorzForce(const Vec2& force)
{
}

void Particle::ClearVertForces()
{
	VertSumForces = 0;
}

void Particle::ClearHorzForces()
{
}


