#ifndef PARTICLE_H
#define PARTICLE_H
#include "Vec2.h"
#include "defs.h"

class Particle
{
public:
	Particle() = default;
	void InitVert(float& vert, float mass);
	void integrateVert(float& deltatime);
	void addVertForce(const float& force);

	void InitHorz(Vec2& pos, float mass);
	void integrateHorz(float& deltatime);
	void addHorzForce(const Vec2& force);

	void ClearVertForces();
	void ClearHorzForces();

public:
	
	float* objectVertPos = nullptr;
	float VertAccelerate;
	float VertVel;
	float VertMass;
	float VertinvMass;
	float VertSumForces;

	Vec2* objectHorzPos = nullptr;
	Vec2 HorzVel;
	Vec2 HorzAccelerate;
   float HorzsumForces;
   float Horzmass;
   float HorzinvMass;


};


#endif // !PARTICLE_H


