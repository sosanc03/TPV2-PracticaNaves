#pragma once
#include "../ecs/System.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
#include "../systems/NetworkSystem.h"
#include "../components/BulletInfo.h"
class BulletNetSystem :
    public System
{
public:
	BulletNetSystem();
	virtual ~BulletNetSystem();

	void receive(const Message&) override;
	void initSystem() override;
	void update() override;

	void changeBulletPos(float x, float y, float rot);
	void createNewBullet(float posX, float posY, float velX, float velY, int id);
private:
	void handleShoot(const Message&);
	void handleGameOver(const Message&);
	void handleGameStart(const Message&);

	//void DisableOnExitUpdate(Entity* a);

	bool running_;
};
