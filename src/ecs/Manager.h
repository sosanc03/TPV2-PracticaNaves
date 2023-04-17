#pragma once
#include <array>
#include <vector>
#include "../utils/Singleton.h"
#include "System.h"

using namespace std;

class Entity;

class Manager : public Singleton <Manager> {
private:
    array<vector<Entity*>, maxGroupId> entsByGroup_;

    array<System*, maxSystemId> sys;
    vector<Message> msgs;
    vector<Message> auxmsgs;
public:
    Manager();
    virtual ~Manager();

    Entity* addEntity(grpId_type gId = _grp_GENERAL);

    inline const auto& getEntitiesByGroup(grpId_type gId) {
        return entsByGroup_[gId];
    }

    void refresh();
    void update();
    void render();

    void updateSystems();

    template<typename T, typename ...Ts>
    inline T* addSystem(sysId_type sId, Ts &&... args) {
        removeSystem<T>(sId);
        System* s = new T(std::forward<Ts>(args)...);
        s->setContext(this);
        s->initSystem();
        sys[sId] = s;
        return static_cast<T*>(s);
    }

    template<typename T>
    inline T* getSystem(sysId_type sId) {
        return static_cast<T*>(sys[sId]);
    }

    template<typename T>
    inline void removeSystem(sysId_type sId) {
        if (sys[sId] != nullptr) {
            delete sys[sId];
            sys[sId] = nullptr;
        }
    }

    inline void send(const Message& m, bool delay = false) {
        if (!delay) {
            for (System* s : sys) {
                if (s != nullptr)
                    s->receive(m);
            }
        }
        else {
            msgs.emplace_back(m);
        }
    }

    inline void flushMessages() {
        std::swap(msgs, auxmsgs);
        for (auto& m : auxmsgs) {
            for (System* s : sys) {
                if (s != nullptr)
                    s->receive(m);
            }
        }
        auxmsgs.clear();
    }
};