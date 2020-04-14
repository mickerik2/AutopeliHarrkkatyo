#pragma once
#include <SFML/Graphics.hpp>
#include<math.h>
#include<string>
class Player
{
public:
	sf::Sprite playerSprite;
	sf::Texture texture;

	Player(std::string pic);
	~Player();

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	void move();
	void bump(char dir);

	void driveThroughGate(int id);

	float getX();
	float getY();
	float getForward();


	float speed=0;
	float maxspeed = 2.5; // max speed of the car
	float sideSpeed = 0;

	float turnspeed=0.5;
	float cornerTurnspeed = 0.4;
	float currentTurnspeed;

	float maxAcceleration = 0.015; //acceleration of the car
	float currentAcceleration;
	float resistanse = 0.003; // slowing speed when not pressing gas
	float resistanseNormal = 0.01; // slowing speed when not pressing gas

	int textureWidth=56;
	int textureHeight=25;

	float dy = 0;
	float dx = 0;
	float Ndy = 0; //Normals
	float Ndx = 0;

	void SetLocation(int x, int y);

	int lapsCompleted=0;
	bool gates[3];

	void restart();

protected:
	float x;
	float y;
	float forward;

};

