#include "Framework.h"
#include "Rect.h"

Rect::Rect(Vector3 position, Vector3 size, float rotation)
	: position(position), size(size), rotation(rotation)
{
	// Vertices
	{
		// 백터 크기 재설정
		vertices.assign(4, VertexColor());

		// 좌 하단
		vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[0].color = Color(1, 0, 0, 1);

		// 우상단
		vertices[1].position = Vector3(0.5f, 0.5f, 0.0f);
		vertices[1].color = Color(1, 0, 0, 1);

		// 우하단
		vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
		vertices[2].color = Color(1, 0, 0, 1);

		// 좌상단
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
		indices = { 0,1,2,0,3,1 }; // 그리는 순서
		
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

		// 정점 위치 전달
		for (int i = 0; i < 4; i++) verticesPosition[i] = vertices[i].position;
	}
}

Rect::~Rect()
{
	// 딜리트 순서는 가능한 역순
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
	// 여기에는 책체가 매 프레임마다 할 행동들을 적어준다
	// Move();													// 움직이고
	UpdateWorld();												// 월드상 배치
	collision->UpdateCollisionData(world, verticesPosition);	// 충돌 박스에 데이터 전달
}

void Rect::Render()
{
	// 그림 그리는 코드
	vb->SetIA();
	ib->SetIA();
	il->SetIA();

	// 삼각형을 어떻게 그릴지 정해주는 함수
	DC->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
	);

	vs->SetShader();

	wb->SetVSBuffer(0);
	// 이 0이 hlsl에 있는 "cbuffer WorldBuffer : register(b0)"의 b0임

	ps->SetShader();

	DC->DrawIndexed(ib->GetCount(), 0, 0);
}

void Rect::Move()
{
	/* 이건 내꺼 -> 이 경우에 후키 판정 없음
	if (Name == "Player") {
		// 이건 누르고 있을 경우
		// Get.Down이면 누를때 한번, UP일떈 눌렀다 땟을때 한번
		if (Keyboard::Get()->Press('w') || Keyboard::Get()->Press('W')) {
			// 이친구는 프레임과 프레임 사이의 시간을 반환, 이값에 계속 더해져서 1이 됐다면 1초가 지났다는 것
			// Time::Get()->Delta();
			position.y += 1;
			position.y += 100 * Time::Delta(); // 이렇게 해야 컴 성능에 따른 속도 차이를 최대한 비슷하게 맞출수 있음
		}
		if (Keyboard::Get()->Press('a') || Keyboard::Get()->Press('A')) {
			if(!Keyboard::Get()->Press('w') || !Keyboard::Get()->Press('W')) position.y -= 100 * Time::Delta();
			if(Keyboard::Get()->Press('w') || Keyboard::Get()->Press('W')) position.y += 100 * Time::Delta();
		}
		if (Keyboard::Get()->Press('s') || Keyboard::Get()->Press('S')) position.y -= 1;
		if (Keyboard::Get()->Press('D') || Keyboard::Get()->Press('d')) position.x += 1;

		// 이건 키보드로 스페이스바 눌렀을 경우
		// 일반적인 키는 ''안에 키로 전달, 그외는 (alt contl 같은 경우 VK(버츄얼 키)를 통해 전달한다
		if (Keyboard::Get()->Down(VK_SPACE)) {
			size.x += 5;
			size.y += 5;
		}

		if (Keyboard::Get()->Up(VK_SPACE)) {
			size.x -= 5;
			size.y -= 5;
		}
	}
	*/
	
	// 강사님 코드
	float mSpd = 100;
	/*
	if (Keyboard::Get()->Press('w') || Keyboard::Get()->Press('W')) {
		position.y += mSpd * Time::Delta(); 
		// 선입력 확인(s가 먼저 눌렸는지 확인)
		if (Keyboard::Get()->Press('s') || Keyboard::Get()->Press('S') && moveD == false) {
			// 이동값을 2배 시키면 위에 있는 증가한 값이 사라짐 (결과적으로 +100 + (-100 * 2) = -100)
			position.y -= (mSpd * 2) * Time::Delta();
		}
	}

	else if (Keyboard::Get()->Press('s') || Keyboard::Get()->Press('S')) {
		moveD = true; // 아래로 움직이는거 트루
		position.y -= mSpd * Time::Delta();
	}
	// s키 떄면 아래로 움직이지 않으니 당연히 moveD도 flase가 되야함
	if (Keyboard::Get()->Up('s') || Keyboard::Get()->Press('S')) moveD = false;

	// H0내 불필요
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

	/*
			점프 만드는법
			(모든 점프는 기본적으로 bool값을 이용해 스페이스바를 눌렀을 경우 해당 bool값을 true로 바꿔
			해당 bool값이 true일때 점프 이동을 실행하는 것을 기본으로 둠)

				1. 점프시간 이용하기 (일정한 시간의 점프 구현 가능)
				// 주로 RGP에서 주로 사용
					- 스페이스바를 눌렀을 경우 일정시간(타임::댈타())동안 위로 간다
					- 일던 시간이 지나면 다시 원래 있던 곳으로 천천히 내려온다

				2. 중력 이용하기 (감가속이 쉬운 점프 구현 가능)
				// 플렛포머(마리오같은) 게임에서 주로 사용
					- 스페이스바를 누를 경우 중력값만큼 이동 시작
					- 중력값은 처음에 +였다 시간이 지날수록 -로 바뀐다(역중력)

				3. 특정 거리 이동 (목적지 도달이 쉬운 점프 구현 가능 // 비 추천)
				// AI를 이용시 이점이 있을 수 있음
					- 스페이스 바를 누를경우 현재 자신의 위치에서 특정 좌표까지 서서히 이동
					- 해당 좌표 도달시 천천히 떨어짐
			(만약, 점프를 누르고 있는동안 점프의 높이가 점점 증가하는 방식의 점프를 만들고 싶다면 bool이용 안해도 됨)
		*/
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
	// ImGUI를 이용해 UI생성 
	ImGui::Begin("Rect", &bOpen); // 여기부터
	{
		ImGui::Text(MakeLable("Rect").c_str()); // 이거 없었는데 추가해도 문제 X
		// ImGui::InputFloat3(MakeLable("Pos").c_str(), position, 2);
		// ImGui::InputFloat3(MakeLable("Size").c_str(), size, 2);
		ImGui::SliderFloat2(MakeLable("Pos").c_str(), position, 0, WinMaxWidth);
		/*ImGui::SliderFloat2(MakeLable("Size").c_str(), size, 0, WinMaxHeight);*/	
		/*ImGui::SliderAngle(MakeLable("Rot").c_str(), &rotation, 0, 360.0f);*/
		
		// 이처럼 특정 기능이 실행되면 함수를 실행하는 조건문도 작성 가능
		/*if (ImGui::ColorPicker4(MakeLable("Color").c_str(), color)) UpdateColor();*/
	}
	ImGui::End(); // 여기까지
	// 중괄호 안에 코드(주로 함수)를 실행
	// 비긴, 엔드 둘중 하나라도없음 터짐

	// size, rotate부분은 /**/ 안에 들어가 있는게 나중에 수정한것 즉, 수업시간에 만든 부분이다.
}

void Rect::UpdateColor()
{
	D3D11_MAPPED_SUBRESOURCE subResource;
	DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	{// 매핑 중인 공간
		for (VertexColor& v : vertices) v.color = color; // vertices에 변경 값 넣어주고

		memcpy(subResource.pData, vertices.data(), vb->GetCount() * vb->GetStride());
	}
	DC->Unmap(vb->GetResource(), 0);
}

string Rect::MakeLable(string lable)
{
	// 자기 자신의 주소를 매계변수로 받은 라벨 뒤에 직접 적음
	string Label = lable + "##" + to_string((uint)this);

	return Label;
}

void Rect::UpdateWorld()
{// 여기서 업데이트에 있는 부분을 여기에 만듬(but, '(float)D3DXToRadian(rotation)'가 아닌 그냥 'rotation'
	D3DXMatrixScaling(&S, size.x, size.y, size.z);						// 로커 크기를 월드상 크기로 변경
	//D3DXMatrixRotationZ(&R, (float)D3DXToRadian(rotation));				// 로컬 회전값을 월드상 회전값으로 변경
	D3DXMatrixRotationZ(&R, rotation);
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);		// 로컬 위치를 월드상위치로 변경

	world = S * R * T;
	wb->SetWorld(world);
}

void Rect::SetColor(Color color)
{
	this->color = color;
	UpdateColor();
}
