#pragma once
#include"Renderer.h"

class InputHandler
{

public:
	InputHandler(sf::RenderWindow* pw,Game* pGame);
	~InputHandler();

	void processEvents(bool inGame);

private:
	Player* pPlayer;
	Game* pGame;
	sf::RenderWindow* pWindow;
};

