#include "MapData.h"

MapChipData::MapChipData(uint32 value) {
    data.gc = value & 0x0000FFFF;
    data.sp = value & 0x00070000;
    data.hi = value & 0x07f80000;
    data.at = value & 0x08000000;
    data.ef = value & 0xf0000000;

    graphName = mcg.getName(uint16(data.gc));
}

MapChipData::operator uint32() const noexcept {
    return data.gc | data.sp << 16 | data.hi << 19 |
        data.at << 27 | data.ef << 28;
}

MapChipRelationData::MapChipRelationData(uint16 value) {
    data.ladder = value & 0x0F;
    value >>= 8;
    data.cliff = value & 0x0F;
}

MapChipRelationData::operator uint16() const noexcept {
    return data.ladder | data.cliff << 8;
}

void MapChipGraph::loadMapChipGraphName(const String& fileName) {
    String tmp = MAP_PATH + fileName;
    const CSVData csv(tmp);

    if (!csv) {
        throw Error(U"Failed to open " + fileName);
    }

    for (size_t row = 0; row < csv.rows(); row++) {
        map.emplace(row + 1, csv[row][0]);
    }
}

void MapChipGraph::loadMapChipGraphTexture() {
    for(const auto& i : map) {
        String path = getPath(i.first);
        TextureAsset::Register(i.second, path); 
    }
}

String MapChipGraph::getPath(uint16 graphCode) const {
    return MAP_PATH + U"MapChip/"  + map.at(graphCode) + U".png";
}

String MapChipGraph::getName(uint16 graphCode) const {
    return map.at(graphCode);
}