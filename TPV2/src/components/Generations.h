#pragma once
#include "../ecs/Component.h"
class Generations :
    public Component
{
private:
    int gen_;
public:
    Generations(int gen) {
        gen_ = gen;
    }

    int getGen() { return gen_; }

    void setGen(int gen) { gen_ = gen; }
};

