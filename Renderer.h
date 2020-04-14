#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Player.h"
#include "Gate.h"

class Renderer
{
public:

	Renderer(sf::RenderWindow* pw, Game* pGame);


	void render(bool inGame);


private:
	//window variable where we render things
	sf::RenderWindow* pWindow = nullptr;
	Game* pGame;
	Player* pPlayer;
	AI* pAI;
	Gate* pgates;
	int numberOfGates = 3;

	sf::Font MyFont;

	sf::Text LapTimes[4];

	sf::Text Menu[2];
};

