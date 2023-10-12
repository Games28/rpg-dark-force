#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H
#include "olcPixelGameEngine.h"
#include "Physics.h"
#include "Raycast.h"
#include "Powers.h"




class Object
{
public:
	Object() = default;
	

	void Update(Powers& powers,Map& map, float deltatime);
	
	void HorzMovement(float deltatime, Map& map,Player & player);
	void VertMovement(float deltatime,Player &player);

	//physics integrate
	void integrate(float& deltatime);
	void physicsconstants();
	void physicobjectlift(float& deltatime);

	//vertical physics
	void Vertphysicssetup(float mass);
	void Vertintegrate(float& deltatime);
	void VertClearForces();
	void AddVertForce(const float& force);

	//horiziontal physics
	void Horzphysicssetup(float mass);
	void Horzintegrate(float& deltatime);
	Vec2 HorzIntegrate(float& deltatime);
	void AddHorzForces(const Vec2& force);
	void HorzClearForces();

public:
	float x, y;
	int texture;
	olc::Sprite* sprite;
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
	float offset = 0;
	float currentheight = 0;
	//movement 
	float rotationangle = 0;
	int turndirection = 0;
	int movedirection = 0;
	float movespeed = 100;
	float turnspeed = 45 * (PI / 180);
	bool islifting = false;
	bool isfalling = false;
	int ObjectHeight = 0;
	int ThrowDirection = 0;
	bool isthrown = false;

	Physics physics;

	//physics intergrate

	//bool isfalling;
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
	Vec2 Horzpos;
	Vec2 HorzVel;
	Vec2 HorzAccelerate;
	Vec2 HorzSumforces;
	float HorzMass;
	float HorzInvMass;
};




class ObjectManager
{
public:
	ObjectManager() = default;
	void InitSprite();
	void InitObject();
	void Update(olc::PixelGameEngine* pge, float deltatime, Map& map, Player& player);
	void Input(olc::PixelGameEngine* pge,Player& player);
	void Render(olc::PixelGameEngine* pge, Player& player, Raycast& ray);
	void RenderMapObjects(olc::PixelGameEngine* pge);
	olc::Pixel SelectedPixel(olc::PixelGameEngine* ptr, Object* obj, olc::Sprite* sprite, olc::vf2d size, float samplex, float sampley, float Angle);
public:
	float deg2rad(float fAngleDeg) { return fAngleDeg * PI / 180.0f; }
	std::list<Object> objects;
	Powers powers;
	olc::Sprite* sprites[NUM_SPRITES];
	bool ispickedup = false;
	Object* ptr = nullptr;
};

#endif // !OBJECTMANAGER_H



