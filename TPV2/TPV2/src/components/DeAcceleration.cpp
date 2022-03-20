// #include "DeAcceleration.h"
// #include <cassert>
// #include "../ecs/Entity.h"
// #include "../ecs/Manager.h"
// #include "../sdlutils/SDLUtils.h"
// #include "Image.h"
// #include "Transform.h"
// DeAcceleration::DeAcceleration() :
// 	tr_(nullptr), desa_(0.995f)
// {
// }

// DeAcceleration::~DeAcceleration()
// {
// }

// void DeAcceleration::initComponent()
// {
// 	tr_ = ent_->getComponent<Transform>();
// 	assert(tr_ != nullptr);
	
// }

// void DeAcceleration::update()
// {
// 	auto& vel_ = tr_->getVel();

// 	vel_.set(vel_ * desa_);

// 	if (vel_.magnitude() < 0.05f) {

// 		vel_.set(0.0f, 0.0f);
// 	}
// }
