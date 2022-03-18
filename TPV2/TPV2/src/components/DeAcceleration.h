
// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"

class Transform;

class DeAcceleration : public ecs::Component {
public:

	__CMPID_DECL__(ecs::_DEACCELERATION)

		DeAcceleration();
	virtual ~DeAcceleration();
	void initComponent() override;
	void update() override;

private:
	float  desa_;
	Transform* tr_;
};

