#pragma once
#include<Siv3D.hpp>
#include<map>


class MapChipData {
private:
    uint32 ef;  // 侵入不可
    bool at;    // 種類 0: Floor 1: Step
    uint32 hi;  // 高さ
    uint32 sp;  // 空き
    uint32 gc;  // 画像番号

    String graphName;   // テクスチャ名

public:
    explicit MapChipData(uint32 value);
    operator uint32() const noexcept;

    String getGraphName() const { return graphName; }
    uint32 getEF() const { return ef; }
    bool getAT() const { return at; }
    uint32 getHI() const { return hi; }
    uint32 getSP() const { return sp; }
    uint32 getGC() const { return gc; }
};


class MapChipGraph {
private:
    inline static std::map<uint16, String> map;

public:
    MapChipGraph() = delete;
    static void loadName(const String& fileName);  // MapChipInfoをロード
    static void loadTexture();     // Textureをロード
    static String getName(uint16 graphCode);   // 画像の名前を返す
    static String getPath(uint16 graphCode);   // 画像のパスを返す
};


class MapChipRelationGraph {
private:
    inline static std::map<uint16, String> cliffMap;

public:
    MapChipRelationGraph() = delete;

    enum class Part : int {
        up,
        buttom,
    };

    static void loadName(const String& fileName); // MapChipRelationInfoをロード
    static void loadTexture();     // Textureをロード
    static String getCliffName(uint16 graphCode, Part part);
    static String getCliffPath(uint16 graphCode, Part part);
};


class MapChipRelationData {
    uint16 cliff;   // 崖の画像番号
    uint16 ladder;  // 梯子の画像番号
    uint16 part;

public:
    explicit MapChipRelationData(uint16 value);
    operator uint16() const noexcept;

    uint16 getCliff() const { return cliff; }
    uint16 getLadder() const { return ladder; }
    uint16 getPart() const {return part;}

    String getCliffName(MapChipRelationGraph::Part part) const;
};

__declspec(selectany) extern  const String MAP_PATH = U"Data/Map/";
