#include "Framework.h"
#include "VertexType.h" 

/*
	D3D11_INPUT_ELEMENT_DESC�� ����
		- SemanticName 
			: ���� �������� �ǹ̸� ��Ÿ���� ����(�̸�)
		
		- SemanticIndex 
			: SemanticName�� �ߺ��Ǵ� ��쿡 �����͸� �����ϱ� ���� �ε��� ��(��ȣ)
		
		- Format 
			: ������ ����(�ؼ���)
		
		- InputSlot 
			: �Է� ������ �ε��� (��κ� 0)
		
		- AlignedByteOffset 
			: ���� �������� ����Ʈ ���� ���� (0�� �⺻��, �ڵ����)
		
		- InputSlotClass 
			: ���Ǵ� ������ ���� (���ý� ����)
		
		- InstanceDataStepRate 
			: �ν��Ͻ� ���� �����͸� �о���̴µ� ����� ���� ����Ʈ�� (��κ� 0, �����ð��� �������� ������)
*/

D3D11_INPUT_ELEMENT_DESC VertexColor::descs[] {
	// ���� ��ġ 
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 
	0, D3D11_INPUT_PER_VERTEX_DATA,0},

	// ���� ����
	{"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,
	D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,0}
};

D3D11_INPUT_ELEMENT_DESC VertexTexture::descs[] {
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
	0, D3D11_INPUT_PER_VERTEX_DATA,0},

	// UV(2���� ����) : �׸��� ��ǥ
	{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,
	D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,0}
};
// �ؼ����� ����� �ؼ������ ���� �ɵ�, �̰� ���� ����� GPU�� ������ �ؼ��� �Ҽ� �̾�