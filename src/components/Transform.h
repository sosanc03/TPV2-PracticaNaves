#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <iostream>

const float PI = 3.1415;

struct Transform : public Component {
	Vector2D pos_;// posiciones
	Vector2D speed_;// velocidad
	Vector2D dir_;// dirección
	float w_;// ancho
	float h_;// altura
	float rot_;// rotación

	Transform(Vector2D pos, Vector2D velocity, float width, float height, float rot = 0) {
		pos_ = pos;// posición
		speed_ = velocity;// velocidad
		w_ = width;// ancho
		h_ = height;// alto
		rot_ = rot;// rotación
	}

	Transform() : Component() {
		pos_ = new Vector2D(0, 0);// posición
		speed_ = new Vector2D(0, 0);// velocidad
		w_ = 0;// ancho
		h_ = 0;// alto
		rot_ = 0;// rotación
		dir_ = Vector2D(0, 0);// dirección
	}

	virtual ~Transform() {}// destructora

	void move() {
		pos_ = pos_ + speed_;
	}
};