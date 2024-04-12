#pragma once

#include "Skeleton/TextureRect.h"

class Arrow {
public:
	Arrow();
	~Arrow();

	int GetCount() { return count; }

	BoundingBox* GetCollision() { return Image.GetCollision(); }

private:
	TextureRect Image;
	
	int count = 0;
};

class Bomb {
public:
	Bomb();
	~Bomb();

	int GetCount() { return count; }
	BoundingBox* GetCollision() { return Image.GetCollision(); }

private:
	TextureRect Image;

	int count = 0;
};

class Bottle {
public:
	Bottle();
	~Bottle();

	int GetCount() { return count; }
	bool GetFull() { return full; }
	BoundingBox* GetCollision() { return Image.GetCollision(); }

private:
	TextureRect Image;

	bool full = false;
	int count = 0;
};

class Heart {
public:
	Heart();
	~Heart();

	BoundingBox* GetCollision() { return Image.GetCollision(); }

private:
	TextureRect Image;
};

class Rooby {
public:
	Rooby();
	~Rooby();

	BoundingBox* GetCollision() { return Image.GetCollision(); }

private:
	TextureRect Image;
};