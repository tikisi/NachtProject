#pragma once
#include<Siv3D.hpp>
#include<map>


class MapChipData {
private:
    struct {
        uint32 ef : 4;  // �N���s��
        uint32 at : 1;  // ��� 0: Floor 1: Step
        uint32 hi : 8;  // ����
        uint32 sp : 3;  // ��
        uint32 gc : 16; // �摜�ԍ�
    } data;

    // For Graphics
    String graphName;

public:
    explicit MapChipData(uint32 value);
    operator uint32() const noexcept;

    String getGraphName() const { return graphName; }
    uint32 getEF() const { return data.ef; }
    uint32 getAT() const { return data.at; }
    uint32 getHI() const { return data.hi; }
    uint32 getSP() const { return data.sp; }
    uint32 getGC() const { return data.gc; }
};



class MapChipRelationData {
    struct {
        uint16 cliff : 8;   // �R�̉摜�ԍ�
        uint16 ladder : 8;  // ��q�̉摜�ԍ�
    } data;

public:
    explicit MapChipRelationData(uint16 value);
    operator uint16() const noexcept;

    uint16 getCliff() const { return data.cliff; }
    uint16 getLadder() const { return data.ladder; }
};


class MapChipGraph {
private:
    std::map<uint16, String> map;

public:
    explicit MapChipGraph() {}

    void loadMapChipGraphName(const String& fileName);  // MapChipInfo�����[�h
    void loadMapChipGraphTexture();     // Texture�����[�h
    String getName(uint16 graphCode) const;   // �摜�̖��O��Ԃ�
    String getPath(uint16 graphCode) const;   // �摜�̃p�X��Ԃ�
};


__declspec(selectany) extern MapChipGraph mcg;
__declspec(selectany) extern  const String MAP_PATH = U"Data/Map/";
