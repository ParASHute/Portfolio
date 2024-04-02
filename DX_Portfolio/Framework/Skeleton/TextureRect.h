#pragma once

class TextureRect {
public:
	TextureRect(Vector3 position, Vector3 size, float rotation = 0.0f);

	// ����� �̹��� ��ΰ� �ִ� ���
	TextureRect(Vector3 position, Vector3 size, float rotation, wstring path);

	// �Ҹ��ڴ� ������ ����� �ִϸ��̼� Ŭ�󽺺��� ������ �̰����� ����ϱ� ������ �����Լ��� ����
	virtual ~TextureRect();

	void Update();
	void Render();
	void Gui();

	void UpdateWorld();

	void SetPosition(Vector3 position) { this->position = position; }
	Vector3 GetPosition() { return position; }

	void SetSize(Vector3 size) { this->size = size; }
	Vector3 GetSize() { return size; }


	// �׸� �ؼ��ϰ� ���̴� ���� �ǳ��� ����
	void SetSRV(ID3D11ShaderResourceView* srv) { this->srv = srv; }
	void SetShader(wstring shaderPath);
	void SetImage(wstring imagePath);

	BoundingBox* GetCollision() { return collision; }

protected:
	// ������ VertexColor������ color�� ���� �ǹ̿��� Texture�� ����
	vector<VertexTexture> vertices;	
	VertexBuffer* vb = nullptr;
	
	vector<UINT> indices;
	IndexBuffer* ib = nullptr;

	InputLayout* il = nullptr;

	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	WorldBuffer* wb = nullptr;
	D3DXMATRIX world;
	D3DXMATRIX S, R, T;

	Vector3 position;
	Vector3 size;
	float rotation;

	// Color color = Color(1, 0, 0, 1); -> �츮�� �׸������� ����� ���̱� ������ ��� ����
	ID3D11ShaderResourceView* srv = nullptr;
	ID3D11RasterizerState* rs = nullptr;

	bool bOpen = true;

	RectEdge* edge = nullptr;
	BoundingBox* collision = nullptr;

	Vector3 verticesPosition[4];

	string Name;

	// �̵� üũ
	bool moveD = false; // �Ʒ��� �����̴���
	bool moveR = false;	// ���� �����̴���
	bool moveU = false; // ���� ������
	bool G = true; // �߷� ����

	// �̴� ���� ������ ���� ī����
	//int countJump = 0; 

	float TimeDelta = 0;
	float GravityTime;


	D3D11_MAPPED_SUBRESOURCE subRe;
};