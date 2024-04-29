#include "stdafx.h"
#include "Program.h"

#include "Systems/Window.h"

#include "MakeMap/MakeMap.h"

#include "TestScene/00_PlayerTest/PlayerTest_Spear.h"
#include "TestScene/01_PlayerAnimationTest/01_PlayerAnimationTest.h"

void Program::Init()
{
	States::Create();
	Camera::Create();

	// CreatBuffer
	{
		vpb = new VPBuffer();

		// view ��� ����
		{
			D3DXMatrixLookAtLH(
				&view,
				&Vector3(0, 0, 0),	// cam pos
				&Vector3(0, 0, 1),	// cam Look at
				&Vector3(0, 1, 0)	// cam's top
			);

			vpb->SetView(view);
		}
	}

	// prohection matrix
	{
		D3DXMatrixOrthoOffCenterLH(
			&proj,
			0.0f,					// ���� ��				// x coord Min
			(float)WinMaxWidth,		// ���� ��				// x coord Max
			0.0f,					// ���ϴ�				// y coord Min
			(float)WinMaxHeight,	// �ֻ��				// y coord Max
			0, 1					// �ּ� ����, �ִ� ����	// z coord Min, Max
		);
		vpb->SetProj(proj);
	}

	// DemoSetting
	{
		//Push(new MakeMap);	
		
		//Push(new SpearPlayerTest);
		Push(new PlayerAnimationTest);
	}
}

void Program::Destroy()
{
	SAFE_DELETE(vpb);

	for (IObject* obj : objs)
	{
		obj->Destroy();
		SAFE_DELETE(obj);
	}
}

void Program::Update()
{
	for (IObject* obj : objs)
		obj->Update();
}

void Program::Render()
{
	vpb->SetVSBuffer(1);

	for (IObject* obj : objs)
		obj->Render();
}

void Program::PostRender()
{

	for (IObject* obj : objs)
		obj->PostRender();
}

void Program::GUI()
{
	for (IObject* obj : objs)
	{
		obj->GUI();
	}
}

void Program::Push(IObject* obj)
{
	objs.push_back(obj);
	obj->Init();
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR param, int command)
{
	srand((UINT)time(NULL));

	DXDesc desc;
	desc.AppName = L"D2DGame";
	desc.instance = instance;
	desc.handle = NULL;
	desc.width = WinMaxWidth;
	desc.height = WinMaxHeight;

	Program* program = new Program();
	Window* window = new Window(desc);
	WPARAM wParam = window->Run(program);

	SAFE_DELETE(window);
	SAFE_DELETE(program);

	return wParam;

}
