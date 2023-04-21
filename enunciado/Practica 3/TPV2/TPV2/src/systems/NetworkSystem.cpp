// This file is part of the course TPV2@UCM - Samir Genaim

#include "NetworkSystem.h"

#include <iostream>

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLNetUtils.h"
#include "../utils/Vector2D.h"
#include "GameCtrlSystem.h"
#include "network_messages.h"
#include "FightersSystem.h"
#include "BulletsSystem.h"

NetworkSystem::NetworkSystem() :
	host_(false), //
	side_(0), //
	sock_(), //
	p_(), //
	sockSet_(), //
	port_(), //
	connected_(false), //
	otherPlayerAddr_(), name() {

}

NetworkSystem::~NetworkSystem() {
	if (p_ != nullptr) {
		SDLNet_UDP_Close(sock_);
		SDLNet_FreePacket(p_);
	}
}

void NetworkSystem::recieve(const Message& m) {
	if (!host_)
		return;

	switch (m.id) {
	case _m_GAME_START:
		tellOtherClientToStartGame();
		break;
	default:
		break;
	}
}

void NetworkSystem::initSystem() {
}

void NetworkSystem::putName()
{

	bool done = false;
	bool success = false;
	names[0] = "Player 1";
	names[1] = "Player 2";
	while (!done) {

		std::cout << "Please, enter your UserName: \n";
		std::cin >> name;
		if (name.length() <= 10) {
			done = true;
		}
		else
			std::cout << "The name must have less than 10 characters\n";
	}
}
bool NetworkSystem::connect() {

	char choice;
	bool done = false;
	bool success = false;

	while (!done) {

		std::cout << "Do you want to be host, client or exit [h/c/e]? "
			<< std::endl;
		std::cin >> choice;
		switch (choice) {
		case 'h':
		case 'H':
			success = initHost();
			done = true;
			break;
		case 'c':
		case 'C':
			success = initClient();
			done = true;
			break;
		case 'e':
		case 'E':
			done = true;
			break;
		default:
			break;
		}
	}

	return success;
}

void NetworkSystem::disconnect() {
	if (!connected_)
		return;

	net::Message m;

	m.id = net::_DISCONNECTING;
	p_->address = otherPlayerAddr_;
	SDLNetUtils::serializedSend(m, p_, sock_);

}

void NetworkSystem::update() {
	net::Message m;
	while (SDLNetUtils::deserializedReceive(m, p_, sock_) > 0) {
		switch (m.id) {
		case net::_CONNECTION_REQUEST:
			handleConnectionRequest();
			break;
		case net::_FIGHTER_POS:
			handleFighterPos();
			break;
		case net::_BULLET_SHOT:
			handleBulletShot();
			break;
		case net::_START_GAME_REQUEST:
			handleStartGameRequest();
			break;
		case net::_START_THE_GAME:
			handleStartTheGame();
			break;
		case net::_DISCONNECTING:
			handleDisconnecting();
			break;
		default:
			break;
		}

	}

}

bool NetworkSystem::initConnection(Uint16 port) {
	sock_ = SDLNet_UDP_Open(port);
	if (!sock_) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	sockSet_ = SDLNet_AllocSocketSet(1);
	if (!sockSet_) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	SDLNet_UDP_AddSocket(sockSet_, sock_);
	p_ = SDLNet_AllocPacket(512);
	if (!p_) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	port_ = SDLNetUtils::getSocketPort(sock_);

	return true;
}

bool NetworkSystem::initHost() {

	Uint16 port;
	std::cout << "Enter a port number to use: ";
	if (!(std::cin >> port)) {
		std::cerr << "Invalid port" << std::endl;
		return false;
	}

	if (!initConnection(port))
		return false;
	host_ = true;
	side_ = 0;
	connected_ = false;
	names[side_] = name;
	return true;

}

bool NetworkSystem::initClient() {

	Uint16 port;
	std::string host;

	std::cout << "Enter the host and port (separated by space) of the host: "
		<< std::endl;
	if (!(std::cin >> host >> port)) {
		std::cerr << "Invalid host/port" << std::endl;
		return false;
	}

	if (SDLNet_ResolveHost(&otherPlayerAddr_, host.c_str(), port) < 0) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	host_ = false;

	initConnection(0);

	char nameToSend[11];

	net::NameMessage m;
	m.id = net::_CONNECTION_REQUEST;
	string_to_chars(name, m.nameSend);
	p_->address = otherPlayerAddr_;
	
	SDLNetUtils::serializedSend(m, p_, sock_);

	if (SDLNet_CheckSockets(sockSet_, 3000)) {
		if (SDLNet_SocketReady(sock_)) {
			SDLNetUtils::deserializedReceive(m, p_, sock_);
			if (m.id == net::_REQUEST_ACCEPTED) {
				net::ReqAccMsg m;
				m.deserialize(p_->data);
				side_ = m.side;
				host_ = false;
				connected_ = true;
				names[side_] = name;
				chars_to_string(names[1 - side_], m.nameSend);
			}

		}
	}

	if (!connected_) {
		std::cout << "Could not connect to the other player " << std::endl;
		return false;
	}

	return true;

}

void NetworkSystem::sendFighterPosition(Transform* tr) {
	if (!connected_)
		return;

	net::FighterPosMsg m;
	m.id = net::_FIGHTER_POS;
	m.side = side_;
	m.x = tr->pos_.getX();
	m.y = tr->pos_.getY();
	m.rot = tr->rot_;
	p_->address = otherPlayerAddr_;
	SDLNetUtils::serializedSend(m, p_, sock_, otherPlayerAddr_);
}

void NetworkSystem::sendBulletPosition(Transform* tr) {
	if (!connected_)
		return;

	net::BulletPosMsg m;
	m.id = net::_BULLET_POS;
	m.side = side_;
	m.x = tr->pos_.getX();
	m.y = tr->pos_.getY();
	m.rot = tr->rot_;
	p_->address = otherPlayerAddr_;
	SDLNetUtils::serializedSend(m, p_, sock_, otherPlayerAddr_);
}

void NetworkSystem::handleConnectionRequest() {

	if (!connected_ && host_) {
		net::NameMessage mH;
		mH.deserialize(p_->data);
		chars_to_string(names[1 - side_], mH.nameSend);

		otherPlayerAddr_ = p_->address;
		connected_ = true;
		net::ReqAccMsg m;
		m.id = net::_REQUEST_ACCEPTED;
		string_to_chars(name, m.nameSend);
		m.side = 1 - side_;
		SDLNetUtils::serializedSend(m, p_, sock_, otherPlayerAddr_);
	}
}

void NetworkSystem::sendStarGameRequest() {
	assert(!isHost());

	net::StartRequestMsg m;

	m.id = net::_START_GAME_REQUEST;
	m.side = side_;
	p_->address = otherPlayerAddr_;
	SDLNetUtils::serializedSend(m, p_, sock_, otherPlayerAddr_);

}

void NetworkSystem::sendBulletShot(float posX, float posY, float velX, float velY)
{
	net::BulletShotMsg m;
	if (!connected_)
		return;

	m.id = net::_BULLET_SHOT;
	m.side = side_;
	m.posX = posX;
	m.posY = posY;
	m.velX = velX;
	m.velY = velY;
	p_->address = otherPlayerAddr_;
	SDLNetUtils::serializedSend(m, p_, sock_, otherPlayerAddr_);
}

void NetworkSystem::handleFighterPos() {
	net::FighterPosMsg m;
	m.deserialize(p_->data);
	mngr_->getSystem<FightersSystem>()->changeFighterPos(m.side, m.x, m.y, m.rot);
}


void NetworkSystem::handleBulletShot()
{
	net::BulletShotMsg m;
	m.deserialize(p_->data);
	mngr_->getSystem<BulletsSystem>()->createNewBullet(m.posX, m.posY, m.velX, m.velY);
}

void NetworkSystem::handleStartGameRequest() {
	mngr_->getSystem<GameCtrlSystem>()->startGame();
}

void NetworkSystem::handleStartTheGame() {
	assert(!host_);
	mngr_->getSystem<GameCtrlSystem>()->startGame();
}

void NetworkSystem::handleGameOver() {
	assert(!host_);
	mngr_->getSystem<GameCtrlSystem>()->gameOver();
}

void NetworkSystem::handleDisconnecting() {
	connected_ = false;
	host_ = true;
	side_ = 0;
	names[0] = name;
	mngr_->getSystem<GameCtrlSystem>()->stopTheGame();
}

void NetworkSystem::tellOtherClientToStartGame() {
	net::Message m;

	m.id = net::_START_THE_GAME;
	SDLNetUtils::serializedSend(m, p_, sock_, otherPlayerAddr_);
}

void NetworkSystem::string_to_chars(std::string& str, char c_str[11])
{
	auto i = 0u;
	for (; i < str.size() && i < 10; i++) c_str[i] = str[i];
	c_str[i] = 0;

}
void NetworkSystem::chars_to_string(std::string& str, char c_str[11])
{
	c_str[10] = 0;
	str = std::string(c_str);
}


