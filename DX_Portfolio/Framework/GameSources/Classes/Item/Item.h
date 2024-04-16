#pragma once

#include "Skeleton/TextureRect.h"

class Arrow {
public:
	Arrow(Vector3 position, Vector3 size, float rotation);
	~Arrow();

	int GetCount() { return count; }

	void SetIamge();

	BoundingBox* GetCollision() { return Image->GetCollision(); }

private:
	TextureRect* Image;
	string Type = "Arrow";
	int count = 0;
};

class Bomb {
public:
	Bomb(Vector3 position, Vector3 size, float rotation);
	~Bomb();

	int GetCount() { return count; }

	void SetIamge();

	BoundingBox* GetCollision() { return Image->GetCollision(); }

private:
	TextureRect* Image;
	string Type = "Bomb";
	int count = 0;
};

class Bottle {
public:
	Bottle(Vector3 position, Vector3 size, float rotation);
	~Bottle();

	int GetCount() { return count; }
	bool GetFull() { return full; }
	
	void SetIamge();

	BoundingBox* GetCollision() { return Image->GetCollision(); }

private:
	TextureRect* Image;
	string Type = "Bottle";
	bool full = false;
	int count = 0;
};

class Heart {
public:
	Heart(Vector3 position, Vector3 size, float rotation);
	~Heart();

	void SetIamge();

	BoundingBox* GetCollision() { return Image->GetCollision(); }

private:
	TextureRect* Image;
	string Type = "Heart";
};

class Rooby {
public:
	Rooby(Vector3 position, Vector3 size, float rotation);
	~Rooby();

	void SetIamge();

	BoundingBox* GetCollision() { return Image->GetCollision(); }

private:
	TextureRect* Image;
	string Type = "Rooby";
};