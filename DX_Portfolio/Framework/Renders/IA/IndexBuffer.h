#pragma once
class IndexBuffer {
public:
	~IndexBuffer();

	void Create(const vector<uint>& indices,
		const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);

	ID3D11Buffer* GetResource() { return buffer; }
	uint GetStride() { return stride; }
	uint GetOffset() { return offset; }
	uint GetCount() { return count; }

	void SetIA();

private:
	ID3D11Buffer* buffer = nullptr;

	// ���ۿ��� �� ������ ũ�⸦ ��Ÿ���� ��
	uint stride = 0;

	// ���ۿ��� ���� ���� ��ġ
	uint offset = 0;

	// ���ۿ��� ���� ������ ����
	uint count = 0;
};