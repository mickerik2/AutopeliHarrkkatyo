#pragma once
#include <SFML/Graphics.hpp>

class Gate
{
public:
	Gate();
	void SetLocation(int x, int y);
	sf::Sprite GateSprite;
	sf::Texture texture;

	void setID(int id);
	int getID();

private:
	int x;
	int y;

	int textureWidth = 3;
	int textureHeight = 100;
	int id=0;

};