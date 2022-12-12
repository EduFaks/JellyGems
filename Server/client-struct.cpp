#include "includer.h"

Client::Client() {
	x = rand() % ServerWidth;
	y = 0;
	score = 0;
	color = sf::Vector3f(255, 255, 255);

	name = " ";
	socket.setBlocking(false);
}

void Client::Update(int ClientID) {
	sf::Packet	updatePacket;
	int			packetType;
	std::string	nameCheck;
	float		Xu = 1, Yu = 1;

	while (socket.receive(updatePacket) != sf::Socket::Done) {}
	updatePacket >> packetType >> nameCheck >> Xu >> Yu;
	std::cout << packetType << " | " << nameCheck << " | " << Xu << " | " << Yu << std::endl;

	if (packetType != 3) {
		Disconnect(ClientID, "player disconnected | invalid packet | not update packet ");
		return;
	}

	if (name.compare(nameCheck)) {
		Disconnect(ClientID, "player disconnected | invalid name | update packet ");
		return;
	}

	if (x >= 0 && x <= ServerWidth && y >= 0 && y <= ServerHeight) {
		x = Xu;
		y = Yu;
	}
	else {
		Disconnect(ClientID, "player disconnected | invalid coordinates | update packet ");
		return;
	}
}

void Client::Connect(int ClientID) {
	sf::Packet	connectionPacket;
	int			PacketType;
	std::string	receivedName;
	int			ClientMode;

	connected = true;

	while (socket.receive(connectionPacket) != sf::Socket::Done) {}
	connectionPacket >> PacketType >> receivedName >> ClientMode;

	if (PacketType != 2) {
		Disconnect(ClientID, "player disconnected | invalid packet | not binding packet ");
		return;
	}

	if (receivedName.length() <= 12)
		name = receivedName;
	else {
		name = receivedName.substr(0, 12);
		Disconnect(ClientID, "player disconnected | invalid name lenght ");
		return;
	}

	if (ClientMode == 1 || ClientMode == 0) {
		spectator = ClientMode;
	}
	else {
		Disconnect(ClientID, "player disconnected | invalid mode ");
		return;
	}

	OnlineClientCount++;
	ConsoleFormat::Tip("new player connected!", ClientID, name.c_str());
}

void Client::Disconnect(int ClientID, const char* output) {
	sf::Packet TmpPacket;
	TmpPacket << 5;
	ConsoleFormat::Warning(output, ClientID, name.c_str());
	name = " ";
	connected = false;
	OnlineClientCount--;
	socket.send(TmpPacket);
	socket.disconnect();
}