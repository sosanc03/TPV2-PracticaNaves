#pragma once
#include "../ecs/Component.h"
struct Generations : public Component
{
    int gen_ = 3;// número de generación
    Generations(int g) { gen_ = g; }
    ~Generations() {}
    
};

