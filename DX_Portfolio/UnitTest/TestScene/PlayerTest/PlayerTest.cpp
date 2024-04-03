#include "stdafx.h"
#include "PlayerTest.h"

void pTest::Init()
{
	player = new Player({ 100,100,0 }, { 100,100,1 });
}

void pTest::Destroy()
{
	SAFE_DELETE(player);
}

void pTest::Update()
{
	player->Update();
}

void pTest::Render()
{
	player->Render();
}

void pTest::PostRender()
{
}

void pTest::GUI()
{
	ImGui::Begin("player"); 
	{
		player->GUI();
	}
	ImGui::End();
}
