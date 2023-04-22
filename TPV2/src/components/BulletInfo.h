#pragma once
#include "../ecs/Component.h"
struct BulletInfo : public Component
{
    BulletInfo(int id) {
        id_ = id;
    }
    uint32_t id_;
};

