
 #pragma once

 #include "../ecs/Component.h"

 struct Health : ecs::Component {

 public:

 	__CMPID_DECL__(ecs::_HEALTHCTRL)

    Health():vidas_(3) {};
    virtual ~Health() {};

 	int vidas_;
 };


