#include "Framework.h"
#include "Texture2D.h"

using namespace DirectX; // 여기는 말그대로 여기만 쓰니까 상관 ㄴㄴ

vector<TextureDesc> Textures::descs; // 임시 전역 변수화

Texture2D::Texture2D(wstring filePath)
	:filePath(filePath)
{
	Textures::Load(this); // 생성자에서 만들어짐과 동시에 자기가 자기를 로드 하는거임
}

void Textures::Delet()
{
	for (TextureDesc desc : descs) SAFE_RELEASE(desc.srv);
}

void Textures::Load(Texture2D* texture) { // 텍스쳐2D를 생성하거나 따로 만들때, 해당 데이터를 이용해서 같은 데이터가 있는지 확인하고 없으면 생성
	HRESULT hr;
	TexMetadata metaData;

	// 그림이 가지고 있는 경로의 확장자 추출 (확장자 마다 데이터 추출 방법이 달라서)
	wstring ext = Path::GetExtension(texture->filePath);

	// 거기에 맞춰 데이터 추출하는 가정문
	if (ext == L"tga") {
		hr = GetMetadataFromTGAFile(texture->filePath.c_str(), metaData);
		CHECK(hr);
	}

	else if (ext == L"dds") {
		hr = GetMetadataFromDDSFile(texture->filePath.c_str(), DDS_FLAGS_NONE, metaData);
		CHECK(hr);
	}

	else {
		hr = GetMetadataFromWICFile(texture->filePath.c_str(),WIC_FLAGS_NONE, metaData);
		CHECK(hr);
	}

	// 해당 그림에 너비와 높이를 변수화 
	UINT width = metaData.width;
	UINT height = metaData.height;

	// 텍스쳐2D가 가지고 있는 파일 경로 이미지의 주소, 너비, 높이를 desc에 담음
	TextureDesc desc;
	desc.filePath = texture->filePath;
	desc.height = height;
	desc.width = width;

	TextureDesc exist;
	bool bExist = false;

	// 만약 desc가 새로 만들기 위한 Texture2D의 주소, 너미, 높이가 이미 가지고있는 데이터인지 검사
	for (TextureDesc temp : descs) {
		if (desc == temp) {
			// 주소, 너비 높이가 같은 이미지가 있을경우
			bExist == true;
			exist = temp;	// 이미 있는 데이터를 exsit에 넣기
			break;
		}
	}

	
	if (bExist == true) {	// 택스쳐 데이터가 이미 있다면
		texture->srv = exist.srv;	// 이미 있는 데이터의 srv넣기
		texture->metaData = metaData;
	}

	else { // 전에 만든 택스쳐 데이터가 없다면
		ScratchImage image;	// 이미지 파일로 부터 텍스쳐 데이터를 추출하는데 사용(이미지 차체를 추출)

		if (ext == L"tga") {
			hr = LoadFromTGAFile(texture->filePath.c_str(), &metaData, image);
			CHECK(hr);
		}

		else if (ext == L"dds") {
			hr = LoadFromDDSFile(texture->filePath.c_str(),DDS_FLAGS_NONE, &metaData, image);
			CHECK(hr);
		}

		else {
			hr = LoadFromWICFile(texture->filePath.c_str(),WIC_FLAGS_NONE, &metaData, image);
			CHECK(hr);
		}

		ID3D11ShaderResourceView* srv = nullptr;
		hr = CreateShaderResourceView(DEVICE, image.GetImages(), image.GetImageCount(), metaData, &srv);
		CHECK(hr);

		desc.srv = srv;
		texture->srv = srv;
		texture->metaData = metaData;

		descs.push_back(desc);
	}
} // 까지가 그럼 불러오기

void Texture2D::ReadPixel(vector<Color>* pixels)
{
	ID3D11Texture2D* texture;
	srv->GetResource((ID3D11Resource**)&texture);

	ReadPixel(texture, pixels);
}

void Texture2D::ReadPixel(ID3D11Texture2D* texture, vector<Color>* pixels)
{
	// 원본 택스쳐 정보
	D3D11_TEXTURE2D_DESC srvDesc;
	texture->GetDesc(&srvDesc);

	// 원본 텍스쳐 복사본
	D3D11_TEXTURE2D_DESC destDesc;
	ZeroMemory(&destDesc, sizeof(D3D11_TEXTURE2D_DESC));

	// 복사본 desc설정
	destDesc.Usage = D3D11_USAGE_STAGING;
	destDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	destDesc.Width = srvDesc.Width;
	destDesc.Height = srvDesc.Height;
	destDesc.MipLevels = 1;
	destDesc.ArraySize = 1;
	destDesc.Format = srvDesc.Format;
	destDesc.SampleDesc = srvDesc.SampleDesc;

	ID3D11Texture2D* destTex = nullptr;

	HRESULT hr = DEVICE->CreateTexture2D(&destDesc, nullptr, &destTex);
	CHECK(hr);

	// 원본 texture를 복사본인 destTex에 넣음
	D3DX11LoadTextureFromTexture(DC, texture, nullptr, destTex);

	UINT* colors = new UINT[destDesc.Width * destDesc.Height];

	D3D11_MAPPED_SUBRESOURCE subRe;
	DC->Map(destTex, 0, D3D11_MAP_READ, 0, &subRe);
	{
		// 그림의 픽셀 색상을 전부 추출
		memcpy(colors, subRe.pData, sizeof(UINT) * destDesc.Width * destDesc.Height);
	}
	DC->Unmap(destTex, 0);

	// 이미지의 가로 * 세로 == 픽셀 개수
	int pixelNum = destDesc.Width * destDesc.Height;

	// OoenGL과의 호환을 위한 색상위치 수정
	{
		UINT* alpha = new UINT[pixelNum];
		UINT* red = new UINT[pixelNum];
		UINT* green = new UINT[pixelNum];
		UINT* blue = new UINT[pixelNum];

		for (int i = 0; i < pixelNum; i++) {
			alpha[i]	= (colors[i] & 0xFF000000);
			red[i]		= (colors[i] & 0x00FF0000);
			green[i]	= (colors[i] & 0x0000FF00);
			blue[i]		= (colors[i] & 0x000000FF);

			//OpenGL == !RGBA && OpenGL == ABGR 
			red[i] = colors[i] >> 16;
			blue[i] = colors[i] << 16;

			colors[i] = alpha[i] | red[i] | green[i] | blue[i];
		}

		pixels->assign(&colors[0], &colors[pixelNum - 1]);
	}

	SAFE_DELETE_ARRAY(colors);
	SAFE_DELETE(destTex);
}