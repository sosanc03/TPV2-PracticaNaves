#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <iostream>

const float PI = 3.1415;

class Transform : public Component {
private:
	Vector2D position;
	Vector2D velocity;
	Vector2D dir;
	float width;
	float height;
	float rotation;


public:
	Transform();
	Transform(Vector2D Position, Vector2D Velocity, float Width, float Heigth, float Rotation = 0);
	virtual ~Transform() {}

	void update();

	float getW();
	float getH();
	float getR();
	Vector2D getDir();
	inline Vector2D getPos() { return position; }
	inline Vector2D getVel() { return velocity; }

	void setDir();
	void setR(float valRot);
	void setH(float valHei);
	void setW(float valWid);
	void setPos(Vector2D Velocity);
	void setPosX(float X);
	void setPosY(float Y);
	void setVel(Vector2D Velocity);
};