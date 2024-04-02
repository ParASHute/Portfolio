#include "Framework.h"
#include "TextureRect.h"

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation)
	: position(position), size(size), rotation(rotation)
{
	// Vertices
	{
		// ���� ũ�� �缳��
		vertices.assign(4, VertexTexture());

		// �� �ϴ�
		vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[0].uv = Vector2(0, 1);

		// ����
		vertices[1].position = Vector3(0.5f, 0.5f, 0.0f);
		vertices[1].uv = Vector2(1, 0);

		// ���ϴ�
		vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
		vertices[2].uv = Vector2(1, 1);

		// �»��(���̴� �󿡼��� ������ ���Ⱑ 0,0�� �ȴ�)
		vertices[3].position = Vector3(-0.5f, 0.5f, 0.0f);
		vertices[3].uv = Vector2(0, 0);
	}

	//VetexBuffer
	{
		vb = new VertexBuffer();
		vb->Create(vertices, D3D11_USAGE_DYNAMIC);

	}

	// IndexBuffer
	{
		indices = { 0,1,2,0,3,1 }; // �׸��� ����

		ib = new IndexBuffer();
		ib->Create(indices, D3D11_USAGE_IMMUTABLE);
	}

	// VetexShader
	{
		vs = new VertexShader();

		vs->Create(ShaderPath + L"VertexTexture.hlsl", "VS");
	}

	// InputLayout
	{
		il = new InputLayout();
		il->Create(VertexTexture::descs, VertexTexture::count, vs->GetBlob());
	}

	// PixelShader
	{
		ps = new PixelShader();
		ps->Create(ShaderPath + L"VertexTexture.hlsl", "PS");
	}

	// WorldBuffer
	{
		wb = new WorldBuffer();
	}

	// Collisino
	{
		edge = new RectEdge();
		collision = new BoundingBox();

		// ���� ��ġ ����
		for (int i = 0; i < 4; i++) verticesPosition[i] = vertices[i].position;
	}
}

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation, wstring path)
	: position(position), size(size), rotation(rotation)
{
	// Vertices
	{
		// ���� ũ�� �缳��
		vertices.assign(4, VertexTexture());

		// �� �ϴ�
		vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[0].uv = Vector2(0, 1);

		// ����
		vertices[1].position = Vector3(0.5f, 0.5f, 0.0f);
		vertices[1].uv = Vector2(1, 0);

		// ���ϴ�
		vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
		vertices[2].uv = Vector2(1, 1);

		// �»��(���̴� �󿡼��� ������ ���Ⱑ 0,0�� �ȴ�)
		vertices[3].position = Vector3(-0.5f, 0.5f, 0.0f);
		vertices[3].uv = Vector2(0, 0);
	}

	//VetexBuffer
	{
		vb = new VertexBuffer();
		vb->Create(vertices, D3D11_USAGE_DYNAMIC);

	}

	// IndexBuffer
	{
		indices = { 0,1,2,0,3,1 }; // �׸��� ����

		ib = new IndexBuffer();
		ib->Create(indices, D3D11_USAGE_IMMUTABLE);
	}

	// VetexShader
	{
		vs = new VertexShader();

		vs->Create(ShaderPath + L"VertexTexture.hlsl", "VS");
	}

	// InputLayout
	{
		il = new InputLayout();
		il->Create(VertexTexture::descs, VertexTexture::count, vs->GetBlob());
	}

	// PixelShader
	{
		ps = new PixelShader();
		ps->Create(ShaderPath + L"VertexTexture.hlsl", "PS");
	}

	// WorldBuffer
	{
		wb = new WorldBuffer();
	}

	// Collisino
	{
		edge = new RectEdge();
		collision = new BoundingBox();

		// ���� ��ġ ����
		for (int i = 0; i < 4; i++) verticesPosition[i] = vertices[i].position;
	}

	// Rasterizer State
	{
		D3D11_RASTERIZER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));

		desc.CullMode = D3D11_CULL_BACK;
		desc.FillMode = D3D11_FILL_SOLID;
		desc.FrontCounterClockwise = false;

		HRESULT hr = DEVICE->CreateRasterizerState(&desc, &rs);
		CHECK(hr);
	}

	// SRV Extraction (�׸� ������ ����)
	{
		HRESULT hr = D3DX11CreateShaderResourceViewFromFile(
			DEVICE,
			path.c_str(),
			nullptr,
			nullptr,
			&srv,
			nullptr
		);
		CHECK(hr);
	}
}

TextureRect::~TextureRect()
{
	// i�� �����ϴ� �ֵ��� RELEASE�� �ؾ���
	SAFE_RELEASE(srv);
	SAFE_RELEASE(rs);

	SAFE_DELETE(collision);
	SAFE_DELETE(edge);
	SAFE_DELETE(wb);
	SAFE_DELETE(ps);
	SAFE_DELETE(il);
	SAFE_DELETE(vs);
	SAFE_DELETE(ib);
	SAFE_DELETE(vs);
}

void TextureRect::Update()
{
	UpdateWorld();
	collision->UpdateCollisionData(world, verticesPosition);
}

void TextureRect::Render()
{
	vb->SetIA();
	ib->SetIA();
	il->SetIA();

	DC->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
	);

	vs->SetShader();

	wb->SetVSBuffer(0);

	ps->SetShader();

	DC->PSSetShaderResources(0, 1, &srv);
	DC->RSSetState(rs);

	DC->DrawIndexed(ib->GetCount(), 0, 0);
}

void TextureRect::Gui()
{
	// ����(�ʿ��ϸ� �����)
}

void TextureRect::UpdateWorld()
{
	D3DXMatrixScaling(&S, size.x, size.y, size.z);
	//D3DXMatrixRotationZ(&R, (float)D3DXToRadian(rotation));
	D3DXMatrixRotationZ(&R, rotation);
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	world = S * R * T;
	wb->SetWorld(world);
}

void TextureRect::SetShader(wstring shaderPath)
{
	vs->Clear();
	ps->Clear();

	vs->Create(shaderPath, "VS");
	ps->Create(shaderPath, "PS");
}

void TextureRect::SetImage(wstring imagePath)
{
	SAFE_RELEASE(srv);
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(
		DEVICE,
		imagePath.c_str(),
		nullptr,
		nullptr,
		&srv,
		nullptr
	);
	CHECK(hr);

}
