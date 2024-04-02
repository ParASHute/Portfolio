#include "Framework.h"
#include "IndexBuffer.h"

IndexBuffer::~IndexBuffer()
{
	SAFE_RELEASE(buffer);
}

void IndexBuffer::Create(const vector<uint>& indices, const D3D11_USAGE& usage)
{
	stride = sizeof(uint);	// ���� ũ�� ����
	count = indices.size();
	D3D11_BUFFER_DESC desc;		//desc�� ���α׷��Ӱ� ���ϴ� ������ ���� ����� DX�����͸� ����� ���� ����ü
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC)); // desc �޸� �ʱ�ȭ

	//desc ����
	{
		// ��� �뵵 
		desc.Usage = usage;

		// ��� ����
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

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
			break; // �극��ũ �Ȱɾ���
		}
	}

	// ���� ����
	{
		D3D11_SUBRESOURCE_DATA subData; // �ٿ��� �����͸� �ӽ÷� �����ϴ� ����ü
		ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));

		subData.pSysMem = indices.data();

		/*
			HR~�� �ش� �۾��� ���������� ���� �ƴ��� �Ǵ��ϴ� �ڷ���
			�۾��� ���� ������ CHECK�� �־�
			�۾��� ���������� ������� �ʾҴٸ� �����޼����� ����Ѵ�
		*/ 
		HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &buffer);
		CHECK(hr);
	}
}


void IndexBuffer::SetIA()
{
	// ���� ������ 32��Ʈ�� ����
	DC->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, offset);
}
