#include "Framework.h"
#include "Player.h"

Player::Player(Vector3 position, Vector3 size, float rotation)
	: position(position), size(size)
{
	body = new AnimationRect(position, size);
	// 에니메이터 추가 해야됨

	//AttRange = new AnimationRect(position, size);
	// 여기도 추가해야됨
}

Player::~Player()
{
	SAFE_DELETE(body);
}

void Player::Update()
{
	Move();
	// body->Update();

	body->SetPosition(position);
	body->SetSize(size);

	body->Update();
}

void Player::Render()
{
	// body->Render();
	body->Render();
}

void Player::Move()
{
	if (Keyboard::Get()->Press('W')) {
		moveU = true;
		position.y += MoveSpd * Time::Delta();
		if (Keyboard::Get()->Press('S') && moveD == false) position.y += MoveSpd * Time::Delta();
	}
	if (Keyboard::Get()->Up('W')) moveU = false;

	else if (Keyboard::Get()->Press('S')) {
		moveD = true;
		position.y -= MoveSpd * Time::Delta();
		if (Keyboard::Get()->Press('W') && moveU == false) position.y += (MoveSpd * 2) * Time::Delta();
	}
	if (Keyboard::Get()->Up('S')) moveD = false;

	if (Keyboard::Get()->Press('D') && moveU == false && moveD == false) {
		moveR = true;
		position.x += MoveSpd * Time::Delta();
		if (Keyboard::Get()->Press('A') && moveL == false) position.x -= (MoveSpd * 2) * Time::Delta();
	}

	else if (Keyboard::Get()->Press('A') && moveU == false && moveD == false) {
		moveL == true;
		position.x -= MoveSpd * Time::Delta();
	}
	if (Keyboard::Get()->Up('A')) moveL = false;

	if (Keyboard::Get()->Press('L')) {
		bDef = false;
		Attack();
	}
	if (Keyboard::Get()->Up('L')) bDef = true;
}

void Player::Attack()
{
	
}

void Player::Defence()
{
	// bDef가 트루일땐 몬스터와 충돌시에도 Hp 변동 없음 + 플레이어 뒤로 밀림
	if (bDef == true) {
		
	}

	// 그외에는 몬스터와 충돌시 hp변동
	else {
		
	}
}

void Player::GUI()
{
	// body->GUI();

	ImGui::Begin("Player", &bOpen); // 여기부터
	{
		ImGui::Text(MakeLable("Player").c_str()); 
		ImGui::SliderFloat2(MakeLable("Pos").c_str(), position, 0, WinMaxWidth);
		ImGui::SliderFloat2(MakeLable("Size").c_str(), size, 0, WinMaxHeight);
	}
	ImGui::End();
}

string Player::MakeLable(string lable)
{
	// 자기 자신의 주소를 매계변수로 받은 라벨 뒤에 직접 적음
	string Label = lable + "##" + to_string((uint)this);

	return Label;
}
