#pragma once
#include "TextureRect.h"

class ShadedBuffer : public ShaderBuffer {
public:
	ShadedBuffer() :ShaderBuffer(&data, sizeof(data)) {
		data.selection = 1;
		data.blurCount = 1;
		data.textureSize = Vector2(0, 0);
	}

	int* GetSelecttionPtr() { return &data.selection; }
	int* GetBlurCountPtr() { return &data.blurCount; }
	
	void SetTextureSize(Vector2 size) {
		data.textureSize = size;
	}
	//~ShadedBuffer();
	
	// ���α׷��Ӱ� ������ cpu to gpu ���޵����� 
	// 2^n �� ũ��� ����� ���� (n >= 4)
	struct Data
	{
		int selection;			// ȿ�� ���� ��ȣ(4)

		int blurCount;			// �� ����(4)
		Vector2 textureSize;	// �̹��� ������(8)
		// ���� �� 16
	};

private:
	Data data;
};

class ShadedTexture  : public TextureRect {
public:
	ShadedTexture(Vector3 position, Vector3 size, float rotation, wstring path);
	~ShadedTexture();

	void Update();
	void Render();
	void GUI();

private:
	ShadedBuffer* sb = nullptr;
};