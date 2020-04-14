#include "InputHandler.h"


InputHandler::InputHandler(sf::RenderWindow* pw,Game *pGame)
{
	this->pGame = pGame;
	this->pPlayer = this->pGame->GetPlayerRef();
	pWindow = pw;
}


InputHandler::~InputHandler()
{
}

void InputHandler::processEvents(bool inGame)
{
	if (inGame)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			pPlayer->moveLeft();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			pPlayer->moveRight();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			pPlayer->moveUp();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			pPlayer->moveDown();
		}
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			pGame->ToggleMenuChoise(1);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			pGame->ToggleMenuChoise(2);

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			pGame->MenuChoose();
		}

	}
}
