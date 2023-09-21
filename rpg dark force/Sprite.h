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
	float size;
	float distance;
	float angle;
	bool visible;
	bool inSight;
	int width;
	int height;
	bool pickedup;
	int liftup = 0;

	//movement 
	float rotationangle = 0;
	int turndirection = 0;
	int movedirection = 0;
	float movespeed = 100;
	float turnspeed = 45  * (PI / 180);
};



class Sprite
{
public:
	Sprite() = default;
	
	void initSpriteinfo();
	void initsprites();
	
	
	void moveObject(object_t& obj, Map& map,float deltatime);
	
	
	olc::Pixel newSelectedPixel(olc::PixelGameEngine* ptr, olc::Sprite *sprite,float size, float samplex, float sampley, float &diffangle);
	void SpriteProjection(olc::PixelGameEngine* PGEptr, Raycast& rays, Player& player);
	void mapSprites(olc::PixelGameEngine* PGEptr);
	float deg2rad(float fAngleDeg) { return fAngleDeg * PI / 180.0f; }
public:
	object_t objects[NUM_SPRITES];
	
	olc::Sprite* spriteptr[NUM_SPRITES];
	int vertposition = 0;
	int vertlook = 0;
	int heightoffset = 0;
	
	
};


#endif // !SPRITE_H


