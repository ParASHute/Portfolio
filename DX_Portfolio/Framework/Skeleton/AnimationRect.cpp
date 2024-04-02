#include "Framework.h"
#include "AnimationRect.h"

AnimationRect::AnimationRect(Vector3 position, Vector3 size, float rotation)
	:TextureRect(position,size,rotation)
{
	SetShader(ShaderPath + L"VertexTexture.hlsl");

	animator = new Animator();

	// 애니 클립 제작 및 저장
	{
		Texture2D* srcTex = new Texture2D(TexturePath + L"SampleSheet.png");
		
		AnimationClip* RunD = new AnimationClip(
			L"RunD", srcTex, 4, Values::ZeroVec2,
			{ srcTex->GetWidth() * 0.5f, srcTex->GetHeight() * 0.125f }
		);

		animator->AddAnimClip(RunD);

		SAFE_DELETE(srcTex);
	}
	
	animator->SetCurrentAnimClip(L"RunD");

	// Sampler
	{
		D3D11_SAMPLER_DESC desc;
		States::GetSamplerDesc(&desc);
		States::CreateSampler(&desc, &sampler[0]);

		// 선형보간
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		States::CreateSampler(&desc, &sampler[1]);
	}

	//Blend
	{
		D3D11_BLEND_DESC desc;
		States::GetBlendDesc(&desc);
		States::CreateBlend(&desc, &blender[0]);

		desc.RenderTarget[0].BlendEnable = true;
		States::CreateBlend(&desc, &blender[1]);
	}
}

AnimationRect::~AnimationRect()
{
	// SAFE_DELET(animator);
}

void AnimationRect::Upadate()
{
	animator->Update();

	DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subRe);
	{ 

	}
	DC->Unmap(vb->GetResource(), 0);
}

void AnimationRect::Render()
{

}
