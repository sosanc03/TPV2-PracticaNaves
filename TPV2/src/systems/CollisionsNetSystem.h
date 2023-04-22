#pragma once
#include "../ecs/System.h"
#include "../components/FighterInfo.h"
#include "../components/BulletInfo.h"
#include "../components/Transform.h"
class CollisionsNetSystem :
    public System
{
public:
	CollisionsNetSystem();
	virtual ~CollisionsNetSystem();

	void receive(const Message&) override;
	void update() override;

private:
	void checkCollision();
	bool collides(Transform* obj1_, Transform* obj2_);
	void GameStart(const Message&);
	void GameOver(const Message&);

	bool active_;
};