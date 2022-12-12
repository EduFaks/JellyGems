#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <time.h>
#include <thread>
#include <mutex>

#include "player-struct.h"
#include "bouncy-ball.h"
#include "server-struct.h"
#include "extra-draw.h"
#include "server.h"

const int LoginWidth = 500;
const int LoginHeight = 300;

extern float deltaTime;

extern sf::Font font;

extern std::atomic<bool> Login;
extern Client Local;
extern Server MServer;
extern std::atomic <bool> gameStarted;

void DisconnectChain(std::string Message);
