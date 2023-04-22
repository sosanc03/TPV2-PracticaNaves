#pragma once
#include <SDL_net.h>
#include <SDL_stdinc.h>

#include "../ecs/System.h"
#include <string>
#include <array>

using namespace std;

struct Transform;

class NetworkSystem : public System {
public:


	NetworkSystem();// constructora
	virtual ~NetworkSystem();// destructora

	void receive(const Message&) override;
	void update() override;

	void putName();// introduccion y guardado de nombre por consola
	bool connect();// pregunta host o cliente y llama a iniciar en cada caso

	inline Uint8 getSide() // devuelve el lado (o identificador) del player
	{
		return side_;
	}
	inline bool isReady() {// devuelve true si ambos estan conectados
		return connected_;
	}
	inline bool isHost() {// devuelve true si es el host
		return host_;
	}
	inline Uint16 getPort() {// devuelve el puerto
		return port_;
	}
	inline string getName(int i) {// devuelve el nombre sabiendo el id(side)
		return names[i];
	}

	// para actualizar la posicion de las naves en ambos clientes
	void sendFighterPosition(Transform* tr);
	// para actualizar la posicion de las balas en ambos clientes
	void sendBulletPosition(Transform* tr);
	// informacion de las balas para su creacion y comunicacion a ambos clientes (por mensaje)
	void sendBulletShot(float posX, float posY, float velX, float velY, float rot);
	
	// solicitud inicio de juego siendo cliente (se llama desde gameCtrl)
	void sendStarGameRequest();
private:
	
	bool initHost();// inicia host
	bool initClient();// inicia cliente
	// abre y guarda el puerto pedido por consola en el metodo initHost, 
	//crea los sockets y el socketSet
	bool initConnection(Uint16 port);
	void ConnectionRequest();// recogida de datos iniciales del otro cliente

	void FighterPos();// comunica a la otra consola acerca de la posición del player
	void BulletShot();// instanciacion de las balas

	void StartGameRequest();// comunica el cambio de estado siendo host
	void StartTheGame();// comunica el cambio de estado siendo cliente

	void tellOtherClientToStartGame();// cambia el estado de la otra consola

	// paso de string a array de chars
	void string_to_chars(string& str, char c_str[11]);
	// paso de array de chars a string
	void chars_to_string(string& str, char c_str[11]);

	bool host_;// booleano de host
	Uint8 side_; // 0 izq 1 dr
	UDPsocket sock_;// shoket
	UDPpacket* p_;
	SDLNet_SocketSet sockSet_;// shoketSet
	Uint16 port_;// puerto

	bool connected_;// booleano que se pone a true cuando los dos estan conectados
	IPaddress otherPlayerAddr_;// IP del otro jugador

	array<string, 2> names;// guarda los nombres de los players
	string name;// nombre del player
};

