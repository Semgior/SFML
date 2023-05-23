#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

extern char letter_code;
extern int k, lives;

class letter
{
public:
	letter(); // Конструктор
	~letter(); // Деструктор

	void move(float& time_move); // Движение букв
	void draw(RenderWindow& window); // Отрисовка букв
	void restart(); // Установка новых координат

private:
	Font font; // Шрифт объекта
	Text letterObj; // Объект - буква


};

