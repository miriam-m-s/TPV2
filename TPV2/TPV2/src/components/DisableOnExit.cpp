// #include "DisableOnExit.h"

// #include "Transform.h"
// #include <cassert>
// #include "..\ecs\Entity.h"
// #include "../sdlutils/SDLUtils.h"



// DisableOnExit::DisableOnExit() : tr()
// {
// }

// DisableOnExit::~DisableOnExit()
// {
// }
// void DisableOnExit::initComponent()
// {
//     tr = ent_->getComponent<Transform>();
//     assert(tr!= nullptr);
// }
// void DisableOnExit::update()
// {
//     //limites de X
//     if (tr->getPos().getX() <= 0 || tr->getPos().getX() >= sdlutils().width()) {
//         ent_->setAlive(false);
//     }

//     //limites de Y
//     if (tr->getPos().getY() <= 0 || tr->getPos().getY() >= sdlutils().height()) {
//         ent_->setAlive(false);
//     }
// }

