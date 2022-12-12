#pragma once

class Client
{
public:
	float			X, Y;
	int				Score;
	std::string		name;
	sf::Vector3f	Color;

	bool			Spectator = 0;
	bool			Connected = 0;

	Client();

	void ReciveClient(sf::Packet& ClientPacket);
	void UpdatePacket(sf::Packet& ClientPacket);
	void createUpdatePacket(sf::Packet& ClientPacket);
};
