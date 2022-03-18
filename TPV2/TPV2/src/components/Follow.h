
#pragma once
#include "../ecs/Component.h"
class Transform;



#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"
class Follow : public ecs::Component {
public:

	__CMPID_DECL__(ecs::_FOLLOW);


		Follow(ecs::Entity* fighter);
	virtual ~Follow();


	void initComponent() override;
	void update()override;

private:
	Transform* tr_;
	ecs::Entity* fight;
	Transform* caza;
	
};
 
