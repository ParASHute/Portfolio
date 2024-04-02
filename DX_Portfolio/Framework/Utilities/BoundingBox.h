#pragma once

enum {
	x = 0,
	y
};

struct RectEdge
{
	Vector3 LT;
	Vector3 LB;
	Vector3 RT;
	Vector3 RB;
};

struct AxisData {
	Vector3 centerPos;	// �� �߾�
	Vector3 axisDir[2]; // ����� (x,y��)
	float axisLen[2];	// ����� (x,y��)
};

class BoundingBox
{
public:
	BoundingBox();
	~BoundingBox();

	void UpdateCollisionData(const Matrix World,
		const Vector3 verticesLocalPositino[]);

	static bool AABB(BoundingBox* a, BoundingBox* b);
	static bool OBB(BoundingBox* a, BoundingBox* b);

private:
	RectEdge* edge = nullptr;
	AxisData* data = nullptr;

};
