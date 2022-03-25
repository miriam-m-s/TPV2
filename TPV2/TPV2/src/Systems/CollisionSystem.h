#pragma once

#include "../ecs/System.h"

#include <vector>

class AsteroidsSystem;

class CollisionSystem : public ecs::System
{
public:

	__SYSID_DECL__(ecs::_sys_COLLISIONS);

	// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
	void recieve(const Message& m) override;
		// Inicializar el sistema, etc.
	void initSystem() override;
		// Si el juego est� parado no hacer nada, en otro caso comprobar colisiones como
		// en la pr�ctica 1 y enviar mensajes correspondientes.
	void update() override;

private:

	void AstFighterCollision(std::vector<ecs::Entity*> asteroids, ecs::Entity* fighter);

	void AstBulletCollision(std::vector<ecs::Entity*> asteroids, std::vector<ecs::Entity*> bullets, ecs::Entity* fighter);

	// Para gestionar el mensaje de que ha acabado una ronda. Desactivar el sistema.
	void onRoundOver();

		// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
	void onRoundStart();

		// Indica si el sistema est� activo o no (modificar el valor en onRoundOver y
		// onRoundStart, y en update no hacer nada si no est� activo)
	bool active_;

	AsteroidsSystem* astSys_;
};

