#ifndef WALL_H
#define WALL_H

#include "olcPixelGameEngine.h"

#include "Player.h"
#include "Raycast.h"
#include "defs.h"
#include "Map.h"


class Wall
{
public:
	Wall() = default;
	void wallTextures();
	void changeColorIntensity(olc::Pixel& p, float factor);
	void calculateBottomAndTop(float wallDistance,int halfheight, float wallheight, int& wallceil, int& wallfloor, Player& player);
	
	void renderWallProjection(olc::PixelGameEngine* PGEptr, Player& player, Raycast& rays, Map& map);
	int getTexture(int x,int y, int& id, Map& map);
public:
	olc::Sprite sprites[7];
	int text = 0;
	int time = 0;

	int nTestRay = NUM_RAYS / 2;
	float fTestRay = 0.5f;
};

#endif // !WALL_H


