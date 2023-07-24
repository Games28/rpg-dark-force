#ifndef MAP_H
#define MAP_H

#include "defs.h"
#include "MapEditor.h"
#include "olcPixelGameEngine.h"

class Map
{
public:
	struct texturesOne
	{
		int one;
	};

	struct texturesTwo
	{
		int one, two;
	};
	
	struct texturesThree
	{
		int one, two, three;
	};

public:
	Map() = default;
	bool mapHasWallAt(    float x, float y );
	bool isInsideMap(     float x, float y );
	bool isOutSideMap(    float x, float y );
    bool isOnMapBoundary( float x, float y );   // Added Joseph21

	void renderMapGrid(olc::PixelGameEngine* PGEptr);

	int getFromHeightMap( int x, int y );
	void setTextures();


	int getTextureMap(    int x, int y, int Height);

	int gettexture(int x, int y,int layer);
	
	float FloatgetfromHeightmap(int x, int y);
	//new
	void addMapLayer( const std::string& sUserMap);
	void addTextures(const std::string& sUserTexture);
	void InitMap(int sizex, int sizey);
	std::vector<float*> fMaps;
	std::vector<std::string> sMaps;
	std::vector<int*> iTextures;
	std::vector<std::string> sTextures;
	
	texturesOne layeronetextures[5];
	
	int MapX, MapY;
	int texturesize = 6;
	int totallayers = 3;
public:
#define GRND_FLOOR '.'     // no block
#define FRST_FLOOR '#'     // block of height 1
#define SCND_FLOOR '@'     //                 2
#define THRD_FLOOR '*'     //                 3
#define FRTH_FLOOR '-'     //                 4
#define FFTH_FLOOR '+'     //                 5
#define SXTH_FLOOR '='     //                 6

#define FLOOR_1QRTR 'Q'    // block of height 1/4
#define FLOOR_HALVE 'H'    //                 2/4
#define FLOOR_3QRTR 'T'   //                 3/4

#define TEXTURE_BLANK '.'
#define TEXTURE_ZERO '0'
#define TEXTURE_ONE '1'
#define TEXTURE_TWO '2'
#define TEXTURE_THREE '3'
#define TEXTURE_FOUR '4'
#define TEXTURE_FIVE '5'

public:
	//map layout
	std::string Map_levelOne =
	{
		"####################"
		"#..................#"
		"#..................#"
		"#..........###.....#"
		"#..........#.#.....#"
		"#..........#.#.....#"
		"#..........###.....#"
		"#..................#"
		"#..................#"
		"#...........####...#"
		"#...........#..#...#"
		"#...........####...#"
		"#..................#"
		"####################"
	};

	std::string Map_levelTwo =
	{
		"...................."
		"...................."
		"...................."
		"...........###......"
		"...........#.#......"
		"...........#.#......"
		"...........###......"
		"...................."
		"...................."
		"............####...."
		"............#..#...."
		"............####...."
		"...................."
		"...................."
	};

	std::string Map_levelThree =
	{
		"...................."
		"...................."
		"...................."
		"...........###......"
		"...........#.#......"
		"...........#.#......"
		"...........###......"
		"...................."
		"...................."
		"............####...."
		"............#..#...."
		"............####...."
		"...................."
		"...................."
	};

	//texture layout
	std::string Texture_levelOne =
	{
		"11111111111111111111"
		"10000000000000000001"
		"10000000000000000001"
		"10000000000222000001"
		"10000000000203000001"
		"10000000000202000001"
		"10000000000222000001"
		"20000000000000000001"
		"20000000000000000001"
		"20000000000054310001"
		"20000000000030010001"
		"20000000000054410001"
		"10000000000000000001"
		"11111111111111111111"
	};

	std::string Texture_levelTwo =
	{  
		"...................."
		"...................."
		"...................."
		"...........333......"
		"...........3.3......"
		"...........3.3......"
		"...........333......"
		"...................."
		"...................."
		"............4444...."
		"............4..4...."
		"............4444...."
		"...................."
		"...................."
	};

	std::string Texture_levelThree =
	{
		"...................."
		"...................."
		"...................."
		"...........333......"
		"...........3.3......"
		"...........3.3......"
		"...........333......"
		"...................."
		"...................."
		"............4444...."
		"............4..4...."
		"............4444...."
		"...................."
		"...................."
	};




	
};

#endif // !MAP_H


