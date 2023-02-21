#pragma once

namespace ecs {
	using cmpId_type = unsigned __int8;
	enum cmpId : cmpId_type {
		_TRANSFORM = 0,
		_IMAGE = 1,
		_CTRL = 2,
		_HEALTH = 3,
		_DEACCELERATION = 4,
		_GUN = 5,
		_OPPOSITESIDE = 6,

		// do not remove this
		_LAST_CMP_ID
	};
	constexpr cmpId_type maxComponentId = _LAST_CMP_ID;
}
