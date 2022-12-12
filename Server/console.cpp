#include "includer.h"

namespace ConsoleFormat {
	void Tip(const char* Tip, int Additional, const char* AdditionalTip) {
		SetConsoleTextAttribute(consoleHandle, TipColor);
		if (Additional != -1 && AdditionalTip != " ")
			std::cout << "[+] " << Tip << " | " << Additional << " | " << AdditionalTip << std::endl;
		else if (Additional != -1)
			std::cout << "[+] " << Tip << " | " << Additional << std::endl;
		else if (AdditionalTip != " ")
			std::cout << "[+] " << Tip << " | " << AdditionalTip << std::endl;
		else
			std::cout << "[+] " << Tip << std::endl;
		SetConsoleTextAttribute(consoleHandle, DefaultColor);
	}

	void Warning(const char* Warning, int Additional, const char* AdditionalWarn) {
		SetConsoleTextAttribute(consoleHandle, WarningColor);
		if (Additional != -1 && AdditionalWarn != " ")
			std::cout << "[!] " << Warning << " | " << Additional << " | " << AdditionalWarn << std::endl;
		else if (Additional != -1)
			std::cout << "[!] " << Warning << " | " << Additional << std::endl;
		else if (AdditionalWarn != " ")
			std::cout << "[!] " << Warning << " | " << AdditionalWarn << std::endl;
		else
			std::cout << "[!] " << Warning << std::endl;
		SetConsoleTextAttribute(consoleHandle, DefaultColor);
	}

	void Error(const char* Error) {
		SetConsoleTextAttribute(consoleHandle, ErrorColor);
		std::cout << "[-] " << Error << std::endl;
		SetConsoleTextAttribute(consoleHandle, DefaultColor);
	}
}