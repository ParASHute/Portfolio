#pragma once

#include "../../GameSources/Classes/Player.h"
#include "../../GameSources/Classes/Obstacle.h"
#include "../../GameSources/Classes/Monster.h"
#include "../../GameSources/Classes/Inventory/Inventory.h"

class PlayerManager : public SingletonBase<PlayerManager> {
public:
	friend SingletonBase<PlayerManager>;

private:
	PlayerManager();
	~PlayerManager();

	void Update();
	void Render();

	void Move(Obstacle* obstacle);
	void Attack(Monster* monster);
	void Defence(Monster* monster);

	void MakePlayerHpIndicator();

private:
	Player* player = nullptr;
	Obstacle* obstacle = nullptr;
	Monster* monster = nullptr;

	TextureRect* Heart[20] = { nullptr, };

	int playerHp;
	int playerMaxHp;
};