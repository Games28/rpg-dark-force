#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "defs.h"
#include "Map.h"
#include "Player.h"
#include "Raycast.h"
#include "Wall.h"
#include "Sprite.h"
#include "Saber.h"
#include "Force_powers.h"



class darkforce : public olc::PixelGameEngine
{
public:
	darkforce()
	{
		sAppName = "dark force raycaster";
	}
public:
	Map map;
	Player player;
	Raycast ray;
	Wall wall;
	Sprite sprite;
	Saber saber;
	Force_powers powers;
public:

	bool OnUserCreate() override
	{
		
		wall.wallTextures();
		sprite.initSpriteinfo();
		sprite.initsprites();
		saber.initSaber();
		map.InitMap(MAP_NUM_COLS_X, MAP_NUM_ROWS_Y);
		map.addMapLayer(map.Map_levelOne);
		map.addMapLayer(map.Map_levelTwo);
		map.addMapLayer(map.Map_levelThree);
		map.addTextures(map.Texture_levelOne);
		map.addTextures(map.Texture_levelTwo);
		map.addTextures(map.Texture_levelThree);
		powers.initSprite();

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

		Clear(RENDER_CEILING ? olc::BLACK : olc::BLUE);
        

		player.processInput(this,fElapsedTime,map);
		
		player.movePlayer(fElapsedTime, map);
		
		
		
		
		ray.castAllRays(player, map);

		wall.renderWallProjection(this, player, ray,map);
		sprite.SpriteProjection(this, ray, player);
		
		
		
		map.renderMapGrid(this);           // little map
		player.renderMapPlayer(this);// player in the map
		sprite.mapSprites(this);
		ray.renderMapRays(this, player, wall.nTestRay );   // rays in the map
		saber.DrawSaber(this,fElapsedTime);
		powers.Update(this, player,map, sprite,fElapsedTime);

		//DrawLine( wall.nTestRay, 0, wall.nTestRay, ScreenHeight(), olc::MAGENTA );

		return true;
	}
};

int main()
{
	darkforce game;
	if (game.Construct(WINDOW_WIDTH, WINDOW_HEIGHT, 2, 2))
	{
		game.Start();
	}

	return 0;
}
