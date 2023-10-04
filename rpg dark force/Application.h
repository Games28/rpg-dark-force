#ifndef  APPLICATION_H
#define APPLICATION_H
#include "olcPixelGameEngine.h"

#include "defs.h"
#include "Map.h"
#include "Player.h"
#include "Raycast.h"
#include "Wall.h"
#include "Sprite.h"
#include "Saber.h"
#include "Force_powers.h"
#include "ObjectManager.h"

class Application
{
public:
	Application() = default;

	void Setup();

	void ProcessInput(olc::PixelGameEngine* pge, float& fElapsedTime);
	
	void Update(olc::PixelGameEngine* pge,float & fElapsedTime);

	void Render(olc::PixelGameEngine* pge);

public:
	Map map;
	Player player;
	Raycast ray;
	Wall wall;
	Sprite sprite;
	Saber saber;
	Force_powers powers;
	ObjectManager OM;
};


#endif // ! APPLICATION_H


