#include "stdafx.h"
#include "MakeMap.h"

void MakeMap::Init()
{
	uint spacing = 40;
	uint width = (WinMaxWidth * 2) / spacing;
	uint height = (WinMaxHeight * 2) / spacing;

	Map = new TMap(width, height, spacing);

	//Map->GetTileSet()->ChangeTileMap(TexturePath + L"Map/usable/Bush-3.png", 1, 1);
	//Map->GetTileSet()->ChangeTileMap(TexturePath + L"Map/usable/Bush-4.png", 1, 1);
	//Map->GetTileSet()->ChangeTileMap(TexturePath + L"Map/usable/Grass-1.png", 1, 1);
	//Map->GetTileSet()->ChangeTileMap(TexturePath + L"Map/usable/Stump.png", 1, 1);
	//Map->GetTileSet()->ChangeTileMap(TexturePath + L"Map/usable/Tree-1-4.png", 1, 1);
	//Map->GetTileSet()->ChangeTileMap(TexturePath + L"Map/usable/Tree-2-4.png", 1, 1);
	//Map->GetTileSet()->ChangeTileMap(TexturePath + L"Map/usable/Tree-3-4.png", 1, 1);
	//Map->GetTileSet()->ChangeTileMap(TexturePath + L"Map/usable/TilesetDesert.png", 20, 12);
	//Map->GetTileSet()->ChangeTileMap(TexturePath + L"Map/usable/TilesetDungeon.png", 12, 4);
	//Map->GetTileSet()->ChangeTileMap(TexturePath + L"Map/usable/TilesetField.png", 5,15);
	//Map->GetTileSet()->ChangeTileMap(TexturePath + L"Map/usable/TilesetFloor.png", 11, 5);
	//Map->GetTileSet()->ChangeTileMap(TexturePath + L"Map/usable/TilesetHole.png", 11, 5);
	//Map->GetTileSet()->ChangeTileMap(TexturePath + L"Map/usable/TilesetHouse.png", 33, 23);
	//Map->GetTileSet()->ChangeTileMap(TexturePath + L"Map/usable/TilesetInterior.png", 16, 20);
	//Map->GetTileSet()->ChangeTileMap(TexturePath + L"Map/usable/TilesetInteriorFloor.png", 22, 17);
	//Map->GetTileSet()->ChangeTileMap(TexturePath + L"Map/usable/TilesetNature.png", 24, 21);
	//Map->GetTileSet()->ChangeTileMap(TexturePath + L"Map/usable/TilesetRelief.png", 20, 12);
	//Map->GetTileSet()->ChangeTileMap(TexturePath + L"Map/usable/TilesetVillageAbandoned.png", 20, 12);
}

void MakeMap::Destroy()
{
	SAFE_DELETE(Map);
}

void MakeMap::Update()
{
	Map->Update();
}

void MakeMap::Render()
{
	Map->Render();
}

void MakeMap::PostRender()
{
}

void MakeMap::GUI()
{
	Map->GUI();
}
