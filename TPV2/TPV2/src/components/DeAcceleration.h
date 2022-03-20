
// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"


struct DeAcceleration : public ecs::Component {
public:

	__CMPID_DECL__(ecs::_DEACCELERATION)

		DeAcceleration(): desa_(0.995f){
		};
	virtual ~DeAcceleration(){};

    inline void setDesaceleration(float des){
		desa_=des;
	}
	float  desa_;
	
};

