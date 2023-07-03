#ifndef MAP_H
#define MAP_H

#include "defs.h"
#include "MapEditor.h"
#include "olcPixelGameEngine.h"

class Map
{
public:
	Map() = default;
	bool mapHasWallAt(    float x, float y );
	//new has map at for fMap
	bool FloatmapHasWallAt(float x, float y, float playerH);
	bool isInsideMap(     float x, float y );
	bool isOutSideMap(    float x, float y );
    bool isOnMapBoundary( float x, float y );   // Added Joseph21

	void renderMapGrid(olc::PixelGameEngine* PGEptr);

	int getFromHeightMap( int x, int y );

	//heightmap for fmap
	float heightmapfloat(int x, int y);
	int getTextureMap(    int x, int y, int Height);


};

#endif // !MAP_H


