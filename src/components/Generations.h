#pragma once
#include "../ecs/Component.h"
struct Generations : public Component
{
    int gen_ = 3;// n�mero de generaci�n
    Generations(int g) { gen_ = g; }
    ~Generations() {}
    
};

