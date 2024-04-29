#pragma once

#include "Map/TMap.h"
#include "Utilities/FileStream.h"

class Border : public IObject {
public:
	// IObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUI() override;

private:
	TMap* GrassLandBorderDown = nullptr;
	TMap* GrassLandBorderLeft = nullptr;
	TMap* GrassLandBorderRight = nullptr;
	TMap* GrassLandBorder = nullptr;
};