#include "Map.h"

void Map::loadMcd(const String& fileName) {
    const CSVData csv(MAP_PATH + fileName);

    if (!csv) throw Error(U"failed to load " + fileName);

    mcd.reserve(csv.columns(0));
    for (size_t col = 0; col < csv.columns(0); ++col) {
        Array<MapChipData> data;

        for (size_t row = 0; row < csv.rows(); ++row)
            data.emplace_back(Parse<int32>(csv[row][col]));

        mcd.push_back(std::move(data));
    }
}

void Map::loadMrd(const String& fileName) {
    const CSVData csv(MAP_PATH + fileName);

    if (!csv) throw Error(U"failed to load " + fileName);

    mrd.reserve(csv.columns(0));
    for (size_t col = 0; col < csv.columns(0); ++col) {
        Array<MapChipRelationData> data;

        for (size_t row = 0; row < csv.rows(); ++row) {
            data.emplace_back(Parse<int16>(csv[row][col]));
        }

        mrd.push_back(std::move(data));
    }
}

void Map::draw() const {
    /*for (int i = 0; i < mcd.size(); i++) {
        int depth = 0;
        // 最後の行以外
        int j;
        for (j = 0; j < mcd[i].size() - 1; j++) {
            TextureAsset(mcd[i][j].getGraphName()).draw(40 * i, 40 * (j + depth));

            // 崖の描画
            if (mrd[i][j].getCliff() != 0) {
                int delta = mcd[i][j].getHI() - mcd[i][j + 1];
                for (int k = 1; k < delta; k++) {
                    depth++;
                    TextureAsset(mrd[i][j].getCliffName(MapChipRelationGraph::Part::up))
                        .draw(40 * i, 40 * (j + depth));
                }
                depth++;
                TextureAsset(mrd[i][j].getCliffName(MapChipRelationGraph::Part::buttom))
                    .draw(40 * i, 40 * (j + depth));
            }

            // ToDo:梯子の描画

        }

        // 最後の行 高さ０との差分だけ崖を描画
        TextureAsset(mcd[i][j].getGraphName()).draw(40 * i, 40 * (j + depth));
        if (mrd[i][j].getCliff() != 0) {
            int delta = (*(mcd[i].crbegin())).getHI();
            int k;
            for (k = 1; k <= delta; k++) {
                TextureAsset(mrd[i][j + k].getCliffName(MapChipRelationGraph::Part::up))
                    .draw(40 * i, 40 * (j + depth + k));
            }
            TextureAsset(mrd[i][j + k].getCliffName(MapChipRelationGraph::Part::buttom))
                .draw(40 * i, 40 * (j + depth + k));
        }
    }*/

    int max = 0;    // 高さの最大値
    for (int i = 0; i < mcd.size(); i++) {
        for (int j = 0; j < mcd[i].size(); j++) {
            int tmp = mcd[i][j].getHI() + mcd[i].size() - j - 1;
            if (tmp > max) {
                max = tmp;
            }
        }
    }

    for (int i = 0; i < mcd.size(); i++) {
        // 最後の行以外
        int j;
        for (j = 0; j < mcd[i].size() - 1; j++) {
            int hight = mcd[i][j].getHI();
            int chipDrawHeight = max - hight - (mcd[i].size() - j - 1);
            TextureAsset(mcd[i][j].getGraphName()).draw(40 * i, 40 * chipDrawHeight);

            // 崖の描画
            if (mrd[i][j].getCliff() != 0) {
                int delta = hight - mcd[i][j + 1].getHI();
                int k;
                for (k = 1; k < delta; k++) {
                    TextureAsset(mrd[i][j].getCliffName(MapChipRelationGraph::Part::up))
                        .draw(40 * i, 40 * (chipDrawHeight+ k));
                }
                TextureAsset(mrd[i][j].getCliffName(MapChipRelationGraph::Part::buttom))
                    .draw(40 * i, 40 * (chipDrawHeight  + k));
                // 透過部分の地面描画
            }

            // ToDo:梯子の描画
        }

        // 最後の行を描画
        int hight = mcd[i][j].getHI();
        TextureAsset(mcd[i][j].getGraphName()).draw(40 * i, 40 * (max - hight)); 
        if (mrd[i][j].getCliff() != 0) {
            for(int k = 1; k <=  hight; k++) {
                TextureAsset(mrd[i][j].getCliffName(MapChipRelationGraph::Part::up))
                    .draw(40 * i, 40 * (max - hight + k));
            }
        }
    }
}
