#pragma once

#include <vector>
#include "../utils/Singleton.h"

using namespace std;

class Entity;

class Manager : public Singleton <Manager> { 	
private:
	std::vector<Entity*> ents_;
public:
	Manager();
	virtual ~Manager();

	Entity* addEntity();
	void refresh();
	void update();
	void render();
};