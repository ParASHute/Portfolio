#include "Framework.h"
#include "IShader.h"

void IShader::CompileShader(wstring path, string entryName, string profile, ID3DBlob** blob)
{
	ID3DBlob* error = nullptr;
	HRESULT hr = D3DCompileFromFile(
		path.c_str(),					// ���̴� ���� ���
		nullptr,						// ���̴� ������ ����� ��Ÿ�� ������
		nullptr,						// ����� ������ �ٸ� ������ ������
		entryName.c_str(),				// ������ ��ġ (�ַ� vs �Ǵ� ps) 
		profile.c_str(),				// ������ ���Ͽ��� ����� ������ �̸�
		D3DCOMPILE_ENABLE_STRICTNESS,	// ������ ��� �����ɼ� / �޼��� ������ 1�� ����
		0,								// ����� ������ ���Ե� ������ ��� ���� ��ġ
		blob,							// ������ ����� ������ ���
		&error							// ������ ���� �޼����� ������ ���
	);

	CheckShaderError(hr, error);

	SAFE_RELEASE(error);
}

void IShader::CheckShaderError(HRESULT hr, ID3D10Blob* error)
{
	// HRESULT�� �����Ұ��(���Ͽ��� �����͸� �̾ƿ��µ�)
	if (FAILED(hr)) {
		// ������ ������ ��� 
		if (error) {
			// ������ ���̴��� ���° �ٿ��� ���� ������ Ȯ��
			string str = (const char*)error->GetBufferPointer();

			// ������ ��ġ�� ���̴� ������� �˷��� ���ڸ� Ȯ�� ��ư�� �Ա� ���
			MessageBoxA(handle, str.c_str(), "Shader Error", MB_OK);
		}

		CHECK(false);
	}
}
