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
};  // 여기 세미콜론은 있어도 되고 없어도 됨

cbuffer ShadedBuffer : register(b0)
{
    int _selection;
    int _blurCount;
    
    float2 _textureSize;
}

Texture2D _sourceTex : register(t0);
SamplerState _samp : register(s0);

float4 PS(PixelInput input) : SV_Target
{
    float4 color = _sourceTex.Sample(_samp, (float2) input.uv);
    float4 resultColor = 0;
    if (color.r >= 0.99f && color.g <= 0.01f && color.b >= 0.99f)
        discard;
    
    if (_selection == 1)
    {
        return color;
    }
    
    else if (_selection == 2)
    {
        float3 gray = dot(color.rgb, float3(0.299f, 0.587f, 0.114f));
        resultColor = float4(gray, color.a);
    }
    
    else if (_selection == 3)
    {
        float3 nagative = 1 - abs(color.rgb);
        resultColor = float4(nagative, color.a);
    }
    
    else if (_selection == 4)
    {
        float2 arr[8] =
        {
          float2(-1,+1), float2(+0,+1), float2(+1,+1),  
          float2(-1,+0), /*여긴 기준 평점*/ float2(+1, +0),
          float2 (-1,-1), float2 (+0,-1), float2 (+1,-1),
        };
        
        // 블러의 심도가 높아지면 그만큼 반복해서 색을 최대한으로 지움
        for (int blur = 1; blur < _blurCount; blur++)
        {
            for (int i = 0; i < 8; i++)
            {
                // 픽셀 색 평균 내기
                float x = arr[i].x * (float) blur / _textureSize.x;
                float y = arr[i].y * (float) blur / _textureSize.y;
                
                // uv 넣기
                float2 uv = input.uv + float2(x, y);
                
                // 그걸로 색 변환
                color += _sourceTex.Sample(_samp, uv);
            };
        };

        int blurInterations = _blurCount - 1;
        int offsetCount = 8;
        
        int totalSamples = blurInterations * offsetCount + 1;
        
        resultColor = color / totalSamples;
    }
    
    else if (_selection == 5)
    {
        // UV에서 U는 새로, V는 가로다
        input.uv.x = 1 - input.uv.x;
        
        color = _sourceTex.Sample(_samp, (float2) input.uv);
        
        resultColor == color;
    }
    
    else if (_selection == 6)
    {
        // UV에서 U는 새로, V는 가로다
        input.uv.y = 1 - input.uv.y;
        
        color = _sourceTex.Sample(_samp, (float2) input.uv);
        
        resultColor == color;
    }
    
        return resultColor;
    // 이래 하면 뭔가 설정을 안해두면 사라짐
};