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

	//vertical physics
	void Vertphysicssetup(float lift, float mass);
	void Vertintegrate(float& deltatime);
	void VertClearForces();
	void AddVertForce(const float& force);

	//horiziontal physics
	void Horzphysicssetup(float& x, float& y, float mass);
	void Horzintegrate(float& deltatime);
	Vec2 HorzIntegrate(float& deltatime);
	void AddHorzForces(const Vec2& force);
	void HorzClearForces();

public:
	bool isfalling;
	bool iscaught;
	float gravity;
	int pixels_per_meter;;
	
	float vel;
	float accelerate;
	float deltatime;

	//vertical physics
	float Vertpos;
	float VertAccelerate;
	float VertVel;
	float VertsumForces;
	float VertMass;
	float VertinvMass;
	int Vertradius;


	//horiziontal physics
	Vec2 *Horzpos = nullptr;
	Vec2 HorzVel;
	Vec2 HorzAccelerate;
	Vec2 HorzSumforces;
	float HorzMass;
	float HorzInvMass;

};


class Force
{
public:
	Force() = default;

	static Vec2 GenerateDragForce();
};

#endif // !PARTICLE_H


