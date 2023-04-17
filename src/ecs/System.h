#pragma once
#include "ecs.h"

class Manager;
using namespace ecs;

class System {
public:
	virtual ~System() { }
	void setContext(Manager* mngr) {
		mngr_ = mngr;
	}
	virtual void initSystem() { }
	virtual void update() { }
	virtual void receive(const Message&) { }
protected:
	Manager* mngr_;
};