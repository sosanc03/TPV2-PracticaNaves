#include "Transform.h"


Transform::Transform() : Component() {
	pos_ = new Vector2D(0, 0);
	speed_ = new Vector2D(0, 0);
	w_ = 0;
	h_ = 0;
	rot_ = 0;
	dir_ = Vector2D(0, 0);
}

Transform::Transform(Vector2D pos, Vector2D velocity, float width, float height,  float rot) : Component() {
	pos_ = pos;
	speed_ = velocity;
	w_ = width;
	h_ = height;
	rot_ = rot;
}

void Transform::update()  {	
	pos_ = pos_ + speed_;	
}

float Transform::getW() {
	return w_;
}

float Transform::getH() {
	return h_;
}

float Transform::getR() {
	return rot_;
}

Vector2D Transform::getDir() {
	return dir_;
}

void Transform::setR(float rot) {
	rot_ += rot;
	setDir();
}

void Transform::setH(float height) {
	h_ = height;
}

void Transform::setW(float width) {
	w_ = width;
}

void Transform::setPos(Vector2D pos) {
	pos_ = pos;
}

void Transform::setPosX(float x) {
	pos_.setX(x);
}

void Transform::setDir() {
	float angle = (rot_*PI)/180.0f;
	dir_ = Vector2D(sin(angle), -cos(angle));
}

void Transform::setPosY(float y) {
	pos_.setY(y);
}

void Transform::setVel(Vector2D velocity) {
	speed_ = velocity;
}
