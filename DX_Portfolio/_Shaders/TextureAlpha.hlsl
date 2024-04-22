
// VertexInput == VertexBuffer�� �ִ� ������
// VertexShader���� ����� ������
struct VertexInput
{
	float4 position : POSITION0;	// ��ġ
	float2 uv		: TEXCOORD0;	// �׸� ��ǥ
};

// PixelInput
// PixelShader���� ����� ������
struct PixelInput
{
	float4 position : SV_POSITION0; // ��ġ
	float2 uv		: TEXCOORD0;	// �׸� ��ǥ
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
	
	output.uv = input.uv;
	
	return output;
};

cbuffer AlphaBuffer : register(b0)
{
	float4 _clearColor;
	float _alpha;
};

Texture2D _sourceTex : register(t0);
SamplerState _samp : register(s0);

float4 PS(PixelInput input) : SV_Target
{
	float4 color = _sourceTex.Sample(_samp, (float2)input.uv);
	float4 resultColor = 0;
	
	if (color.r >= 0.99f && color.g <= 0.01f && color.b >= 0.99f) 
		discard; 
	
	if (_alpha >= 0.001f)
	{
		resultColor.r = (color.r - (color.r * _alpha)) +
			(_clearColor.r * _alpha);
		
		resultColor.g = (color.g - (color.g * _alpha)) +
			(_clearColor.g * _alpha);
		
		resultColor.b = (color.b - (color.b * _alpha)) +
			(_clearColor.b * _alpha);
		
		resultColor.a = (color.a - (color.a * _alpha)) +
			(_clearColor.a * _alpha);
	}
	else
	{
		resultColor = color;
	}

	return resultColor;
};