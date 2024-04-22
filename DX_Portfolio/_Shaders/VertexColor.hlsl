
// VertexInput == VertexBuffer�� �ִ� ������
// VertexShader���� ����� ������
struct VertexInput
{
	float4 position : POSITION0;	// ��ġ
	float4 color : COLOR0;			// ����
};

// PixelInput
// PixelShader���� ����� ������
struct PixelInput
{
	float4 position : SV_POSITION0; // ��ġ
	float4 color : COLOR0;			// ����
};

// ���� ���۶� �̸��� ���� ���� 0���� �ִ� ��� ����
cbuffer WorldBuffer : register(b0)
{
	matrix _world;
};

// VP ���۶� �̸��� ���� ���� 1���� �ִ� ��� ����
cbuffer VPBuffer : register(b1)
{
	matrix _view;
	matrix _projection;
};

PixelInput VS(VertexInput input)
{
	PixelInput output;
	
	// ������ ��ġ�� ���带 ���ϰ�
	output.position = mul(input.position, _world);
	// ���尡 ������ �����Ϳ� �並 ���ϰ�
	output.position = mul(output.position, _view);
	// ����� ������ �����Ϳ� ���������� ���Ѵ�.
	output.position = mul(output.position, _projection);
	// �� ������ ���ؾ� DirectX �� ������ ��ġ�Ѵٰ� �ν��Ҽ� ����
	
	output.color = input.color;
	
	return output;
};

// SV_Target�� �޸𸮻� �����ִ� �������� ���� �ѵ����͸�
// �ڵ����� ����� ������ִ� �ɷ� ����Ѵ�. // Ȯ������ ����
float4 PS(PixelInput input) : SV_Target
{
	return input.color;
};

/*
Semantic : ����ƽ
- HLSL���� �������� �ǹ̸� �����ϴµ� ����ϴ� ����
- ���̴��� �Է� �����Ϳ� ��� �����͸� �ùٸ��� �ؼ��ϰ� ó���ϴµ� ���
- ���� �̸��ڿ� : �� �Բ� ����
- SV_ ���λ�� �����ϴ� ����ƽ�� DirectX�� ������ Ư���� �ǹ̸� ���Ѵ�.
- �̷��� �������� �ý��� �� ����ƽ�̶� �θ���. // SystemValue_

slot
- GPU���� ����ϴ� ��� ����, �ؽ���, ���÷� ���� �پ��� �����͸� �ĺ��ϴ�
��ȣ
- �� ������ ������ ��ȣ�� ���ϸ�, �ش� �������� ����� ���ҿ� ����
�پ��� ������ �����Ѵ�.
- register Ű���带 ����Ͽ� �����Ѵ�.

- ��� ���� ����
- ��� �����͸� �����ϴµ� ���Ǹ�, VS�� PS�� �����Ҽ� �ִ�.
- �ַ� ������ ���� ������ ���� �پ��� �����͸� �ǳ��ٶ� ����Ѵ�.
- ��� ���� ������ register(b#)�� ����Ͽ� �����Ѵ�. 
// #���� ���� ��ȣ�� ��

- �ؽ�ó ����
- �̹��� �����͸� �����ϴµ� ���
- �ؽ�ó ������ register(t#)�� ����Ͽ� �����Ѵ�. 

- ���÷� ����
- �̹����� �����ϴ� ���� ����Ǵ� ����
- ���÷� ������ register(s#)�� ����Ͽ� �����Ѵ�. 

cbuffer : ��� ���� // constant buffer
- ���̴��� ����Ҽ��ִ� ���� ������ �����ϴµ� ���
- CPU���� ���� �����Ͱ� �ƴ� �ٸ� �����͸� �����Ҷ� ���
- �� ��� ���� �������ʹ� �Ѱ��� ������۸� �Ҵ��Ҽ� �ִ�.
- ��� ���� ���ο��� �������� ������ ������ �� �ִ�.
- ��, �̷��� �����ʹ� ���̴� ���۸� ���� ������ �������� �ǳ�����Ѵ�.
*/
