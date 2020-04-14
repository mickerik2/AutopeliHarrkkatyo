#pragma once
#include "Level.h"
#include"Player.h"
#include"AI.h"
#include"Gate.h"
#include <SFML/Graphics.hpp>
#include "AudioPlayer.h"

class Game
{
public:

	Game();

	~Game();

	void update(bool inGame);

	sf::Image GetLevelData();
	
	Player* GetPlayerRef();
	AI* GetAIRef();

	Gate* GetGatesRef();

	double GetTimeAsSeconds();
	bool inGame = false;
	bool GetInGame();

	void restart();

	int chosenText = 0;
	void ToggleMenuChoise(int choise);
	void MenuChoose();

	bool RequestExit();
	bool GetOnHold();

private:

	Level level;
	Player player;
	AudioPlayer AudioP;
	AI ai;
	int NumberOfLapsToWin = 4;
	Gate gates[3];
	sf::Clock clock;
	sf::Time elapsed;

	bool exit = false;
	bool onHold = true;

	void checkCollisionFront();
	void checkCollisionLeft();
	void checkCollisionRight();
	void checkCollisionBack();
	void checkCollision();
	void checkCollisionAI();
	void checkLap();
	void checkWinner();


	void determineAIAction();


};

