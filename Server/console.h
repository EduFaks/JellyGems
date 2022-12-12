#pragma once

namespace ConsoleFormat {
	void Tip(const char* Tip, int Additional = -1, const char* AdditionalTip = " ");

	void Warning(const char* Warning, int Additional = -1, const char* AdditionalTip = " ");

	void Error(const char* Error);
}