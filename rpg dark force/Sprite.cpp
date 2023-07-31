#include "Sprite.h"

void Sprite::initSpriteinfo()
{
	sprites[0] = { 640,630, 0, false ,100 };
	sprites[1] = { 660,690,1 ,false,100};
	sprites[2] = { 250,600, 1,false ,100 };
	sprites[3] = { 240,610, 2 ,false,200};
	sprites[4] = { 300,400, 2 ,false,200};
}

void Sprite::initsprites()
{
	spriteptr[0] = new olc::Sprite("probidle.png");
	spriteptr[1] = new olc::Sprite("r2d2ground.png");
	spriteptr[2] = new olc::Sprite("trooperT.png");


}

void Sprite::calculateBottomandTop(Player& player, float distance,float& SHeight,float& SWidth, int halfheight, float& ceiling, float& floor)
{
	int sliceHeight = ((TILE_SIZE / distance) * DIST_TO_PROJ_PLANE);
	ceiling = halfheight - (sliceHeight *  player.fPlayerH) * sliceHeight;
	floor = halfheight + (sliceHeight * player.fPlayerH);

}





olc::Pixel Sprite::newSelectedPixel(olc::PixelGameEngine* ptr, olc::Sprite* sprite,float size, float samplex, float sampley, float& diffangle)
{
	auto is_in_range = [=](float a, float low, float high) {
		return (low <= a && a < high);
	};

	// "bodge" angle in the range [ -PI, PI )
	
	
	olc::vf2d vOffset;
	if (is_in_range(diffangle, -0.75f * 3.14159265f, -0.25f * 3.14159265f))
     	 vOffset = { 1.0f, 0.0f }; else   // sprite from the left
		if (is_in_range(diffangle, -0.25f * 3.14159265f, +0.25f * 3.14159265f)) 
			vOffset = { 0.0f, 0.0f }; else   //                 back
			if (is_in_range(diffangle, +0.25f * 3.14159265f, +0.75f * 3.14159265f)) 
				vOffset = { 3.0f, 0.0f }; 
			else   //                 right
				vOffset = { 2.0f, 0.0f };        //                 front


	// the subsprites are 100 x 100 pixels
	olc::vf2d vSample = ((vOffset + olc::vf2d(samplex, sampley)) * size / olc::vf2d(float(sprite->width), float(sprite->height)));
	return sprite->Sample(vSample.x, vSample.y);
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
	sprite_t visibleSprites[NUM_SPRITES];
	int numVisibleSprites = 0;

	for (int i = 0; i < NUM_SPRITES; i++)
	{
		

		float angleSpritePlayer = atan2(sprites[i].y - player.y, sprites[i].x - player.x) - atan2(sin(player.rotationAngle), cos(player.rotationAngle));

		if (angleSpritePlayer > PI)
			angleSpritePlayer -= TWO_PI;
		if (angleSpritePlayer < -PI)
			angleSpritePlayer += TWO_PI;

		

		const float ESPSILON = 0.2f;

		const float EPSILON = 0.2f;
		if (angleSpritePlayer < (FOV_ANGLE / 2) + EPSILON) {
			sprites[i].visible = true;
			sprites[i].angle = angleSpritePlayer;
			
			sprites[i].distance = distanceBetweenPoints(sprites[i].x, sprites[i].y, player.x, player.y);
			visibleSprites[numVisibleSprites] = sprites[i];
			numVisibleSprites++;
		}
		else {
			sprites[i].visible = false;
		}
	}

	for (int i = 0; i < numVisibleSprites - 1; i++)
	{
		for (int j = i + 1; j < numVisibleSprites; j++)
		{
			if (visibleSprites[i].distance < visibleSprites[j].distance)
			{
				sprite_t temp = visibleSprites[i];
				visibleSprites[i] = visibleSprites[j];
				visibleSprites[j] = temp;
			}
		}
	}

	int nHorizonHeight = WINDOW_HEIGHT * player.fPlayerH + (int)player.lookupordown;





	for (int i = 0; i < numVisibleSprites; i++)
	{
		sprite_t sprite = visibleSprites[i];
		//new
		float fVecX = sprite.x - player.x;
		float fVecY = sprite.y - player.y;
		float distancefromplayer = sqrtf(fVecX * fVecX + fVecY * fVecY);
		float fPlayerA_rad = deg2rad(player.rotationAngle);
		float fEyeX = cosf(fPlayerA_rad);
		float fEyeY = sinf(fPlayerA_rad);
		float fObjectAngle = atan2f(fVecY, fVecX) - atan2f(fEyeY, fEyeX);
		if (fObjectAngle < -3.14159f)
			fObjectAngle += 2.0f * 3.14159f;

		if (fObjectAngle > 3.14159f)
			fObjectAngle -= 2.0f * 3.14159f;

		float fPlayerFOV_rad = deg2rad(60.0f);
		float fCompensatePlayerHeight = (player.fPlayerH - 0.5f) * 64;

		float  fObjHlveSliceHeight = float(WINDOW_HEIGHT / sprite.distance);
		float  spriteheight = (TILE_SIZE / sprite.distance) * DIST_TO_PROJ_PLANE;
		float  fObjHlveSliceHeightScld = float((WINDOW_HEIGHT * 1) / sprite.distance);

		float fObjCeilingNormalized = float(nHorizonHeight) - fObjHlveSliceHeight;
		float fObjCeilingScaled = float(nHorizonHeight) - sprite.distance;
		// and adapt all the scaling into the ceiling value
		float fScalingDifference = fObjCeilingNormalized - fObjCeilingScaled;
		float fObjCeiling = float(nHorizonHeight) - (spriteheight / 2) * 1.0f;
		float fObjFloor = float(nHorizonHeight) + (spriteheight / 2);

		fObjCeiling += fCompensatePlayerHeight * fObjHlveSliceHeight * 2.0f;
		fObjFloor += fCompensatePlayerHeight * fObjHlveSliceHeight * 2.0f;

		float fObjHeight = fObjFloor - fObjCeiling;
		float fObjAR = float(spriteptr[sprite.texture]->height) / float(spriteptr[sprite.texture]->width);
		float fObjWidth = fObjHeight / fObjAR;

		float fMidOfObj = (0.5f * (sprite.angle / (fPlayerFOV_rad / 2.0f)) + 0.5f) * float(WINDOW_WIDTH);


		
		// render the sprite
		for (int fx = 0; fx < (int)fObjWidth; fx++) {
			// get distance across the screen to render
			int nObjColumn = int(fMidOfObj + fx - (fObjWidth / 2.0f));
			// only render this column if it's on the screen
			if (nObjColumn >= 0 && nObjColumn < WINDOW_WIDTH) {
				for (int fy = 0; fy < (int)fObjHeight; fy++) {
					// calculate sample coordinates as a percentage of object width and height
					float fSampleX = fx / fObjWidth;
					float fSampleY = fy / fObjHeight;
					// sample the pixel and draw it
					if (fx > 0 && fx < WINDOW_WIDTH && fy > 0 && fy < WINDOW_HEIGHT)
					{
						olc::Pixel pSample;
						//new
						if (sprite.stationary)
						{
							pSample = spriteptr[sprite.texture]->Sample(fSampleX, fSampleY);
						}
						else
						{
							pSample = newSelectedPixel(PGEptr, spriteptr[sprite.texture],sprite.size, fSampleX, fSampleY, fObjectAngle);
						}
						
						float dist = rays.rays[nObjColumn].listinfo[0].distance;
						if (sprite.distance < dist)
						{
							if (pSample != olc::MAGENTA)
							{
								PGEptr->Draw(nObjColumn, fObjCeiling + fy, pSample);

							}
						}
					}
				}
			}
			
		}

	}
	
}

void Sprite::mapSprites(olc::PixelGameEngine* PGEptr)
{
	for (int i = 0; i < NUM_SPRITES; i++)
	{
		for (int i = 0; i < NUM_SPRITES; i++) {
			PGEptr->FillRect(
				sprites[i].x * MINIMAP_SCALE_FACTOR,
				sprites[i].y * MINIMAP_SCALE_FACTOR,
				2,
				2,
				(sprites[i].visible) ? 0xFF00FFFF : 0xFF444444
			);
		}
	}
}
