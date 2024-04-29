#pragma once

#include "Tile.h"
#include "TileSet.h"

class IndexNumBuffer : public ShaderBuffer
{
public:

    IndexNumBuffer()  
        : ShaderBuffer(&data, sizeof(Data))
    {
        data.index = 0;
    }

    void SetIndex(uint index) { data.index = index; }

    struct Data
    {
        uint index;
        Vector3 dummy;
    };

private:
    Data data;
};

class TMap
{
public:
    // width = ���ο� �� Ÿ���� ����
    // height = ���ο� �� Ÿ���� ����
    // width , height ���� 10�̶�� �� 100��
    // Ÿ���� �򸰴�.
    // spacing�� �� Ÿ���� ����,���� ����
    TMap(uint width, uint height, uint spacing);
    TMap(uint width, uint height, uint spacing, wstring path);
    ~TMap();

    void Update();
    void Render();
    void GUI();

    void GenerateTileMap();

    void MapVertexBuffer();
    void UnmapVertexBuffer();

    void Save(string path);
    void Load(string path);

    Tile* GetTile(Vector3 mPos);

    TileSet* GetTileSet() { return tileSet; }

private:
    
    vector<VertexTile> vertices;
    VertexBuffer* vb = nullptr;

    InputLayout* il = nullptr;

    vector<uint> indices;
    IndexBuffer* ib = nullptr;

    VertexShader* vs = nullptr;
    PixelShader* ps = nullptr;

    Matrix world = Values::Identity;
    WorldBuffer* wb = nullptr;

    IndexNumBuffer* inb = nullptr;

    ID3D11SamplerState* sampler[2];
    ID3D11BlendState* blend[2];

    uint width = 0;
    uint height = 0;
    uint spacing = 0;

    uint vertexCount = 0;
    uint indexCount = 0;

    D3D11_MAPPED_SUBRESOURCE subResource;

    Tile** tiles = nullptr;   
    
    TileSet* tileSet = nullptr;


};