#ifndef FORCE_POWERS_H
#define FORCEPOWERS_H
#include "olcPixelGameEngine.h"
#include "Player.h"
#include "Sprite.h"
#include "Physics.h"

class Force_powers
{
public:
	void initSprite();
	void TKmove(object_t& sprite, Player& player, Map& map);
	void TKstrafe(object_t& sprite, Player& player);
	void TKrotation(object_t& sprite, Player& player, Map& map);
	bool isinsight(object_t& sprite, Player& player, float fov, float& angle2player);
	void TKUpdate(olc::PixelGameEngine* PGEptr, Player& player,Map& map, Sprite& sprite,float deltatime);
	void moveInput(olc::PixelGameEngine* pge,Player& player, object_t& sprite,Sprite& spr, Map& map, float dt);
	void physicsUpdate(object_t& sprite, float dt);

public:
	olc::Sprite* indicatorsprite[2];
	float differencex;
	float differencey;
	bool ispickedup = false;
	object_t* spr = nullptr;
	Physics particle;
};

#endif // !FORCE_POWERS_H



