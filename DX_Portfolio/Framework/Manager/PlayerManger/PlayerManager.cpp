#include "Framework.h"
#include "PlayerManager.h"

PlayerManager::PlayerManager()
{
	player = new Player({32,32,0}, {100,100,1});
	obstacle = new Obstacle({32,32,0}, {110,110,1});
	monster = new Monster({32,32,0}, {120,120,1});
	for (int i = 0; i < 20; i++) {
		Heart[i]->SetImage(TexturePath + L"Item/Hearts_Red_1.png");
		Heart[i] = new TextureRect({0 + (8 * i),WinMaxHeight,0}, {16, 16, 1});
	}
}

PlayerManager::~PlayerManager()
{
	for (int i = 19; i >= 0; i--) SAFE_DELETE(Heart[i]);
	SAFE_DELETE(monster);
	SAFE_DELETE(obstacle);
	SAFE_DELETE(player);
}

void PlayerManager::Update()
{
}

void PlayerManager::Render()
{
}

void PlayerManager::Move(Obstacle* obstacle)
{
}

void PlayerManager::Attack(Monster* monster)
{
}

void PlayerManager::Defence(Monster* monster)
{
}

void PlayerManager::MakePlayerHpIndicator()
{
}
