#pragma once

// (�ܻ�)�簢�� ��ü ��� ��ü
class Rect {
public:
	// ��ü ��ġ, ũ��, ȸ��
	Rect(Vector3 position, Vector3 size, float rotation = 0.0f);
	~Rect();

	// �� ������ ���� ����� �����
	void Update();

	// �� ������ ���� �׸��� �׸��� �ڵ��
	void Render();

	void Move(); // ����

	void GUI();	// UIâ ����
	
	void UpdateColor();
	string MakeLable(string lable);

	void UpdateWorld();
	void SetColor(Color color);
	// �̰� ���� �ΰ��� ����

	BoundingBox* GetCollision() { return collision; }
	
	Vector3 GetSize() { return size; }
	void SetSize(Vector3 size) { this->size = size; }

	Vector3 GetPosition() { return position; }
	void SetPosition(Vector3 pos) { this->position = pos; }

private:
	// ������ �����͵� (�簢���̴ϱ� 4�� �ʿ��ؼ� ���ͷ� ����)
	vector<VertexColor> vertices;
	VertexBuffer* vb = nullptr;

	// �ﰢ�� �׸��� ����
	vector<UINT> indices;
	IndexBuffer* ib = nullptr;

	// ������ ������ �ؼ����
	InputLayout* il = nullptr;

	// �׸��� �׸� �����͵�
	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	WorldBuffer* wb = nullptr;			// ������ GPU�� �Ѱ��� ����
	D3DXMATRIX world;					// �ν��� ����
	D3DXMATRIX S, R, T;					// ������ �ش� ��ü�� ũ��, ȸ��, ����

	Vector3 position;					// ��ǥ
	Vector3 size;						// ũ��
	float rotation;						// ȸ��

	Color color = Color(1, 0, 0, 1);	// ��ü �� (RGBA)

	bool bOpen = true;					// imGUI���� ����� �� ��

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
};