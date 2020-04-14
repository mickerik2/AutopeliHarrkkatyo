#pragma once
#include "Player.h"
#include<string>

class AI :public Player
{
public:
	bool hard;
	void setDifficulty(bool hard);
	AI(std::string pic);
	~AI();
};
