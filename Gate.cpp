#include "Gate.h"

Gate::Gate()
{
	if (!texture.loadFromFile("GatePic.png", sf::IntRect(0, 0, textureWidth, textureHeight)))
	{

	}
	GateSprite.setTexture(texture);

	GateSprite.setOrigin(textureWidth / 2, textureHeight / 2);
}


void Gate::SetLocation(int x, int y)
{
	this->x = x;
	this->y = y;
	GateSprite.setPosition(sf::Vector2f(x, y));
}

void Gate::setID(int id)
{
	this->id = id;
}
int Gate::getID()
{
	return id;
}