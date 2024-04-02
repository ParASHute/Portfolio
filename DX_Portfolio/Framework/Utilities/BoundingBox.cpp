#include "Framework.h"
#include "BoundingBox.h"

BoundingBox::BoundingBox()
{
	edge = new RectEdge();
	data = new AxisData();
}

BoundingBox::~BoundingBox()
{
	SAFE_DELETE(data);
	SAFE_DELETE(edge);
}

void BoundingBox::UpdateCollisionData(const Matrix world, const Vector3 verticesLocalPositino[])
{
	//AABB
	{
		// local pos -> World pos
		D3DXVec3TransformCoord(&edge->LT, &verticesLocalPositino[3], &world);
		D3DXVec3TransformCoord(&edge->LB, &verticesLocalPositino[0], &world);
		D3DXVec3TransformCoord(&edge->RT, &verticesLocalPositino[1], &world);
		D3DXVec3TransformCoord(&edge->RB, &verticesLocalPositino[2], &world);
	}

	// OBB
	{
		// CenterPos Vector Upadate (�� �߽� Ȯ��)
		{
			data->centerPos = Vector3(
				(edge->LT.x + edge->LB.x + edge->RT.x + edge->RB.x) * 0.25f,	// LT�� RB�� ��� ���� �Ŷ� �������� �̷��� �ϴ°� ������ ������ �����̴�.
				(edge->LT.y + edge->LB.y + edge->RT.y + edge->RB.y) * 0.25f,
				0
			);
		}

		// AxisDir Updata (�� ���� Ȯ��)
		{
			// �븻�� �� �Լ� ��κ��� ����ȭ �ϴ� �Լ��̴�
			// ����ȭ�� ��� ���� 0 ~ 1 �� �ٲٴ� �����̴�.
			D3DXVec3TransformNormal(&data->axisDir[x],
				&Vector3(1, 0, 0), &world);

			D3DXVec3TransformNormal(&data->axisDir[y],
				&Vector3(0, 1, 0), &world);

			D3DXVec3Normalize(&data->axisDir[x], &data->axisDir[x]);
			D3DXVec3Normalize(&data->axisDir[y], &data->axisDir[y]);
		}

		// AxisLen Updata(�� ���� ���ϱ� // ������ ���� ���ü��� �ֱ� �����̴�.)
		{
			Vector3 unitAxis[2] = {
				data->axisDir[x], data->axisDir[y]
			};

			Vector3 verticesPos[4] = {
				edge->LT, edge->LB, edge->RB, edge->RT
			};

			float minValuse[2] = {
				INT_MAX, INT_MAX
			};

			float maxValuse[2] = {
				INT_MIN, INT_MIN
			};

			for (int i = 0; i < 4; i++) {
				Vector3 point = verticesPos[i];

				for (int j = 0; j < 2; j++) {
					float projection =
						D3DXVec3Dot(&point, &unitAxis[j]);

					// �簢���� ������ �ִ� x,y���� �ּҰ� / �ִ밪 ã��
					if (projection < minValuse[j]) minValuse[j] = projection;
					if (projection > maxValuse[j]) maxValuse[j] = projection;
				}
			}
			data->axisLen[x] = (maxValuse[x] - minValuse[x]) * 0.5f;
			data->axisLen[y] = (maxValuse[y] - minValuse[y]) * 0.5f;
		}
	}
}

bool BoundingBox::AABB(BoundingBox* a, BoundingBox* b)
{
	if(a == nullptr || b == nullptr ) return false;
	RectEdge aEdge = *a->edge;
	RectEdge bEdge = *b->edge;

	/*
		ȸ������ ���� �簢������ �浹�� ������ �簢���� ����
		���� ū XY�� �������� XY�� ���ϴ� ������ �����ϴ�.

		�ֿ� ������ �޸��� ����
	*/

	if (aEdge.LT.x <= bEdge.RB.x &&
		aEdge.LT.y >= bEdge.RB.y &&
		aEdge.RB.x >= bEdge.LT.x &&
		aEdge.RB.y <= bEdge.LT.y)
		return true;

	return false;
}

bool BoundingBox::OBB(BoundingBox* a, BoundingBox* b)
{
	AxisData ad = *a->data;
	AxisData bd = *b->data;

	Vector3 centerDir, axis;
	float centerProjDist, r1, r2;

	// a�� b ������ �Ÿ�
	centerDir = ad.centerPos - bd.centerPos;

	// a�� x��
	{
		axis = ad.axisDir[x];

		// ���� ���� ���� �Ÿ� 
		centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

		r1 = ad.axisLen[x];
		r2 = abs(D3DXVec3Dot(&bd.axisDir[x], &axis) * bd.axisLen[x])
			+ abs(D3DXVec3Dot(&bd.axisDir[y], &axis) * bd.axisLen[y]);

		if (centerProjDist > r1 + r2)return false;
	}

	// a�� y��
	{
		axis = ad.axisDir[y];

		// ���� ���� ���� �Ÿ� 
		centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

		r1 = ad.axisLen[y];
		r2 = abs(D3DXVec3Dot(&bd.axisDir[x], &axis) * bd.axisLen[x])
			+ abs(D3DXVec3Dot(&bd.axisDir[y], &axis) * bd.axisLen[y]);

		if (centerProjDist > r1 + r2)return false;
	}

	// b�� x��
	{
		axis = bd.axisDir[x];

		// ���� ���� ���� �Ÿ� 
		centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

		r1 = bd.axisLen[x];
		r2 = abs(D3DXVec3Dot(&ad.axisDir[x], &axis) * ad.axisLen[x])
			+ abs(D3DXVec3Dot(&ad.axisDir[y], &axis) * ad.axisLen[y]);

		if (centerProjDist > r1 + r2)return false;
	}

	// a�� y��
	{
		axis = bd.axisDir[y];

		// ���� ���� ���� �Ÿ� 
		centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

		r1 = bd.axisLen[y];
		r2 = abs(D3DXVec3Dot(&ad.axisDir[x], &axis) * ad.axisLen[x])
			+ abs(D3DXVec3Dot(&ad.axisDir[y], &axis) * ad.axisLen[y]);

		if (centerProjDist > r1 + r2)return false;
	}

	return true;
}
