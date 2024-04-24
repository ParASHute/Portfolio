#include "Framework.h"
#include "Texture2D.h"

using namespace DirectX;
vector<TextureDesc> Textures::descs;

Texture2D::Texture2D(wstring filePath)
	:filePath(filePath)
{
	Textures::Load(this);
}

void Textures::Delete()
{
	for (TextureDesc desc : descs)
		SAFE_RELEASE(desc.srv);
}

// �ؽ�ó2D�� �����ϰų� ���� ���鶧 �ش� texture2D�� �����͸� �̿��ؼ�
// �̹� �ش� �׸��� �����Ͱ� �ִ��� Ȯ���ϰ� ���ٸ� ����� �Լ�
void Textures::Load(Texture2D* texture)
{
	HRESULT hr;
	TexMetadata metaData;

	// �׸��� �������ִ� ����� Ȯ���� ����
	// Ȯ���ڿ� ���� �׸� ������ ���� �Լ� ȣ��
	wstring ext = Path::GetExtension(texture->filePath);
	if (ext == L"tga")
	{
		hr = GetMetadataFromTGAFile(texture->filePath.c_str(), metaData);
		CHECK(hr);
	}
	else if (ext == L"dds")
	{
		hr = GetMetadataFromDDSFile(texture->filePath.c_str(),
			DDS_FLAGS_NONE, metaData);
		CHECK(hr);
	}
	else {
		hr = GetMetadataFromWICFile(texture->filePath.c_str(), WIC_FLAGS_NONE, metaData);
		CHECK(hr);
	}

	// �ش� �׸��� �ʺ�� ���̸� ����ȭ
	UINT width = metaData.width;
	UINT height = metaData.height;

	// Texture2D�� �������ִ� ���� ��� �̹�����
	// �ּ�, �ʺ�, ���̸� desc�� ����
	TextureDesc desc;
	desc.filePath = texture->filePath;
	desc.width = width;
	desc.height = height;

	TextureDesc exist;
	bool bExist = false;

	// ���� �̹� �������ִ� descs�� �̹��� ����� �ϴ� Texture2D��
	// �ּ�, �ʺ�, ���̰� ���� �̹��� �����Ͱ� �̹� �ִ��� �˻�
	for (TextureDesc temp : descs)
	{
		if (desc == temp)
		{
			// �ּ�, �ʺ�, ���̰� ���� �̹����� �������
			bExist = true;
			exist = temp; // �̹� �ִ� �����͸� exist�� �ֱ�
			break;
		}
	}

	// �ؽ�ó �����Ͱ� �̹� �ִٸ�
	if (bExist == true) {
		texture->srv = exist.srv;  // �̹� �ִ� �������� srv �ֱ�
		texture->metaData = metaData;
	}

	// ������ ���� �ؽ��� �����Ͱ� ���ٸ�
	else {
		// �̹��� ���Ϸ� ���� �ؽ�ó �����͸� �����ϴµ� ���
		ScratchImage image;

		if (ext == L"tga") {
			hr = LoadFromTGAFile(texture->filePath.c_str(), &metaData, image);
			CHECK(hr);
		}
		else if (ext == L"dds") {
			hr = LoadFromDDSFile(texture->filePath.c_str(),
				DDS_FLAGS_NONE, &metaData, image);
			CHECK(hr);
		}
		else {
			hr = LoadFromWICFile(texture->filePath.c_str(),
				WIC_FLAGS_NONE, &metaData, image);
			CHECK(hr);
		}

		ID3D11ShaderResourceView* srv = nullptr;
		hr = CreateShaderResourceView(DEVICE, image.GetImages(),
			image.GetImageCount(), metaData, &srv);
		CHECK(hr);

		desc.srv = srv;
		texture->srv = srv;
		texture->metaData = metaData;

		descs.push_back(desc);
	}
}

void Texture2D::ReadPixel(vector<Color>* pixels)
{
	ID3D11Texture2D* texture;
	srv->GetResource((ID3D11Resource**)&texture);

	ReadPixel(texture, pixels);
}

void Texture2D::ReadPixel(ID3D11Texture2D* texture, vector<Color>* pixels)
{
	// ���� �ؽ��� ����
	D3D11_TEXTURE2D_DESC srvDesc;
	texture->GetDesc(&srvDesc);

	// ���� ������ ���纻
	D3D11_TEXTURE2D_DESC destDesc;
	ZeroMemory(&destDesc, sizeof(D3D11_TEXTURE2D_DESC));

	// ���纻 desc ����
	destDesc.Usage = D3D11_USAGE_STAGING;
	destDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	destDesc.Width = srvDesc.Width;
	destDesc.Height = srvDesc.Height;
	destDesc.MipLevels = 1;
	destDesc.ArraySize = 1;
	destDesc.Format = srvDesc.Format;
	destDesc.SampleDesc = srvDesc.SampleDesc;

	ID3D11Texture2D* destTex = nullptr;

	HRESULT hr = DEVICE->CreateTexture2D(&destDesc, nullptr,
		&destTex);
	CHECK(hr);
	// ���� texture�� ���纻�� destTex�� ���� �ִ´�.
	D3DX11LoadTextureFromTexture(DC, texture, nullptr, destTex);

	UINT* colors = new UINT[destDesc.Width * destDesc.Height];

	D3D11_MAPPED_SUBRESOURCE subRe;
	DC->Map(destTex, 0, D3D11_MAP_READ, 0, &subRe);
	{
		// �׸��� �ȼ� ������ ���� ����
		memcpy(colors, subRe.pData, sizeof(UINT) *
			destDesc.Width * destDesc.Height);
	}
	DC->Unmap(destTex, 0);

	// �̹��� ���� * ���� ��, �ȼ� ����
	int pixelNum = destDesc.Width * destDesc.Height;

	// OpenGL�� ȣȯ�Ǳ� ���� ���� ��ġ�� ����
	{
		UINT* alpha = new UINT[destDesc.Width * destDesc.Height];
		UINT* red = new UINT[destDesc.Width * destDesc.Height];
		UINT* green = new UINT[destDesc.Width * destDesc.Height];
		UINT* blue = new UINT[destDesc.Width * destDesc.Height];

		for (int i = 0; i < pixelNum; i++)
		{
			alpha[i] = (colors[i] & 0xFF000000);
			red[i] = (colors[i] & 0x00FF0000);
			green[i] = (colors[i] & 0x0000FF00);
			blue[i] = (colors[i] & 0x000000FF);

			// OpenGL�� ARGB�� �ƴ� ABGR �����̱� ������
			// R�� B�� ��ġ�� �ٲ۴�
			red[i] = colors[i] >> 16;
			blue[i] = colors[i] << 16;

			colors[i] = alpha[i] | red[i] | green[i] | blue[i];
		}
		pixels->assign(&colors[0], &colors[pixelNum - 1]);
	}

	SAFE_DELETE_ARRAY(colors);
	SAFE_DELETE(destTex);
}
