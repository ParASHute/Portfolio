#pragma once

#include "Skeleton/TextureRect.h"

enum class OBSTACLE {
	TREE = 0,
	WATER,
	BREAKABLE,
};

class Obstacle {
public:
	Obstacle(Vector3 position, Vector3 size, float rotation = 0.0f);
	~Obstacle();

	BoundingBox* GetCollision() { return Image->GetCollision(); }

	void SetImage(OBSTACLE type);

private:
	TextureRect* Image;
	OBSTACLE type;
};