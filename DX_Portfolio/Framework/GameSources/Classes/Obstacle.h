#pragma once

#include "Skeleton/TextureRect.h"

enum class OBSTACLE {
	TREE = 0,
	WATER,
	BREAKABLE,
};

class Obstacle {
public:
	Obstacle();
	~Obstacle();

	BoundingBox* GetCollision() { return Image->GetCollision(); }

	void SetImage(OBSTACLE type);

private:
	TextureRect* Image;
	OBSTACLE type
};