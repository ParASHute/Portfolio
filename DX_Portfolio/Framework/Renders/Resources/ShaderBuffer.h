#pragma once
#include "Framework.h"

// ���� ������ �̿��� �����͸� cpu���� gpu�� �Ѱ��ٶ� ����� ����
// ��� ���� ��ü(�θ�)
class ShaderBuffer {
public:
	void SetVSBuffer(uint slot) {
		// ������ ����
		MapData();

		// PS���� ����� �����͸� 1�� �Ѱ��ְڴ�.
		DC->VSSetConstantBuffers(slot, 1, &buffer);
	}

	void SetPSBuffer(uint slot) {
		// ������ ����
		MapData();

		// PS���� ����� �����͸� 1�� �Ѱ��ְڴ�.
		DC->PSSetConstantBuffers(slot, 1, &buffer);
	} 

protected:
	// ��ī�� ���� �̿��� �����͸� ������ ������۸� ����� �޴´�.
	ShaderBuffer(void* data, uint dataSize) : data(data), dataSize(dataSize) {
		// ���뵵 
		desc.Usage = D3D11_USAGE_DYNAMIC;

		// ���� ũ��
		desc.ByteWidth = dataSize;

		// ���ε� ���
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // ��� ����

		// cpu ���� ���
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		// ���� �����
		HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, &buffer);
		CHECK(hr);
	}

private:
	// DX���� ���� �����͸� ��õ��� ����ΰ� �ش絥���͸� ��Ÿ���߿� ����, ���縦 �㷰�ϴ� ���̴�
	// Map�� ���� �ݵ�� unMap�� ����������Ѵ�.(������ ����)
	void MapData() {
		// ������ �ӽú���(temp����)
		D3D11_MAPPED_SUBRESOURCE subResource;

		HRESULT hr = DC->Map(
			buffer,						// ���� ���
			0,							// ���� ���� ��ġ(0�� ÷���� �ϰڴܰ�)
			D3D11_MAP_WRITE_DISCARD,	// ���� ���(����� �ٽþ��ڴ�)
			0,							// �߰��� ������ ���� ���ҽ�
			&subResource				// ������ �����͸� ������ ����
		); // "buffer"�� �ִ� (���ۺ��� �ִ�) ��� �����͸� ����� �ٽ� ���°ɷ� ���� ������ "subResource"�� �����ϰڴ�.

		// ������ �ִ��� Ȯ���Ŀ�
		CHECK(hr);

		// ������ ���� (�����ִ� �����͸�, ���⿡��, �̸�ŭ)
		memcpy(subResource.pData, data, dataSize);

		DC->Unmap(buffer, 0); // �׸��� ����ų� ������ ���ؼ��� ����� �׻� ���� ����
	}

private:
	D3D11_BUFFER_DESC desc = { 0 };
	ID3D11Buffer* buffer = nullptr;

	void* data = nullptr; // �ڷ����� �������� ���� � �ڷ����� �����͵� ����ų�� �ִ� �������̴�.
	uint dataSize = 0;
};