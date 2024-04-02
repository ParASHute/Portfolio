#include "Framework.h"
#include "VertexShader.h"

VertexShader::~VertexShader()
{
	Clear();
}

void VertexShader::Create(const wstring path, const string entryName)
{
	this->path = path;				// ��� �޾ƿ���
	this->entryName = entryName;	// ������ �޾ƿ���

	CompileShader(path, entryName, "vs_5_0", &blob);

	HRESULT hr = DEVICE->CreateVertexShader(
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		nullptr,
		&shader
	);
	CHECK(hr);
}

void VertexShader::Clear()
{
	SAFE_RELEASE(blob);
	SAFE_RELEASE(shader);
}

void VertexShader::SetShader()
{
	DC->VSSetShader(shader, nullptr, 0);
}
