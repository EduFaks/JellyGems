#include "includer.h"

HANDLE	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

sf::Packet bindingPacket;
sf::Packet InGamePack;

//Dummy packet to check disconnection
sf::Packet Dummy;

sf::TcpListener listener;

int OnlineClientCount = 0;
bool gameStarted = false;

std::thread		updateClients;
std::thread		receiveClients;

//Creates array of clients/players
Client clients[MaxClients]; 

//Creates the board layout and displays it
void Board() {
	std::cout << "---------------------------------------------------------------------------------------\n";
	for (int i = 0; i < MaxClients; i++) {
		std::cout << "| Player " << i << ": " << clients[i].name.c_str() << std::setw(20 - strlen(clients[i].name.c_str()))
			<< " | Pos: " << clients[i].x << std::setw(5 - (clients[i].x < 100 ? (clients[i].x < 10 ? 1 : 2) : 3)) << " " << clients[i].y << std::setw(5 - (clients[i].y < 100 ? (clients[i].y < 10 ? 1 : 2) : 3))
			<< " | Score: " << clients[i].score << " | Connected: " << (clients[i].connected ? "Yes |" : "No  |") << " Spectator: " << (clients[i].spectator ? "True  |" : "False |") << std::endl;
	}
	std::cout << "---------------------------------------------------------------------------------------\n\n";
}

//Loop through all players and bind each connection to a player
void PlayerBind() {
	std::cout << std::endl;
	ConsoleFormat::Tip("----- Waiting For Max Players -----");

	for (int index = 0; index <= MaxClients - 1; index++) {
		//Keep trying to bind same player object until successful (in case of packet errors or disconection during reciving process)
		while (!clients[index].connected)
		{
			if (listener.accept(clients[index].socket) == sf::Socket::Done)
				clients[index].Connect(index);
			else
				ConsoleFormat::Error("unable to bind client to socket");
		}

		//Creates initial packet
		NetPacket::InitialPacketUpdate(clients, bindingPacket);
		//Send packet to all online players
		for (int index = 0; index <= MaxClients - 1; index++)
		{
			if (clients[index].connected) {
				clients[index].socket.send(bindingPacket);
			}
		}
	}
	ConsoleFormat::Tip("All clients connected!");
	std::cout << std::endl;
}

void ReceiveClients() {
	while (true)
	{
		if (gameStarted)
		{
			for (int index = 0; index <= MaxClients - 1; index++) {
				//Checks if player online
				if (!clients[index].connected)
					break;
				//Update client position
				clients[index].Update(index);
			}
		}
	}
}

void UpdateClients() {
	while (true)
	{
		if (gameStarted)
		{
			for (int index = 0; index <= MaxClients - 1; index++) {
				//Creates in game packet
				NetPacket::InGamePacket(clients, InGamePack);
				//Send packet to all online players
				for (int index = 0; index <= MaxClients - 1; index++)
					clients[index].socket.send(InGamePack);
			}
		}
	}
}

int main() {
	//Rezise window and move's to the corner of monitor
	MoveWindow(GetConsoleWindow(), 0, 0, 750, 800, TRUE);

	//Set console color to default value
	SetConsoleTextAttribute(consoleHandle, DefaultColor);

	receiveClients	= std::thread(ReceiveClients);
	updateClients		= std::thread(UpdateClients);

	//----- BANNER -----
	std::cout << "----------------------------------------------------\n";
	std::cout << "                  Jelly Server V" << ServerVersion << "                   \n";
	std::cout << "----------------------------------------------------\n";
	std::cout << "Port: " << ServerPort << "\nMax Players: " << MaxClients << "\nLocal IP: " << sf::IpAddress::getLocalAddress() << " | Public IP: " << sf::IpAddress::getPublicAddress() << std::endl;
	std::cout << "----------------------------------------------------\n";

	//Bind the listener to a port | Error Check
	if (listener.listen(ServerPort) != sf::Socket::Done)
		ConsoleFormat::Error("unable to bind port to listener | In Use?");

	PlayerBind();

	//Main Server Loop
	while (true)
	{
		//Display board if key (S) pressed
		if (GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(0x53) & 0x1)
			Board();

		//Disconnect players if key (D) pressed
		if (GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(0x44) & 0x1) {
			int tmpID;
			std::cout << "\nEnter player ID to disconnect: ";
			std::cin >> tmpID;
			if (tmpID <= MaxClients && clients[tmpID].connected)
				clients[tmpID].Disconnect(tmpID);
			else
				ConsoleFormat::Error("Player ID not found!");
		}

		//Force binding loop
		if (GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(0x52) & 0x1)
			PlayerBind();

		if (MaxClients == OnlineClientCount) {
			gameStarted = true;
		}
			
		//Loop through all players and bind each connection to a player
		for (int p = 0; p <= MaxClients; p++) {
			if (clients[p].socket.receive(Dummy) == sf::Socket::Disconnected)
				clients[p].Disconnect(p);
		}

		//If all players disconnect start binding again
		if (OnlineClientCount == 0)
			PlayerBind();

		//Close all connections and end server
		if (GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(VK_ESCAPE)) {
			char tmpOptionClose;
			ConsoleFormat::Warning("Close server? (y/n)");
			std::cin >> tmpOptionClose;
			if (tmpOptionClose == 'y') {
				Board();
				for (int p = 0; p <= MaxClients - 1; p++)
					clients[p].Disconnect(p);

				std::cout << std::endl;
				ConsoleFormat::Warning("Exiting Server...");
				Sleep(5000);
				return 0;
			}
		}
	}

	return 1;
}