#pragma once

#include "GameSources/Classes/Player.h"

class PlayerAnimationTest : public IObject{
public:
	// IObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUI() override;

private:
	Player* player = nullptr;
};