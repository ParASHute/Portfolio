#include "Framework.h"
#include "Player.h"

Player::Player(Vector3 position, Vector3 size, float rotation)
	: position(position), size(size)
{
	spearBody = new Rect(position, size);
}

Player::~Player()
{
	SAFE_DELETE(spearBody);
}

void Player::Update()
{
	Move();
	// body->Update();

	spearBody->SetPosition(position);
	spearBody->SetSize(size);

	spearBody->Update();
}

void Player::Render()
{
	// body->Render();
	spearBody->Render();
}

void Player::Move()
{
	if (Keyboard::Get()->Press('w') || Keyboard::Get()->Press('W')) {
		position.y += MoveSpd * Time::Delta();
		if (Keyboard::Get()->Press('s') || Keyboard::Get()->Press('S') && moveD == false) position.y -= (MoveSpd * 2) * Time::Delta();
	}

	else if (Keyboard::Get()->Press('s') || Keyboard::Get()->Press('S')) {
		moveD = true; // 아래로 움직이는거 트루
		position.y -= MoveSpd * Time::Delta();
	}
	// s키 떄면 아래로 움직이지 않으니 당연히 moveD도 flase가 되야함
	if (Keyboard::Get()->Up('s') || Keyboard::Get()->Press('S')) moveD = false;

	if (Keyboard::Get()->Press('a') || Keyboard::Get()->Press('A')) {
		position.x -= MoveSpd * Time::Delta();
		if (Keyboard::Get()->Press('d') || Keyboard::Get()->Press('D') && moveR == false) position.x += (MoveSpd * 2) * Time::Delta();
	}

	else if (Keyboard::Get()->Press('D') || Keyboard::Get()->Press('d')) {
		moveR == true;
		position.x += MoveSpd * Time::Delta();
	}

	if (Keyboard::Get()->Up('D') || Keyboard::Get()->Up('d')) moveR = false;

	if (Keyboard::Get()->Press('L') || Keyboard::Get()->Press('l')) {
		bDef = false;
		Attack();
	}
}

void Player::Attack()
{
	// 플레이어 앞에 무색의 사각형 추가 이 랙트와 몬스터의 충돌시 삭제
	// Rect();
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
	// spearBody->GUI();

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
