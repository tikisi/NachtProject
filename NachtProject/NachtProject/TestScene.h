#pragma once
#include <Siv3D.hpp>
#include "Map.h"

using App = SceneManager<String>;

class TestScene : public App::Scene {
private: 
    Map map;
public:
    TestScene(const InitData& init) : IScene(init), 
        map(U"testMap.csv", U"testMapRelation.csv"){
    }

    void update() override {
    }

    void draw() const override {
        map.draw();
    }
};
