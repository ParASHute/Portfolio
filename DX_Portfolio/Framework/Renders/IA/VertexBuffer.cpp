#include "Framework.h"
#include "VertexBuffer.h"

VertexBuffer::~VertexBuffer ()
{
	/*
		SAFE_RELEASE�� ID3D�� �����ϴ� �������̽��� �����ϴµ� ���Ǹ�
		�ش� �������̽����� ���α׷��Ӱ� ����� ���� �ƴ�
		�ٷ����� �������� ����� �������� ����̱� ������
		������ ����Ʈ�� �ƴ� "SAFE_RELEASE"�� ����Ѵ�.

		** ���� ����� ������ �㶧�� SAFE_RELEASE�ؾ� �Ǵ� ���� ������ ����Ʈ�� �ؼ� �׷�
	*/

	SAFE_RELEASE(buffer);
}

void VertexBuffer::SetIA()
{
	//��ǫ ������� ���� �־��ִ� �Լ�
	DC->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
}
