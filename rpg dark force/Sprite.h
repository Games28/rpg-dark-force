#ifndef SPRITE_H
#define SPRITE_H
#include "olcPixelGameEngine.h"
#include "Player.h"
#include "defs.h"
#include "Raycast.h"

struct object_t
{
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
	float offset;

	
	//movement 
	float rotationangle = 0;
	int turndirection = 0;
	int movedirection = 0;
	float movespeed = 100;
	float turnspeed = 45  * (PI / 180);
	bool islifting = false;
	bool isfalling = false;
};



class Sprite
{
public:
	Sprite() = default;

	void initSpriteinfo();
	void initsprites();


	void moveObject(object_t& obj, Player& player, Map& map, float deltatime);


	olc::Pixel newSelectedPixel(olc::PixelGameEngine* ptr, object_t* obj, olc::Sprite* sprite, olc::vf2d size, float samplex, float sampley, float Angle);
	void SpriteProjection(olc::PixelGameEngine* PGEptr, Raycast& rays, Player& player);
	void mapSprites(olc::PixelGameEngine* PGEptr, Sprite& sprite);
	float deg2rad(float fAngleDeg) { return fAngleDeg * PI / 180.0f; }
public:
	std::list<object_t> objects;
	
	olc::Sprite* spriteptr[NUM_SPRITES];
	int vertposition = 0;
	int vertlook = 0;
	int heightoffset = 0;
	
	
};


#endif // !SPRITE_H


