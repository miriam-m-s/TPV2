#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

class RenderSystem : public ecs::System {
public:

	__SYSID_DECL__(ecs::_sys_RENDER)

		RenderSystem();
	virtual ~RenderSystem();
	void initSystem() override;
	void update() override;

private:
	void drawAsteroids();
	void drawBullet();
	void drawFighter();
	void drawState();
};

