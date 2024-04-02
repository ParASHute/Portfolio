#include "Framework.h"
#include "VertexType.h" 

/*
	D3D11_INPUT_ELEMENT_DESC의 구조
		- SemanticName 
			: 정점 데이터의 의미를 나타내는 문구(이름)
		
		- SemanticIndex 
			: SemanticName이 중복되는 경우에 데이터를 구분하기 위한 인덱스 값(번호)
		
		- Format 
			: 데이터 형식(해석법)
		
		- InputSlot 
			: 입력 슬롯의 인덱스 (대부분 0)
		
		- AlignedByteOffset 
			: 정점 데이터의 바이트 잔위 간격 (0이 기본값, 자동계산)
		
		- InputSlotClass 
			: 사용되는 데이터 형식 (버택스 정보)
		
		- InstanceDataStepRate 
			: 인스턴스 마다 데이터를 읽어들이는데 사용할 스템 레이트값 (대부분 0, 지연시간을 줄지말지 결정함)
*/

D3D11_INPUT_ELEMENT_DESC VertexColor::descs[] {
	// 정점 위치 
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 
	0, D3D11_INPUT_PER_VERTEX_DATA,0},

	// 정점 색상
	{"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,
	D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,0}
};

D3D11_INPUT_ELEMENT_DESC VertexTexture::descs[] {
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
	0, D3D11_INPUT_PER_VERTEX_DATA,0},

	// UV(2차원 백터) : 그림의 좌표
	{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,
	D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,0}
};
// 해석법을 적어둔 해설지라고 보면 될듯, 이걸 정의 해줘야 GPU가 데이터 해석을 할수 이씀