#pragma once

#include "Skeleton/AnimationRect.h"
#include "Inventory.h"

class Player {
public:
	// ������ & �Ҹ���
	Player(Vector3 position, Vector3 size, float rotation = 0.0f);
	~Player();

	// �����Լ� 
	void Update();
	void Render();
	void Move();
	void Attack();
	void Defence();

	// ���� & ����
	Vector3 GetPos() { return position; }
	void SetPos(Vector3 position) { this->position = position; }
	
	float GetHP() { return Hp; }
	void SetHp(float Hp) { this->Hp = Hp; }

	float GetMaxHp() { return MaxHp; }
	void SetMaxHP(float MaxHp) { this->MaxHp = MaxHp; }

private:
	// ���� ����
	float Hp;
	float MaxHp;
	int Def;
	int Att;
	int MoveSpd;
	Inventory* inven;

	// Ʈ����
	bool bDef;
	bool bAtt;

	// ���� & ���Ϳ�
	Vector3 position;
};