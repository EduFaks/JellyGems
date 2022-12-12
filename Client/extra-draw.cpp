#include "includer-c.h"
#include <sstream>

void extradraw::DrawLine(sf::RenderWindow* Window, int x1, int y1, int x2, int y2) {
	sf::Vertex line[] = { sf::Vertex(sf::Vector2f(x1, y1)), sf::Vertex(sf::Vector2f(x2, y2)) };
	line->color = sf::Color(255, 255, 255, 10);
	Window->draw(line, 2, sf::Lines);
}

void extradraw::DrawString(sf::RenderWindow* Window, int X, int Y, int size, std::string Text, sf::Color Color) {
	sf::Text tmpText;
	tmpText.setCharacterSize(size);
	tmpText.setString(Text);
	tmpText.setFont(font);

	tmpText.setFillColor(Color);

	sf::FloatRect textRect = tmpText.getLocalBounds();
	tmpText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	tmpText.setPosition(X, Y);

	Window->draw(tmpText);
}

void extradraw::ConnectDots(sf::RenderWindow* Window, std::vector<Bouncy> Balls) {
	for (int a = 0; a < Balls.size(); a++) {
		for (int b = 0; b < Balls.size(); b++) {
			if (FindDistance(Balls[a].X, Balls[a].Y, Balls[b].X, Balls[b].Y) <= 35) {
				DrawLine(Window, Balls[a].X + Balls[a].Size, Balls[a].Y + Balls[a].Size, Balls[b].X + Balls[b].Size, Balls[b].Y + Balls[b].Size);
			}
		}
	}
}

float extradraw::FindDistance(int x1, int y1, int x2, int y2) {
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

int extradraw::MessageBoard(sf::RenderWindow* Window, std::vector<Bouncy>& Dots, std::string Message, int Size, bool exit) {
	extradraw::Button tmpButton(LoginWidth / 2, LoginHeight / 1.6, Size, false, " Ok ");

	sf::Event event;
	while (Window->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			Window->close();
		if (event.type == sf::Event::MouseButtonPressed) {
			tmpButton.CheckSelection(event);
		}
	}

	Window->clear();

	extradraw::ConnectDots(Window, Dots);

	for (int i = 0; i < Dots.size(); i++)
	{
		Dots[i].Move();
		Dots[i].Draw(Window);
	}

	extradraw::DrawString(Window, LoginWidth / 2, LoginHeight / 2.4, Size, Message);
	tmpButton.Draw(Window);

	if (tmpButton.isSelected && exit)
		return 2;
	else if (tmpButton.isSelected)
		return 1;
	else
		return 0;
}

//----------- Textbox -----------//

extradraw::Textbox::Textbox(int x, int y, int size, bool Selected, int Lim, std::string Rang) {
	textobj.setCharacterSize(size);
	textobj.setFont(font);

	isSelected = Selected;
	Limit = Lim;
	X = x;
	Y = y;
	Width = size * 8;
	Height = size * 1.2;

	Range = Rang;
}

void extradraw::Textbox::CheckSelection(sf::Event event) {
	if (event.mouseButton.x >= X - (Width / 2) &&
		event.mouseButton.x <= X + (Width / 2) &&
		event.mouseButton.y >= Y - (Height / 2) && event.mouseButton.y <= Y + (Height / 2))
		isSelected = true;
	else
		isSelected = false;
}

void extradraw::Textbox::Draw(sf::RenderWindow* Window) {
	sf::RectangleShape Box(sf::Vector2f(Width, Height));
	Box.setOrigin(Width / 2, Height / 2);
	Box.setPosition(X, Y);
	Box.setFillColor(sf::Color::Black);
	Box.setOutlineThickness(1);

	if (isSelected) {
		Box.setOutlineColor(Color);
		textobj.setFillColor(sf::Color::White);
	}
	else {
		Box.setOutlineColor(sf::Color(Color.r, Color.g, Color.b, Color.a - 100));
		textobj.setFillColor(sf::Color(255, 255, 255, 150));
	}

	textobj.setString(Text);
	sf::FloatRect textRect = textobj.getLocalBounds();
	textobj.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	textobj.setPosition(X, Y);

	Window->draw(Box);
	Window->draw(textobj);
}

void extradraw::Textbox::TextInput(sf::Event event) {
	uint32_t tmpChar = event.text.unicode;

	if (isSelected) {
		if (tmpChar == 8) {
			if (Text.size() != 0)
				Text.erase(Text.size() - 1);
		}
		else if (Text.size() + 1 <= Limit && Range.find((char)tmpChar) != std::string::npos) {
			if (tmpChar >= 32 && tmpChar <= 126)
				Text += (char)tmpChar;
			else if (tmpChar >= 192 && tmpChar <= 255)
				Text += (char)tmpChar;
		}
	}
}

//----------- Button -----------//

extradraw::Button::Button(int x, int y, int size, bool Selected, std::string Text) {
	textobj.setCharacterSize(size);
	textobj.setString(Text);
	textobj.setFont(font);

	isSelected = Selected;
	X = x;
	Y = y;
	Width = Text.size() * size;
	Height = size * 1.5;
}

void extradraw::Button::CheckSelection(sf::Event event) {
	if (event.mouseButton.x >= X - (Width / 2) &&
		event.mouseButton.x <= X + (Width / 2) &&
		event.mouseButton.y >= Y - (Height / 2) && event.mouseButton.y <= Y + (Height / 2))
		isSelected = true;
	else
		isSelected = false;
}

void extradraw::Button::Draw(sf::RenderWindow* Window) {
	sf::RectangleShape Box(sf::Vector2f(Width, Height));
	Box.setOrigin(Width / 2, Height / 2);
	Box.setPosition(X, Y);
	Box.setFillColor(sf::Color::Black);
	Box.setOutlineThickness(1);

	if (isSelected) {
		Box.setOutlineColor(sf::Color::White);
		textobj.setFillColor(sf::Color::White);
	}
	else {
		Box.setOutlineColor(sf::Color(255, 255, 255, 150));
		textobj.setFillColor(sf::Color(255, 255, 255, 150));
	}

	sf::FloatRect textRect = textobj.getLocalBounds();
	textobj.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	textobj.setPosition(X, Y);

	Window->draw(Box);
	Window->draw(textobj);
}