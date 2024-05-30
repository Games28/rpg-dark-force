#include "Wall.h"

void Wall::wallTextures()
{
    //std::string sPath = "image/";
	sprites[0] = olc::Sprite("scenery/sand1.png");
	sprites[1] = olc::Sprite("scenery/stonewall.png");
	sprites[2] = olc::Sprite("scenery/Tatooinedoor1.png");
	sprites[3] = olc::Sprite("scenery/Tatooinedoor2.png");
	sprites[4] = olc::Sprite("scenery/tatooinewindow2.png");
	sprites[5] = olc::Sprite("scenery/Tatooinehousewall.png");
	
	

	std::cout << "All textures loaded." << std::endl;
}

void Wall::changeColorIntensity(olc::Pixel& p, float factor)
{
    // Joseph21 - assumed implementation
    p *= factor;
}

void Wall::calculateBottomAndTop(float wallDistance, int halfheight, float wallheight, int& wallceil, int& wallfloor, Player &player)
{
	int nsliceHeight = ((TILE_SIZE / wallDistance) * DIST_TO_PROJ_PLANE);
	wallceil  = halfheight - (float(nsliceHeight) * (1.0f - player.fPlayerH)) - (wallheight - 1) * nsliceHeight;
	wallfloor = halfheight + (float(nsliceHeight) *  player.fPlayerH );
}

olc::Pixel Wall::SelectSceneryPixel(int textureid, int samplex, int sampley, float distance, Side side)
{
	olc::Pixel p;

	int32_t isamplex = samplex;
	int32_t isampley = sampley;

	switch (side)
	{
	case Side::Top:
	{
		p = sprites[textureid].GetPixel(isamplex, isampley);
	}break;

	case Side::Roof:
	{
		p = sprites[textureid].GetPixel(isamplex, isampley);
	}break;

	case Side::Bottom:
	{
		p = sprites[textureid].GetPixel(isamplex, isampley);
		//float fdistance = ((3.0f / distance) * 100.0f);
		//
		//if (fdistance >= 1.0f) fdistance = 1.0f;
		//
		//
		//
		//p.r = uint8_t(float(p.r) * fdistance);
		//p.g = uint8_t(float(p.g) * fdistance);
		//p.b = uint8_t(float(p.b) * fdistance);
	}break;

	case Side::WalL:
	{
		p = sprites[textureid].GetPixel(isamplex, isampley);

		float brightness = 3.0;
		float scale = 0.0f;
		if (distance >= 10) scale = 10.0f * brightness;
		if (distance >= 100) scale = 100.0f * brightness;
		float fdistance = ((1.0 / distance) * scale);
		
		if (fdistance >= 1.0f) fdistance = 1.0f;
		


		p.r = uint8_t(float(p.r) * fdistance);
		p.g = uint8_t(float(p.g) * fdistance);
		p.b = uint8_t(float(p.b) * fdistance);
		
	}break;

	case Default:
	{
		std::cout << "error with texture" << std::endl;
	}break;
	}


	return p;
}



void Wall::renderWallProjection(olc::PixelGameEngine* PGEptr, Player& player, Raycast& rays, Map& map)
{

	int halfscreenwidth  = WINDOW_WIDTH / 2;
	int nHorizonHeight = WINDOW_HEIGHT * player.fPlayerH + (int)player.lookupordown;
	float anglestep = 60 / float(WINDOW_WIDTH);
	
	for (int x = 0; x < NUM_RAYS; x++) {     // iterate over all slices of the screen from left to right

        // work out angle from player perspective belonging to this slice
		float fViewangle = float(x - halfscreenwidth) * anglestep;

		int wallTopY, wallBottomY, nWallCeil, nWallCeil2, nWallFloor;
		int colheight, coordX, coordY;
		float Fcolheight, fDistnace;
		int below1 = 0;
		int theTexture;
		std::vector<int> textures;
		// calculated corrected distance as well as bottom and top of the wall projection - per hitpoint
		for (int i = 0; i < (int)rays.rays[x].listinfo.size(); i++)
		{
			rays.rays[x].listinfo[i].distance *= cos(fViewangle * PI / 180.0f);
			calculateBottomAndTop(rays.rays[x].listinfo[i].distance, nHorizonHeight, rays.rays[x].listinfo[i].FHeight, rays.rays[x].listinfo[i].ceil_front, rays.rays[x].listinfo[i].bottom_front, player);
		}

		for (int i = 0; i < (int)rays.rays[x].listinfo.size(); i++)
		{
			if (i == (int)rays.rays[x].listinfo.size() - 1)
			{
				rays.rays[x].listinfo[i].ceil_back = rays.rays[x].listinfo[i].ceil_front;
			}
			else
			{
				int nDummy;
				calculateBottomAndTop(rays.rays[x].listinfo[i + 1].distance, nHorizonHeight, rays.rays[x].listinfo[i].FHeight, rays.rays[x].listinfo[i].ceil_back, nDummy, player);
			}
		}

		// if there's at least one hitpoint ...
		if (rays.rays[x].listinfo.size() > 0) {

            // ... set the working variables using the first hitpoint ...
            Fcolheight = rays.rays[x].listinfo[0].FHeight;
            nWallCeil = rays.rays[x].listinfo[0].ceil_front;
            nWallCeil2 = rays.rays[x].listinfo[0].ceil_back;
            nWallFloor = rays.rays[x].listinfo[0].bottom_front;
			coordX = int(rays.rays[x].listinfo[0].wallHitX);
			coordY = int(rays.rays[x].listinfo[0].wallHitY);
			fDistnace = rays.rays[x].listinfo[0].distance;
			
		} else {
		    // ... if there's no hitpoint, set the working variables to correspond with empty horizon displaying
//            colheight = 0;
            Fcolheight = 1;
            nWallCeil = nHorizonHeight;
            nWallCeil2 = nHorizonHeight;
            nWallFloor = nHorizonHeight;
			theTexture = 0;
		}

		rays.Depthbuffer[x] = fDistnace;
		// code to debug the resulof the hit list info
		// prints the hit list info for the slice that is denoted by nTestRay (upon releasing T)
		
//		float fPlayerH = TILE_SIZE / 2.0f;
		float fFoV = 60.0f;
		float fAngleStep = fFoV / (float)NUM_RAYS;
		float fViewAngle = (float)(x - (NUM_RAYS / 2)) * fAngleStep;
		float fCurAngle = (player.rotationAngle * 180.0f / PI) + fViewAngle;
		float fPlayerX = player.x;
		float fPlayerY = player.y;
		float fCosCurAngle  = cos( fCurAngle * PI / 180.0f);
		float fSinCurAngle  = sin( fCurAngle * PI / 180.0f);
		float fCosViewAngle = cos(fViewAngle * PI / 180.0f);

#define ROOF_COLOR olc::CYAN

		int hitindex = 0;

		for (int y = WINDOW_HEIGHT - 1; y >= 0; y--)
		{
#define UNKNOWN_DRAW  0
#define FLOOR_DRAW    1
#define WALL_DRAW     2
#define CEIL_DRAW     3
#define ROOF_DRAWING  4

			int drawmode = UNKNOWN_DRAW;
			if (y >= nWallFloor)
			{
				drawmode = (y <= nHorizonHeight) ? CEIL_DRAW : FLOOR_DRAW;
			}
			else if (nWallFloor > y && y > nWallCeil)
			{
				drawmode = WALL_DRAW;
			}
			else if (nWallCeil >= y && y > nWallCeil2)
			{
				drawmode = (Fcolheight == 0) ? FLOOR_DRAW : ROOF_DRAWING;
			}
			else
			{
				while (drawmode == UNKNOWN_DRAW)
				{
					if (hitindex < (int)rays.rays[x].listinfo.size() - 1)
					{
						// the y coord is above the current wall and roof slide, but there are still hit points to process
						// so there could be other walls behind current wall sticking out above it
						hitindex += 1;
						Fcolheight = rays.rays[x].listinfo[hitindex].FHeight;
						nWallCeil = rays.rays[x].listinfo[hitindex].ceil_front;
						nWallCeil2 = rays.rays[x].listinfo[hitindex].ceil_back;
						nWallFloor = rays.rays[x].listinfo[hitindex].bottom_front;
						coordX = int(rays.rays[x].listinfo[hitindex].wallHitX);
						coordY = int(rays.rays[x].listinfo[hitindex].wallHitY);
						fDistnace = rays.rays[x].listinfo[hitindex].distance;


						if (y >= nWallFloor)
						{
							drawmode = (y <= nHorizonHeight) ? CEIL_DRAW : FLOOR_DRAW;
						}
						else if (nWallFloor > y && y > nWallCeil)
						{
							drawmode = WALL_DRAW;
						}
						else if (nWallCeil >= y && y > nWallCeil2)
						{
							drawmode = ROOF_DRAWING;
						}
					}
					else
					{
						//drawmode = CEIL_DRAW;
						drawmode = (y <= nHorizonHeight) ? CEIL_DRAW : FLOOR_DRAW;
					}
				}
			}

			switch (drawmode)
			{
			case CEIL_DRAW:
			{
				if (RENDER_CEILING)
				{
					float fFloorProjDistance = (((TILE_SIZE * player.fPlayerH) / (float)(nHorizonHeight - y)) * DIST_TO_PROJ_PLANE) / fCosViewAngle;
					float fFloorProjX = fPlayerX + fFloorProjDistance * fCosCurAngle;
					float fFloorProjY = fPlayerY + fFloorProjDistance * fSinCurAngle;
					int nSampleX = (int)(fFloorProjX) % TILE_SIZE;
					int nSampleY = (int)(fFloorProjY) % TILE_SIZE;

					//olc::Pixel p = sprites[0].GetPixel(nSampleX, nSampleY);
					olc::Pixel p = SelectSceneryPixel(0, nSampleX, nSampleY,fDistnace, Side::Top);
					PGEptr->Draw(x, y, p);
				}
				break;
			}
			case FLOOR_DRAW:
			{
				float fFloorProjDistance = (((TILE_SIZE * player.fPlayerH) / (float)(y - nHorizonHeight)) * DIST_TO_PROJ_PLANE) / fCosViewAngle;
				float fFloorProjX = fPlayerX + fFloorProjDistance * fCosCurAngle;
				float fFloorProjY = fPlayerY + fFloorProjDistance * fSinCurAngle;
				float fTILE_SIZE = TILE_SIZE;
				while (fFloorProjX < 0.0f) { fFloorProjX += floor(fTILE_SIZE); }
				while (fFloorProjY < 0.0f) { fFloorProjY += floor(fTILE_SIZE); }
				int nSampleX = (int)(fFloorProjX) % TILE_SIZE;
				int nSampleY = (int)(fFloorProjY) % TILE_SIZE;

				//olc::Pixel p = sprites[0].GetPixel(nSampleX, nSampleY);
				olc::Pixel p = SelectSceneryPixel(0, nSampleX, nSampleY,fDistnace, Side::Bottom);
				PGEptr->Draw(x, y, p);
				break;
			}
			case ROOF_DRAWING:
			{
				//olc::Pixel p = ROOF_COLOR;

				float fRoofProjDistance = (((player.fPlayerH - float(Fcolheight)) * TILE_SIZE / float(y - nHorizonHeight)) * DIST_TO_PROJ_PLANE) / fCosViewAngle;
				float fRoofProjX = player.x + fRoofProjDistance * fCosCurAngle;
				float fRoofProjY = player.y + fRoofProjDistance * fSinCurAngle;
				
				int nSampleX = (int)(fRoofProjX) % TILE_SIZE;
				int nSampleY = (int)(fRoofProjY) % TILE_SIZE;
				//olc::Pixel p = sprites[1].GetPixel(nSampleX, nSampleY);
				olc::Pixel p = SelectSceneryPixel(1, nSampleX, nSampleY,fDistnace, Side::Roof);
				PGEptr->Draw(x, y, p);
				break;
			}
			case WALL_DRAW:
			{
				float fSampleY = 0;
				int nDisplayBlockHeight = 0;
				int textureid = 0;
				
				if (STRETCHED_TEXTURING)
				{
					fSampleY = float(y - wallTopY) / float(wallBottomY - wallTopY);
				}
				else {
					float blocksize = float(nWallFloor - nWallCeil) / Fcolheight;

					float relative = float(y - nWallCeil);
					nDisplayBlockHeight = int(Fcolheight);
					while (relative > blocksize)
					{
						relative -= blocksize;
						nDisplayBlockHeight -= 1;
					}

					fSampleY = relative / blocksize;
				}
				if (nDisplayBlockHeight == 2)
				{
					int i = 0;
				}
				float fSampleX;
				
				int indexX = rays.rays[x].listinfo[hitindex].mapX;
				int indexY = rays.rays[x].listinfo[hitindex].mapY;
				textureid = getTexture(indexX, indexY, nDisplayBlockHeight, map);
				if (rays.rays[x].listinfo[hitindex].wasHitVertical) {
					fSampleX = (int)rays.rays[x].listinfo[hitindex].wallHitY % TILE_SIZE;
				}
				else
				{
					fSampleX = (int)rays.rays[x].listinfo[hitindex].wallHitX % TILE_SIZE;
				}

				//fSampleX = int(fSampleX) % TILE_SIZE;
				fSampleY = fSampleY * float(TILE_SIZE);
				// having both sample coordinates, get the sample and draw the pixel
				
					//olc::Pixel auxSample = sprites[textureid].GetPixel(fSampleX, fSampleY);
				olc::Pixel auxSample = SelectSceneryPixel(textureid, (int)fSampleX, (int)fSampleY,fDistnace, Side::WalL);
					PGEptr->Draw(x, y, auxSample);
				//DepthDraw(x, y, rays.rays[x].listinfo[0].distance, auxSample);

				break;
			}
			}

		}

//		PGEptr->DrawString(10, 50, "fLookUp  = " + std::to_string(player.lookupordown));
//		PGEptr->DrawString(10, 40, "fPlayerH = " + std::to_string(player.fPlayerH));
	}
}

int Wall::getTexture(int x,int y, int& id, Map& map)
{
	
	int textureid[3];
	int selected = id - 1;
	
    return map.iTextures[selected][y * map.MapX + x];
	
}

