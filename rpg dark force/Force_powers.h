#ifndef FORCE_POWERS_H
#define FORCEPOWERS_H
#include "olcPixelGameEngine.h"
#include "Player.h"
#include "Sprite.h"
#include "Particle.h"

class Force_powers
{
public:
	void initSprite();
	void TKmove(object_t& sprite, Player& player);
	void TKstrafe(object_t& sprite, Player& player);
	void TKrotation(object_t& sprite, Player& player);
	bool isinsight(object_t& sprite, Player& player, float fov, float& angle2player);
	void Update(olc::PixelGameEngine* PGEptr, Player& player,Map& map, Sprite& sprite,float deltatime);
	void moveInput(olc::PixelGameEngine* pge, object_t& sprite,Sprite& spr, Map& map, float dt);

public:
	olc::Sprite* indicatorsprite[2];
	float differencex;
	float differencey;
	bool ispickedup = false;
	object_t* spr = nullptr;
};

#endif // !FORCE_POWERS_H



