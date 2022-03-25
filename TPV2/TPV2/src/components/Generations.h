// // This file is part of the course TPV2@UCM - Samir Genaim

 #pragma once
 #include "../ecs/Component.h"

 struct Generations : ecs::Component {
 public:

     __CMPID_DECL__(ecs::_GENERATIONS);

    Generations(int generations) :numgenerations(generations) {};
    virtual ~Generations() {};

 	int numgenerations;
 };

