#include "Sprite.h"

void Sprite::initSpriteinfo()
{
	//objects[0] = { 640,630, 0, false ,100 };
	//objects[1] = { 660,690,1 ,false,100};
	//objects[2] = { 250,600, 1,false ,100 };
	//objects[3] = { 240,610, 2 ,false,200};
	objects[0] = { 300,400, 2 , 0.5f,false ,{60,125} };
	//objects[1] = { 250,600,2,0.5f,false, {60,125 } };
	objects[0].liftup = 0;
	objects[0].offset = 0;
	//objects[1].liftup = 0;
	
	

	

	

	
	
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
	object_t visibleSprites[NUM_SPRITES];
	int numVisibleSprites = 0;

	for (int i = 0; i < NUM_SPRITES; i++)
	{


		float angleSpritePlayer = atan2(objects[i].y - player.y, objects[i].x - player.x) - atan2(sin(player.rotationAngle), cos(player.rotationAngle));

		if (angleSpritePlayer > PI)
			angleSpritePlayer -= TWO_PI;
		if (angleSpritePlayer < -PI)
			angleSpritePlayer += TWO_PI;





		const float ESPSILON = 0.2f;

		const float EPSILON = 0.2f;
		if (angleSpritePlayer < (FOV_ANGLE / 2) + EPSILON) {
			objects[i].visible = true;
			objects[i].angle = angleSpritePlayer;

			objects[i].distance = distanceBetweenPoints(objects[i].x, objects[i].y, player.x, player.y);
			visibleSprites[numVisibleSprites] = objects[i];
			numVisibleSprites++;
		}
		else {
			objects[i].visible = false;
		}
	}

	for (int i = 0; i < numVisibleSprites - 1; i++)
	{
		for (int j = i + 1; j < numVisibleSprites; j++)
		{
			if (visibleSprites[i].distance < visibleSprites[j].distance)
			{
				object_t temp = visibleSprites[i];
				visibleSprites[i] = visibleSprites[j];
				visibleSprites[j] = temp;
			}
		}
	}

	int nHorizonHeight = WINDOW_HEIGHT * player.fPlayerH + (int)player.lookupordown;





	for (int i = 0; i < numVisibleSprites; i++)
	{
		//object_t sprite = visibleSprites[i];

		float fVecX = visibleSprites[i].x - player.x;
		float fVecY = visibleSprites[i].y - player.y;
		float distancefromplayer = sqrtf(fVecX * fVecX + fVecY * fVecY);

		
		if (PGEptr->GetKey(olc::F9).bHeld)
		{
			visibleSprites[i].offset += 5.0f;
		}

		float fPlayerA_rad = deg2rad(visibleSprites[i].offset);
		float fEyeX = cosf(fPlayerA_rad);
		float fEyeY = sinf(fPlayerA_rad);
		visibleSprites[i].rotationangle =  atan2f(fEyeY, fEyeX) - atan2f(fVecY, fVecX);

		
		

		

		if (visibleSprites[i].rotationangle < -3.14159f)
			visibleSprites[i].rotationangle += 2.0f * 3.14159f;

		if (visibleSprites[i].rotationangle > 3.14159f)
			visibleSprites[i].rotationangle -= 2.0f * 3.14159f;


		//fObjectAngle += sprite.rotationangle;

		float fPlayerFOV_rad = deg2rad(60.0f);
		float fCompensatePlayerHeight = (player.fPlayerH - 0.5f) * 64;

		float  fObjHlveSliceHeight = float(WINDOW_HEIGHT / visibleSprites[i].distance);
		float  spriteheight = (TILE_SIZE / visibleSprites[i].distance) * DIST_TO_PROJ_PLANE;
		float  fObjHlveSliceHeightScld = float((WINDOW_HEIGHT * 0.5f) / visibleSprites[i].distance);

		float fObjCeilingNormalized = float(nHorizonHeight) - fObjHlveSliceHeight;
		float fObjCeilingScaled = float(nHorizonHeight) - visibleSprites[i].distance;
		// and adapt all the scaling into the ceiling value
		float fScalingDifference = fObjCeilingNormalized - fObjCeilingScaled;
		float fObjCeiling = float(visibleSprites[i].liftup + nHorizonHeight) - (spriteheight / 2) * visibleSprites[i].scale;
		float fObjFloor = float(visibleSprites[i].liftup + nHorizonHeight) + (spriteheight / 2);

		fObjCeiling += fCompensatePlayerHeight * fObjHlveSliceHeight * 2.0f;
		fObjFloor += fCompensatePlayerHeight * fObjHlveSliceHeight * 2.0f;

		float fObjHeight = fObjFloor - fObjCeiling;
		float fObjAR = float(spriteptr[visibleSprites[i].texture]->width) / float(spriteptr[visibleSprites[i].texture]->height);
		float fObjWidth = fObjHeight / fObjAR;

		float fMidOfObj = (0.5f * (visibleSprites[i].angle / (fPlayerFOV_rad / 2.0f)) + 0.5f) * float(WINDOW_WIDTH);

		

		PGEptr->DrawString(200, 10, "objectangle " + std::to_string(visibleSprites[i].offset));




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
						if (visibleSprites[i].stationary)
						{
							pSample = spriteptr[visibleSprites[i].texture]->Sample(fSampleX, fSampleY);
						}
						else
						{
							pSample = newSelectedPixel(PGEptr, &visibleSprites[i], spriteptr[visibleSprites[i].texture], visibleSprites[i].size, fSampleX, fSampleY, visibleSprites[i].rotationangle);
						}

						float dist = rays.rays[nObjColumn].listinfo[0].distance;
						if (visibleSprites[i].distance < dist)
						{
							if (pSample != olc::MAGENTA && rays.Depthbuffer[nObjColumn] >= visibleSprites[i].distance)
							{
								PGEptr->Draw(nObjColumn, fObjCeiling + fy, pSample);
								rays.Depthbuffer[nObjColumn] = visibleSprites[i].distance;

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

	for (int i = 0; i < NUM_SPRITES; i++) {
			
			PGEptr->FillRect(
				objects[i].x * MINIMAP_SCALE_FACTOR,
				objects[i].y * MINIMAP_SCALE_FACTOR,
				2,
				2,
				olc::WHITE
			);
		}
	

	
}
