#include "Transform.h"


Transform::Transform() : Component() {
	pos = new Vector2D(0, 0);
	speed = new Vector2D(0, 0);
	width = 0;
	height = 0;
	rotation = 0;
	dir = Vector2D(0, 0);
}

Transform::Transform(Vector2D Position, Vector2D Velocity, float Width, float Heigth,  float Rotation) : Component() {
	pos = Position;
	speed = Velocity;
	width = Width;
	height = Heigth;
	rotation = Rotation;
}

void Transform::update()  {	
	pos = pos + speed;	
}

float Transform::getW() {
	return width;
}

float Transform::getH() {
	return height;
}

float Transform::getR() {
	return rotation;
}

Vector2D Transform::getDir() {
	return dir;
}

void Transform::setR(float Rotation) {
	rotation += Rotation;
	std::cout << rotation << endl;
	setDir();
}

void Transform::setH(float Height) {
	height = Height;
}

void Transform::setW(float Width) {
	width = Width;
}

void Transform::setPos(Vector2D Position) {
	pos = Position;
}

void Transform::setPosX(float X) {
	pos.setX(X);
}

void Transform::setDir() {
	float angle = (rotation*PI)/180.0f;
	dir = Vector2D(sin(angle), -cos(angle));
}

void Transform::setPosY(float Y) {
	pos.setY(Y);
}

void Transform::setVel(Vector2D Velocity) {
	speed = Velocity;
}
