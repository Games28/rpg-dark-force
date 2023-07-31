#ifndef SPRITE_H
#define SPRITE_H
#include "olcPixelGameEngine.h"
#include "Player.h"
#include "defs.h"
#include "Raycast.h"

struct sprite_t
{
	float x, y;
	int texture;
	bool stationary;
	float size;
	float distance;
	float angle;
	bool visible;
	bool inSight;
	int width;
	int height;
	bool pickedup;
	
};



class Sprite
{
public:
	Sprite() = default;
	
	void initSpriteinfo();
	void initsprites();
	void calculateBottomandTop(Player& player, float distance,float& SHeight, float& SWidth, int halfheight, float& ceiling, float& floor);
	
	
	olc::Pixel newSelectedPixel(olc::PixelGameEngine* ptr, olc::Sprite *sprite,float size, float samplex, float sampley, float &diffangle);
	void SpriteProjection(olc::PixelGameEngine* PGEptr, Raycast& rays, Player& player);
	void mapSprites(olc::PixelGameEngine* PGEptr);
	float deg2rad(float fAngleDeg) { return fAngleDeg * PI / 180.0f; }
public:
	sprite_t sprites[NUM_SPRITES];
	olc::Sprite* spriteptr[NUM_SPRITES];
	int vertposition = 0;
	int vertlook = 0;
	int heightoffset = 0;
	int lookoffset = 0;
	
};


#endif // !SPRITE_H


