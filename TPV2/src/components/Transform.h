#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <iostream>

const float PI = 3.1415;

class Transform : public Component {
private:
	Vector2D pos_;// posiciones
	Vector2D speed_;// velocidad
	Vector2D dir_;// dirección
	float w_;// ancho
	float h_;// altura
	float rot_;// rotación



public:
	Transform();// contructora que setea todo a 0 por defecto
	Transform(Vector2D pos, Vector2D velocity, float width, float height, float rot = 0);// contructora
	virtual ~Transform() {}// destructora

	void update();// update

	float getW();// devuelve el ancho
	float getH();// devuelve el alto
	float getR();// devuelve la rota´ción
	Vector2D getDir();// devuelve la dirección
	inline Vector2D getPos() { return pos_; }// devuelve la posición
	inline Vector2D getVel() { return speed_; }// devuelve la velocidad

	void setW(float width);// setea  el ancho
	void setH(float height);// setea el alto
	void setR(float rot);// setea la rotación
	void setDir();// setea la dirección
	void setPos(Vector2D pos);// setea la posición
	void setPosX(float x);// setea la posición en X
	void setPosY(float y);// setea la posición en Y
	void setVel(Vector2D velocity);// setea la velocidad
};