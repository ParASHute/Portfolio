#include "Framework.h"
#include "TextureRect.h"

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation)
	: position(position), size(size), rotation(rotation)
{
	// Vertices
	{
		// 백터 크기 재설정
		vertices.assign(4, VertexTexture());

		// 좌 하단
		vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
		
		// 그림 좌표계는 내가 알고 있는 컴퓨터의 좌표계를 사용함
		// 하지만 쉐이더의 경우에는 절대적으로 그림을 0 부터 1까지만 그림(나중에 배울 예정)
		// 그래서 그것에 맞춘 좌표계 치환(그림 크기가 끝에 맞춰서 그릴수 있게끔)의 개념으로서 uv를 사용한다 생각하면 된다
		vertices[0].uv = Vector2(0, 1);

		// 우상단
		vertices[1].position = Vector3(0.5f, 0.5f, 0.0f);
		vertices[1].uv = Vector2(1, 0);

		// 우하단
		vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
		vertices[2].uv = Vector2(1, 1);

		// 좌상단(쉐이더 상에서의 시작은 여기가 0,0이 된다)
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
		indices = { 0,1,2,0,3,1 }; // 그리는 순서

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

		// 정점 위치 전달
		for (int i = 0; i < 4; i++) verticesPosition[i] = vertices[i].position;
	}
}

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation, wstring path)
	: position(position), size(size), rotation(rotation)
{
	// Vertices
	{
		// 백터 크기 재설정
		vertices.assign(4, VertexTexture());

		// 좌 하단
		vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);

		// 그림 좌표계는 내가 알고 있는 컴퓨터의 좌표계를 사용함
		// 하지만 쉐이더의 경우에는 절대적으로 그림을 0 부터 1까지만 그림(나중에 배울 예정)
		// 그래서 그것에 맞춘 좌표계 치환(그림 크기가 끝에 맞춰서 그릴수 있게끔)의 개념으로서 uv를 사용한다 생각하면 된다
		vertices[0].uv = Vector2(0, 1);

		// 우상단
		vertices[1].position = Vector3(0.5f, 0.5f, 0.0f);
		vertices[1].uv = Vector2(1, 0);

		// 우하단
		vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
		vertices[2].uv = Vector2(1, 1);

		// 좌상단(쉐이더 상에서의 시작은 여기가 0,0이 된다)
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
		indices = { 0,1,2,0,3,1 }; // 그리는 순서

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

		// 정점 위치 전달
		for (int i = 0; i < 4; i++) verticesPosition[i] = vertices[i].position;
	}

	// Rasterizer State
	// Rasterizer는 버택스 쉐이더로 찍은 정점들의 사이와 내부를 채우는 역할을 함
	// 이게 없으면 기본값으로 
	{
		D3D11_RASTERIZER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));

		// CullMode는 그리지 않을 부분을 설정하는 것
		// 'D3D11_CULL_BACK'은 뒷면은(반시계방향) 안그리겠다.
		// 필요에 따라서 뒷면을 그리지 않는데, 가끔가다가 지혼자 그림
		// 3d에서는 몰라도 2d에서는 필요없는 뒷면을 그려 
		// 굳이 메모리를 잡아 먹게 할 필요는 없음
		desc.CullMode = D3D11_CULL_BACK;


		// FillMode는 채우는 방식을 설정하는 것
		// 'D3D11_FILL_SOLID'는 전부 체우겠다는 뜻(빈공간 생성X)
		// 하는 방식도있긴 하지만, 잘 안씀(디버깅 최적화 용으로만 씀)
		desc.FillMode = D3D11_FILL_SOLID;

		// 시계방향 설정(fals가 시계 방향 true는 당연히 반대로 반시계 방향)
		desc.FrontCounterClockwise = false;

		HRESULT hr = DEVICE->CreateRasterizerState(&desc, &rs);
		CHECK(hr);
	}

	// SRV Extraction (그림 데이터 추츨)
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
	// i로 시작하는 애들은 RELEASE로 해야함
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
	// 생략(필요하면 만들것)
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
	SAFE_RELEASE(srv); // 이게 NEW마냥 메모리 잡아 먹어서 지우면 메모리 사용량이 낮아짐
	// SRV Extraction (그림 데이터 추츨)
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
