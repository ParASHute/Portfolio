#include "Framework.h"
#include "VertexType.h"

/*
    D3D11_INPUT_ELEMENT_DESC

    SemanticName		: ���� �������� �ǹ̸� ��Ÿ���� ����
    SemanticIndex		: �� �̸��� �ߺ��Ǵ� ��� �����ϱ� ���� �ε��� ��
    Format				: ������ ������ ��Ÿ��
    InputSlot			: �Է� ������ �ε���
    AligendByteOffset	: ���� �������� ����Ʈ ź�� ������ ( 0 = �ڵ���� )
    InputSlotClass		: ���Ǵ� ������ ������ ����
    InstanceDataStepRate: �ν��Ͻ����� �����͸� �о���̴µ� ����� ���� ����Ʈ ��
*/

D3D11_INPUT_ELEMENT_DESC VertexColor::descs[]
{
    {"POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0,							0	,D3D11_INPUT_PER_VERTEX_DATA,0 },
    {"COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0,D3D11_APPEND_ALIGNED_ELEMENT	,D3D11_INPUT_PER_VERTEX_DATA,0 },
};

D3D11_INPUT_ELEMENT_DESC VertexTexture::descs[]
{
    {"POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0,							0	,D3D11_INPUT_PER_VERTEX_DATA,0 },
    {"TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0,D3D11_APPEND_ALIGNED_ELEMENT	,D3D11_INPUT_PER_VERTEX_DATA,0 },
};

D3D11_INPUT_ELEMENT_DESC VertexTile::descs[]
{
    {"POSITION",0, DXGI_FORMAT_R32G32B32_FLOAT,
    0,							0,
    D3D11_INPUT_PER_VERTEX_DATA,0 },

    {"TEXCOORD",0, DXGI_FORMAT_R32G32_FLOAT,
    0, D3D11_APPEND_ALIGNED_ELEMENT,
    D3D11_INPUT_PER_VERTEX_DATA,0 },

    {"TEXCOORD",1, DXGI_FORMAT_R32G32_FLOAT,
    0, D3D11_APPEND_ALIGNED_ELEMENT,
    D3D11_INPUT_PER_VERTEX_DATA,0 },

    {"COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,
    0, D3D11_APPEND_ALIGNED_ELEMENT,
    D3D11_INPUT_PER_VERTEX_DATA,0 },

    {"INDEX",	0, DXGI_FORMAT_R32_UINT,
    0, D3D11_APPEND_ALIGNED_ELEMENT,
    D3D11_INPUT_PER_VERTEX_DATA,0 }
};