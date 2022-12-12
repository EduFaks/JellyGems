#pragma once

namespace extradraw
{
	void DrawLine(sf::RenderWindow* Window, int x1, int y1, int x2, int y2);
	void DrawString(sf::RenderWindow* Window, int X, int Y, int size, std::string Text, sf::Color Color = sf::Color::White);
	void ConnectDots(sf::RenderWindow* Window, std::vector<Bouncy> Balls);
	float FindDistance(int x1, int y1, int x2, int y2);
	int MessageBoard(sf::RenderWindow* Window, std::vector<Bouncy>& Dots, std::string Message, int Size, bool exit = false);

	class Textbox
	{
	public:
		Textbox(int x, int y, int size, bool Selected, int Lim, std::string Rang);

		void CheckSelection(sf::Event event);
		void Draw(sf::RenderWindow* Window);
		void TextInput(sf::Event event);

		std::string Text = "";
		sf::Color Color = sf::Color::White;

	private:
		int X, Y;
		int Width, Height;
		sf::Text textobj;
		std::string Range = "";
		bool isSelected = false;
		bool atLimit = false;
		int Limit;
	};

	class Button
	{
	public:
		Button(int x, int y, int size, bool Selected, std::string Text);

		void CheckSelection(sf::Event event);
		void Draw(sf::RenderWindow* Window);

		bool isSelected = false;

	private:
		int X, Y;
		int Width, Height;
		sf::Text textobj;
	};
};