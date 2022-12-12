#include "includer-c.h"
#include <string>


//Multiplayer Variables
sf::Packet			ServerBindPacket;
sf::Packet			SInicializer;
Server				MServer;
Client				Local;

//Engine Variables
sf::RenderWindow	GameWindow(sf::VideoMode(LoginWidth, LoginHeight), " ", sf::Style::Close);

//Clock and Time Variables
sf::Clock			MClock;
float				deltaTime;
std::thread			ServerManagerThread;

//Message Window Variables
std::atomic <bool>	MessageWindowInUse = false;
std::string			MessageBoardText = "";
std::atomic<bool>	Login(false);
std::atomic <bool>	gameStarted = false;
sf::Font			font;

//Login Menu Elements
extradraw::Textbox	nickInput(LoginWidth / 2, LoginHeight / 2, 25, false, 12, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_-1234567890");
extradraw::Textbox	ipInput(LoginWidth / 2, LoginHeight / 1.6, 25, false, 15, "1234567890.");
extradraw::Button	enterButton(LoginWidth / 2, LoginHeight / 1.3, 20, false, "join");
sf::Text			Title;
std::vector<Bouncy> BackDots;

//Disconnect player and displays screen message
void DisconnectChain(std::string Message) {
	MessageBoardText = Message;
	MessageWindowInUse = true;
	Local.Connected = false;
	Login = false;
	enterButton.isSelected = false;
}

void Gameplay() {
	if (GameWindow.getSize().x != MServer.Width || GameWindow.getSize().y != MServer.Height)
		GameWindow.setSize(sf::Vector2u(MServer.Height, MServer.Width));

	sf::Event event;
	while (GameWindow.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			GameWindow.close();
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape)
				Login = false;
		}
	}

	GameWindow.clear();
	//std::cout << "Gameplay" << std::endl;
}

//Waiting for players screen
void PlayerLobby() {
	sf::Event event;
	while (GameWindow.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			GameWindow.close();
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape)
				Login = false;
		}
	}

	GameWindow.clear();

	extradraw::ConnectDots(&GameWindow, BackDots);

	for (int i = 0; i < BackDots.size(); i++)
	{
		BackDots[i].Move();
		BackDots[i].Draw(&GameWindow);
	}

	std::string tmpPlayerCount;
	tmpPlayerCount = std::to_string(MServer.Online);
	tmpPlayerCount += "/";
	tmpPlayerCount += std::to_string(MServer.Max);
	extradraw::DrawString(&GameWindow, LoginWidth / 2, LoginHeight / 2.2, 30, "Waiting For Players...");
	extradraw::DrawString(&GameWindow, LoginWidth / 2, LoginHeight / 1.8, 30, tmpPlayerCount);
}

//Initialize all login menu variables
int MenuInicial() {
	for (int b = 0; b < 80; b++)
		BackDots.push_back(Bouncy(LoginWidth, LoginHeight, 20, 2));
	return 1;
}

void Menu() {
	sf::Event event;
	while (GameWindow.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			GameWindow.close();
		if (event.type == sf::Event::MouseButtonPressed) {
			nickInput.CheckSelection(event);
			ipInput.CheckSelection(event);
			enterButton.CheckSelection(event);
		}
		if (event.type == sf::Event::TextEntered) {
			nickInput.TextInput(event);
			ipInput.TextInput(event);
		}
	}

	GameWindow.clear();

	extradraw::ConnectDots(&GameWindow, BackDots);

	for (int i = 0; i < BackDots.size(); i++)
	{
		BackDots[i].Move();
		BackDots[i].Draw(&GameWindow);
	}

	extradraw::DrawString(&GameWindow, LoginWidth / 2, LoginHeight / 3.5, 60, "JELLY");
	extradraw::DrawString(&GameWindow, LoginWidth / 5.5, LoginHeight / 2, 28, "Name:");
	extradraw::DrawString(&GameWindow, LoginWidth / 5.5, LoginHeight / 1.6, 28, "IP:");

	if (enterButton.isSelected) {
		if (nickInput.Text.empty())
			nickInput.Color = sf::Color::Red;
		else
			nickInput.Color = sf::Color::White;

		if (ipInput.Text.empty()) {
			ipInput.Color = sf::Color::Red;
		}
		else
			ipInput.Color = sf::Color::White;

		if (!ipInput.Text.empty() && !nickInput.Text.empty()) {
			Local.name = nickInput.Text;
			MServer.IP = ipInput.Text;
			Login = true;
		}
	}

	nickInput.Draw(&GameWindow);
	ipInput.Draw(&GameWindow);

	enterButton.Draw(&GameWindow);
}

int main() {
	ShowWindow(GetConsoleWindow(), SW_SHOW);

	bool exitM = false;

	srand(time(NULL));

	if (!font.loadFromFile("Core/Less-Light.otf")) {
		MessageBoardText = "Unable To Load Font";
		MessageWindowInUse = true;
		exitM = true;
	}
	
	std::thread serverManagerThread(ServerManager);
	MenuInicial(); 

	while (GameWindow.isOpen()) {
		if (!MessageWindowInUse) {
			if (gameStarted)
				Gameplay();
			else if (Login)
				PlayerLobby();
			else
				Menu();
		}
		else {
			if (extradraw::MessageBoard(&GameWindow, BackDots, MessageBoardText, 25, exitM) == 2)
				exit(1);
			else if (extradraw::MessageBoard(&GameWindow, BackDots, MessageBoardText, 25, exitM) == 1)
				MessageWindowInUse = false;
		}
			
		GameWindow.display();
		deltaTime = MClock.restart().asSeconds();
	}
	return 0;
}