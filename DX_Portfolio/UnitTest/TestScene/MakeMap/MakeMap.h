#pragma once

#include "Map/TMap.h"
#include "Utilities/FileStream.h"

class MakeMap : public IObject {
	// IObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUI() override;

private:
	TMap* Map = nullptr;
};