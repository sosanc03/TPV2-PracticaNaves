#pragma once
#include "../ecs/Component.h"
class Generations :
    public Component
{
private:
    int gen_;// número de generación
public:
    Generations(int gen) {// constructora
        gen_ = gen;// generación
    }

    int getGen() { return gen_; }// devuelve la generación

    void setGen(int gen) { gen_ = gen; }// setea la generación
};

