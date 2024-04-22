
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

cbuffer ShadedBuffer : register(b0)
{
	int _selection;
	
	int _blurCount;
	float2 _textureSize;
};

	Texture2D _sourceTex : register(t0);
	SamplerState _samp : register(s0);

// SV_Target�� �޸𸮻� �����ִ� �������� ���� �ѵ����͸�
// �ڵ����� ����� ������ִ� �ɷ� ����Ѵ�. // Ȯ������ ����
float4 PS(PixelInput input) : SV_Target
{
	float4 color = _sourceTex.Sample(_samp, (float2)input.uv);
	float4 resultColor = 0;
	
	if (color.r >= 0.99f && color.g <= 0.01f && color.b >= 0.99f) 
		discard; 
	// discard�� ���� �׸��� �ʰ� �ѱ�� Ű����
	// �׸��� ���� ���� �������� ó���ȴ�.
	
	if (_selection == 1)
	{
		return color;
	}
	else if (_selection == 2)
	{
		// Gray
		float3 gray = dot(color.rgb, float3(0.299f, 0.587f, 0.114f));
		resultColor = float4(gray, color.a);
	}
	else if (_selection == 3)
	{
		// Nagative
		float3 negative = 1 - abs(color.rgb);
		resultColor = float4(negative, color.a);
	}
	else if (_selection == 4)
	{
		// Blur
		
		// �ֺ� �ȼ� ��ġ
		float2 arr[8] =
		{
			float2(-1, +1), float2(+0, +1), float2(+1, +1),
			float2(-1, +0),  /* ���� ����*/  float2(+1, +0),
			float2(-1, -1), float2(+0, -1), float2(+1, -1)
		};

		// ���α׷��Ӱ� ������ �� ���� ��ŭ �ݺ�
		for (int blur = 1; blur < _blurCount; blur++)
		{
			// �ֺ� �ȼ� ������ŭ �ݺ�
			for (int i = 0; i < 8; i++)
			{
				float x = arr[i].x * (float) blur 
				/ _textureSize.x;
				
				float y = arr[i].y * (float) blur 
				/ _textureSize.y;
				
				// �ֺ� �ȼ��� uv���� ã�Ƴ�
				float2 uv = input.uv + float2(x, y);
				
				// �ش� uv�� ���� ������ ���ݻ��� ��� �߰�
				color += _sourceTex.Sample(_samp, uv);
			};
		};

		int blurInterations = _blurCount - 1;
		int offsetCout = 8;
		
		int totalSamples = blurInterations * offsetCout + 1;
		
		resultColor = color / totalSamples;
	}
	else if (_selection == 5)
	{
		input.uv.x = 1 - input.uv.x;
		
		color = _sourceTex.Sample(_samp, (float2) input.uv);
		resultColor = color;			
	}
	else if (_selection == 6)
	{
		input.uv.y = 1 - input.uv.y;
		
		color = _sourceTex.Sample(_samp, (float2) input.uv);
		resultColor = color;
	}
	
	return resultColor;
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
