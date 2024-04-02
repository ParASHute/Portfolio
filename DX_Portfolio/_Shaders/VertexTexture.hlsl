struct VertexInput
{
    float4 position : POSITION0;    // 정점 위치
    float2 uv : TEXCOORD0;          // 그림 좌표    
};

struct PixelInput
{
    float4 position : SV_POSITION0; // 픽셀 위치
    float2 uv : TEXCOORD0; // 그림 좌표
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
    // discard는 색을 그리지 않고 넘기는 키워드 (그리지 않는 색은 당연히 투명 처리)
    // 저위에 r,b 값을 바꾸면 조금더 쉽게 처리 될꺼임
    // 그림그리는 툴마다 마젠타의 표현력이 다르기 때문에 101이 아닌 0.01정도의 값을줌
    // gpu는 cpu에 비해 단순 작업만 하기 떄문에 10^-3부터는 인식을 못함
    return color;
}