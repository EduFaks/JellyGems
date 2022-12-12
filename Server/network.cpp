#include "includer.h"

void NetPacket::FullClientPacket(Client& client, sf::Packet& InitialPacket) {
	InitialPacket << client.x << client.y;
	InitialPacket << client.score;
	InitialPacket << client.name;
	InitialPacket << client.color.x << client.color.y << client.color.z;
	InitialPacket << client.spectator;
	InitialPacket << client.connected;
}

void NetPacket::GameClientPacket(Client& client, sf::Packet& ClientPacket) {
	ClientPacket << client.x << client.y;
	ClientPacket << client.score;
	ClientPacket << client.connected;
}

void NetPacket::InitialPacketUpdate(Client* clients, sf::Packet& InitialPacket) {
	InitialPacket.clear();
	InitialPacket << 3;
	InitialPacket << ServerVersion;
	InitialPacket << ServerWidth << ServerHeight;
	InitialPacket << OnlineClientCount;
	InitialPacket << MaxClients;

	//Creates packet for each client object
	for (int i = 0; i <= OnlineClientCount - 1; i++)
		NetPacket::FullClientPacket(clients[i], InitialPacket);
}

void NetPacket::InGamePacket(Client* clients, sf::Packet& InGamePacet) {
	InGamePacet.clear();
	InGamePacet << 3;
	InGamePacet << OnlineClientCount;
	//Creates packet for each client object
	for (int i = 0; i <= OnlineClientCount - 1; i++)
		NetPacket::GameClientPacket(clients[i], InGamePacet);
}