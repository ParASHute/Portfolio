#pragma once

#include "Skeleton/Rect.h"

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

	// ImGui
	void GUI();
	string MakeLable(string lable);

	// ���� & ����
	void SetAni(AnimType type);
	void SetType(AnimType type) { this->type = type; }

	Vector3 GetPos() { return position; }
	void SetPos(Vector3 position) { this->position = position; }
	
	float GetHP() { return Hp; }
	void SetHp(float Hp) { this->Hp = Hp; }

	float GetMaxHp() { return MaxHp; }
	void SetMaxHP(float MaxHp) { this->MaxHp = MaxHp; }

	BoundingBox* GetCollision() { return body->GetCollision() ; }

private:
	// ���� ����
	float Hp;
	float MaxHp;
	int Def = 5;
	int Att = 0;
	int MoveSpd = 100;
	Inventory* inven;

	// Ʈ����
	bool bDef = true;
	bool bOpen = true; // ImGui ���¿� Ʈ����

	// ������ ����� Ʈ���ŵ�
	bool moveU = false;	// ���� �����̴���
	bool moveD = false; // �Ʒ��� �����̴���
	bool moveR = false; // ���������� �����̴���
	bool moveL = false; // �������� �̵��ϴ���

	AnimType type = AnimType::Down;

	// ���� & ���Ϳ�
	Vector3 position;
	Vector3 size;

	// ���� (���ϸ��̼�)
	AnimationRect* body;

	// ���� ���� -> ���� ��� + ����
	AnimationRect* attMotion;
	Rect* attRange;

	// ��� ����
	Rect* defenceRange;
};