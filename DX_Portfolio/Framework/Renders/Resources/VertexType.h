#pragma once

// 스트럭트는 원시 고대 클래스 -> 생성자가 있음
struct VertexColor {	// 단색의 네모를 만들기 위해 사용 예정
	// 스트럭트의 생성자
	VertexColor()
		: position(0, 0, 0), color(0, 0, 0, 0) {}

	VertexColor(Vector3 posion, Color color)
		:position(posion), color(color) {}

	// 정점 위치
	Vector3 position;

	// 정점의 색
	Color color;

	// 정점 데이터의 구조를 서술해주는 역할
	static D3D11_INPUT_ELEMENT_DESC descs[];

	// 정점 데이터의 개수(위치, 색)
	static const uint count = 2;
};

struct VertexTexture {	// 택스쳐가있는 네모를 만들기 위해 사용 예정
	// 스트럭트의 생성자
	VertexTexture()
		: position(0, 0, 0), uv(0, 0) {}

	VertexTexture(Vector3 posion, Vector2 uv)
		:position(posion), uv(uv) {}

	Vector3 position;

	// 그림의 좌표
	Vector2 uv;

	static D3D11_INPUT_ELEMENT_DESC descs[];
	static const uint count = 2;
};