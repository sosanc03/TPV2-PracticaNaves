#pragma once
#include "../ecs/Component.h"
struct Generations :
    public Component
{
public:
    Generations() {};
//private:
//    int gen_;// número de generación
//public:
//    Generations(int gen) {// constructora
//        gen_ = gen;// generación
//    }
//
//    int getGen() { return gen_; }// devuelve la generación
//
//    void setGen(int gen) { gen_ = gen; }// setea la generación
};

