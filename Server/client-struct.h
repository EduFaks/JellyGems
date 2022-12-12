#pragma once

class Client
{
public:
	float			x, y;
	std::string		name;
	int				score;
	sf::Vector3f	color;

	sf::TcpSocket	socket;
	bool			connected = false;
	bool			spectator = false;

	Client();
	void Connect(int ClientID);
	void Update(int ClientID);
	void Disconnect(int ClientID, const char* output = "player disconnected ");
private:
};
