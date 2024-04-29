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



private:
	Player* player = nullptr;
};