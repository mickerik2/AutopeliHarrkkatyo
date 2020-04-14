#include "Game.h"
#include<iostream>
#include <cstdlib>
#include <time.h>

Game::Game():player("car2.png"),ai("car.png")
{

	/* initialize random seed: */
	srand(time(NULL));

	//level.Randomize();
	level.Generate();

	player.SetLocation(level.p1Start.x, level.p1Start.y);
	ai.SetLocation(level.p2Start.x, level.p2Start.y);


	gates[0].SetLocation(level.startLocation.x, level.startLocation.y - 200+50);
	gates[1].SetLocation(level.startLocation.x + 5 * 200+50, level.startLocation.y);
	gates[1].GateSprite.rotate(90);

	gates[2].SetLocation(level.startLocation.x + 200 * 2 + 200, level.startLocation.y + 200 * 2+50); //GOAL
	for (int i = 0; i < 3; i++)
	{
		gates[i].setID(i);
	}
	clock.restart();

}
void Game::MenuChoose()
{
	if (chosenText == 1)
	{
		restart();
	}
	else if(chosenText==2)
	{
		exit = true;
	}
}
bool Game::RequestExit()
{
	return exit;
}

void Game::ToggleMenuChoise(int choise)
{
	if (chosenText == 0)
	{
		chosenText = choise;
	}
	else if (chosenText == 1)
	{
		chosenText = 2;
	}
	else
	{
		chosenText = 1;
	}

}

Game::~Game()
{

}

void Game::update(bool inGame)
{
	if (inGame && !onHold) 
	{
		elapsed = clock.getElapsedTime();
		//level.Randomize();
		checkCollision();

		checkCollisionAI();

		checkLap();

		determineAIAction();

		/*
		checkCollisionFront();
		checkCollisionBack();
		checkCollisionLeft();
		checkCollisionRight();
		*/

		player.move();
		ai.move();
		checkWinner();

		if (player.getForward() < 270)
		{
			if (player.getForward() < 180)
			{
				if (player.getForward() < 90)
				{
					AudioP.changePitch(0.96);
				}
				else
				{
					AudioP.changePitch(0.98);
				}
			}
			else
			{
				AudioP.changePitch(1.02);
			}
		}
		else
		{
			AudioP.changePitch(1.04);

		}
	}
	else if(inGame && onHold)
	{
		elapsed = clock.getElapsedTime();
		checkLap();

		if (elapsed.asSeconds() > 1)
		{
			std::cout << "OnHold OFF";

			if (player.lapsCompleted == 0 && ai.lapsCompleted==0)
			{
				onHold = false;
				clock.restart();
				AudioP.playEngineSound();
				std::cout << "on hold false";

			}
			else
			{
				this->inGame = false;
				AudioP.stopAllInGameSounds();
				std::cout << "in Game false";
			}
		}
	}

}
bool Game::GetOnHold()
{
	return onHold;
}
void Game::restart()
{
	inGame = true;
	player.SetLocation(level.p1Start.x, level.p1Start.y);
	ai.SetLocation(level.p2Start.x, level.p2Start.y);

	ai.restart();
	player.restart();
	clock.restart();
}
double Game::GetTimeAsSeconds()
{
	return elapsed.asSeconds();
}

sf::Image Game::GetLevelData()
{
	return this->level.leveldata;
}

Player* Game::GetPlayerRef()
{
	return &this->player;
}

AI* Game::GetAIRef()
{
	return &this->ai;
}

bool Game::GetInGame()
{
	return inGame;
}

Gate* Game::GetGatesRef()
{
	return &this->gates[0];
}

void Game::checkLap()
{
	for (int i = 0; i < 3; i++)
	{
		if (gates[i].GateSprite.getGlobalBounds().intersects(ai.playerSprite.getGlobalBounds()))
		{
			ai.driveThroughGate(i);
		}
		if (gates[i].GateSprite.getGlobalBounds().intersects(player.playerSprite.getGlobalBounds()))
		{
			player.driveThroughGate(i);

		}
	}
	/*if (player.playerSprite.getGlobalBounds().intersects(ai.playerSprite.getGlobalBounds()))	//This triggers way too early...
	{
		if (player.speed > ai.speed)
		{
			player.bump('b');
		}
		else
		{
			ai.bump('b');
		}

	}*/
}
void Game::checkWinner()
{
	if (player.lapsCompleted == NumberOfLapsToWin)
	{
		std::cout << "PLAYER1 WINS!!!";
		onHold =true;
		player.lapsCompleted = 5;
		clock.restart();
	}
	else if (ai.lapsCompleted == NumberOfLapsToWin)
	{
		std::cout << "AI WINS!!!";
		onHold = true;
		ai.lapsCompleted = 5;
		clock.restart();

	}
}

//  Huom. Mietittiin ja tehtiin tämä funktio yhdessä Aleksi Pakkasen kanssa keväällä 2019
void Game::checkCollisionFront()
{
	//HUOM playerSprite.setOrigin(textureWidth-6, textureHeight/2);
	//Player car is 56*25 pixels

	float forward = player.getForward();
	//forward vector dx,dy
	float dx = cos(forward*0.0174532925);
	float dy = sin(forward*0.0174532925);
	// normal to forward vector
	float normalX= cos((forward+90)*0.0174532925);
	float normalY = sin((forward + 90)*0.0174532925);
	// headlight coordinates
	sf::Vector2f LeftFront((player.getX() + 6 * dx)-normalX*25/2, (player.getY()+6*dy) - 25 / 2 * normalY); // axis of car is at 50 and 25/2, car is 56*25 pixels
	sf::Vector2f RightFront((player.getX() + 6 * dx) + normalX * 25 / 2, (player.getY()+6*dy) + 25 / 2 * normalY);


	if (level.leveldata.getPixel(LeftFront.x,LeftFront.y) != sf::Color::Black || level.leveldata.getPixel(RightFront.x, RightFront.y) != sf::Color::Black)
	{
		player.bump('b');

	}
}

void Game::checkCollisionLeft()
{
	float forward = player.getForward();
	//forward vector dx,dy
	float dx = cos(forward*0.0174532925);
	float dy = sin(forward*0.0174532925);
	// normal to forward vector
	float normalX = cos((forward + 90)*0.0174532925);
	float normalY = sin((forward + 90)*0.0174532925);
	// headlight coordinates
	sf::Vector2f LeftFront((player.getX() + 6 * dx) - normalX * 25 / 2, (player.getY() + 6 * dy) - 25 / 2 * normalY); // center is 50 , 25/2 car is 56 , 25/2
	sf::Vector2f LeftRear((player.getX() - 50 * dx) - normalX * 25 / 2, (player.getY() - 50 * dy) - 25 / 2 * normalY); // center is 50 , 25/2 car is 56 , 25/2

	if (level.leveldata.getPixel(LeftFront.x, LeftFront.y) != sf::Color::Black || level.leveldata.getPixel(LeftRear.x, LeftRear.y) != sf::Color::Black)
	{
		player.bump('r');

	}

}
void Game::checkCollisionRight()
{
	float forward = player.getForward();
	//forward vector dx,dy
	float dx = cos(forward*0.0174532925);
	float dy = sin(forward*0.0174532925);
	// normal to forward vector
	float normalX = cos((forward + 90)*0.0174532925);
	float normalY = sin((forward + 90)*0.0174532925);
	// headlight coordinates
	sf::Vector2f RightRear((player.getX() - 50 * dx) + normalX * 25 / 2, (player.getY() - 50 * dy) + 25 / 2 * normalY);
	sf::Vector2f RightFront((player.getX() + 6 * dx) + normalX * 25 / 2, (player.getY() + 6 * dy) + 25 / 2 * normalY);

	if (level.leveldata.getPixel(RightFront.x, RightFront.y) != sf::Color::Black || level.leveldata.getPixel(RightRear.x, RightRear.y) != sf::Color::Black)
	{
		player.bump('l');

	}

}
void Game::checkCollisionBack()
{
	float forward = player.getForward();
	//forward vector dx,dy
	float dx = cos(forward*0.0174532925);
	float dy = sin(forward*0.0174532925);
	// normal to forward vector
	float normalX = cos((forward + 90)*0.0174532925);
	float normalY = sin((forward + 90)*0.0174532925);

	// rearlight coordinates
	sf::Vector2f LeftRear((player.getX() - 50 * dx) - normalX * 25 / 2, (player.getY() - 50 * dy) - 25 / 2 * normalY); // center is 50 , 25/2 car is 56 , 25/2
	sf::Vector2f RightRear((player.getX() - 50 * dx) + normalX * 25 / 2, (player.getY() - 50 * dy) + 25 / 2 * normalY);


	if (level.leveldata.getPixel(LeftRear.x, LeftRear.y) != sf::Color::Black || level.leveldata.getPixel(RightRear.x, RightRear.y) != sf::Color::Black)
	{
		player.bump('f');
	}


}

void Game::determineAIAction()
{
	float forward = ai.getForward();
	//forward vector dx,dy
	float dx = cos(forward*0.0174532925);
	float dy = sin(forward*0.0174532925);
	// normal to forward vector
	float normalX = cos((forward + 90)*0.0174532925);
	float normalY = sin((forward + 90)*0.0174532925);

	int AIvisionRange = 70;

	// look at pixels 10 pixel in front of cars nose
	sf::Vector2f LeftFront((ai.getX() + (6+AIvisionRange)* dx) - normalX * 25 / 2, (ai.getY() + (6 + AIvisionRange) * dy) - 25 / 2 * normalY); // axis of car is at 50 and 25/2, car is 56*25 pixels
	sf::Vector2f RightFront((ai.getX() + (6 + AIvisionRange) * dx) + normalX * 25 / 2, (ai.getY() + (6 + AIvisionRange) * dy) + 25 / 2 * normalY);
	sf::Vector2f MiddleFront((ai.getX() + (6 + AIvisionRange) * dx), (ai.getY() + (6 + AIvisionRange) * dy));


	if (level.leveldata.getPixel(MiddleFront.x, MiddleFront.y) != sf::Color::Black)	//if there are walls ahead
	{
		sf::Vector2f Left((ai.getX() + 6 * dx) - normalX * 25 / 2, (ai.getY() + 6 * dy) - 25 / 2 * normalY);
		sf::Vector2f Right((ai.getX() + 6 * dx) + normalX * 25 / 2, (ai.getY() + 6 * dy) + 25 / 2 * normalY);

		//std::cout << "midleBlack";
		for (int i = 0; i < 150; i++)
		{
			
			sf::Vector2f Left2(Left.x-normalX*i,Left.y-normalY*i);
			sf::Vector2f Right2(Right.x + normalX * i,Right.y + normalY * i);

		//	std::cout << Left2.x << "," << Left2.y << std::endl;

			if (level.leveldata.getPixel(Left2.x, Left2.y) != sf::Color::Black)
			{
				ai.moveRight();
				i = 150;
				//std::cout << "moveRight: "<< std::endl;
			}
			else if (level.leveldata.getPixel(Right2.x, Right2.y) != sf::Color::Black)
			{
				ai.moveLeft();
				i = 150;
				//std::cout << "moveLeft: " << std::endl;
			}

		}
	}
	else if (level.leveldata.getPixel(LeftFront.x, LeftFront.y) != sf::Color::Black)	// walls ahead but only to left corner
	{
		//std::cout << "left black -> moveRight: " << std::endl;
		ai.moveRight();

	}
	else if (level.leveldata.getPixel(RightFront.x, RightFront.y) != sf::Color::Black)	// walls ahead of the right corner
	{
		//std::cout << "Right black -> moveLeft: " << std::endl;
		ai.moveLeft();
	}
	else if (level.leveldata.getPixel(LeftFront.x - normalX * 10, LeftFront.y - normalY * 10) != sf::Color::Black)	// left side almost at wall
	{
		ai.moveRight();
		//std::cout << "moveRight: " << std::endl;
	}
	else if (level.leveldata.getPixel(RightFront.x + normalX * 10, RightFront.y + normalY * 10) != sf::Color::Black)	// Right side almost at wall
	{
		//std::cout << "moveLeft: " << std::endl;
		ai.moveLeft();

	}
	else // press gas when not turning
	{
		ai.moveUp();
		return;
	}

	if ((rand() % 2 + 1) == 2)//sometimes press gas on turns
	{
	ai.moveUp();
	} 

}

//  Huom. Mietittiin ja aloitettiin tämä funktio yhdessä Aleksi Pakkasen kanssa keväällä 2019.
void Game::checkCollision()
{
	//HUOM playerSprite.setOrigin(textureWidth-6, textureHeight/2);
	//Player car is 56*25 pixels

	float forward = player.getForward();
	//forward vector dx,dy
	float dx = cos(forward*0.0174532925);
	float dy = sin(forward*0.0174532925);
	// normal to forward vector
	float normalX = cos((forward + 90)*0.0174532925);
	float normalY = sin((forward + 90)*0.0174532925);

	// headlight coordinates
	sf::Vector2f LeftFront((player.getX() + 6 * dx) - normalX * 25 / 2, (player.getY() + 6 * dy) - 25 / 2 * normalY); // axis of car is at 50 and 25/2, car is 56*25 pixels
	sf::Vector2f RightFront((player.getX() + 6 * dx) + normalX * 25 / 2, (player.getY() + 6 * dy) + 25 / 2 * normalY);

	// rearlight coordinates
	sf::Vector2f LeftRear((player.getX() - 50 * dx) - normalX * 25 / 2, (player.getY() - 50 * dy) - 25 / 2 * normalY);
	sf::Vector2f RightRear((player.getX() - 50 * dx) + normalX * 25 / 2, (player.getY() - 50 * dy) + 25 / 2 * normalY);
	if (level.leveldata.getPixel(LeftFront.x, LeftFront.y) != sf::Color::Black && level.leveldata.getPixel(RightFront.x, RightFront.y) != sf::Color::Black&&level.leveldata.getPixel(LeftRear.x, LeftRear.y) != sf::Color::Black && level.leveldata.getPixel(RightRear.x, RightRear.y) != sf::Color::Black)
	{
		player.SetLocation(level.p1Start.x, level.p1Start.y);

	}
	else
	{
		if (level.leveldata.getPixel(LeftFront.x, LeftFront.y) != sf::Color::Black || level.leveldata.getPixel(RightFront.x, RightFront.y) != sf::Color::Black)
		{
			player.bump('b');
			AudioP.playCrashSound();
		}
		if (level.leveldata.getPixel(LeftRear.x, LeftRear.y) != sf::Color::Black || level.leveldata.getPixel(RightRear.x, RightRear.y) != sf::Color::Black)
		{
			player.bump('f');
			AudioP.playCrashSound();

		}
		if (level.leveldata.getPixel(RightFront.x, RightFront.y) != sf::Color::Black || level.leveldata.getPixel(RightRear.x, RightRear.y) != sf::Color::Black)
		{
			player.bump('l');
			AudioP.playCrashSound();


		}
		if (level.leveldata.getPixel(LeftFront.x, LeftFront.y) != sf::Color::Black || level.leveldata.getPixel(LeftRear.x, LeftRear.y) != sf::Color::Black)
		{
			player.bump('r');
			AudioP.playCrashSound();


		}
	}

}
void Game::checkCollisionAI()
{
	//HUOM playerSprite.setOrigin(textureWidth-6, textureHeight/2);
	//Player car is 56*25 pixels

	float forward = ai.getForward();
	//forward vector dx,dy
	float dx = cos(forward*0.0174532925);
	float dy = sin(forward*0.0174532925);
	// normal to forward vector
	float normalX = cos((forward + 90)*0.0174532925);
	float normalY = sin((forward + 90)*0.0174532925);

	// headlight coordinates
	sf::Vector2f LeftFront((ai.getX() + 6 * dx) - normalX * 25 / 2, (ai.getY() + 6 * dy) - 25 / 2 * normalY); // axis of car is at 50 and 25/2, car is 56*25 pixels
	sf::Vector2f RightFront((ai.getX() + 6 * dx) + normalX * 25 / 2, (ai.getY() + 6 * dy) + 25 / 2 * normalY);

	// rearlight coordinates
	sf::Vector2f LeftRear((ai.getX() - 50 * dx) - normalX * 25 / 2, (ai.getY() - 50 * dy) - 25 / 2 * normalY);
	sf::Vector2f RightRear((ai.getX() - 50 * dx) + normalX * 25 / 2, (ai.getY() - 50 * dy) + 25 / 2 * normalY);
	if (level.leveldata.getPixel(LeftFront.x, LeftFront.y) != sf::Color::Black && level.leveldata.getPixel(RightFront.x, RightFront.y) != sf::Color::Black&&level.leveldata.getPixel(LeftRear.x, LeftRear.y) != sf::Color::Black && level.leveldata.getPixel(RightRear.x, RightRear.y) != sf::Color::Black)
	{
		ai.SetLocation(level.p2Start.x, level.p2Start.y);

	}
	else
	{
		if (level.leveldata.getPixel(LeftFront.x, LeftFront.y) != sf::Color::Black || level.leveldata.getPixel(RightFront.x, RightFront.y) != sf::Color::Black)
		{
			ai.bump('b');

		}
		if (level.leveldata.getPixel(LeftRear.x, LeftRear.y) != sf::Color::Black || level.leveldata.getPixel(RightRear.x, RightRear.y) != sf::Color::Black)
		{
			ai.bump('f');
		}
		if (level.leveldata.getPixel(RightFront.x, RightFront.y) != sf::Color::Black || level.leveldata.getPixel(RightRear.x, RightRear.y) != sf::Color::Black)
		{
			ai.bump('l');

		}
		if (level.leveldata.getPixel(LeftFront.x, LeftFront.y) != sf::Color::Black || level.leveldata.getPixel(LeftRear.x, LeftRear.y) != sf::Color::Black)
		{
			ai.bump('r');

		}
	}

}