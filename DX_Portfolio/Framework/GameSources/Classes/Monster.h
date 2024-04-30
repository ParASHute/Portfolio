#pragma once

#include "Skeleton/AnimationRect.h"
#include "Item/Item.h"

enum class MonsterType {
	BlueSmlime = 0,
	PurpleSlime,
	Orc,
	Skeleton,
	Boss
};

class Monster{
public:
	Monster(Vector3 position, Vector3 size, MonsterType type, float rotation = 0.0f);
	Monster(Vector3 position, Vector3 size, float rotation = 0.0f);
	~Monster();

	void Update();
	void Render();
	void Move();
	void Attack();

	// ImGui
	void GUI();
	string MakeLable(string lable);

	// ���� & ����
	Vector3 GetPos() { return position; }
	void SetPos(Vector3 position) { this->position = position; }

	void SetMonsterType();

	float GetHP() { return Hp; }
	void SetHp(float Hp) { this->Hp = Hp; }

	float GetMaxHp() { return MaxHp; }
	void SetMaxHP(float MaxHp) { this->MaxHp = MaxHp; }

	BoundingBox* GetCollision() { return body->GetCollision(); }

	// ���
	void MakeAni();

private:
	MonsterType type;

	// ���� ����
	float Hp;
	float MaxHp = 3;
	int Def = 5;
	int Att = 0;
	int MoveSpd = 100;
	Heart* DropItem1;
	Rooby* DropItem2;

	// Ʈ����
	bool bDef = true;
	bool bOpen = true; // ImGui ���¿� Ʈ����

	// ������ ����� Ʈ���ŵ�
	bool moveU = false;	// ���� �����̴���
	bool moveD = false; // �Ʒ��� �����̴���
	bool moveR = false; // ���������� �����̴���
	bool moveL = false; // �������� �̵��ϴ���

	//bool moveU = false; // ���� ������
	//bool G = true; // �߷� ����

	// ���� & ���Ϳ�
	Vector3 position;
	Vector3 size;

	// ���� (���ϸ��̼�)
	AnimationRect* body;
};