#include "Framework.h"
#include "ShadedTexture.h"

ShadedTexture::ShadedTexture(Vector3 position, Vector3 size, float rotation, wstring path)
	:TextureRect(position,size,rotation,path)
{
	sb = new ShadedBuffer();
	sb->SetTextureSize(Vector2(size.x, size.y));
	SetShader(ShaderPath + L"TextureShader.hlsl");
}

ShadedTexture::~ShadedTexture()
{
	SAFE_DELETE(sb);
}

void ShadedTexture::Update()
{
	__super::Update();
	// __super�� �θ𲨸� ��밡��
}

void ShadedTexture::Render()
{
	sb->SetPSBuffer(0);
	__super::Render();
}

void ShadedTexture::GUI()
{
	ImGui::Begin("Shaded");
	{
		// ���״�� ���� ó�� ��ư 1���� ���� �ְԲ� ���ִ� ��
		ImGui::RadioButton("Normal", sb->GetSelecttionPtr(),1);
		ImGui::RadioButton("Gray", sb->GetSelecttionPtr(), 2);
		ImGui::RadioButton("Negative", sb->GetSelecttionPtr(), 3);
		ImGui::RadioButton("Blur", sb->GetSelecttionPtr(), 4);
		ImGui::RadioButton("pivotRL", sb->GetSelecttionPtr(), 5);
		ImGui::RadioButton("PivotUD", sb->GetSelecttionPtr(), 6);
		ImGui::SliderInt("BlurCounter", sb->GetBlurCountPtr(), 1 ,20);
	}
	ImGui::End();
}