#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <iostream>

const float PI = 3.1415;

struct Transform : public Component {
	Vector2D pos_;// posiciones
	Vector2D speed_;// velocidad
	Vector2D dir_;// direcci�n
	float w_;// ancho
	float h_;// altura
	float rot_;// rotaci�n

	Transform(Vector2D pos, Vector2D velocity, float width, float height, float rot = 0) {
		pos_ = pos;// posici�n
		speed_ = velocity;// velocidad
		w_ = width;// ancho
		h_ = height;// alto
		rot_ = rot;// rotaci�n
	}

	Transform() : Component() {
		pos_ = new Vector2D(0, 0);// posici�n
		speed_ = new Vector2D(0, 0);// velocidad
		w_ = 0;// ancho
		h_ = 0;// alto
		rot_ = 0;// rotaci�n
		dir_ = Vector2D(0, 0);// direcci�n
	}

	virtual ~Transform() {}// destructora

	void move() {
		pos_ = pos_ + speed_;
	}
};