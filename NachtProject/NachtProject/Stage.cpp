#include "Stage.h"

void Stage::loadMcd(const String& fileName) {
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

void Stage::loadMrd(const String& fileName) {
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

void Stage::draw() const {
    int max = 0;    // çÇÇ≥ÇÃç≈ëÂíl
    for (int i = 0; i < mcd.size(); i++) {
        for (int j = 0; j < mcd[i].size(); j++) {
            int tmp = mcd[i][j].getHI() + mcd[i].size() - j - 1;
            if (tmp > max) {
                max = tmp;
            }
        }
    }

    for (int i = 0; i < mcd.size(); i++) {
        // ç≈å„ÇÃçsà»äO
        int j;
        for (j = 0; j < mcd[i].size() - 1; j++) {
            const int hight = mcd[i][j].getHI();
            const int chipDrawHeight = max - hight - (mcd[i].size() - j - 1);
            TextureAsset(mcd[i][j].getGraphName()).draw(40 * i, 40 * chipDrawHeight);

            // äRÇÃï`âÊ
            if (mrd[i][j].getCliff() != 0) {
                const int delta = hight - mcd[i][j + 1].getHI();
                int k;
                for (k = 1; k < delta; k++) {
                    TextureAsset(mrd[i][j].getCliffName(MapChipRelationGraph::Part::up))
                        .draw(40 * i, 40 * (chipDrawHeight + k));
                }
                // ìßâﬂïîï™ÇÃínñ ï`âÊ
                TextureAsset(mcd[i][j + 1].getGraphName()).draw(40 * i, 40 * (chipDrawHeight + k));
                TextureAsset(mrd[i][j].getCliffName(MapChipRelationGraph::Part::buttom))
                    .draw(40 * i, 40 * (chipDrawHeight + k));
            }

            // ToDo:íÚéqÇÃï`âÊ
        }

        // ç≈å„ÇÃçsÇï`âÊ
        const int hight = mcd[i][j].getHI();
        TextureAsset(mcd[i][j].getGraphName()).draw(40 * i, 40 * (max - hight));
        if (mrd[i][j].getCliff() != 0) {
            for (int k = 1; k <= hight; k++) {
                TextureAsset(mrd[i][j].getCliffName(MapChipRelationGraph::Part::up))
                    .draw(40 * i, 40 * (max - hight + k));
            }
        }
    }
}
