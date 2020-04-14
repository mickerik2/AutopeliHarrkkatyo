#pragma once
#include <SFML/Graphics.hpp>
#include<string>

class Level
{
public:
	sf::Image leveldata;
	const int width = 1440;
	const int height = 1000;

	//New stuff
	sf::Vector2f startLocation;
	sf::Vector2f p1Start;
	sf::Vector2f p2Start;

	sf::Vector2f currentLocation;


	Level();
	void Randomize();
	void Generate();

private:
	void generateBlock(int startx,int starty,int x,int y);
	void generateBlackCircle(int centerX, int centerY, int radius);
	void generateGreenCircle(int centerX, int centerY, int radius);
	void GenerateQuarterCircle(int centerX, int centerY, int radiusOut, int radiusIn, std::string sector);

};

