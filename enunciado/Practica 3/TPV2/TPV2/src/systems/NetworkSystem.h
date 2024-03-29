#pragma once
#include <SDL_net.h>
#include <SDL_stdinc.h>

#include "../ecs/System.h"
#include <string>
#include <array>
#include "network_messages.h"
struct Transform;

class NetworkSystem : public ecs::System {
public:

	__SYSID_DECL__(ecs::_sys_NETWORK)

		NetworkSystem();
	virtual ~NetworkSystem();

	void recieve(const Message&) override;
	void initSystem() override;
	void update() override;

	void putName();
	bool connect();
	void disconnect();

	inline Uint8 getSide() {
		return side_;
	}

	inline bool isReday() {
		return connected_;
	}

	inline bool isHost() {
		return host_;
	}

	inline Uint16 getPort() {
		return port_;
	}
	
	inline std::string getName(int i) {
		return names[i];
	}

	void sendFighterPosition(Transform* tr);
	void sendBulletPosition(Transform* tr);
	
	void sendStarGameRequest();
	void sendBulletShot(float posX, float posY, float velX, float velY);

	void string_to_chars(std::string& str, char c_str[11]);
	void chars_to_string(std::string& str, char c_str[11]);
private:

	bool initHost();
	bool initClient(); 
	bool initConnection(Uint16 port);

	void handleConnectionRequest();
	void handleFighterPos();
	void handleBulletShot();

	void handleStartGameRequest();
	void handleStartTheGame();
	void handleGameOver();
	void handleDisconnecting();

	void tellOtherClientToStartGame();


	bool host_;
	Uint8 side_; // 0 left 1 right
	UDPsocket sock_;
	UDPpacket* p_;
	SDLNet_SocketSet sockSet_;
	Uint16 port_;

	bool connected_;
	IPaddress otherPlayerAddr_;

	std::array<std::string, 2> names;
	std::string name;
};

