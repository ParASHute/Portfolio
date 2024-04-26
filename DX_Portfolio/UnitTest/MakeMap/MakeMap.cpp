#include "stdafx.h"
#include "MakeMap.h"

void MakeMap::Init()
{
	uint spacing = 40;
	uint width = (WinMaxWidth * 2) / spacing;
	uint height = (WinMaxHeight * 2) / spacing;

	GrassLandBase = new TMap(width, height, spacing);
	GrassLandBorderDown = new TMap(width, height, spacing);
	GrassLandBorderLeft = new TMap(width, height, spacing);
	GrassLandBorderRight = new TMap(width, height, spacing);
	GrassLandBorderUp = new TMap(width, height, spacing);


	GrassLandBase->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetField.png", 5,15);
	GrassLandBorderDown->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetNatureDown.png", 24, 21);
	GrassLandBorderLeft->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetNatureLeft.png", 21, 24);
	GrassLandBorderRight->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetNatureRight.png", 21, 24);
	GrassLandBorderUp->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetNatureUP.png", 24, 21);


	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"Bush-3.png", 1, 1);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"Bush-4.png", 1, 1);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"Grass-1.png", 1, 1);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"Stump.png", 1, 1);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"Tree-1-4.png", 1, 1);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"Tree-2-4.png", 1, 1);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"Tree-3-4.png", 1, 1);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetDesert.png", 20, 12);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetDungeon.png", 12, 4);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetField.png", 5,15);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetFloor.png", 11, 5);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetHole.png", 11, 5);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetHouse.png", 33, 23);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetInterior.png", 16, 20);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetInteriorFloor.png", 22, 17);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetNatureDown.png", 24, 21);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetNatureLeft.png", 21, 24);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetNatureRight.png", 21, 24);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetNatureUP.png", 24, 21);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetRelief.png", 20, 12);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetReliefUpSideDown.png", 20, 12);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetVillageAbandoned.png", 20, 12);

	GrassLandBase->Load(TilePath + "Field1-1/GrassLandBase.data");
	GrassLandBorderDown->Load(TilePath + "Field1-1/GrassLandBorderDown.data");
	GrassLandBorderLeft->Load(TilePath + "Field1-1/GrassLandBorderLeft.data");
	GrassLandBorderRight->Load(TilePath + "Field1-1/GrassLandBorderRight.data");
	GrassLandBorderUp->Load(TilePath + "Field1-1/GrassLandBorderUp.data");
}

void MakeMap::Destroy()
{
	SAFE_DELETE(GrassLandBorderUp);
	SAFE_DELETE(GrassLandBorderRight);
	SAFE_DELETE(GrassLandBorderLeft);
	SAFE_DELETE(GrassLandBorderDown);
	SAFE_DELETE(GrassLandBase);
}

void MakeMap::Update()
{	
	GrassLandBase->Update();
	GrassLandBorderDown->Update();
	GrassLandBorderLeft->Update();
	GrassLandBorderRight->Update();
	GrassLandBorderUp->Update();
}

void MakeMap::Render()
{
	GrassLandBase->Render();
	GrassLandBorderDown->Render();
	GrassLandBorderLeft->Render();
	GrassLandBorderRight->Render();
	GrassLandBorderUp->Render();
}

void MakeMap::PostRender()
{

}

void MakeMap::GUI()
{
	//GrassLandBase->GUI();
	//GrassLandBorderDown->GUI();
	//GrassLandBorderLeft->GUI();
	//GrassLandBorderRight->GUI();
	//GrassLandBorderUp->GUI();
}
