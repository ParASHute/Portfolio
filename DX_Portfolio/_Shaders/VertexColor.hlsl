// 쉐이더 파일 (hlsl확장자 파일)

// 쉐이더에 정의한건 하나의 공식인거임 그 공식에 대한 해설지가 아래 있는거임

// VertexInput 구조체, VertexBuffer에 있는 데이터 
// VertexShader에서 사용할 데이터
struct VertexInput
{
    float4 position : POSITION0;    // 정점 위치    "position"이라는 변수가 "POSITION0" 스트림의 위치에 대한 정보를 저장한다
    float4 color : COLOR0;          // 정점 색상    
}; // 중괄호 세미콜론 하나하나 다 직접 해야됨 ㅇㅇ

// PixelInput 구조체 정의
// PixelShader에서 사용할 데이터 
struct PixelInput
{
    float4 position : SV_POSITION0; // 픽셀 위치    픽셀의 위치를 나타내는 시스템 값을 의미
    float4 color : COLOR0;          // 픽셀 색상
};

// 상수 버퍼 레지스터 b0에 할당된 월드 행렬을 저장하는 상수 버퍼
// 월드 버퍼라는 이름의 버퍼 슬롯 0번에 있는 상수 버퍼
cbuffer WorldBuffer : register(b0) // 0 ~ 127
{
    matrix _world;
};

// 상수 버퍼 레지스터 b1에 할당된 뷰 행렬과, 프로젝션 행렬을 저장하는 상수 버퍼
// VP 버퍼라는 이름의 버퍼 슬롯 1번에 있는 상수 버퍼
cbuffer VPBuffer : register(b1)
{
    matrix _view;
    matrix _projection;
};

// 정점 셰이더 함수
// 입력으로 VertexInput을 받고 PixelInput 구조체를 반환
PixelInput VS(VertexInput input)
{
    PixelInput output;
    
    output.position = mul(input.position, _world);          // 정점 위치에 월드 행렬을 곱함(mul)
    output.position = mul(output.position, _view);          // 결과에 뷰 행렬을 곱함
    output.position = mul(output.position, _projection);    // 결과에 프로젝션 매트릭스 곱함
    // 위 순서대로 곱해야 DX가 공간에 워치한다고 인식 할 수 있음
    output.color = input.color;
    return output;
}

// 픽셀 셰이더 함수
// 입력으로 PixelInput 구조체를 받고, float4 형태의 픽셀 색상을 반환
float4 PS(PixelInput input) : SV_Target // SV_Target은 메모리상 데이터중 적절ㄹ한 데이터를 자동으로 끌고와 사용해주는 것으로 추정된다함
{
    return input.color;
}

/*
    Semantic : 세멘틱 스트럭트에서 "형 변수명 : 대문자" 에서 대문자 부분
        - HLSL 셰이더에서 데이터의 의미를 지정하는 데 사용
        - 셰이더가 입력 데이터와 출력 데이터를 올바르게 해석하고 처리할 수 있도록 해줌
        - 변수 이름 뒤에 ':' 기호와 함께 지정
        - 시스템 값 세멘틱은 'SV_(시스템 밸류의 준말)' 접두사로 시작하는 세멘틱이며 Direct3D에서 정의된 특별한 의미를 가짐
        - 시스템 값 세멘틱은 셰이더 스테이지 간에 데이터를 전달하는데 사용
*/

/*
    slot : " : register(b1)"부분 
        - GPU에서 사용하는 상수 버퍼, 텍스처, 샘플러 등의 자원들을 식별하는 인덱스
        - 각 슬롯을 고유한 번호를 가지며, 해당 자원의 유형과 역할에 따라 다양한 슬롯이 존제
        - register라는 키워드를 사용하여 지정
        - 각 자원이 어떤 슬롯에 할당될 것인지 명시적으로 지정할 수 있음
        - 주요 슬롯
            1) 상수 버퍼 슬롯
                - 상수 버퍼 슬롯은 register(b#)을 사용하여 지정
                - 주로 정점에 대한 데이터가 아닌 다양한 데이터를 건내줄때 사용
                - 상수 데이터를 저장하는데 사용되며, VS와 PS에서 공유
            
            2) 텍스처 슬롯
                - 텍스처 버퍼 슬롯은 register(t#)을 사용하여 지정
                - 이미지 데이터를 저장하는데 사용
        
            3) 샘플러 슬롯
                - 샘플러 슬롯은 register(s#)을 사용하여 지정
                - 이미지를 가공하는 법이 저장되는 슬롯
                - 텍스처를 샘플링하는 데 사용
*/

/*
    cbuffer : 상수 버퍼 (Constant Buffer)
        - 셰이더에서 사용하는 전역 변수를 저장하는데 사용
        - CPU에서 정점 데이터가 아닌 다른 데이터를 전달할때 사용
        - 각 상수 버퍼 레지스터에는 한 개의 상수 버퍼만 할당할 수 있음
        - 상수 버퍼 내부에는 여러 개의 변수를 선언할 수 있다
        - 단, 이런 데이터는 쉐이더 버퍼를 통해 지정된 형식으로 건내 줘야함
*/