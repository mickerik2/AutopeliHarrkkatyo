#include "Level.h"
#include <cstdlib>
#include <time.h>
#include<math.h>
#include <SFML/Graphics.hpp>
#include<string>


Level::Level()
{
	/* initialize random seed: */
	srand(time(NULL));

	leveldata.create(this->width, this->height);
	sf::Vector2f tmp(width * 1 / 4-100, height * 1 / 4);
	startLocation = tmp;

	sf::Vector2f tmp1(startLocation.x+500, startLocation.y+430);
	p1Start = tmp1;

	sf::Vector2f tmp2(startLocation.x + 600, startLocation.y + 470);
	p2Start = tmp2;



}
void Level::Randomize()// NOT used
{
	for (int x = 0; x < this->width; x++)
	{
		for (int y = 0; y < this->height; y++)
		{
			//leveldata.setPixel(x, y, sf::Color::Black);
			leveldata.setPixel(x, y, sf::Color(rand() % 100, rand() % 156+100, rand() % 100));
		}
	}
	
	int bigRadius = height / 4;
	int smallRadius = bigRadius / 2;

	generateBlackCircle(width / 4,height/4+10, bigRadius);

	generateBlackCircle(width * 3 / 4, height / 4+10, bigRadius);

	generateBlackCircle(width / 4, height *3/ 4-10, bigRadius);

	generateBlackCircle(width * 3 / 4, height *3/ 4-10, bigRadius);

	generateGreenCircle(width / 4, height / 4 + 10, smallRadius);

	generateGreenCircle(width * 3 / 4, height / 4 + 10, smallRadius);

	generateGreenCircle(width / 4, height * 3 / 4 - 10, smallRadius);

	generateGreenCircle(width * 3 / 4, height * 3 / 4 - 10, smallRadius);


	generateGreenCircle(width / 4+ smallRadius, height / 4 + 10+ smallRadius, smallRadius);

	generateGreenCircle(width * 3 / 4-smallRadius, height / 4 + 10+smallRadius, height / 8);

	/*generateGreenCircle(width / 4, height * 3 / 4 - 10, height / 8);

	generateGreenCircle(width * 3 / 4, height * 3 / 4 - 10, height / 8);*/


	generateBlock(width / 4+ height / 4-10, height / 4 + 10- height / 16, 300, height / 8);
	generateBlock(width / 4 + height / 4 - 10, height * 3 / 4 - 10 - height / 16, 300, height / 8);
	
}
void Level::Generate()
{
	int bigRadius = 200;
	int smallRadius = bigRadius/2;

	for (int x = 0; x < this->width; x++)
	{
		for (int y = 0; y < this->height; y++)
		{
			leveldata.setPixel(x, y, sf::Color(rand() % 100, rand() % 156 + 100, rand() % 100));
		}
	}

	GenerateQuarterCircle(startLocation.x, startLocation.y, bigRadius, smallRadius, "NW");
	GenerateQuarterCircle(startLocation.x, startLocation.y, bigRadius, smallRadius, "SW");
	GenerateQuarterCircle(startLocation.x, startLocation.y+3*smallRadius, bigRadius, smallRadius, "NE");
	GenerateQuarterCircle(startLocation.x + 3 * smallRadius, startLocation.y + 3 * smallRadius, bigRadius, smallRadius, "SW");

	generateBlock(startLocation.x,startLocation.y - bigRadius,3*smallRadius,smallRadius);

	GenerateQuarterCircle(startLocation.x + 3 * smallRadius, startLocation.y, bigRadius, smallRadius, "NE");
	GenerateQuarterCircle(startLocation.x + 6 * smallRadius, startLocation.y, bigRadius, smallRadius, "SW");
	GenerateQuarterCircle(startLocation.x + 6 * smallRadius, startLocation.y, bigRadius, smallRadius, "SE");
	GenerateQuarterCircle(startLocation.x + 9 * smallRadius, startLocation.y, bigRadius, smallRadius, "NW");
	GenerateQuarterCircle(startLocation.x + 9 * smallRadius, startLocation.y, bigRadius, smallRadius, "NE");

	generateBlock(startLocation.x+5*bigRadius, startLocation.y, smallRadius, 3*smallRadius);
	generateBlock(startLocation.x+bigRadius*2-smallRadius , startLocation.y+bigRadius*2, smallRadius*6, smallRadius);

	GenerateQuarterCircle(startLocation.x + 9 * smallRadius, startLocation.y + 3 * smallRadius, bigRadius, smallRadius, "SE");


	generateBlock(1, height-303, 200, 200);	//Menu AREA

}


void Level::GenerateQuarterCircle(int centerX, int centerY, int radiusOut, int radiusIn, std::string sector)
{
	int XT;
	int YT;
	if (sector == "NW")
	{
		for (int x = 0; x < this->width; x++)
		{
			for (int y = 0; y < this->height; y++)
			{
				XT = pow(x - centerX, 2);
				YT = pow(y - centerY, 2);
				if (pow(radiusOut, 2) > XT + YT && x <= centerX&&y <= centerY)
				{
					leveldata.setPixel(x, y, sf::Color::Black);
				}
			}
		}

		for (int x = 0; x < this->width; x++)
		{
			for (int y = 0; y < this->height; y++)
			{
				XT = pow(x - centerX, 2);
				YT = pow(y - centerY, 2);
				if (pow(radiusIn, 2) > XT + YT && x <= centerX&&y <= centerY)
				{
					leveldata.setPixel(x, y, sf::Color(rand() % 100, rand() % 156 + 100, rand() % 100));
				}
			}
		}
	}
	else if (sector == "NE")
	{
		for (int x = 0; x < this->width; x++)
		{
			for (int y = 0; y < this->height; y++)
			{
				XT = pow(x - centerX, 2);
				YT = pow(y - centerY, 2);
				if (pow(radiusOut, 2) > XT + YT && x >= centerX&&y <= centerY)
				{
					leveldata.setPixel(x, y, sf::Color::Black);
				}
			}
		}

		for (int x = 0; x < this->width; x++)
		{
			for (int y = 0; y < this->height; y++)
			{
				XT = pow(x - centerX, 2);
				YT = pow(y - centerY, 2);
				if (pow(radiusIn, 2) > XT + YT && x >= centerX&&y <= centerY)
				{
					leveldata.setPixel(x, y, sf::Color(rand() % 100, rand() % 156 + 100, rand() % 100));
				}
			}
		}
	}
	else if (sector == "SW")
	{
		for (int x = 0; x < this->width; x++)
		{
			for (int y = 0; y < this->height; y++)
			{
				XT = pow(x - centerX, 2);
				YT = pow(y - centerY, 2);
				if (pow(radiusOut, 2) > XT + YT && x <= centerX&&y >= centerY)
				{
					leveldata.setPixel(x, y, sf::Color::Black);
				}
			}
		}

		for (int x = 0; x < this->width; x++)
		{
			for (int y = 0; y < this->height; y++)
			{
				XT = pow(x - centerX, 2);
				YT = pow(y - centerY, 2);
				if (pow(radiusIn, 2) > XT + YT && x <= centerX&&y >= centerY)
				{
					leveldata.setPixel(x, y, sf::Color(rand() % 100, rand() % 156 + 100, rand() % 100));
				}
			}
		}
	}
	else if (sector == "SE")
	{
		for (int x = 0; x < this->width; x++)
		{
			for (int y = 0; y < this->height; y++)
			{
				XT = pow(x - centerX, 2);
				YT = pow(y - centerY, 2);
				if (pow(radiusOut, 2) > XT + YT && x > centerX&&y > centerY)
				{
					leveldata.setPixel(x, y, sf::Color::Black);
				}
			}
		}

		for (int x = 0; x < this->width; x++)
		{
			for (int y = 0; y < this->height; y++)
			{
				XT = pow(x - centerX, 2);
				YT = pow(y - centerY, 2);
				if (pow(radiusIn, 2) > XT + YT && x >= centerX&&y >= centerY)
				{
					leveldata.setPixel(x, y, sf::Color(rand() % 100, rand() % 156 + 100, rand() % 100));
				}
			}
		}
	}
}

void Level::generateBlackCircle(int centerX, int centerY, int radius)
{
	int XT;
	int YT;
	for (int x = 0; x < this->width; x++)
	{
		for (int y = 0; y < this->height; y++)
		{
			XT = pow(x - centerX, 2);
			YT = pow(y - centerY, 2);
			if (pow(radius, 2) > XT + YT)
			{
				leveldata.setPixel(x, y, sf::Color::Black);
			}
		}
	}
}
void Level::generateGreenCircle(int centerX, int centerY, int radius)
{
	int XT;
	int YT;
	for (int x = 0; x < this->width; x++)
	{
		for (int y = 0; y < this->height; y++)
		{
			XT = pow(x - centerX, 2);
			YT = pow(y - centerY, 2);
			if (pow(radius, 2) > XT + YT)
			{
				leveldata.setPixel(x, y, sf::Color(rand() % 100, rand() % 156 + 100, rand() % 100));
			}
		}
	}
}
void Level::generateBlock(int startx,int starty,int x,int y)
{


	for (int j = starty; j <= starty + y; j++)
	{
		for (int i = startx; i <= startx + x; i++)
		{
			if (i < this->width && j < this->height)
			{
				leveldata.setPixel(i, j, sf::Color::Black);
			}
		}
	}
}
