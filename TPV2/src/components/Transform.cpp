#include "Transform.h"


Transform::Transform() : Component() {
	position = new Vector2D(0, 0);
	velocity = new Vector2D(0, 0);
	width = 0;
	height = 0;
	rotation = 0;
	dir = Vector2D(0, 0);
}

Transform::Transform(Vector2D Position, Vector2D Velocity, float Width, float Heigth,  float Rotation) : Component() {
	position = Position;
	velocity = Velocity;
	width = Width;
	height = Heigth;
	rotation = Rotation;
}

void Transform::update()  {	
	position = position + velocity;	
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
	position = Position;
}

void Transform::setPosX(float X) {
	position.setX(X);
}

void Transform::setDir() {
	float angle = (rotation*PI)/180.0f;
	dir = Vector2D(sin(angle), -cos(angle));
}

void Transform::setPosY(float Y) {
	position.setY(Y);
}

void Transform::setVel(Vector2D Velocity) {
	velocity = Velocity;
}
