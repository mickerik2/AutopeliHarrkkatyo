#include "Renderer.h"
#include<iostream>
#include<string.h>


Renderer::Renderer(sf::RenderWindow* pw, Game* pGame)
{
	pWindow=pw;
	this->pGame = pGame;
	pPlayer = pGame->GetPlayerRef();
	pgates = pGame->GetGatesRef();
	pAI = pGame->GetAIRef();

	// Load from a font file on disk
	if (!MyFont.loadFromFile("arial.ttf"))
	{
		// Error...
	}
	for (int i = 0; i < 4; i++)
	{
		LapTimes[i].setFont(MyFont);
		LapTimes[i].setString("0");


		LapTimes[i].setPosition(10, 700 + 32 * i);
	}

	for (int i = 0; i < 2; i++)
	{
		Menu[i].setFont(MyFont);
		Menu[i].setCharacterSize(48);
		Menu[i].setPosition(550, 400 + 60 * i);
	}
	Menu[0].setString("New Race  ->");
	Menu[1].setString("Quit  ->");

}


void Renderer::render(bool inGame)
{
	if (inGame)
	{
		pWindow->clear(sf::Color::Black);

		sf::Texture map;
		map.loadFromImage(this->pGame->GetLevelData());
		sf::Sprite mapSprite(map);

		sf::Sprite PlayerSprite = pPlayer->playerSprite;
		sf::Sprite AISprite = pAI->playerSprite;
		//sf::Sprite GateSprite = pgates->GateSprite;

		// draw everything here...
		pWindow->draw(mapSprite);
		pWindow->draw(PlayerSprite);
		pWindow->draw(AISprite);
		for (int i = 0; i < numberOfGates; i++)
		{
			sf::Sprite GateSprite = (pgates + i)->GateSprite;
			pWindow->draw(GateSprite);
		}
		for (int i = 0; i < 4; i++)
		{
			if (pPlayer->lapsCompleted < 4)
			{
				LapTimes[pPlayer->lapsCompleted].setString(std::to_string(pGame->GetTimeAsSeconds()));
			}
			if (pPlayer->lapsCompleted == 0 && LapTimes[1].getString() != "0")
			{
				for (int j = 0; j < 4; j++)
				{
					LapTimes[j].setString("0");
				}
			}

			if (LapTimes[i].getString() != "0")
			{
				pWindow->draw(LapTimes[i]);

			}
			
			
		}

		// end the current frame
		pWindow->display();
	}
	else
	{
		int chosenText = pGame->chosenText;
		pWindow->clear(sf::Color::Blue);
		for (int i = 0; i < 2; i++)
		{
			if (i == chosenText - 1)
			{
				Menu[i].setFillColor(sf::Color::Red);
			}
			else
			{
				Menu[i].setFillColor(sf::Color::White);

			}
			pWindow->draw(Menu[i]);
		}

		// end the current frame
		pWindow->display();
	}
}

