#include "Force_powers.h"

void Force_powers::initSprite()
{
	indicatorsprite[0] = new olc::Sprite("newicon.png");
	indicatorsprite[1] = new olc::Sprite( "newiconglow.png" );
}

void Force_powers::TKmove(object_t& sprite, Player& player, Map& map)
{
    float movex = sprite.x + player.movedifference.x;
	float movey = sprite.y + player.movedifference.y;

	if (!map.mapHasWallAt(movex, movey))
	{
		sprite.x += player.movedifference.x;
		sprite.y += player.movedifference.y;
	}
	
}

void Force_powers::TKstrafe(object_t& sprite, Player& player)
{
	sprite.x += player.strafedifference.x;
	sprite.y += player.strafedifference.y;
}

void Force_powers::TKrotation(object_t& sprite, Player& player, Map& map)
{
	auto Deg2Rad = [=](float angle) {return angle / 180.0f * 3.14159f; };

	float differenceX = sprite.x - player.x;
	float differenceY = sprite.y - player.y;

	float distance = sqrtf(differenceX * differenceX + differenceY * differenceY);

	float angle_player_to_object = atan2f(differenceY, differenceX);

	float angle_difference = player.rotationdifference;

	float rotatex = sprite.x + distance * (cosf(angle_player_to_object + angle_difference) - cosf(angle_player_to_object));
	float rotatey = sprite.y + distance * (sinf(angle_player_to_object + angle_difference) - sinf(angle_player_to_object));
	
	if (!map.mapHasWallAt(rotatex, rotatey))
	{
		sprite.x += distance * (cosf(angle_player_to_object + angle_difference) - cosf(angle_player_to_object));
		sprite.y += distance * (sinf(angle_player_to_object + angle_difference) - sinf(angle_player_to_object));
	}

	
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

void Force_powers::TKUpdate(olc::PixelGameEngine* PGEptr, Player& player, Map& map, Sprite& sprite, float deltatime)
{
	float fObjPlyA;
	olc::vi2d indicatorPos = { PGEptr->ScreenWidth() / 2, 30 };
	PGEptr->DrawSprite(indicatorPos, indicatorsprite[0]);


	if (!ispickedup)
	{

		for (int i = 0; i < NUM_SPRITES; i++)
		{
			spr = &sprite.objects[i];
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
			moveInput(PGEptr, player, *spr, sprite, map, deltatime);
			PGEptr->DrawSprite(indicatorPos, indicatorsprite[1]);
			TKmove(*spr, player, map);
			TKstrafe(*spr, player);
			TKrotation(*spr, player, map);
			if (spr->islifting)
			{
				spr->liftup -= 5.0f;
			}

		}
		else
		{
			
		}


		if (!PGEptr->GetKey(olc::SPACE).bHeld)
		{
			
			spr->islifting = false;
			spr->pickedup = false;
			ispickedup = false;
			spr = nullptr;
			
		}



	}

	for (int i = 0; i < NUM_SPRITES; i++)
	{
		
		if (!sprite.objects[i].islifting)
		{
			//sprite.objects[i].liftup += 5.0f;

			
			particle.physicssetup(sprite.objects[i].liftup);
			sprite.objects[i].liftup = particle.physicobjectlift(deltatime);
		}
	}

}

void Force_powers::moveInput(olc::PixelGameEngine* pge,Player& player, object_t& sprite,Sprite& spr, Map& map, float dt)
{
	//movement input
			if (pge->GetKey(olc::I).bHeld) sprite.movedirection = +1;
			if (pge->GetKey(olc::K).bHeld) sprite.movedirection = -1;
		    if (pge->GetKey(olc::J).bHeld) sprite.rotationangle += -0.5;
		    if (pge->GetKey(olc::L).bHeld) sprite.rotationangle += 0.5;
			
			if (pge->GetKey(olc::I).bReleased) sprite.movedirection = 0;
			if (pge->GetKey(olc::K).bReleased) sprite.movedirection = 0;
		    //if (pge->GetKey(olc::J).bReleased) sprite.turndirection = 0;
		    //if (pge->GetKey(olc::L).bReleased) sprite.turndirection = 0;
			
		
			//lift input
			if (pge->GetKey(olc::U).bHeld) sprite.islifting = true;
			if (pge->GetKey(olc::U).bReleased) sprite.islifting = false;
			

			spr.moveObject(sprite,player,map, dt);
			
			
}

void Force_powers::physicsUpdate(object_t& sprite, float dt)
{
	
	
		particle.physicssetup(sprite.liftup);
		particle.physicobjectlift(dt);
	

}
