#pragma once

// 이친구는 그림을 더 안전하게 뽑아내는 방법일 뿐, 이걸 통해서 에니매이션을 만든건 아님

struct TextureDesc {
	wstring filePath = L"";
	UINT width = 0;
	UINT height = 0;
	ID3D11ShaderResourceView* srv = nullptr;

	bool operator == (const TextureDesc& other) {
		bool b = true;

		b &= filePath == other.filePath;
		b &= width == other.width;
		b &= height == other.height;
		// 3개중 하나라도 다르면 전부다 false가 리턴되있음
		// srv는 오퍼가 따로 없기 때문에.... 비교불가

		return b;
	}
};

class Texture2D {
public:
	Texture2D(wstring filePath);	// 여기는 택스쳐스 위택생성자라 봐도 무방

	void ReadPixel(vector<Color>* pixels);
	static void ReadPixel(ID3D11Texture2D* texture, vector<Color>* pixels);
	
	ID3D11ShaderResourceView* GetSRV() { return srv; }

	float GetWidth() { return (float)metaData.width; }
	float GetHeight() { return (float)metaData.height; }
	wstring GetFilePath() { return filePath; }

private:
	friend class Textures;

	wstring filePath = L"";
	ID3D11ShaderResourceView* srv = nullptr;
	DirectX::TexMetadata metaData;
};

class Textures {
public:
	static void Delet();	// 여기는 택스쳐2d 위탁소멸바라 봐도 무방


private:
	friend class Texture2D;

	static void Load(Texture2D* texture);
	static vector<TextureDesc> descs;
};