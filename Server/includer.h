#pragma once

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include <thread>

#include <SFML/Network.hpp>

#include "client-struct.h"
#include "console.h"
#include "network.h"

// Color to display message on server console (logs)
#define DefaultColor	3
#define TipColor		2
#define WarningColor	6
#define ErrorColor		4

extern HANDLE consoleHandle;
extern int OnlineClientCount;

// Variables to verify on client connection
#define ServerWidth		200
#define ServerHeight	400
#define ServerVersion	1

#define MaxClients		1
#define ServerPort		4004
