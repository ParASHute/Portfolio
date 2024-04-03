#include "Framework.h"
#include "Rect.h"

Rect::Rect(Vector3 position, Vector3 size, float rotation)
	: position(position), size(size), rotation(rotation)
{
	// Vertices
	{
		// ���� ũ�� �缳��
		vertices.assign(4, VertexColor());

		// �� �ϴ�
		vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[0].color = Color(1, 0, 0, 1);

		// ����
		vertices[1].position = Vector3(0.5f, 0.5f, 0.0f);
		vertices[1].color = Color(1, 0, 0, 1);

		// ���ϴ�
		vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
		vertices[2].color = Color(1, 0, 0, 1);

		// �»��
		vertices[3].position = Vector3(-0.5f, 0.5f, 0.0f);
		vertices[3].color = Color(1, 0, 0, 1);
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

		vs->Create(ShaderPath + L"VertexColor.hlsl", "VS");
	}

	// InputLayout
	{
		il = new InputLayout();
		il->Create(VertexColor::descs, VertexColor::count, vs->GetBlob());
	}

	// PixelShader
	{
		ps = new PixelShader();
		ps->Create(ShaderPath + L"VertexColor.hlsl", "PS");
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

Rect::~Rect()
{
	// ����Ʈ ������ ������ ����
	SAFE_DELETE(collision);
	SAFE_DELETE(edge);
	SAFE_DELETE(wb);
	SAFE_DELETE(ps);
	SAFE_DELETE(il);
	SAFE_DELETE(vs);
	SAFE_DELETE(ib);
	SAFE_DELETE(vs);
}

void Rect::Update()
{
	// Move();													// �����̰�
	UpdateWorld();												// ����� ��ġ
	collision->UpdateCollisionData(world, verticesPosition);	// �浹 �ڽ��� ������ ����
}

void Rect::Render()
{
	// �׸� �׸��� �ڵ�
	vb->SetIA();
	ib->SetIA();
	il->SetIA();

	// �ﰢ���� ��� �׸��� �����ִ� �Լ�
	DC->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
	);

	vs->SetShader();

	wb->SetVSBuffer(0);

	ps->SetShader();

	DC->DrawIndexed(ib->GetCount(), 0, 0);
}

void Rect::Move()
{
	float mSpd = 100;
	/*
	if (Keyboard::Get()->Press('w') || Keyboard::Get()->Press('W')) {
		position.y += mSpd * Time::Delta(); 
		// ���Է� Ȯ��(s�� ���� ���ȴ��� Ȯ��)
		if (Keyboard::Get()->Press('s') || Keyboard::Get()->Press('S') && moveD == false) {
			// �̵����� 2�� ��Ű�� ���� �ִ� ������ ���� ����� (��������� +100 + (-100 * 2) = -100)
			position.y -= (mSpd * 2) * Time::Delta();
		}
	}

	else if (Keyboard::Get()->Press('s') || Keyboard::Get()->Press('S')) {
		moveD = true; // �Ʒ��� �����̴°� Ʈ��
		position.y -= mSpd * Time::Delta();
	}
	// sŰ ���� �Ʒ��� �������� ������ �翬�� moveD�� flase�� �Ǿ���
	if (Keyboard::Get()->Up('s') || Keyboard::Get()->Press('S')) moveD = false;

	// H0�� ���ʿ�
	*/

	if (Keyboard::Get()->Press('a') || Keyboard::Get()->Press('A')) {
		position.x -= mSpd * Time::Delta();
		if (Keyboard::Get()->Press('d') || Keyboard::Get()->Press('D') && moveR == false) position.x += (mSpd * 2) * Time::Delta();
	}

	else if (Keyboard::Get()->Press('D') || Keyboard::Get()->Press('d')) {
		moveR == true;
		position.x += mSpd * Time::Delta();
	}

	if (Keyboard::Get()->Up('D') || Keyboard::Get()->Up('d')) moveR = false;

	if (Keyboard::Get()->Down(VK_SPACE) && moveU == false && G == false) moveU = true;

	if (moveU == true) {
		TimeDelta += Time::Get()->Delta();
		if (TimeDelta <= 1) position.y += mSpd * Time::Delta();
	}

	if(TimeDelta != 0 && Keyboard::Get()->Up(VK_SPACE)) G = true;

	if (G == true) {
		position.y -= mSpd * Time::Delta();
		if (position.y <= size.y / 2) {
			moveU = false;
			G = false;
			TimeDelta = 0;
			position.y = size.y / 2;
		}
	}
}

void Rect::GUI()
{
	// ImGUI�� �̿��� UI���� 
	ImGui::Begin("Rect", &bOpen);
	{
		ImGui::Text(MakeLable("Rect").c_str());
		ImGui::SliderFloat2(MakeLable("Pos").c_str(), position, 0, WinMaxWidth);
		/*ImGui::SliderFloat2(MakeLable("Size").c_str(), size, 0, WinMaxHeight);*/	
		/*ImGui::SliderAngle(MakeLable("Rot").c_str(), &rotation, 0, 360.0f);*/
	}
	ImGui::End(); // �������
}

void Rect::UpdateColor()
{
	D3D11_MAPPED_SUBRESOURCE subResource;
	DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	{
		for (VertexColor& v : vertices) v.color = color; 

		memcpy(subResource.pData, vertices.data(), vb->GetCount() * vb->GetStride());
	}
	DC->Unmap(vb->GetResource(), 0);
}

string Rect::MakeLable(string lable)
{
	// �ڱ� �ڽ��� �ּҸ� �Ű躯���� ���� �� �ڿ� ���� ����
	string Label = lable + "##" + to_string((uint)this);

	return Label;
}

void Rect::UpdateWorld()
{
	D3DXMatrixScaling(&S, size.x, size.y, size.z);
	D3DXMatrixRotationZ(&R, rotation);
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);
	world = S * R * T;
	wb->SetWorld(world);
}

void Rect::SetColor(Color color)
{
	this->color = color;
	UpdateColor();
}
