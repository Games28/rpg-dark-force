#include "Sprite.h"

void Sprite::initSpriteinfo()
{

	object_t obj;
	obj.x = 300;
	obj.y = 400;
	obj.texture = 2;
	obj.scale = 0.5f;
	obj.stationary = false;
	obj.size = { 60,125 };
	obj.liftup = 0;
	obj.offset = 0;

	object_t obj1;
	obj1.x = 200;
	obj1.y = 400;
	obj1.texture = 2;
	obj1.scale = 0.5f;
	obj1.stationary = false;
	obj1.size = { 60,125 };
	obj1.liftup = 0;
	obj1.offset = 0;

	objects.push_back(obj);
	objects.push_back(obj1);
	

	

	

	
	
}

void Sprite::initsprites()
{
	spriteptr[0] = new olc::Sprite("probidle.png");
	spriteptr[1] = new olc::Sprite("r2d2ground.png");
	spriteptr[2] = new olc::Sprite("trooperT2.png");


}



void Sprite::moveObject(object_t& obj,Player& player,Map& map,float deltatime)
{

	auto normalizeangle = [=](float& angle)
	{
			angle = remainder(angle, TWO_PI);
			if (angle < 0) {
				angle = TWO_PI + angle;
			}
	};

	

		

		float movestep = obj.movedirection * obj.movespeed * deltatime;

		float newObjectX = obj.x + cos(player.rotationAngle) * movestep;
		float newObjectY = obj.y + sin(player.rotationAngle) * movestep;

		if (!map.mapHasWallAt(newObjectX, newObjectY))
		{
			obj.x = newObjectX;
			obj.y = newObjectY;
		
		}

	
}





olc::Pixel Sprite::newSelectedPixel(olc::PixelGameEngine* ptr,object_t* obj, olc::Sprite* sprite,olc::vf2d size, float samplex, float sampley, float Angle)
{
	auto is_in_range = [=](float a, float low, float high) {
		return (low <= a && a < high);
	};
	
	// "bodge" angle in the range [ -PI, PI )

	olc::vf2d TileSize = { 60,125 };
	olc::vf2d vOffset;
	if (is_in_range(Angle, -0.75f * 3.14159265f, -0.25f * 3.14159265f))
     	 vOffset = { 1.0f, 0.0f }; else   // sprite from the left
		if (is_in_range(Angle, -0.25f * 3.14159265f, +0.25f * 3.14159265f)) 
			vOffset = { 0.0f, 0.0f }; else   //                 back
			if (is_in_range(Angle, +0.25f * 3.14159265f, +0.75f * 3.14159265f)) 
				vOffset = { 3.0f, 0.0f }; 
			else   //                 right
				vOffset = { 2.0f, 0.0f };        //                 front
	
	
	
	
	// the subsprites are 100 x 100 pixels
	olc::vf2d vSample = ((vOffset + olc::vf2d(samplex, sampley)) * size) / olc::vf2d(float(sprite->width), float(sprite->height));


	

	//test
	olc::Pixel p = sprite->Sample(vSample.x, vSample.y);



	return p;
}


void Sprite::SpriteProjection(olc::PixelGameEngine* PGEptr, Raycast& rays, Player& player)
{
	int halfscreenheight = WINDOW_HEIGHT * player.fPlayerH;

	auto normalizeAngle = [=](float* angle)
		{
			*angle = remainder(*angle, TWO_PI);
			if (*angle < 0) {
				*angle = TWO_PI + *angle;
			}
		};

	auto distanceBetweenPoints = [=](float x1, float y1, float x2, float y2)
		{
			return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
		};
	
	

	for (auto & obj : objects)
	{
		obj.visible = false;

		float angleSpritePlayer = atan2(obj.y - player.y, obj.x - player.x) - atan2(sin(player.rotationAngle), cos(player.rotationAngle));

		if (angleSpritePlayer > PI)
			angleSpritePlayer -= TWO_PI;
		if (angleSpritePlayer < -PI)
			angleSpritePlayer += TWO_PI;





		const float ESPSILON = 0.2f;

		const float EPSILON = 0.2f;
		if (angleSpritePlayer < (FOV_ANGLE / 2) + EPSILON) {
			obj.visible = true;
			obj.angle = angleSpritePlayer;

			obj.distance = distanceBetweenPoints(obj.x, obj.y, player.x, player.y);
			
			
		}
		else {
			obj.visible = false;
		}
	}

	

	objects.sort([=](const object_t& a, const object_t& b)
		{
			return a.distance > b.distance;
		}
	);

	int nHorizonHeight = WINDOW_HEIGHT * player.fPlayerH + (int)player.lookupordown;





	for (auto & obj : objects)
	{

		if (obj.visible)
		{
			//object_t sprite = visibleSprites[i];

			float fVecX = obj.x - player.x;
			float fVecY = obj.y - player.y;
			float distancefromplayer = sqrtf(fVecX * fVecX + fVecY * fVecY);

			


			float fPlayerA_rad = deg2rad(player.rotationAngle);
			float fEyeX = cosf(fPlayerA_rad);
			float fEyeY = sinf(fPlayerA_rad);
			obj.rotationangle = atan2f(fEyeY, fEyeX) - atan2f(fVecY, fVecX);


			if (PGEptr->GetKey(olc::F9).bHeld)
			{
				obj.offset += 1.0f;
			}
			if (PGEptr->GetKey(olc::F8).bHeld)
			{
				obj.offset -= 1.0f;
			}

			if (obj.offset < -3.14159f)
				obj.offset += 2.0f * 3.14159f;

			if (obj.offset > 3.14159f)
				obj.offset -= 2.0f * 3.14159f;

			obj.rotationangle += obj.offset;

			if (obj.rotationangle < -3.14159f)
				obj.rotationangle += 2.0f * 3.14159f;

			if (obj.rotationangle > 3.14159f)
				obj.rotationangle -= 2.0f * 3.14159f;


			//fObjectAngle += sprite.rotationangle;

			float fPlayerFOV_rad = deg2rad(60.0f);
			float fCompensatePlayerHeight = (player.fPlayerH - 0.5f) * 64;

			float  fObjHlveSliceHeight = float(WINDOW_HEIGHT / obj.distance);
			float  spriteheight = (TILE_SIZE / obj.distance) * DIST_TO_PROJ_PLANE;
			float  fObjHlveSliceHeightScld = float((WINDOW_HEIGHT * 0.5f) / obj.distance);

			float fObjCeilingNormalized = float(nHorizonHeight) - fObjHlveSliceHeight;
			float fObjCeilingScaled = float(nHorizonHeight) - obj.distance;
			// and adapt all the scaling into the ceiling value
			float fScalingDifference = fObjCeilingNormalized - fObjCeilingScaled;
			float fObjCeiling = float(obj.liftup + nHorizonHeight) - (spriteheight / 2) * obj.scale;
			float fObjFloor = float(obj.liftup + nHorizonHeight) + (spriteheight / 2);

			fObjCeiling += fCompensatePlayerHeight * fObjHlveSliceHeight * 2.0f;
			fObjFloor += fCompensatePlayerHeight * fObjHlveSliceHeight * 2.0f;

			float fObjHeight = fObjFloor - fObjCeiling;
			float fObjAR = float(spriteptr[obj.texture]->width) / float(spriteptr[obj.texture]->height);
			float fObjWidth = fObjHeight / fObjAR;

			float fMidOfObj = (0.5f * (obj.angle / (fPlayerFOV_rad / 2.0f)) + 0.5f) * float(WINDOW_WIDTH);



			PGEptr->DrawString(200, 10, "objectangle " + std::to_string(obj.offset));
			PGEptr->DrawString(200, 20, "sprite.angle " + std::to_string(obj.angle));



			// render the sprite
			for (float fx = 0.0f; fx < (int)fObjWidth; fx++) {
				// get distance across the screen to render
				int nObjColumn = int(fMidOfObj + fx - (fObjWidth / 2.0f));
				// only render this column if it's on the screen
				if (nObjColumn >= 0 && nObjColumn < WINDOW_WIDTH) {
					for (float fy = 0.0f; fy < (int)fObjHeight; fy++) {
						// calculate sample coordinates as a percentage of object width and height
						float fSampleX = fx / fObjWidth;
						float fSampleY = fy / fObjHeight;
						// sample the pixel and draw it
						//if (fx > 0 && fx < WINDOW_WIDTH && fy > 0 && fy < WINDOW_HEIGHT)
						{
							olc::Pixel pSample;
							//new
							if (obj.stationary)
							{
								pSample = spriteptr[obj.texture]->Sample(fSampleX, fSampleY);
							}
							else
							{
								pSample = newSelectedPixel(PGEptr, &obj, spriteptr[obj.texture], obj.size, fSampleX, fSampleY, obj.rotationangle);
							}

							float dist = rays.rays[nObjColumn].listinfo[0].distance;
							if (obj.distance < dist)
							{
								if (pSample != olc::MAGENTA && rays.Depthbuffer[nObjColumn] >= obj.distance)
								{
									PGEptr->Draw(nObjColumn, fObjCeiling + fy, pSample);
									rays.Depthbuffer[nObjColumn] = obj.distance;

								}
							}
						}
					}
				}

			}
		}
	}
}

void Sprite::mapSprites(olc::PixelGameEngine* PGEptr,Sprite& sprite)
{

	for (auto & obj : objects) {
			
		olc::Pixel p;
		if (obj.visible)
		{
			p = olc::WHITE;
		}
		else
		{
			p = olc::GREY;
		}
			PGEptr->FillRect(
				obj.x * MINIMAP_SCALE_FACTOR,
				obj.y * MINIMAP_SCALE_FACTOR,
				2,
				2,
				p
			);
		}
	

	
}
