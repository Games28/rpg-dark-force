#ifndef POWERS_H
#define POWERS_H
#include "olcPixelGameEngine.h"
#include "Player.h"
#include "Physics.h"

class Object;

enum powertype
{
	PULLING,
	THROWN
};

enum THROWINGDIRECITON
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	STILL
};
class Powers
{
public:
	Powers() = default;
	void initSprite();
	void TKmove(Object& object, Player& player, Map& map);
	void TKstrafe(Object& object, Player& player);
	void TKrotation(olc::PixelGameEngine* pge, Object& object, Player& player, Map& map);
	bool isinsight(Object& object, Player& player, float fov, float& angle2player);
	void TKpull(Object& object, Player& player,float Height);

	void TKthrow(Object& object, Map& map,Player& player, float& deltatime);

public:
	olc::Sprite* indicatorsprite[2];
	float differencex;
	float differencey;
	int throwcount = 0;

	powertype ptype = powertype::THROWN;
	THROWINGDIRECITON throwdir = THROWINGDIRECITON::STILL;
};

#endif // !POWERS_H



