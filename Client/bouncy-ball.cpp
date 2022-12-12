#include "includer-c.h"

Bouncy::Bouncy(int WidthRange, int HeightRange, int SpeedRange, float BallSize) {
	MaxWidth = WidthRange;
	MaxHeight = HeightRange;
	Size = BallSize;

	X = rand() % WidthRange;
	Y = rand() % HeightRange;

	vX = rand() % (SpeedRange + SpeedRange) + (-SpeedRange);
	vY = rand() % (SpeedRange + SpeedRange) + (-SpeedRange);

	Ball.setRadius(BallSize);
	Ball.setFillColor(sf::Color(255, 255, 255, 180));
}

void Bouncy::Move() {
	Collision();
	X += vX * deltaTime;
	Y += vY * deltaTime;

	Ball.setPosition(X, Y);
}

void Bouncy::Draw(sf::RenderWindow* Window) {
	Window->draw(Ball);
}

void Bouncy::Collision() {
	if (Y <= 0 || Y >= MaxHeight)
		vY = -vY;
	if (X <= 0 || X >= MaxWidth)
		vX = -vX;
}