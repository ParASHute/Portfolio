#pragma once

#include "Skeleton/AnimationRect.h"
#include "Item/Item.h"

enum class MonsterType {

};

class Monster{
public:
	Monster();
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

	float GetHP() { return Hp; }
	void SetHp(float Hp) { this->Hp = Hp; }

	float GetMaxHp() { return MaxHp; }
	void SetMaxHP(float MaxHp) { this->MaxHp = MaxHp; }

	BoundingBox* GetCollision() { return body->GetCollision(); }

private:
	// ���� ����
	float Hp;
	float MaxHp = 3;
	int Def = 5;
	int Att = 0;
	int MoveSpd = 100;
	Item* DropItem;

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

	// ���� ����
	AnimationRect* AttRange;
};