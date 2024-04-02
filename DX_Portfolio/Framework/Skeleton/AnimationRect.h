#pragma once

#include "TextureRect.h"
#include "Utilities/Animator.h"

class AnimationRect : public TextureRect {
public:
	AnimationRect(Vector3 position, Vector3 size, float rotation = 0.0f);
	~AnimationRect();

	void Upadate();
	void Render();

	BoundingBox* GetCollision() { return collision; }

private:
	Animator* animator = nullptr;

	ID3D11SamplerState* sampler[2];
	ID3D11BlendState* blender[2];
};