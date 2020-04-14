#include "AI.h"
#include<string>

void AI::setDifficulty(bool hard)
{
	this->hard = hard;
}
AI::~AI()
{

}
AI::AI(std::string pic):Player(pic)
{

}