#include "Framework.h"
#include "Monster.h"

Monster::Monster(Vector3 position, Vector3 size, MonsterType type, float rotation)
	:position(position), size(size), type(type)
{
	body = new AnimationRect(position, size);

	switch (type) {

	case MonsterType::BlueSmlime: {
		Texture2D* srcTex = new Texture2D(TexturePath + L"Monster/slime.png");

		AnimationClip* Idle = new AnimationClip(L"Idle", srcTex, 5, 
			Values::ZeroVec2, 
			{ srcTex->GetWidth(),(srcTex->GetWidth() * 0.2f) });
		AnimationClip* Move = new AnimationClip(L"Move", srcTex, 5, 
			{ srcTex->GetWidth(),(srcTex->GetWidth() * 0.2f) }, 
			{ srcTex->GetWidth(),(srcTex->GetWidth() * 0.2f) * 3 });
		AnimationClip* Hitted = new AnimationClip(L"Hitted", srcTex, 5, 
			{ srcTex->GetWidth(),(srcTex->GetWidth() * 0.2f) * 3},
			{ srcTex->GetWidth(),(srcTex->GetWidth() * 0.2f) * 4 });
		AnimationClip* Die = new AnimationClip(L"Die", srcTex, 5, 
			{ srcTex->GetWidth(),(srcTex->GetWidth() * 0.2f) * 4}, 
			{ srcTex->GetWidth(),(srcTex->GetWidth() * 0.2f) * 5 });

		Animator* ani = new Animator();
		ani->AddAnimClip(Idle);
		ani->AddAnimClip(Move);
		ani->AddAnimClip(Hitted);
		ani->AddAnimClip(Die);

		body->SetAnimator(ani);
		body->GetAnimator()->SetCurrentAnimClip(L"Idle");

		SAFE_DELETE(srcTex);

		body->SetPosition(position);
		body->SetSize(size);

		body->UpdateWorld();
	} break;

	case MonsterType::PurpleSlime: {

	} break;

	case MonsterType::Orc: {

	} break;

	case MonsterType::Skeleton: {

	} break;

	case MonsterType::Boss: {

	} break;

	default:
		break;
	}
}

Monster::~Monster()
{
}

void Monster::Update()
{
}

void Monster::Render()
{
}

void Monster::Move()
{
}

void Monster::Attack()
{
}

void Monster::GUI()
{
}

string Monster::MakeLable(string lable)
{
	return string();
}
