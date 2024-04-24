#include "stdafx.h"
#include "MakeMap.h"

void MakeMap::Init()
{
	uint spacing = 40;
	uint width = (WinMaxWidth * 2) / spacing;
	uint height = (WinMaxHeight * 2) / spacing;

	Map = new TMap(width, height, spacing);

	// TileSet::Get()->ChangeTileMap(TexturePath + L"타일 사용할거", 0, 0);
	// 여기에 경로 새로운 경로가 한글이라서 문제
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
