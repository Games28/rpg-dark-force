#ifndef POWERS_H
#define POWERS_H
#include "olcPixelGameEngine.h"
#include "Player.h"
#include "Physics.h"

class Object;


class Powers
{
public:
	Powers() = default;
	void initSprite();
	void TKmove(Object& object, Player& player, Map& map);
	void TKstrafe(Object& object, Player& player);
	void TKrotation(olc::PixelGameEngine* pge, Object& object, Player& player, Map& map);
	bool isinsight(Object& object, Player& player, float fov, float& angle2player);

	void TKthrow(Object& object, Map& map, float& deltatime);

public:
	olc::Sprite* indicatorsprite[2];
	float differencex;
	float differencey;
	
	
};

#endif // !POWERS_H



