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
	void TKrotation(sprite_t& sprite, Player& player);
	bool isinsight(sprite_t& sprite, Player& player, float fov, float& angle2player);
	void Update(olc::PixelGameEngine* PGEptr, Player& player, Sprite& sprite);

public:
	olc::Sprite* indicatorsprite[2];
};

#endif // !FORCE_POWERS_H



