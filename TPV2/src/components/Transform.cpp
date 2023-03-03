#include "Transform.h"


Transform::Transform() : Component() {
	pos_ = new Vector2D(0, 0);// posici�n
	speed_ = new Vector2D(0, 0);// velocidad
	w_ = 0;// ancho
	h_ = 0;// alto
	rot_ = 0;// rotaci�n
	dir_ = Vector2D(0, 0);// direcci�n
}

Transform::Transform(Vector2D pos, Vector2D velocity, float width, float height,  float rot) : Component() {
	pos_ = pos;// posici�n
	speed_ = velocity;// velocidad
	w_ = width;// ancho
	h_ = height;// alto
	rot_ = rot;// rotaci�n
}

void Transform::update()  {	
	pos_ = pos_ + speed_;// actualiza la posici�n	
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
	float angle = (rot_*PI)/180.0f;// �ngulo en radianes
	dir_ = Vector2D(sin(angle), -cos(angle));
}

void Transform::setPosY(float y) {
	pos_.setY(y);
}

void Transform::setVel(Vector2D velocity) {
	speed_ = velocity;
}
