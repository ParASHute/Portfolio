#pragma once

// ��Ʈ��Ʈ�� ���� ��� Ŭ���� -> �����ڰ� ����
struct VertexColor {	// �ܻ��� �׸� ����� ���� ��� ����
	// ��Ʈ��Ʈ�� ������
	VertexColor()
		: position(0, 0, 0), color(0, 0, 0, 0) {}

	VertexColor(Vector3 posion, Color color)
		:position(posion), color(color) {}

	// ���� ��ġ
	Vector3 position;

	// ������ ��
	Color color;

	// ���� �������� ������ �������ִ� ����
	static D3D11_INPUT_ELEMENT_DESC descs[];

	// ���� �������� ����(��ġ, ��)
	static const uint count = 2;
};

struct VertexTexture {	// �ý��İ��ִ� �׸� ����� ���� ��� ����
	// ��Ʈ��Ʈ�� ������
	VertexTexture()
		: position(0, 0, 0), uv(0, 0) {}

	VertexTexture(Vector3 posion, Vector2 uv)
		:position(posion), uv(uv) {}

	Vector3 position;

	// �׸��� ��ǥ
	Vector2 uv;

	static D3D11_INPUT_ELEMENT_DESC descs[];
	static const uint count = 2;
};