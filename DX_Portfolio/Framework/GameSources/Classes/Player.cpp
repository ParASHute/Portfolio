#include "Framework.h"
#include "Player.h"

Player::Player(Vector3 position, Vector3 size, float rotation)
	: position(position), size(size)
{
	body = new AnimationRect(position, size);
	
	Animator* ani = new Animator();

	//Idle
	Texture2D* srcTex = new Texture2D(TexturePath + L"Player/SeparateAnim/Idle.png");
	AnimationClip* IdleD = new AnimationClip(L"IdleD", srcTex, 4,
		Values::ZeroVec2, 
		{ srcTex->GetWidth() * 0.25f, srcTex->GetHeight() });

	AnimationClip* IdleU = new AnimationClip(L"IdleU", srcTex, 4,
		{ srcTex->GetWidth(), srcTex->GetHeight()},
		{ srcTex->GetWidth() * 0.25f * 2, srcTex->GetHeight() });

	AnimationClip* IdleL = new AnimationClip(L"IdleL", srcTex, 4,
		{ srcTex->GetWidth(), srcTex->GetHeight() },
		{ srcTex->GetWidth() * 0.25f * 3, srcTex->GetHeight()});

	AnimationClip* IdleR = new AnimationClip(L"IdleR", srcTex, 4,
		{ srcTex->GetWidth() * 0.25f * 3, srcTex->GetHeight() },
		{ srcTex->GetWidth() * 0.25f * 4, srcTex->GetHeight() });

	ani->AddAnimClip(IdleD);
	ani->AddAnimClip(IdleU);
	ani->AddAnimClip(IdleL);
	ani->AddAnimClip(IdleR);

	SAFE_DELETE(srcTex);



	// Move
	srcTex = new Texture2D(TexturePath + L"Player/SeparateAnim/Walk.png");
	AnimationClip* MoveD = new AnimationClip(L"MoveD", srcTex, 4,
		Values::ZeroVec2, { srcTex->GetWidth() * 0.25f, srcTex->GetHeight() }, true);

	AnimationClip* MoveU = new AnimationClip(L"MoveU", srcTex, 4,
		{ srcTex->GetWidth() * 0.25f, 0 }, 
		{ srcTex->GetWidth() * 0.25f * 2 , srcTex->GetHeight() }, true);

	AnimationClip* MoveL = new AnimationClip(L"MoveL", srcTex, 4,
		{ srcTex->GetWidth() * 0.25f * 2 , 0}, 
		{ srcTex->GetWidth() * 0.25f * 3, srcTex->GetHeight() }, true);

	AnimationClip* MoveR = new AnimationClip(L"MoveR", srcTex, 4,
		{ srcTex->GetWidth() * 0.25f * 3, 0 }, 
		{ srcTex->GetWidth() * 0.25f * 4, srcTex->GetHeight() }, true);

	ani->AddAnimClip(MoveD);
	ani->AddAnimClip(MoveU);
	ani->AddAnimClip(MoveL);
	ani->AddAnimClip(MoveR);

	SAFE_DELETE(srcTex);

	// Att
	srcTex = new Texture2D(TexturePath + L"Player/SeparateAnim/Attack.png");
	AnimationClip* AttD = new AnimationClip(L"AttD", srcTex, 4,
		Values::ZeroVec2,
		{ srcTex->GetWidth() * 0.25f, srcTex->GetHeight() });

	AnimationClip* AttU = new AnimationClip(L"AttU", srcTex, 4,
		{ srcTex->GetWidth(), srcTex->GetHeight() * 0.25f },
		{ srcTex->GetWidth() * 0.25f * 2, srcTex->GetHeight() });

	AnimationClip* AttL = new AnimationClip(L"AttL", srcTex, 4,
		{ srcTex->GetWidth(), srcTex->GetHeight() * 0.25f * 2 },
		{ srcTex->GetWidth() * 0.25f * 3, srcTex->GetHeight() });

	AnimationClip* AttR = new AnimationClip(L"AttR", srcTex, 4,
		{ srcTex->GetWidth(), srcTex->GetHeight() * 0.25f * 3 },
		{ srcTex->GetWidth() * 0.25f * 4, srcTex->GetHeight() });

	ani->AddAnimClip(AttD);
	ani->AddAnimClip(AttU);
	ani->AddAnimClip(AttL);
	ani->AddAnimClip(AttR);

	SAFE_DELETE(srcTex);

	// Item
	srcTex = new Texture2D(TexturePath + L"Player/SeparateAnim/Item.png");
	AnimationClip* Item = new AnimationClip(L"Item", srcTex, 4,
		Values::ZeroVec2,
		{ srcTex->GetWidth(), srcTex->GetHeight()});

	ani->AddAnimClip(Item);

	SAFE_DELETE(srcTex);

	// Dead
	srcTex = new Texture2D(TexturePath + L"Player/SeparateAnim/Dead.png");
	AnimationClip* Dead = new AnimationClip(L"Dead", srcTex, 4,
		Values::ZeroVec2,
		{ srcTex->GetWidth(), srcTex->GetHeight() });
	ani->AddAnimClip(Dead);

	SAFE_DELETE(srcTex);

	body->SetAnimator(ani);
	body->GetAnimator()->SetCurrentAnimClip(L"IdleD");

	body->SetPosition(position);
	body->SetSize(size);

	body->UpdateWorld();

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
		type = AnimType::Up;
		SetAni(type);
		moveU = true;
		position.y += MoveSpd * Time::Delta();
		if (Keyboard::Get()->Press('S') && moveD == false) {
			type = AnimType::Up;
			SetAni(type);
			position.y += MoveSpd * Time::Delta();
		}
	}
	if (Keyboard::Get()->Up('W')) {
		moveU = false;
		type = AnimType::IdleU;
		SetAni(type);
	}

	else if (Keyboard::Get()->Press('S')) {
		type = AnimType::Down;
		SetAni(type);
		moveD = true;
		position.y -= MoveSpd * Time::Delta();
		if (Keyboard::Get()->Press('W') && moveU == false) {
			type = AnimType::Up;
			SetAni(type);
			position.y += (MoveSpd * 2) * Time::Delta();
		}
	}
	if (Keyboard::Get()->Up('S')) {
		type = AnimType::IdleD;
		SetAni(type);
		moveD = false;
	}

	if (Keyboard::Get()->Press('D') && moveU == false && moveD == false) {
		type = AnimType::Right;
		SetAni(type);
		moveR = true;
		position.x += MoveSpd * Time::Delta();
		if (Keyboard::Get()->Press('A') && moveL == false) {
			type = AnimType::Left;
			SetAni(type);
			position.x -= (MoveSpd * 2) * Time::Delta();
		}
	}
	if (Keyboard::Get()->Up('D')) {
		type = AnimType::IdleR;
		SetAni(type);
		moveD = false;
	}

	else if (Keyboard::Get()->Press('A') && moveU == false && moveD == false) {
		type = AnimType::Up;
		SetAni(type);
		moveL == true;
		position.x -= MoveSpd * Time::Delta();
	}
	if (Keyboard::Get()->Up('A')) {
		type = AnimType::IdleL;
		SetAni(type);
		moveL = false;
	}

	if (Keyboard::Get()->Press('L')) {
		if (type == AnimType::IdleD || type == AnimType::Down) type = AnimType::AttD;
		else if (type == AnimType::IdleU || type == AnimType::Up) type = AnimType::AttU;
		else if (type == AnimType::IdleL || type == AnimType::Left) type = AnimType::AttL;
		else if (type == AnimType::IdleR || type == AnimType::Right) type = AnimType::AttR;
		SetAni(type);
		bDef = false;
		Attack();
	}

	if (Keyboard::Get()->Up('L')) bDef = true;
}

void Player::SetAni(AnimType type)
{
	switch (type) {
	// Idle
	case AnimType::IdleD:{
		body->GetAnimator()->SetCurrentAnimClip(L"IdleD");
	}break;

	case AnimType::IdleU:{
		body->GetAnimator()->SetCurrentAnimClip(L"IdleU");
	}break;

	case AnimType::IdleL:{
		body->GetAnimator()->SetCurrentAnimClip(L"IdleL");
	}break;

	case AnimType::IdleR:{
		body->GetAnimator()->SetCurrentAnimClip(L"IdleR");
	}break;

	// Move
	case AnimType::Down:{
		body->GetAnimator()->SetCurrentAnimClip(L"MoveD");
	}break;

	case AnimType::Up:{
		body->GetAnimator()->SetCurrentAnimClip(L"MoveU");
	}break;

	case AnimType::Left:{
		body->GetAnimator()->SetCurrentAnimClip(L"MoveL");
	}break;

	case AnimType::Right:{
		body->GetAnimator()->SetCurrentAnimClip(L"MoveR");
	}break;

	// Att
	case AnimType::AttD:{
		body->GetAnimator()->SetCurrentAnimClip(L"AttD");
	}break;

	case AnimType::AttU:{
		body->GetAnimator()->SetCurrentAnimClip(L"AttU");
	}break;

	case AnimType::AttL:{
		body->GetAnimator()->SetCurrentAnimClip(L"AttL");
	}break;

	case AnimType::AttR:{
		body->GetAnimator()->SetCurrentAnimClip(L"AttR");
	}break;

	// Item
	case AnimType::Item:{
		body->GetAnimator()->SetCurrentAnimClip(L"Item");
	}break;

	// Dead
	case AnimType::Dead:{
		body->GetAnimator()->SetCurrentAnimClip(L"Dead");
	}break;
	
	default:
		break;
	}
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
