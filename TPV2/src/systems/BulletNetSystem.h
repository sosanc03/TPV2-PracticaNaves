#pragma once
#include "../ecs/System.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
#include "../systems/NetworkSystem.h"
#include "../components/BulletInfo.h"
#include "../components/DisableOnExit.h"

class BulletNetSystem :
    public System
{
public:
	BulletNetSystem();
	virtual ~BulletNetSystem();

	void receive(const Message&) override;
	void initSystem() override;
	void update() override;

	void createNewBullet(float posX, float posY, float velX, float velY, int id);
private:
	void handleShoot(const Message&);
	void GameOver(const Message&);
	void GameStart(const Message&);

	void DisableOnExitUpdate(Entity* a, Transform* tr_);

	int cont_;
	bool running_;
};
