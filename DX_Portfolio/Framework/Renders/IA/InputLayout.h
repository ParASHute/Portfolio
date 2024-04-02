#pragma once
/*
	InputLayout
		- ���ؽ� ������ ������ ������ �����Ѵ�
		- ���ؽ� ���� �������� �� ���(��ġ, ���� �׸� ��ǥ��)�� ����, ũ��, ���� ���� ����
		- IA�ܰ迡�� VS�� �����͸� �����ϱ� ���� ���� �����͸� �ް� 
			�ش� ��Ƽ� �ùٸ��� �ؼ��ϱ� ���� ���

		��ī�� ��û�� ſ�� ��Ȯ�ϰ� �ڷ����� ����ϱ� ���ؼ� ����Ѵ� �����ϸ� �ȴ�
*/
class InputLayout {
public:
	~InputLayout();

	// Randers/Resource�� �ִ� VertexType�� �ִ´�
	void Create(D3D11_INPUT_ELEMENT_DESC* descs, uint count, ID3DBlob* blob);
	void SetIA();

private:
	ID3D11InputLayout* inputLayout = nullptr;
};