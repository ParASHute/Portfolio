#pragma once
// �����͸� �����ϴ� �ڽ���� ���� ��

class VertexBuffer {
public:
	~VertexBuffer ();


	/*
		template<typename T>�� �̴㿡 ���� �Լ��� ���� T��
		��� ���� ����Ҽ� �ֵ��� ���ִ� ����̴�.
		Create���� ���ø��� �ÿ��� ������ �׸��� ���� �簢���� ����
		�ٸ� �����͸� �ǳ� ��� �ϱ� �����̴�.

		(��ǥ �� ��� ��� �� ������ ������ ���� �޶����� �����̴�.)
	*/
	template<typename T>
	void Create(const vector<T>& verices,
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

template<typename T>
inline void VertexBuffer ::Create(const vector<T>& vertices, const D3D11_USAGE& usage)
{
	stride = sizeof(T);	// ���� ũ�� ����
	count = vertices.size();	// ���� ����
	D3D11_BUFFER_DESC desc;		//desc�� ���α׷��Ӱ� ���ϴ� ������ ���� ����� DX�����͸� ����� ���� ����ü
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC)); // desc �޸� �ʱ�ȭ

	//desc ����
	{
		// ��� �뵵 
		desc.Usage = usage;

		// ��� ����
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		// ���� ũ��
		desc.ByteWidth = stride * count;

		//cpu ���� ����(��ī�� �� ���� ����)
		switch (usage)
		{
		case D3D11_USAGE_DEFAULT:
			// gpu�� ���� �� �� �ִ� ����(cpu���� �Ұ�)

		case D3D11_USAGE_IMMUTABLE:
			// ��ī���� ���� �� ���� ������ ������ �Ұ��� ����
			break;

		case D3D11_USAGE_DYNAMIC:
			// cpu�� ����, �������� ����
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			break;

		case D3D11_USAGE_STAGING:
			// cpu���� ���� cpu,��ī �� �������� ����
			desc.CPUAccessFlags =
				D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
			break;
		}
	}

	// ����
	{
		D3D11_SUBRESOURCE_DATA subData; // �ٿ��� �����͸� �ӽ÷� �����ϴ� ����ü
		ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));

		subData.pSysMem = vertices.data();

		// HR~�� �ش� �۾��� ���������� ���� �ƴ��� �Ǵ��ϴ� �ڷ���
		// �۾��� ���� ������ CHECK�� �־�
		// �۾��� ���������� ������� �ʾҴٸ� �����޼����� ����Ѵ�
		HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &buffer);
		CHECK(hr);
	}
}
