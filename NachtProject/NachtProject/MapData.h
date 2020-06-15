#pragma once
#include<Siv3D.hpp>
#include<map>


class MapChipData {
private:
    uint32 ef;  // �N���s��
    bool at;    // ��� 0: Floor 1: Step
    uint32 hi;  // ����
    uint32 sp;  // ��
    uint32 gc;  // �摜�ԍ�

    String graphName;   // �e�N�X�`����

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
    static void loadName(const String& fileName);  // MapChipInfo�����[�h
    static void loadTexture();     // Texture�����[�h
    static String getName(uint16 graphCode);   // �摜�̖��O��Ԃ�
    static String getPath(uint16 graphCode);   // �摜�̃p�X��Ԃ�
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

    static void loadName(const String& fileName); // MapChipRelationInfo�����[�h
    static void loadTexture();     // Texture�����[�h
    static String getCliffName(uint16 graphCode, Part part);
    static String getCliffPath(uint16 graphCode, Part part);
};


class MapChipRelationData {
    uint16 cliff;   // �R�̉摜�ԍ�
    uint16 ladder;  // ��q�̉摜�ԍ�
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
