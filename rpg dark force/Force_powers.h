#ifndef FORCE_POWERS_H
#define FORCEPOWERS_H
#include "olcPixelGameEngine.h"
#include "Player.h"
#include "Sprite.h"

class Force_powers
{
public:
	void initSprite();
	void TKmove(sprite_t& sprite, Player& player);
	void TKstrafe(sprite_t& sprite, Player& player);
	void TKrotation(sprite_t& sprite, Player& player);
	bool isinsight(sprite_t& sprite, Player& player, float fov, float& angle2player);
	void Update(olc::PixelGameEngine* PGEptr, Player& player, Sprite& sprite,float deltatime);

public:
	olc::Sprite* indicatorsprite[2];
	float differencex;
	float differencey;
	bool ispickedup = false;
	sprite_t* spr = nullptr;
};

#endif // !FORCE_POWERS_H



