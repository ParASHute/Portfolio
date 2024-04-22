#include "Framework.h"
#include "Camera.h"

Camera::Camera()
{
	vpb = new VPBuffer();
	
	// View ��� ����
	{
		D3DXMatrixLookAtLH
		(
			&view,
			&Vector3(0, 0, 0),	 // ī�޶� ��ġ
			&Vector3(0, 0, 1),	 // ī�޶� ���� ����
			&Vector3(0, 1, 0)	 // ī�޶��� ���� ����
		);
	
		vpb->SetView(view);
	}
	
	// projection ��� ����
	{
		D3DXMatrixOrthoOffCenterLH
		(
			&proj,
			0.0f,				// ���� ��		// x��ǥ �ּ�
			(float)WinMaxWidth,	// ������ ��		// x��ǥ �ִ�
			0.0f,				// �� �Ʒ�		// y��ǥ �ּ�
			(float)WinMaxHeight,// �� ��			// y��ǥ �ִ�
			0,					// �ּ� ����		// z��ǥ �ּ�
			1					// �ִ� ����		// z��ǥ �ִ�
		);
	
		vpb->SetProj(proj);
	}
} // Program���� ������

Camera::~Camera()
{
	SAFE_DELETE(vpb);
}


void Camera::Update()
{
	Move();
	UpdateView();
}

void Camera::Render()
{
	vpb->SetVSBuffer(1);
}

void Camera::Move()
{
	// Ÿ�� ��
	if (target != nullptr) {
		// position.x = target->GetPosition().x; -> �ȵ�(��Ʈ�� �߽��� ����� �߽�, ī�޶�� ���ϴ��� �߽� �׷��� �ȵ�)
		position.x = target->GetPosition().x - (WinMaxWidth * 0.5f);
		position.y = target->GetPosition().y - (WinMaxHeight * 0.5f);
	}

	else {
		// F3������ ������ ���� ���� �����ϸ��
		// ���� ����, ������ ������ �����
		if (Keyboard::Get()->Down(VK_F3)) bMove = !bMove;
		
		if (bMove) {
			if (Keyboard::Get()->Press('W')) position.y += moveSpd * Time::Delta();
			else if (Keyboard::Get()->Press('S')) position.y -= moveSpd * Time::Delta();
			
			if (Keyboard::Get()->Press('A')) position.x -= moveSpd * Time::Delta();
			else if (Keyboard::Get()->Press('D')) position.x += moveSpd * Time::Delta();
		}
		
	}
}

void Camera::UpdateView()
{
	D3DXMatrixLookAtLH
	(
		&view,
		&position,	 // ī�޶� ��ġ
		&(position + Vector3(0, 0, 1)),	 // ī�޶� ���� ����
		&Vector3(0, 1, 0)	 // ī�޶��� ���� ����
	);

	vpb->SetView(view);

}

const Vector3 Camera::GetMPosition()
{
	Vector3 MPos = Mouse::Get()->GetPosition();
	
	MPos += position;

	return MPos;
}