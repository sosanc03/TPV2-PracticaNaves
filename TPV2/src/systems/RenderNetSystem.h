#pragma once
#include "../ecs/System.h"
#include <string>
class RenderNetSystem :
    public System
{
public:

	void receive(const Message&) override;
	RenderNetSystem();
	virtual ~RenderNetSystem();
	void initSystem() override;
	void update() override;

private:
	void drawMsgs();
	void drawFighters();
	void drawFigh(Entity* e);
	void drawBullets();
	void draw(Entity* e);
	void drawId(Entity* e);

	void handleGameStart(const Message&);
	void handleGameOver(const Message&);
	void drawBox(Entity* e);

	void drawWaitingMsg();


	bool running_;
	bool over_;
	uint32_t killedId_;

};


