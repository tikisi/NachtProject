#pragma once
#include <Siv3D.hpp>
#include "MapData.h"

class Map {
private:
    Array<Array<MapChipData> > mcd;
    Array<Array<MapChipRelationData> > mrd;

    void loadMcd(const String &fileName);
    void loadMrd(const String &filename);

public:
    Map(const String &mapChipDataFile, const String &mapChipRelationDataFile) {
        loadMcd(mapChipDataFile);
        loadMrd(mapChipRelationDataFile);
    }

    //void update();
    void draw() const;
};
