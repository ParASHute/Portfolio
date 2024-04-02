#pragma once
// ���� �����Լ��� �ִ� �������̽� Ŭ�� �̸� ���� ���ڸ��� I�� �ٿ� ǥ��
// �������̴� ��� �Լ��� ���� �����Լ��� Ư¡�� �ְ�
// �������̽��� ��� �޴� ��� �ڽ� ��ü�� �ݵ�� �θ�ü�� ��� �Լ��� ������ ������ ��üȭ ��ų�� ����
// CPU���� ��ī���� ���̴������ ������ ����
// ���̴� ���۰� ������ �����͸� IShader�� ����� ������ ó���� �̶� �����ϸ� ���ϴ�.

class IShader {
public:
	// ����
	virtual void Create(const wstring path, const string entryName) = 0;

	// ��ü �ʱ�ȭ
	virtual void Clear() = 0;

	// ���̴��� ����
	virtual void SetShader() = 0;

protected:
	void CompileShader(wstring path, string entryName, string profile,
		ID3DBlob** blob);

	wstring path = L"";		// ������ ���
	string entryName = "";	// ���� ��� (vs�� ������ ps�� ������)

private:
	// �̰� �ۺ��̳� ������Ƽ��� �ö� �ܺ� �Ǵ� �ڽ��� ���� �����ϸ� �ַ��� �����Ҽ� �ֱ� ����
	void CheckShaderError(HRESULT hr, ID3D10Blob* error);
};