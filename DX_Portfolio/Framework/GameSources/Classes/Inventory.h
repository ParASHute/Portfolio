#pragma once

class Inventory {
public:
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