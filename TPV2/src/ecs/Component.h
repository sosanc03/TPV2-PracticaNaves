#pragma once
class Entity;

class Component
{
protected:
	Entity* ent_;
public:
	Component() : ent_() {}
	virtual ~Component() {}
	inline void setContext(Entity* ent) {
		ent_ = ent;
	}

	virtual void initComponent() { }
	virtual void update() { }
	virtual void render() { }

};

