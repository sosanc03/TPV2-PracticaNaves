#include "Manager.h"
#include "Entity.h"

Manager::Manager() : entsByGroup_() {
    for (auto& groupEntities : entsByGroup_) {
        groupEntities.reserve(100);
    }
}

Manager::~Manager() {
    for (auto& ents : entsByGroup_) {
        for (auto e : ents)
            delete &e;
    }
}

Entity* Manager::addEntity(grpId_type gId) {
    Entity* e = new Entity();
    e->setAlive(true);
    e->setContext(this);
    e->addToGroup(gId);
    entsByGroup_[gId].push_back(e);
    return e;
}

void Manager::refresh() {
    for (grpId_type gId = 0; gId < maxGroupId; gId++) {
        auto& grpEnts = entsByGroup_[gId];
        grpEnts.erase(
            std::remove_if(grpEnts.begin(), grpEnts.end(),
                [](Entity* e) {
                    if (e->isAlive()) {
                        return false;
                    }
                    else {
                        delete e;
                        return true;
                    }
                }),
            grpEnts.end());
    }
}

void Manager::update() {
    for (auto& ents : entsByGroup_) {
        auto n = ents.size();
        for (auto i = 0u; i < n; i++)
            ents[i]->update();
    }
}
void Manager::render() {
    for (auto& ents : entsByGroup_) {
        auto n = ents.size();
        for (auto i = 0u; i < n; i++)
            ents[i]->render();
    }
}



void Manager::updateSystems() {
    for (auto& system : sys) {
        system->update();
    }
}