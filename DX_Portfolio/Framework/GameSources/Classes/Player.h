#pragma once

#include "Skeleton/AnimationRect.h"
#include "Inventory.h"

class Player {
public:
	// 생성자 & 소멸자
	Player(Vector3 position, Vector3 size, float rotation = 0.0f);
	~Player();

	// 구성함수 
	void Update();
	void Render();
	void Move();
	void Attack();
	void Defence();

	// 게터 & 세터
	Vector3 GetPos() { return position; }
	void SetPos(Vector3 position) { this->position = position; }
	
	float GetHP() { return Hp; }
	void SetHp(float Hp) { this->Hp = Hp; }

	float GetMaxHp() { return MaxHp; }
	void SetMaxHP(float MaxHp) { this->MaxHp = MaxHp; }

private:
	// 구성 변수
	float Hp;
	float MaxHp;
	int Def;
	int Att;
	int MoveSpd;
	Inventory* inven;

	// 트리거
	bool bDef;
	bool bAtt;

	// 게터 & 세터용
	Vector3 position;
};