#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <iostream>

const float PI = 3.1415;

class Transform : public Component {
private:
	Vector2D pos_;// posiciones
	Vector2D speed_;// velocidad
	Vector2D dir_;// direcci�n
	float w_;// ancho
	float h_;// altura
	float rot_;// rotaci�n



public:
	Transform();// contructora que setea todo a 0 por defecto
	Transform(Vector2D pos, Vector2D velocity, float width, float height, float rot = 0);// contructora
	virtual ~Transform() {}// destructora

	void update();// update

	float getW();// devuelve el ancho
	float getH();// devuelve el alto
	float getR();// devuelve la rota�ci�n
	Vector2D getDir();// devuelve la direcci�n
	inline Vector2D getPos() { return pos_; }// devuelve la posici�n
	inline Vector2D getVel() { return speed_; }// devuelve la velocidad

	void setW(float width);// setea  el ancho
	void setH(float height);// setea el alto
	void setR(float rot);// setea la rotaci�n
	void setDir();// setea la direcci�n
	void setPos(Vector2D pos);// setea la posici�n
	void setPosX(float x);// setea la posici�n en X
	void setPosY(float y);// setea la posici�n en Y
	void setVel(Vector2D velocity);// setea la velocidad
};