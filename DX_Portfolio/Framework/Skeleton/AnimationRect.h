#pragma once

#include "TextureRect.h"
#include "Utilities/Animator.h"

enum class AnimType
{
	DOWN = 0,
	LEFT_DOWN,
	LEFT
};

class AnimationRect : public TextureRect {
public:
	AnimationRect(Vector3 position, Vector3 size, float rotation = 0.0f);
	~AnimationRect();

	void Update();
	void Render();

	Animator* GetAnimator() { return animator; }
	void SetAnimator(Animator* animator);

private:
	Animator* animator = nullptr;

	ID3D11SamplerState* sampler[2];
	ID3D11BlendState* blend[2];

	AnimType animType = AnimType::LEFT;
};