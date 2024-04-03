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
		moveD = true; // �Ʒ��� �����̴°� Ʈ��
		position.y -= MoveSpd * Time::Delta();
	}
	// sŰ ���� �Ʒ��� �������� ������ �翬�� moveD�� flase�� �Ǿ���
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
	// �÷��̾� �տ� ������ �簢�� �߰� �� ��Ʈ�� ������ �浹�� ����
	// Rect();
}

void Player::Defence()
{
	// bDef�� Ʈ���϶� ���Ϳ� �浹�ÿ��� Hp ���� ���� + �÷��̾� �ڷ� �и�
	if (bDef == true) {
		
	}

	// �׿ܿ��� ���Ϳ� �浹�� hp����
	else {
		
	}
}

void Player::GUI()
{
	// spearBody->GUI();

	ImGui::Begin("Player", &bOpen); // �������
	{
		ImGui::Text(MakeLable("Player").c_str()); 
		ImGui::SliderFloat2(MakeLable("Pos").c_str(), position, 0, WinMaxWidth);
		ImGui::SliderFloat2(MakeLable("Size").c_str(), size, 0, WinMaxHeight);
	}
	ImGui::End();
}

string Player::MakeLable(string lable)
{
	// �ڱ� �ڽ��� �ּҸ� �Ű躯���� ���� �� �ڿ� ���� ����
	string Label = lable + "##" + to_string((uint)this);

	return Label;
}
