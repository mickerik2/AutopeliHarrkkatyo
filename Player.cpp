#include "Player.h"
#include<iostream>
#include<string>
#include<math.h>






Player::Player(std::string pic)
{
	// load a 32x32 rectangle that starts at (10, 10)
	//if (!texture.loadFromFile("heikki.png", sf::IntRect(45, 60, 32, 32)))
	//{
	//	 error...
	//}

	if (!texture.loadFromFile(pic, sf::IntRect(0, 0, textureWidth, textureHeight)))
	{
	//	 error...
	}

	playerSprite.setTexture(texture);
	//playerSprite.setPosition(sf::Vector2f(0, 0));

	playerSprite.setOrigin(textureWidth-6, textureHeight/2);
	forward = playerSprite.getRotation();//this updates its value

	//normal = forward + 90; // this does NOT update its value

	currentAcceleration = maxAcceleration;
	currentTurnspeed = turnspeed;
	for (int i = 0; i < 3; i++)
	{
		gates[i] = false;
	}
	
}

void Player::SetLocation(int x, int y)
{
	this->x = x;
	this->y = y;
}
void Player::bump(char directionToBumb)
{
	if (directionToBumb == 'b')
	{
		speed = -0.5;
		currentAcceleration = 0;
		currentTurnspeed = turnspeed;
	}
	else if(directionToBumb == 'f')
	{
		speed = 0.5;
		currentAcceleration = 0;
		currentTurnspeed = turnspeed;
	}
	else if (directionToBumb == 'r')
	{
		sideSpeed = 1;
		currentTurnspeed = turnspeed;
	}
	else if (directionToBumb == 'l')
	{
		sideSpeed = -1;
		currentTurnspeed = turnspeed;
	}

}

void Player::move() // called in game.update
{
	//speed -= resistanse;
	if (speed < 0)
	{
		if (currentTurnspeed == cornerTurnspeed)
			speed += 2 * resistanse;
		speed += resistanse;
	}
	else if (speed > 0)
	{
		if (currentTurnspeed == cornerTurnspeed)
			speed -= 2 * resistanse;
		speed -= resistanse;
	}

	if (sideSpeed < 0)
	{
		sideSpeed += resistanseNormal;
	}
	else if (sideSpeed > 0)
	{
		sideSpeed -= resistanseNormal;
	}


	if (speed > maxspeed)
	{
		speed = maxspeed;
	}

	if (currentTurnspeed == turnspeed)
	{
		dx = 0;
		dy = 0;

		//Change to radius by multiplying with 0.0174532925
		dx = cos(forward*0.0174532925) * 1;
		dy = sin(forward*0.0174532925) * 1;

		Ndx = cos((forward + 90) *0.0174532925) * 1;
		Ndy = sin((forward + 90) *0.0174532925) * 1;
	}

	x += dx * speed + Ndx * sideSpeed;
	y += dy * speed + Ndy * sideSpeed;

	playerSprite.setPosition(sf::Vector2f(x, y));

	//std::cout << "speed: " << speed << ", acce:" << currentAcceleration << std::endl;
	//std::cout << "forward: " << forward<< ", normal:" << forward + 90 << std::endl;

}


Player::~Player()
{

}

void Player::moveLeft() // turn left
{
	//x -= 1;
	//playerSprite.setPosition(sf::Vector2f(x, y));

	forward -= currentTurnspeed *speed;
	if (forward < 0)
	{
		forward += 360;
	}
	playerSprite.setRotation(forward);
}
void Player::moveRight() // turn right 
{
	//x += 1;
	//playerSprite.setPosition(sf::Vector2f(x, y));
	forward += currentTurnspeed *speed;
	while(forward > 359)
	{
		forward -= 359;
	}
	playerSprite.setRotation(forward);

}
void Player::moveUp() // add acceleration
{
	currentTurnspeed = turnspeed;
	currentAcceleration = maxAcceleration;
	speed += currentAcceleration;

}
void Player::moveDown() // break
{
	currentTurnspeed = cornerTurnspeed;
}

float Player::getY()
{
	return y;
}

float Player::getX()
{
	return x;
}
float Player::getForward()
{
	return forward;
}

void Player::driveThroughGate(int id)
{
	bool lapcompleted = true; // lap completed
	gates[id] = true;	//this gate is passed

	for (int i = 0; i < 3; i++)
	{
		if (gates[i] == false)
		{
			lapcompleted = false;	//not completed the lap

		}
	}
	if (lapcompleted)
	{

		lapsCompleted++;
		for (int i = 0; i < 3; i++)	//Reset all 
		{
			gates[i] = false;
		}
	}
	else if (id == 2)	// alway reset when crossing goal line
	{
		for (int i = 0; i < 3; i++)
		{

			gates[i] = false;
		}
	}
	/*for (int i = 0; i < 3; i++)
	{
		std::cout << "[" << gates[i] << "]";

	}*/
	std::cout << std::endl;
}
void Player::restart()
{
	playerSprite.setRotation(0);
	speed = 0;
	sideSpeed= 0;
	lapsCompleted = 0;

	for (int i = 0; i < 3; i++)
	{
		gates[i] = false;
	}
}
