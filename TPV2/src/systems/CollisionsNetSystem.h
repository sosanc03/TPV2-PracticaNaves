#pragma once
#include "../ecs/System.h"
#include "../components/FighterInfo.h"
#include "../components/BulletInfo.h"
class CollisionsNetSystem :
    public System
{
public:
	CollisionsNetSystem();
	virtual ~CollisionsNetSystem();

	void receive(const Message&) override;
	void initSystem() override;
	void update() override;

private:
	void handleGameStart(const Message&);
	void handleGameOver(const Message&);

	bool running_;
};