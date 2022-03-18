
#pragma once
#include "../ecs/Component.h"

class Transform;

class DisableOnExit : public ecs::Component {
public:

	
	__CMPID_DECL__(ecs::_DISABLEGUN)

		DisableOnExit();
	virtual ~DisableOnExit();
	void initComponent() override;
	void update() override;

private:
	float initime = 0;
	Transform* tr;
};

