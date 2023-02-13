#pragma once
#include "Component.h"
#include "ecs.h"
#include <array>
#include <vector>
#include <bitset>
#include <iostream>

using namespace std;

class Entity
{
private:
	bool alive_;
	vector<Component*> currCmps_;
	array<Component*, maxComponentId> cmps_;
public:
	Entity() :cmps_(), currCmps_(), alive_() {

		currCmps_.reserve(maxComponentId);
	}

	virtual ~Entity() {
		for (auto c : currCmps_) {
			delete c;
		}
	}

	inline bool isAlive() {
		return alive_;
	}

	inline void setAlive(bool alive) {
		alive_ = alive;
	}

	template<typename T, typename ...Ts>
	inline T* addComponent(cmpId_type cId, Ts&... args) {
		T* c = new T(forward<Ts>(args)...);
		removeComponent(cId);
		currCmps_.push_back(c);
		cmps_[cId] = c;
		c->setContext(this);
		c->initComponent();
		return c;
	}

	inline void removeComponent(cmpId_type cId) {
		if (cmps_[cId] != nullptr) {
			auto iter = std::find(currCmps_.begin(),
				currCmps_.end(),
				cmps_[cId]);
			currCmps_.erase(iter);
			delete cmps_[cId];
			cmps_[cId] = nullptr;
		}
	}

	template<typename T>
	inline T* getComponent(cmpId_type cId) {
		return static_cast<T*>(cmps_[cId]);
	}

	inline bool hasComponent(cmpId_type cId) {
		return cmps_[cId] != nullptr;
	}

	inline void update() {
		auto n = currCmps_.size();
		for (auto i = 0u; i < n; i++)
			currCmps_[i]->update();
	}
	

	inline void render() {
		auto n = currCmps_.size();
		for (auto i = 0u; i < n; i++)
			currCmps_[i]->render();
	}

};

