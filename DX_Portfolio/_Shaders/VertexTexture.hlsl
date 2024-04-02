struct VertexInput
{
    float4 position : POSITION0;    // ���� ��ġ
    float2 uv : TEXCOORD0;          // �׸� ��ǥ    
};

struct PixelInput
{
    float4 position : SV_POSITION0; // �ȼ� ��ġ
    float2 uv : TEXCOORD0; // �׸� ��ǥ
};

cbuffer WorldBuffer : register(b0) // 0 ~ 127
{
    matrix _world;
};

cbuffer VPBuffer : register(b1)
{
    matrix _view;
    matrix _projection;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;
    
    output.position = mul(input.position, _world);
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _projection);
    output.uv = input.uv;
    return output;
}

Texture2D _sourceTex : register(t0);
SamplerState _samp : register(s0);

float4 PS(PixelInput input) : SV_Target
{
    float4 color = _sourceTex.Sample(_samp, (float2) input.uv);
    if (color.r >= 0.99f && color.g <= 0.01f && color.b >= 0.99f)
        discard;
    // discard�� ���� �׸��� �ʰ� �ѱ�� Ű���� (�׸��� �ʴ� ���� �翬�� ���� ó��)
    // ������ r,b ���� �ٲٸ� ���ݴ� ���� ó�� �ɲ���
    // �׸��׸��� ������ ����Ÿ�� ǥ������ �ٸ��� ������ 101�� �ƴ� 0.01������ ������
    // gpu�� cpu�� ���� �ܼ� �۾��� �ϱ� ������ 10^-3���ʹ� �ν��� ����
    return color;
}