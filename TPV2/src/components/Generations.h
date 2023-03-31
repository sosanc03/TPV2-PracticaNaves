#pragma once
#include "../ecs/Component.h"
struct Generations : public ecs::Component
{
    Generations() {}
    ~Generations() {}
    int gen_;// número de generación
};

