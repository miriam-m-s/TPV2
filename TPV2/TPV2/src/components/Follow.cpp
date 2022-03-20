// #include "Follow.h"
// #include <cassert>

// #include "../ecs/Entity.h"
// #include "../sdlutils/SDLUtils.h"
// #include "Transform.h"

// Follow::Follow(ecs::Entity* fighter):tr_(nullptr),fight(fighter)
// {
// }

// Follow::~Follow()
// {
// }

// void Follow::initComponent()
// {
// 	tr_ = ent_->getComponent<Transform>();
// 	assert(tr_ != nullptr);
//     caza= fight->getComponent<Transform>();
// 	assert(caza != nullptr);
// }

// void Follow::update()
// {
// 	auto & v = tr_->getVel();
// 	auto p = tr_->getPos();
// 	auto q = caza->getPos();
// 	v=v.rotate(v.angle(q - p) > 0 ? 1.0f : -1.0f);
// }
