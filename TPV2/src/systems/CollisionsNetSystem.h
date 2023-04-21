#pragma once
#include "../ecs/System.h"
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