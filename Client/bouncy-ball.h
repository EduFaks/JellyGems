#pragma once

class Bouncy
{
public:
	Bouncy(int WidthRange, int HeightRange, int SpeedRange, float BallSize);
	void Move();
	void Draw(sf::RenderWindow* Window);
	float X, Y;
	float Size;

private:
	float vX, vY;
	int MaxWidth, MaxHeight;
	sf::CircleShape Ball;

	void Collision();
};