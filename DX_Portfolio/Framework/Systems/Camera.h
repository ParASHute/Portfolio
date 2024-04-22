#pragma once

#include "Skeleton/TextureRect.h"

class Camera : public SingletonBase<Camera> {
public:
	friend SingletonBase<Camera>;

	void Update();
	void Render();

	void Move();
	void UpdateView();

	const Vector3 GetPosition() { return position; }
	const Vector3 GetMPosition();	// ���콺 ��ġ

	void Setposition(Vector3 position) { this->position = position; }
	
	void SetTarget(TextureRect* target) { this->target = target; }
	void DelTartget() { this->target = nullptr; }
	TextureRect* GetTarget() { return target; }

private:
	Camera();
	~Camera();

private:
	VPBuffer* vpb = nullptr;
	Matrix view, proj;

	Vector3 position = Values::ZeroVec3;

	bool bMove = false;
	float moveSpd = 100.0;

	// �̰� Ÿ������ ī�޶� ���� �ٴ� ������
	// ���Է�, �÷��̾� ��� ��� ����
	TextureRect* target = nullptr;
};