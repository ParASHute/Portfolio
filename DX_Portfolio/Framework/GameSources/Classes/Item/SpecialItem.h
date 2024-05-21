#pragma once

#include "Skeleton/TextureRect.h"

class Sowrd {
public:
	Sowrd(Vector3 position,Vector3 size, float rotation);
	~Sowrd();

	BoundingBox* GetCollision() { return Image->GetCollision(); }

	bool GetPossessSowrd() { return false; }
	void SetPossessSowrd(bool possessSowrd) { this->possessSowrd = possessSowrd; }

private:
	TextureRect* Image;

	bool possessSowrd = false;
};

class HeartPlate {
public:
	HeartPlate(Vector3 position, Vector3 size, float rotation);
	~HeartPlate();

	BoundingBox* GetCollision() { return Image->GetCollision(); }

	int GetHeartPlateCount() { return heartPlateCount; }
	void SetHeartPlateCount(int heartPlateCount) { this->heartPlateCount = heartPlateCount; }

private:
	TextureRect* Image;

	int heartPlateCount = 3;
};

class Bow {
public:
	Bow(Vector3 position, Vector3 size, float rotation);
	~Bow();

	BoundingBox* GetCollision() { return Image->GetCollision(); }

	// �������� �� ������ usable
	bool GetUsable() { return usable; }
	void SetUsavble(bool usable) { this->usable = usable; }

	int GetArrowCount() { return arrowCount; }
	void SetArrowCount(int arrowCount) { this->arrowCount = arrowCount; }

	// �������� �� �� ��, ī��Ʈ�� 0�� �ƴ� ��쿡
	bool GetShootArrow() { return shootArrow; }
	void SetShootArrow();

private:
	TextureRect* Image;

	bool usable = false;

	int arrowCount = 0;;
	bool shootArrow = false;
};

class BombPorket {
public:
	BombPorket(Vector3 position, Vector3 size, float rotation);
	~BombPorket();

	BoundingBox* GetCollision() { return Image->GetCollision(); }

	// �������� �� ������ usable
	bool GetUsable() { return usable; }
	void SetUsable(bool usable) { this->usable = usable; }

	// �������� �� ����, ī��Ʈ�� 0�� �ƴ� ��쿡
	bool GetUseBomb() { return useBomb; }
	void SetUseBomb();

	int GetBombCount() { return bombCount; }
	void SetBombCount(int bombCount) { this->bombCount = bombCount; }

private:
	TextureRect* Image;

	bool usable = false;

	int bombCount = 0;
	bool useBomb = false;;
};