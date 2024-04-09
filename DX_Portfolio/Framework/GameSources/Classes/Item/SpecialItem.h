#pragma once

#include "Skeleton/TextureRect.h"

enum class ItemType {
	HEART = 0,
	ARROW,
	BOME,
	EMPTY_BOTTLE,
	FULL_BOTTLE
};

class Item {
public:
	Item(Vector3 position, Vector3 size, float rotatioin = 0.0f);
	~Item();

	void SetImage(ItemType type);

	ItemType GetType() { return type; }
	int GetItemCount() { return  itemCount; }

	void SetType(ItemType type) { this->type = type; }
	int SetItemCount(int itemCount) { this->itemCount = itemCount; }

private:
	TextureRect image;

	ItemType type;
	int itemCount;
};