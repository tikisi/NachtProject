#include "Map.h"

void Map::loadMcd(const String &fileName) {
    const CSVData csv(MAP_PATH + fileName);

    if (!csv) throw Error(U"failed to load " + fileName);

    mcd.reserve(csv.rows());
    for (size_t row = 0; row < csv.rows(); ++row) {
        Array<MapChipData> data;

        for (size_t col = 0; col < csv.columns(row); ++col)
            data.emplace_back(Parse<int32>(csv[row][col]));

        mcd.push_back(std::move(data));
    }
}

void Map::loadMrd(const String &fileName) {
    const CSVData csv(MAP_PATH + fileName);

    if(!csv) throw Error(U"failed to load " + fileName);

    mrd.reserve(csv.rows());
    for(size_t row = 0; row < csv.rows(); ++row) {
        Array<MapChipRelationData> data;

        for(size_t col = 0; col < csv.columns(row); ++ col) {
            data.emplace_back(Parse<int16>(csv[row][col]));
        }

        mrd.push_back(std::move(data));
    }
}

void Map::draw() const {
    for(int i = 0; i < mcd.size(); i++) {
        for(int j = 0; j < mcd[i].size(); j++) {
            TextureAsset(mcd[i][j].getGraphName()).draw(40*i, 40*j);
        }
    }   
}
