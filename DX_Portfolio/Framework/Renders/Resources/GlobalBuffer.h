#pragma once
// ���⵵ �ε��� ����ó�� ������ϸ�

#include "Framework.h"
// #include "Renders/Resources/ShaderBuffer.h"

/*
	WVP = ����(����) * ��(ī�޶�) * ��������(������)

	 WVP�� 3���������� ���� 2���� ��ũ�� ��ǥ�� ��ȯ�ϴ� ������ �ϳ��̴�
	 ����Ͷ��� ���(2����)�̱� ������ 3D���ӵ� ��ũ�� ��ǥ�� ��ȯ�ϴ� ������ �ʿ��ϴ�.

	 World(����)
		- ���� ������ �۷ι� ��ǥ�迡�� ���� ��ǥ��� ��ȯ �ϴ� ���� �ǹ��Ѵ�.
		- ���� ��ġ, ȸ��, ũ�⸦ �����Ѵ�.

	View(ī�޶�)
		- ī�޶��� ��ġ, ����, �þ߸� ��Ÿ���� ���
		- �۷��� ��ǥ�迡�� ī�޶� �ٶ󺸴� ������ ��Ÿ����.(������ ī�޶� �����ϴ°� �ƴ�)
		- ī�޶��� ��ġ�� ������ ���� �����ش�.

	Projection(������)
		- 3D������ 2D��ũ�� ��ǥ�� ��ȯ��Ű�� ���
		- �þ߰�, ��Ⱦ��, ũ���� ���(�ܸ鵵 // ��ü�� ���Ƽ� ���� Ȯ���� �� �� �ִ�)���� ����� ����
*/

class WorldBuffer : public ShaderBuffer {
public:
	WorldBuffer() : ShaderBuffer(&data, sizeof(Data)) {
		D3DXMatrixIdentity(&data.world); // �࿭ �ʱ�ȭ
	}

	void SetWorld(Matrix world) {
		// ��ġ ���
		// ���� ���� ���� ��ȯ
		// world�� ���� ����Ʈ ������ ��, ���� ������ ��
		D3DXMatrixTranspose(&data.world, &world);
	}

	// cpu�� �ѱ� ������ ����
	// 16����� �Ҵ����ִ� ���� ���� ����(int 4�� or char 16�� ó��)
	// 16���� ������ ��ī�� ���� ������ ���� ��Ȳ�� ����
	struct  Data
	{
		// float 4�� �ִ� ����ü
		Matrix world;
	};

private:
	Data data;
};

class VPBuffer : public ShaderBuffer {
public:
	VPBuffer() : ShaderBuffer(&data, sizeof(Data)) {
		D3DXMatrixIdentity(&data.view);
		D3DXMatrixIdentity(&data.projection);
	}

	void SetView(Matrix view) {
		D3DXMatrixTranspose(&data.view, &view);
	}

	void SetProj(Matrix projection) {
		D3DXMatrixTranspose(&data.projection, &projection);
	}

	struct  Data
	{
		// float 4�� �ִ� ����ü
		Matrix view;		// ī�Ŷ�
		Matrix projection;	// ������
	};

private:
	Data data;
};