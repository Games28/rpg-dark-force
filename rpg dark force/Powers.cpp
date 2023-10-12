#include "Powers.h"
#include "ObjectManager.h"

void Powers::initSprite()
{
	indicatorsprite[0] = new olc::Sprite("newicon.png");
	indicatorsprite[1] = new olc::Sprite("newiconglow.png");
}

void Powers::TKmove(Object& object, Player& player, Map& map)
{
	
	float movex = object.x + player.movedifference.x;
	float movey = object.y + player.movedifference.y;

	

	if (!map.mapHasWallAt(movex, movey))
	{
		object.x += player.movedifference.x;
		object.y += player.movedifference.y;
	}
	
}

void Powers::TKstrafe(Object& object, Player& player)
{
	object.x += player.strafedifference.x;
	object.y += player.strafedifference.y;
}

void Powers::TKrotation(olc::PixelGameEngine* pge,Object& object, Player& player, Map& map)
{
	auto Deg2Rad = [=](float angle) {return angle / 180.0f * 3.14159f; };

	float differenceX = object.x - player.x;
	float differenceY = object.y - player.y;

	float distance = sqrtf(differenceX * differenceX + differenceY * differenceY);

	float angle_player_to_object = atan2f(differenceY, differenceX);

	float angle_difference = player.rotationdifference;

	float rotatex = object.x + distance * (cosf(angle_player_to_object + angle_difference) - cosf(angle_player_to_object));
	float rotatey = object.y + distance * (sinf(angle_player_to_object + angle_difference) - sinf(angle_player_to_object));

	if (!map.mapHasWallAt(rotatex, rotatey))
	{
		object.x += distance * (cosf(angle_player_to_object + angle_difference) - cosf(angle_player_to_object));
		object.y += distance * (sinf(angle_player_to_object + angle_difference) - sinf(angle_player_to_object));
	}
	
}

bool Powers::isinsight(Object& object, Player& player, float fov, float& angle2player)
{
	auto Deg2Rad = [=](float angle) {return angle / 180.0f * 3.14159f; };
	auto ModuloTwoPI = [=](float angle)
		{
			float a = angle;
			while (a < 0) a += 2.0f * 3.14159f;
			while (a >= 2.0f * 3.14159f) a -= 2.0f * 3.14159f;
			return a;
		};

	float tempx = object.x - player.x;
	float tempy = object.y - player.y;

	angle2player = ModuloTwoPI(atan2(tempx, tempy));
	float fAligneda = (2.0f * 3.14159f - player.rotationAngle) - 0.5f * 3.14159f;

	return abs(ModuloTwoPI(fAligneda + 3.14159f) - angle2player) < fov;
}

void Powers::TKthrow(Object& object, Map& map,float& deltatime)
{
	//new attempting with physics code inside object class
	//float throwstep = object.ThrowDirection * 2 * deltatime;
	//
	//Vec2 temp;
	//
	//Vec2 drag = Force::GenerateDragForce(object, 2.0f);
	//Vec2 push;
	//object.Horzphysicssetup(4.0f);
	//
	//push = Vec2(50, 50);
	//
	//object.AddHorzForces(push);
	//object.AddHorzForces(drag);
	//
	//
	//temp = object.HorzIntegrate(deltatime);
	//
	//if (!map.mapHasWallAt(temp.x, temp.y))
	//{
	//	object.x = temp.x;
	//	object.y = temp.y;
	//}

	//old attempt with separate physics class
	float throwstep = object.ThrowDirection * 2 * deltatime;

	Vec2 temp;
	object.physics.Horzphysicssetup( 8.0f);
	Vec2 drag = Force::GenerateDragForce(object, 0.02f);

	Vec2 push = Vec2(50 * PIXELS_PER_METER, 50 * PIXELS_PER_METER);
	object.physics.AddHorzForces(push);
	object.physics.AddHorzForces(drag);
	temp = object.physics.HorzIntegrate(object.rotationangle,deltatime);

	float newThrowX = object.x + cos(object.offset) * temp.x;
	float newThrowY = object.y + sin(object.offset) * temp.y;

	

	if (!map.mapHasWallAt(newThrowX, newThrowY))
	{
		object.x = newThrowX;
		object.y = newThrowY;
	}
}
