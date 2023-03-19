#pragma once
#include "../ecs/System.h"
#include "../CheckML.h"
class FighterGunSystem :public ecs::System
{
public:
	__SYSID_DECL__(ecs::_sys_GUN)
		// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
		void recieve(const Message& m) override ;
	// Inicializar el sistema, etc.
	void initSystem() override {};

	FighterGunSystem();
	virtual ~FighterGunSystem();

	void update() override;
	void shoot();
private:


	void onRoundOver();
	void onRoundStart();

	float bulletTime = 0.0;
	int numAsteroids = 0;
	float asteroidTime = 0;
	// Indica si el sistema está activo o no 
	bool active_;
};


