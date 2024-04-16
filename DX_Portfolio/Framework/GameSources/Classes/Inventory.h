#pragma once

#include "Item/Item.h"
#include "Item/SpecialItem.h"

class Inventory : public SingletonBase<Inventory>{
public:
	friend SingletonBase<Inventory>;
private:
	Inventory();
	~Inventory();

	void SetCounter(int index, int count);
	void SetUsable(int index, int count);
	void SetRooby(int rooby);

private:
	// ȭ��(== 0), ��ź, ���
	int counter[3];

	// ��(== 0), Ȱ, ��ź
	bool usable[5];

	int rooby = 0;
};