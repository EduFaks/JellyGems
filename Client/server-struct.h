#pragma once
struct Server
{
	sf::TcpSocket Socket;

	std::string IP;

	int ServerVersion;
	int Width;
	int Height;
	int Online;
	int Max;

	std::vector<Client> Players;
};