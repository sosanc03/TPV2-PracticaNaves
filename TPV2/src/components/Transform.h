#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <iostream>

const float PI = 3.1415;

class Transform : public Component {
private:
	Vector2D pos_;
	Vector2D speed_;
	Vector2D dir_;
	float w_;
	float h_;
	float rot_;


public:
	Transform();
	Transform(Vector2D pos, Vector2D velocity, float width, float height, float rot = 0);
	virtual ~Transform() {}

	void update();

	float getW();
	float getH();
	float getR();
	Vector2D getDir();
	inline Vector2D getPos() { return pos_; }
	inline Vector2D getVel() { return speed_; }

	void setW(float width);
	void setH(float height);
	void setR(float rot);
	void setDir();
	void setPos(Vector2D pos);
	void setPosX(float x);
	void setPosY(float y);
	void setVel(Vector2D velocity);
};