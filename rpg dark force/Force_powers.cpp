#include "Force_powers.h"

void Force_powers::initSprite()
{
	indicatorsprite[0] = new olc::Sprite("newicon.png");
	indicatorsprite[1] = new olc::Sprite( "newiconglow.png" );
}

void Force_powers::TKmove(object_t& sprite, Player& player)
{
	

	
	sprite.x += player.movedifference.x;
	sprite.y += player.movedifference.y;
}

void Force_powers::TKstrafe(object_t& sprite, Player& player)
{
	sprite.x += player.strafedifference.x;
	sprite.y += player.strafedifference.y;
}

void Force_powers::TKrotation(object_t& sprite, Player& player)
{
	auto Deg2Rad = [=](float angle) {return angle / 180.0f * 3.14159f; };

	float differenceX = sprite.x - player.x;
	float differenceY = sprite.y - player.y;

	float distance = sqrtf(differenceX * differenceX + differenceY * differenceY);

	float angle_player_to_object = atan2f(differenceY, differenceX);

	float angle_difference = player.rotationdifference;

	

	sprite.x += distance * (cosf(angle_player_to_object + angle_difference) - cosf(angle_player_to_object));
	sprite.y += distance * (sinf(angle_player_to_object + angle_difference) - sinf(angle_player_to_object));
}



bool Force_powers::isinsight(object_t& sprite, Player& player, float fov, float& angle2player)
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

void Force_powers::Update(olc::PixelGameEngine* PGEptr, Player& player,Map& map, Sprite& sprite, float deltatime)
{
	float fObjPlyA;
	olc::vi2d indicatorPos = { PGEptr->ScreenWidth() / 2, 30 };
	PGEptr->DrawSprite(indicatorPos, indicatorsprite[0]);
	

	if (!ispickedup)
	{
		
			for (auto & s : sprite.objects)
			{
				spr = &s;
				spr->inSight = isinsight(*spr, player, 10.0f * (3.14159f / 180.0f), fObjPlyA);
				
				
				
				if (spr->inSight)
				{
					

					PGEptr->DrawSprite(indicatorPos, indicatorsprite[1]);

					if (PGEptr->GetKey(olc::SPACE).bHeld)
					{
						
						spr->pickedup = true;
						ispickedup = true;
						break;
					}



				}

			}
		
		
		
	}
	else
	{
 		if (spr->pickedup)
		{
			spr->rotationangle = player.rotationAngle;
			PGEptr->DrawSprite(indicatorPos, indicatorsprite[1]);
			TKmove(*spr, player);
			TKstrafe(*spr, player);
			TKrotation(*spr, player);
			moveInput(PGEptr,*spr, sprite,map,deltatime);
		}
		if (PGEptr->GetKey(olc::SPACE).bReleased)
		{

			


			spr->pickedup = false;
			ispickedup = false;
			spr = nullptr;
		}
		
		
	}
	
		
	
	

}

void Force_powers::moveInput(olc::PixelGameEngine* pge, object_t& sprite,Sprite& spr, Map& map, float dt)
{
	
			if (pge->GetKey(olc::I).bHeld)
			{
				sprite.movedirection = +1;
			}

			if (pge->GetKey(olc::K).bHeld)
			{
				sprite.movedirection = -1;
			}
			if (pge->GetKey(olc::J).bHeld)
			{
				sprite.turndirection = -1;
			}
			if (pge->GetKey(olc::L).bHeld)
			{
				sprite.turndirection = +1;
			}

			if (pge->GetKey(olc::I).bReleased)
			{
				sprite.movedirection = 0;
			}

			if (pge->GetKey(olc::K).bReleased)
			{
				sprite.movedirection = 0;
			}
			if (pge->GetKey(olc::J).bReleased)
			{
				sprite.turndirection = 0;
			}
			if (pge->GetKey(olc::L).bReleased)
			{
				sprite.turndirection = 0;
			}
		
			spr.moveObject(sprite,map, dt);
}
