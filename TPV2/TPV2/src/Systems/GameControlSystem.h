#pragma once

#include "../ecs/System.h"

class Entity;

class GameControlSystem:public ecs::System
{
public:

	__SYSID_DECL__(ecs::_sys_GAMECONTROL);

	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void recieve(const Message& m) override;
		// Inicializar el sistema, etc.
	void initSystem() override;
		// Si el juego no está parado y el jugador pulsa SDLK_SPACE cambia el estado
		// como en la práctica 1, etc. Tiene que enviar mensajes correspondientes cuando
		// empieza una ronda o cuando empieza una nueva partida.
	void update() override;

private:
	// Para gestionar el mensaje de que ha habido un choque entre el fighter y un
	// un asteroide. Tiene que avisar que ha acabado la ronda, quitar una vida
	// al fighter, y si no hay más vidas avisar que ha acabado el juego (y quien
	// es el ganador).
	void onCollision_FighterAsteroid();

		// Para gestionar el mensaje de que no hay más asteroides. Tiene que avisar que
		// ha acabado la ronda y además que ha acabado el juego (y quien es el ganador)
	void onAsteroidsExtinction();

	int winner_; // 0 - None, 1 - Asteroids, 2- Fighter
	int state_; // El estado actual del juego (en lugar del componente State)

	ecs::Entity* gamemanager;

};

