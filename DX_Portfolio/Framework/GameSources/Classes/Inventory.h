#pragma once

class Inventory {
public:
	Inventory();
	~Inventory();

	void SetCounter(int index, int count);
	void SetUsable(int index, int count);
	void SetRooby(int rooby);

private:
	// È­»ì(== 0), ÆøÅº, ·çºñ
	int counter[3];

	// °Ë(== 0), È°, ÆøÅº
	bool usable[5];

	int rooby = 0;
};