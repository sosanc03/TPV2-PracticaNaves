#pragma once
#include "../ecs/Component.h"
class Generations :
    public Component
{
private:
    int gen_;// n�mero de generaci�n
public:
    Generations(int gen) {// constructora
        gen_ = gen;// generaci�n
    }

    int getGen() { return gen_; }// devuelve la generaci�n

    void setGen(int gen) { gen_ = gen; }// setea la generaci�n
};

