#include "Force_powers.h"

void Force_powers::initSprite()
{
	indicatorsprite[0] = new olc::Sprite("newicon.png");
	indicatorsprite[1] = new olc::Sprite( "newiconglow.png" );
}

void Force_powers::TKmove(sprite_t& sprite, Player& player)
{
	float differencex = player.movementafter.x - player.movementbefore.x;
	float differencey = player.movementafter.y - player.movementbefore.y;

	sprite.x += differencex;
	sprite.y += differencey;
}

void Force_powers::TKrotation(sprite_t& sprite, Player& player)
{
	auto Deg2Rad = [=](float angle) {return angle / 180.0f * 3.14159f; };

	float differenceX = sprite.x - player.x;
	float differenceY = sprite.y - player.y;

	float distance = sqrtf(differenceX * differenceX + differenceY * differenceY);

	float angle_player_to_object = atan2f(differenceY, differenceX);

	float angle_difference = player.rotateafter - player.rotatebefore;

	float angledifRad = Deg2Rad(angle_difference);

	sprite.x = distance * (cosf(angle_player_to_object + angledifRad) - cosf(angle_player_to_object));
	sprite.y = distance * (sinf(angle_player_to_object + angledifRad) - sinf(angle_player_to_object));
}



bool Force_powers::isinsight(sprite_t& sprite, Player& player, float fov, float& angle2player)
{
	auto Deg2Rad = [=](float angle) {return angle / 180.0f * 3.14159f; };
	auto ModuloTwoPI = [=](float angle)
	{
		float a = angle;
		while (a < 0) a += 2.0f * 3.14159f;
		while (a >= 2.0f * 3.14159f) a -= 2.0f * 3.14159f;
		return a;
	};

	float tempx = sprite.x - player.x;
	float tempy = sprite.y - player.y;

	angle2player = ModuloTwoPI(atan2(tempx, tempy));
	float fAligneda = (2.0f * 3.14159f - player.rotationAngle) - 0.5f * 3.14159f;

	return abs(ModuloTwoPI(fAligneda + 3.14159f) - angle2player) < fov;
}

void Force_powers::Update(olc::PixelGameEngine* PGEptr, Player& player, Sprite& sprite)
{
	float fObjPlyA;
	olc::vi2d indicatorPos = { PGEptr->ScreenWidth() / 2, 30 };
	PGEptr->DrawSprite(indicatorPos, indicatorsprite[0]);
	sprite_t spr;
	for (auto S : sprite.sprites)
	{
		S.inSight = isinsight(S, player, 10.0f * (3.14159f / 180.0f), fObjPlyA);
		
		
		if (S.inSight)
		{
			spr = S;
			
				PGEptr->DrawSprite(indicatorPos, indicatorsprite[1]);
			
				if (PGEptr->GetKey(olc::SPACE).bHeld)
				{
					S.pickedup = true;
					
				}
				if (S.pickedup)
				{
  					TKmove(S, player);
					TKrotation(S, player);
				}
		}
		
	}

	

}
