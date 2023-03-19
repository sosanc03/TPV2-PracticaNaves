// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"

class Transform;

struct FighterCtrl : public ecs::Component {
public:

	//__CMPID_DECL__(ecs::_FIGHTERCTRL)

		FighterCtrl() {};
	virtual ~FighterCtrl() {};

	float thurst = 0.2f;
	float speedLimit = 3.0f;
};

