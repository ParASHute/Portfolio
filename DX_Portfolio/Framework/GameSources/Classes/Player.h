#pragma once

#include "Skeleton/Rect.h"

#include "Skeleton/AnimationRect.h"
#include "Inventory/Inventory.h"

class Player {
public:
	// ������ & �Ҹ���
	Player(Vector3 position, Vector3 size, float rotation = 0.0f);
	~Player();

	// �����Լ� 
	void Update();
	void Render();
	void Move();

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

	int GetMaxHp() { return MaxHp; }
	void SetMaxHP(float MaxHp) { this->MaxHp = MaxHp; }

	bool GetStay() { return bStay; }
	void setStay(int y, int x); 

	void SetCanAtt(bool canAtt) { this->canAtt = canAtt; }

	BoundingBox* GetCollision() { return body->GetCollision() ; }

	AnimationRect* GetAttMotion() { return attMotion; }

	AnimType GetAnimType() { return type; }

	bool GetAttTrigger() { return bAtt; }
	bool GetEquipmentSword() { return equipmentSword; }
	bool GetDefenceTrigger() { return bDef; }

	float GetSwordRange() { return swordRange; }
	
	/*
	bool GetMoveL() { return moveL; }
	*/

private:
	// ���� ����
	float Hp = 3;
	int MaxHp =3;
	int Def = 5;
	int Att = 0;
	int MoveSpd = 100;
	Inventory* inven;

	// Ʈ����
	bool canAtt = false;
	bool equipmentSword = false;
	bool bDef = true;
	bool bAtt = false;
	bool bOpen = true; // ImGui ���¿� Ʈ����

	// ������ ����� Ʈ���ŵ�
	bool moveU = false;	// ���� �����̴���
	bool moveD = false; // �Ʒ��� �����̴���
	bool moveR = false; // ���������� �����̴���
	bool moveL = false; // �������� �̵��ϴ���

	// ��ġ Ʈ����
	bool bStay[4][4];
	bool D1 = false;
	bool D2 = false;
	bool hidden = false;

	AnimType type = AnimType::Down;

	// ���� & ���Ϳ�
	Vector3 position;
	Vector3 size;

	// ���� (���ϸ��̼�)
	AnimationRect* body;

	// ���� ���� -> ���� ��� + ����
	AnimationRect* attMotion;
	float swordRange;
};