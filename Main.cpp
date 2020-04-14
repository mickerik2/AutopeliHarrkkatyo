#include<iostream>
#include "Game.h"
#include "InputHandler.h"
#include "Renderer.h"
using namespace std;


int main()
{
	Game myGame;
	//Player* player;
	//player = myGame.GetPlayerRef();

	//InputHandler inputhandler;

	//sf::RenderWindow window(sf::VideoMode(1616, 1212), "My window");

	sf::RenderWindow window(sf::VideoMode(1440, 900), "My window");


	Renderer* pMyRenderer = new Renderer(&window, &myGame);

	InputHandler handler(&window, &myGame);

	bool inGame = false;



	while (window.isOpen() && !myGame.RequestExit())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}
		/*while (inGame)
		{
			while (window.pollEvent(event))
			{
				// "close requested" event: we close the window
				if (event.type == sf::Event::Closed)
					window.close();
			}

			handler.processEvents(inGame);

			myGame.update(inGame);

			pMyRenderer->render();
		}*/

		handler.processEvents(inGame);

		myGame.update(inGame);

		pMyRenderer->render(inGame);

		inGame = myGame.GetInGame();
	}
	delete pMyRenderer;
}

