#pragma once
#include "../ecs/System.h"
#include <string>

using namespace std;
class RenderNetSystem :
    public System
{
public:

	RenderNetSystem();
	virtual ~RenderNetSystem();

	void receive(const Message&) override;
	void update() override;

private:
	void renderText();
	void renderFighters();
	void renderFighter(Entity* e);
	void renderBullets();
	void renderEntity(Entity* e);
	void renderName(Entity* e);

	void GameStart(const Message&);
	void GameOver(const Message&);

	void renderWaitingText();


	bool active_;
	bool gameOver_;
	uint32_t killedId_;

};


