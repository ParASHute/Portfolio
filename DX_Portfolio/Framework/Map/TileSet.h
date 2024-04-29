#pragma once

class TileSet
{
public:
    //friend class SingletonBase<TileSet>;
    friend class TMap;

    void GUI();

    ID3D11ShaderResourceView* GetSRV() 
    { return tileSRV; }

    void ChangeTileMap(wstring imagePath,
        uint xCount, uint yCount);

    wstring GetTilePath() { return tilePath; }

    uint GetXCount() { return tileXCount; }
    uint GetYCount() { return tileYCount; }

public: // ������ �̱����̶� private
    TileSet(wstring path);
    TileSet();
    ~TileSet();

private:
    ID3D11ShaderResourceView* tileSRV = nullptr;

    uint tileXCount = 0;
    uint tileYCount = 0;

    // �÷��̾ ������ Ÿ���� ���� UV
    Vector2 selectedStartUV = Values::ZeroVec2;

    // �׸��� �̹��� ũ�� ������
    Vector2 texelTileSize = Values::ZeroVec2;

    wstring tilePath = L"";
};