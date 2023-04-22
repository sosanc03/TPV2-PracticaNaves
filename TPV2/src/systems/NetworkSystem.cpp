#include "NetworkSystem.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLNetUtils.h"
#include "../utils/Vector2D.h"
#include "GameCtrlSystem.h"
#include "../ecs/network_messages.h"
#include "FighterCtrlNetSystem.h"
#include "BulletNetSystem.h"
#include <iostream>
#include "GameCtrlNetSystem.h"

// constructora
NetworkSystem::NetworkSystem(){
	host_ = false;// booleano de host
	side_ = 0;// lado en el que se encuntra la nave (0 o 1)
	connected_ = false;// booleano que se pone a true cuando ambos estan conectados
}

// destructora
NetworkSystem::~NetworkSystem() {
	if (p_ != nullptr) {
		SDLNet_UDP_Close(sock_);// cierra el sock
		SDLNet_FreePacket(p_);// libera el UDPpacket
	}
}


// introduccion y guardado de nombre por consola
void NetworkSystem::putName() {
	bool exit = false;
	bool success = false;

	// nombres por defecto
	names[0] = "Player 1";
	names[1] = "Player 2";

	while (!exit) {
		cout << "Introduzca su nombre: \n";
		cin >> name;
		if (name.length() <= 10) { // limite de 10 caracteres
			exit = true;
		}
		else cout << "Debe tener menos de 10 caracteres\n";
	}
}

// pregunta host o cliente y llama a iniciar en cada caso
bool NetworkSystem::connect() {
	char c;
	bool exit = false;
	bool success = false;

	while (!exit) {
		cout << "Host o cliente [h/c]? " << endl;
		cin >> c;
		// cliente o host
		switch (c) {
		case 'h':
		case 'H':
			success = initHost();
			exit = true;
			break;
		case 'c':
		case 'C':
			success = initClient();
			exit = true;
			break;
		default:
			break;
		}
	}
	return success;
}

// pedida de numero de puerto a abrir (por consola)
bool NetworkSystem::initHost() {
	// si se es host
	Uint16 port;
	cout << "Introduce el puerto: " << endl;
	if (!(cin >> port)) {
		cerr << "El puerto no es válido" << endl;
		return false;
	}
	if (!initConnection(port))
		return false;
	host_ = true;
	side_ = 0;
	connected_ = false; // se pone a true cuando se conecta el otro player
	names[side_] = name;
	return true;
}

// pide IPV4 del host ademas del puerto
bool NetworkSystem::initClient() {
	// si no se es host
	Uint16 port;
	string host;

	cout << "Introduce la IPV4 y el puerto del host separado por un espacio: " << endl;
	if (!(cin >> host >> port)) {
		cerr << "Puerto o host no válido" << endl;
		return false;
	}

	if (SDLNet_ResolveHost(&otherPlayerAddr_, host.c_str(), port) < 0) {// busca el host y el port para conectarse
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	host_ = false;// es cliente

	initConnection(0); // crea el shoket del cliente

	char nameToSend[11];

	net::NameMessage m;
	m.id = net::_CONNECTION_REQUEST;
	string_to_chars(name, m.nameSend);
	p_->address = otherPlayerAddr_;// coge la direccion del otro jugador

	SDLNetUtils::serializedSend(m, p_, sock_);// comunica una solicitud de conexion

	// devuelve -1 si da error, si no lo da devuelve el numero de shokets disponibles
	if (SDLNet_CheckSockets(sockSet_, 3000)) {
		// comprueba si la informacion del shocket se puede leer
		if (SDLNet_SocketReady(sock_)) {
			SDLNetUtils::deserializedReceive(m, p_, sock_);
			if (m.id == net::_REQUEST_ACCEPTED) {// si el host acepta la conexion
				// guarda la informacion del player del cliente
				net::ReqAccMsg m;
				m.deserialize(p_->data);
				side_ = m.side;
				connected_ = true;
				names[side_] = name;
				chars_to_string(names[1 - side_], m.nameSend);
			}
		}
	}

	if (!connected_) {
		cout << "No se pudo conectar con el otro jugador" << endl;
		return false;
	}
	return true;
}

// abre y guarda el puerto pedido por consola en el metodo initHost, crea los sockets y el socketSet
bool NetworkSystem::initConnection(Uint16 port) {
	sock_ = SDLNet_UDP_Open(port); // crea el socket

	if (!sock_) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	sockSet_ = SDLNet_AllocSocketSet(1); // crea el socketSet
	if (!sockSet_) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	SDLNet_UDP_AddSocket(sockSet_, sock_);  // mete el socket en el socketSet
	p_ = SDLNet_AllocPacket(512);
	if (!p_) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	port_ = SDLNetUtils::getSocketPort(sock_); // guarda el puerto
	return true;
}

// recogida de datos iniciales del otro cliente
void NetworkSystem::ConnectionRequest() {

	if (!connected_ && host_) {
		net::NameMessage mH;
		mH.deserialize(p_->data);

		chars_to_string(names[1 - side_], mH.nameSend); // coger el nombre del otro jugador (si eres 0 coges 1 y viceversa)

		otherPlayerAddr_ = p_->address; // direccion del otro jugador
		connected_ = true;
		net::ReqAccMsg m;
		m.id = net::_REQUEST_ACCEPTED;
		string_to_chars(name, m.nameSend);
		m.side = 1 - side_;
		SDLNetUtils::serializedSend(m, p_, sock_, otherPlayerAddr_); // comunica entre consolas acerca de id y nombre del player
	}
}


// receive
void NetworkSystem::receive(const Message& m) {
	if (!host_)
		return;
	switch (m.id) {
	case _MSG_START:// avisa a la otra consola del inicio de partida
		tellOtherClientToStartGame();
		break;
	default:
		break;
	}
}

// update
void NetworkSystem::update() {
	net::Message m;// cuando se recibe 
	while (SDLNetUtils::deserializedReceive(m, p_, sock_) > 0) {// lee totod los datos que han llegado
		switch (m.id) {
		case net::_CONNECTION_REQUEST:
			ConnectionRequest(); // recogida de datos iniciales del otro cliente
			break;
		case net::_FIGHTER_POS:
			FighterPos(); // comunica a la otra consola acerca de la posición del player
			break;
		case net::_BULLET_SHOT:
			BulletShot(); // comunica a la otra consola acerca de la posición del bala
			break;
		case net::_START_GAME_REQUEST:
			StartGameRequest(); // comunica el cambio de estado siendo host
			break;
		case net::_START_GAME:
			StartTheGame(); // comunica el cambio de estado siendo cliente
			break;
		default:
			break;
		}
	}
}


// para actualizar la posicion de las naves en ambos clientes
void NetworkSystem::sendFighterPosition(Transform* tr) {
	if (!connected_)
		return;

	net::FighterPosMsg m;

	// info
	m.id = net::_FIGHTER_POS;
	m.side = side_;
	m.x = tr->pos_.getX();
	m.y = tr->pos_.getY();
	m.rot = tr->rot_;

	// comunicacion
	p_->address = otherPlayerAddr_;
	SDLNetUtils::serializedSend(m, p_, sock_, otherPlayerAddr_);
}

// para actualizar la posicion de las balas en ambos clientes
void NetworkSystem::sendBulletPosition(Transform* tr) {
	if (!connected_)
		return;

	net::BulletPosMsg m;

	// info
	m.id = net::_BULLET_POS;
	m.side = side_;
	m.x = tr->pos_.getX();
	m.y = tr->pos_.getY();
	m.rot = tr->rot_;

	// comunicacion
	p_->address = otherPlayerAddr_;
	SDLNetUtils::serializedSend(m, p_, sock_, otherPlayerAddr_);
}
// informacion de las balas para su creacion y comunicacion a ambos clientes (por mensaje)
void NetworkSystem::sendBulletShot(float posX, float posY, float velX, float velY, float rot)
{
	if (!connected_)
		return;

	net::BulletShotMsg m;

	// informacion de la bala
	m.id = net::_BULLET_SHOT;
	m.side = side_;
	m.posX = posX;
	m.posY = posY;
	m.velX = velX;
	m.velY = velY;

	// comunicacion con el otro cliente
	p_->address = otherPlayerAddr_;
	SDLNetUtils::serializedSend(m, p_, sock_, otherPlayerAddr_);
}

// comunica a la otra consola acerca de la posición del player
void NetworkSystem::FighterPos() {
	net::FighterPosMsg m;
	m.deserialize(p_->data);
	mngr_->getSystem<FighterCtrlNetSystem>(_SYS_FIGHTERNET)->changeFighterPos(m.side, m.x, m.y, m.rot);
}

// instanciacion de las balas
void NetworkSystem::BulletShot() {
	net::BulletShotMsg m;
	m.deserialize(p_->data);
	mngr_->getSystem<BulletNetSystem>(_SYS_BULLETNET)->createBullet(m.posX, m.posY, m.velX, m.velY, m.side);
}



// solicitud inicio de juego siendo cliente (se llama desde gameCtrl)
void NetworkSystem::sendStarGameRequest() {
	assert(!host_);

	net::StartRequestMsg m;

	m.id = net::_START_GAME_REQUEST;
	m.side = side_;
	p_->address = otherPlayerAddr_;
	SDLNetUtils::serializedSend(m, p_, sock_, otherPlayerAddr_); // comunicacion con la consola del host

}

// comunica el cambio de estado siendo host
void NetworkSystem::StartGameRequest() {
	mngr_->getSystem<GameCtrlNetSystem>(_SYS_GAMECTRLNET)->GameStart();
}

// comunica el cambio de estado siendo cliente
void NetworkSystem::StartTheGame() {
	assert(!host_);
	mngr_->getSystem<GameCtrlNetSystem>(_SYS_GAMECTRLNET)->GameStart();
}

// cambia el estado de la otra consola
void NetworkSystem::tellOtherClientToStartGame() {
	net::Message m;

	m.id = net::_START_GAME;
	SDLNetUtils::serializedSend(m, p_, sock_, otherPlayerAddr_);
}


// paso de string a array de chars
void NetworkSystem::string_to_chars(string& str, char c_str[11]) {
	auto i = 0u;
	for (; i < str.size() && i < 10; i++) c_str[i] = str[i];
	c_str[i] = 0;

}

// paso de array de chars a string
void NetworkSystem::chars_to_string(string& str, char c_str[11]) {
	c_str[10] = 0;
	str = string(c_str);
}


