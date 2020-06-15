#include "MapData.h"

MapChipData::MapChipData(uint32 value) {
    gc = value & 0x0000FFFF;
    sp = (value & 0x00070000) >> 16;
    hi = (value & 0x07f80000) >> 19;
    at = (value & 0x08000000) >> 27;
    ef = (value & 0xf0000000) >> 28;

    graphName = MapChipGraph::getName(uint16(gc));
}

MapChipData::operator uint32() const noexcept {
    return gc | sp << 16 | hi << 19 |
        at << 27 | ef << 28;
}

MapChipRelationData::MapChipRelationData(uint16 value) {
    ladder = value & 0x0F;
    value >>= 8;
    cliff = value & 0x0F;
}

MapChipRelationData::operator uint16() const noexcept {
    return  ladder | cliff << 8 ;
}

String MapChipRelationData::getCliffName(MapChipRelationGraph::Part part) const {
    return MapChipRelationGraph::getCliffName(cliff, part);
}

void MapChipGraph::loadName(const String& fileName) {
    String tmp = MAP_PATH + fileName;
    const CSVData csv(tmp);

    if (!csv) {
        throw Error(U"Failed to open " + fileName);
    }

    for (size_t row = 0; row < csv.rows(); row++) {
        map.emplace(row + 1, csv[row][0]);
    }
}

void MapChipGraph::loadTexture() {
    for (const auto& i : map) {
        String path = getPath(i.first);
        TextureAsset::Register(i.second, path);
    }
}

String MapChipGraph::getPath(uint16 graphCode) {
    return MAP_PATH + U"MapChip/" + map.at(graphCode) + U".png";
}

String MapChipGraph::getName(uint16 graphCode) {
    return map.at(graphCode);
}

void MapChipRelationGraph::loadName(const String& fileName) {
    String tmp = MAP_PATH + fileName;
    const CSVData csv(tmp);

    if (!csv) {
        throw Error(U"Failed to open " + fileName);
    }

    for (size_t row = 0; row < csv.rows(); row++) {
        cliffMap.emplace(row + 1, csv[row][0]);
    }
}

void MapChipRelationGraph::loadTexture() {
    for (const auto& i : cliffMap) {
        for (int j = 0; j < 2; j++) {
            String name = getCliffName(i.first, static_cast<Part>(j));
            String path = getCliffPath(i.first, static_cast<Part>(j));
            TextureAsset::Register(name, path);
        }
    }
}

String MapChipRelationGraph::getCliffName(uint16 graphCode, Part part) {
    switch(part) {
        case Part::up:
            return cliffMap.at(graphCode) + U"up";
        case Part::buttom:
            return cliffMap.at(graphCode) + U"buttom";
    }
}

String MapChipRelationGraph::getCliffPath(uint16 graphCode, Part part) {
    return MAP_PATH + U"MapChipRelation/" + getCliffName(graphCode, part) + U".png";
}