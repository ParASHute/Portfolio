#include "Framework.h"
#include "Obstacle.h"

Obstacle::Obstacle(Vector3 position, Vector3 size, float rotation)
{
	Image = new TextureRect(position, size);
}

Obstacle::~Obstacle()
{
	SAFE_DELETE(Image);
}

void Obstacle::SetImage(OBSTACLE type)
{
	switch (type) {
	case OBSTACLE::TREE: {
		Image->SetImage(TexturePath + L"³ª¹«");
	} break;

	case OBSTACLE::WATER: {
		Image->SetImage(TexturePath + L"¹°");
	} break;

	case OBSTACLE::BREAKABLE: {
		Image->SetImage(TexturePath + L"¾ð´ö");
	} break;

	default:
		break;
	}
}
