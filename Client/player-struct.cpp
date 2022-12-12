#include "includer-c.h"

Client::Client() {
	Color = sf::Vector3f(255, 255, 255);

	name = " ";
}

void Client::ReciveClient(sf::Packet& ClientPacket) {
	ClientPacket >> X >> Y;
	ClientPacket >> Score;
	ClientPacket >> name;
	ClientPacket >> Color.x >> Color.y >> Color.z;
	ClientPacket >> Spectator;
	ClientPacket >> Connected;
}

void Client::UpdatePacket(sf::Packet& ClientPacket) {
	ClientPacket >> X >> Y;
	ClientPacket >> Score;
	ClientPacket >> Connected;
}

void Client::createUpdatePacket(sf::Packet& ClientPacket) {
	ClientPacket << 3;
	ClientPacket << name;
	ClientPacket << X << Y;
}