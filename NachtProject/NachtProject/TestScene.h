#pragma once
#include <Siv3D.hpp>
#include "Stage.h"

using App = SceneManager<String>;

class TestScene : public App::Scene {
private: 
    Stage stage;
public:
    TestScene(const InitData& init) : IScene(init), 
        stage(U"testMap.csv", U"testMapRelation.csv"){
    }

    void update() override {
    }

    void draw() const override {
        stage.draw();
    }
};
