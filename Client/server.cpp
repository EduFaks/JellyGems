#include "includer-c.h"

sf::Packet SPacket;
sf::Packet CPacket;

int clientState;

/*
-------- Client State Definition --------
	- 1: Force Disconection
	- 2: In Lobby
	- 3: In Game
	- 4: Game Paused
-----------------------------------------
*/

//Infinite loop to manage connection to server
void ServerManager() {
	while (true)
	{
		//If user clicked login, connect to server and wait for all players
		if (Login) {
			if (!Local.Connected)
				BindServer(MServer.IP);
			else if (gameStarted)
				UpdateServer();
			else
				ReciveServer();
		}
	}
}

int UpdateServer() {
	SPacket.clear();
	if (MServer.Socket.receive(SPacket) == sf::Socket::Done) {
		SPacket >> clientState;
		SPacket >> MServer.Online;

		for (int i = 0; i <= MServer.Online - 1; i++)
		{
			if (!MServer.Players.empty()) {
				MServer.Players[i].UpdatePacket(SPacket);
				std::cout << "Player " << i << ": " << MServer.Players[i].name << " | PosX: " << MServer.Players[i].X << " PosY: " << MServer.Players[i].Y << " | Spectator: " << (MServer.Players[i].Spectator ? "True" : "False") << " | Score: " << MServer.Players[i].Score << std::endl;

			}
		}
		SPacket.clear();
		Local.createUpdatePacket(SPacket);
		MServer.Socket.send(SPacket);
		Sleep(200);
	}
	return 1;
}

//Recive each player from server
int ReciveServer() {
	SPacket.clear();
	if (MServer.Socket.receive(SPacket) == sf::Socket::Done) {
		SPacket >> clientState;
		if (clientState == 1) {
			DisconnectChain("Server Forced Disconnection");
			return 0;
		}
		else if (clientState == 3) {
			gameStarted = true;
			return 0;
		}
		else if (clientState > 4) {
			DisconnectChain("Invalid Packet Type - Server Error");
			return 0;
		}

		SPacket >> MServer.ServerVersion >> MServer.Width >> MServer.Height >> MServer.Online >> MServer.Max;

		if (MServer.ServerVersion != 1) {
			DisconnectChain("Version not in Sync with Server Version");
			return 0;
		}

		for (int i = 0; i <= MServer.Online - 1; i++)
		{
			MServer.Players.insert(MServer.Players.begin() + i, Client());
			MServer.Players[i].ReciveClient(SPacket);

			std::cout << "Player " << i << ": " << MServer.Players[i].name << " | PosX: " << MServer.Players[i].X << " PosY: " << MServer.Players[i].Y << " | Spectator: " << (MServer.Players[i].Spectator ? "True" : "False") << " | Score: " << MServer.Players[i].Score << std::endl;
		}
		SPacket.clear();
		std::cout << "Server Screen Width: " << MServer.Width << " | Server Screen Height: " << MServer.Height << " | Players Online: " << MServer.Online << "/" << MServer.Max << std::endl << std::endl;
		return 1;
	}
	return 0;
}

//Inicial connection to server - Update Player Name Server Side
void BindServer(std::string IP) {
	//Packet Type - Client Name - Client Mode
	CPacket.clear();
	CPacket << 2 << Local.name << Local.Spectator << 0;

	//Sends Client Connection Packet and checks for success
	if (MServer.Socket.connect(IP, 4004) == sf::Socket::Done) {
		MServer.Socket.send(CPacket);
		Local.Connected = true;
	}
	else
		DisconnectChain("Unkown Server");
}