#include "Sprite.h"

void Sprite::initSpriteinfo()
{
	sprites[0] = {640,630, 1};
	sprites[1] = { 660,690,1  };
	sprites[2] = { 250,600, 1  };
	sprites[3] = { 240,610, 2 };
	sprites[4] = { 300,400, 2 };
}

void Sprite::initsprites()
{
	spriteptr[0] = new olc::Sprite("probidletest.png");
	spriteptr[1] = new olc::Sprite("r2idletest.png");
	spriteptr[2] = new olc::Sprite("trooper.png");


}

void Sprite::calculateBottomandTop(Player& player, float distance,float& SHeight,float& SWidth, int halfheight, float& ceiling, float& floor)
{
	int sliceHeight = ((TILE_SIZE / distance) * DIST_TO_PROJ_PLANE);
	ceiling = halfheight - (sliceHeight *  player.fPlayerH) * sliceHeight;
	floor = halfheight + (sliceHeight * player.fPlayerH);

}

void Sprite::SpriteProjection(olc::PixelGameEngine* PGEptr, Raycast& rays, Player& player)
{
	
	
	
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

		float angleSpritePlayer = player.rotationAngle - atan2(sprites[i].y - player.y, sprites[i].x - player.x);

		if (angleSpritePlayer > PI)
			angleSpritePlayer -= TWO_PI;
		if (angleSpritePlayer < -PI)
			angleSpritePlayer += TWO_PI;

		angleSpritePlayer = fabs(angleSpritePlayer);

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

	

	for (int i = 0; i < numVisibleSprites; i++)
	{
		sprite_t sprite = visibleSprites[i];

		float prepDistance = sprite.distance * cos(sprite.angle);
		
		float spriteHeight = (TILE_SIZE / prepDistance) * DIST_TO_PROJ_PLANE;
		
		float spriteWidth = spriteHeight;
		

		float spriteTopY = (WINDOW_HEIGHT / 2)-(spriteHeight / 2);
		spriteTopY = (spriteTopY < 0) ? 0 : spriteTopY;
		
		float spriteBottomY = (WINDOW_HEIGHT / 2) + (spriteHeight / 2);
		spriteBottomY = (spriteBottomY > WINDOW_HEIGHT) ? WINDOW_HEIGHT : spriteBottomY;
		
		if (player.lookvert)
		{
			vertlook = player.lookupordown;
		
		}
		if(player.movevert)
		{
			vertlook = -player.lookupordown;
		}
		
		spriteTopY += vertlook;
		spriteBottomY += vertlook;
		
		
		
		float spriteAngle = atan2(sprite.y - player.y, sprite.x - player.x) - player.rotationAngle;
		float spriteScreenPosX = tan(spriteAngle) * DIST_TO_PROJ_PLANE;

		float spriteLeftX = (WINDOW_WIDTH / 2) + spriteScreenPosX - spriteWidth / 2;
		float spriteRightX = spriteLeftX + spriteWidth;

		int textureWidth = spriteptr[sprite.texture]->width;
		int textureHeight = spriteptr[sprite.texture]->height;
	
		for (int x = spriteLeftX; x < spriteRightX; x++)
		{

			float texelWidth = (textureWidth / spriteWidth);
			int textureOffSetX = (x - spriteLeftX) * texelWidth;
			
			for (int y = spriteTopY; y < spriteBottomY; y++)
			{
				
				if (player.lookvert)
				{
					vertposition = -player.lookupordown;
				}
				if (player.movevert)
				{
					vertposition = player.lookupordown;
				}
				
					int distanceFromTop = (y + vertposition) + (spriteHeight / 2) - (WINDOW_HEIGHT / 2) ;
					int textureOffSetY = distanceFromTop * (textureHeight / spriteHeight);
			
				
		
				
					
				
				

				if (x > 0 && x < WINDOW_WIDTH && y > 0 && y < WINDOW_HEIGHT)
				{
					olc::Pixel p = spriteptr[sprite.texture]->GetPixel(textureOffSetX, textureOffSetY);
					if (sprite.distance < rays.rays[x].listinfo[0].distance)
					{
						if (p != olc::MAGENTA)
						{
							PGEptr->Draw(x, y, p);
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



/*josephe inspired sprite rendering code 

int halfScreenWidth = WINDOW_WIDTH / 2;
	int halfScreenHeight = WINDOW_HEIGHT * player.fPlayerH + (int)player.lookupordown;

	for (int i = 0; i < numVisibleSprites; i++)
	{
		sprite_t sprite = visibleSprites[i];
		float fCompensatePlayerHeight = player.fPlayerH - 0.5f;
		float fObjectHiveSliceHeight = float(WINDOW_HEIGHT / sprite.distance);
		float fObjectHiveSliceHeightScaled = float((WINDOW_HEIGHT * 1) / sprite.distance);

		//not picked up
		float fObjectceilnormialized = float(halfScreenHeight) - fObjectHiveSliceHeight;
		float fObjectCeilingscaled = float(halfScreenHeight) - fObjectHiveSliceHeightScaled;
		float fObjectFLoor = float(halfScreenHeight) + fObjectHiveSliceHeight;

		float fScaledifference = fObjectceilnormialized - fObjectCeilingscaled;
		float fObjectceiling = fObjectceilnormialized - 2 * fScaledifference;

		float fObjectHeight = fObjectFLoor - fObjectceiling;
		float fObjectAspectRatio = float(spriteptr[sprite.texture]->height) / float(spriteptr[sprite.texture]->width);
		float fObjectWidth = fObjectHeight / fObjectAspectRatio;
		float fMiddleofObject = (0.5f * (sprite.angle / (player.rotationAngle * PI / 180.0f) / 2.0f) + 0.50f) * float(WINDOW_WIDTH);
		for (float fx = 0.0f; fx < fObjectWidth; fx++)
		{
			int nObjColumn = int(fMiddleofObject + fx - (fObjectWidth / 2.0f));

			if (nObjColumn >= 0 && nObjColumn < WINDOW_WIDTH)
			{
				for (float fy = 0.0f; fy < fObjectHeight; fy++)
				{
					float fSampleX = fx / fObjectWidth;
					float fSampleY = fy / fObjectHeight;

					olc::Pixel p = spriteptr[sprite.texture]->Sample(fSampleX, fSampleY);

					if (p != olc::MAGENTA)
					{
						PGEptr->Draw(nObjColumn, fObjectceiling + fy, p);
					}

				}
			}
		}


	}*/