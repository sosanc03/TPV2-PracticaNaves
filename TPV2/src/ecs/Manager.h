#pragma once
#include <vector>
#include "Entity.h"
#include "../utils/Singleton.h"
using namespace std;

class Manager:public Singleton <Manager> {
protected:
	vector<Entity*> ents_;
public:

	Manager() {
		ents_.reserve(100);
	}

	virtual ~Manager() {
		for (auto e : ents_) {
			delete e;
		}
	}

	template<typename T>
	Entity* addEntity(T* e) {
		e->setAlive(true);
		ents_.push_back(e);
		return e;
	}


	virtual void refresh() {
		ents_.erase(
			remove_if(ents_.begin(), ents_.end(), [](Entity* e) {
				if (e->isAlive()) {
					return false;
				}
				else {
					delete e;
					return true;
				}
				}),
			ents_.end());
	}

	virtual void update() {
		auto n = ents_.size();
		for (auto i = 0; i < n; i++)
			ents_[i]->update();
	}

	virtual void render() {
		auto n = ents_.size();
		for (auto i = 0; i < n; i++)
			ents_[i]->render();
	}

	virtual string getStateID() { return "nothing"; };

};
