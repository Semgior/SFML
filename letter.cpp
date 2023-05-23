#include "letter.h"

char letter_code = 'A' + rand() % 26;
int lives = -1;

letter::letter()
{
	font.loadFromFile("Font/font.ttf");
	letterObj.setFont(font);
	letterObj.setCharacterSize(100);
	letterObj.setFillColor(Color::Red);
	letterObj.setStyle(Text::Bold);
	letterObj.setPosition(rand() % 1200 + 10, 700);
}

letter::~letter()
{
}

void letter::move(float & time)
{
	letterObj.move(0, 0.5 * time);
	if (letterObj.getPosition().y > 450 && (letterObj.getPosition().x > 190 && letterObj.getPosition().x < 1100))
	{
		if(lives < 7)
			lives++;
		
		restart();
	}
	else if (letterObj.getPosition().y > 750 && (letterObj.getPosition().x < 190 || letterObj.getPosition().x > 1100))
	{
		if (lives < 7)
			lives++;
		restart();
	}

}

void letter::draw(RenderWindow& window)
{
	if (k == 0)
	{
		window.draw(letterObj);
	}
	else
	{
		restart();
	}
}

void letter::restart()
{
	{
		k = 0;
		srand(time(0));
		letter_code = 'a' + rand() % 26;
		letterObj.setString(letter_code);
		float coord_x = (rand() % 1200 + 10);
		float coord_y = (rand() % 150 + 10);
		letterObj.setPosition(Vector2f(coord_x, coord_y));
	}

}
