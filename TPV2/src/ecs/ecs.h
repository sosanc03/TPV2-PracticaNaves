#pragma once

namespace ecs {
	using cmpId_type = unsigned __int8;
	enum cmpId : cmpId_type {
		TRANSFORM_H = 0,
		IMAGE_H = 1,
		FIGHTERCTRL_H = 2,
		HEALTH_H = 3,
		DEACCELERATION_H = 4,
		GUN_H = 5,
		OPPOSITESIDE_H = 6,
		FOLLOW_H = 7,
		DISABLEONEXIT_H = 8,
		GENERATIONS_H = 9,
		// do not remove this
		_LAST_CMP_ID
	};
	constexpr cmpId_type maxComponentId = _LAST_CMP_ID;

	using grpId_type = unsigned __int8;
	enum grpId : grpId_type {
		_grp_ASTEROIDS = 0,
		_grp_BULLETS = 1,
		_LAST_GRP_ID
	};
	constexpr grpId_type maxGroupId = _LAST_GRP_ID;
}
