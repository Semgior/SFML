#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

extern char letter_code;
extern int k, lives;

class letter
{
public:
	letter(); // �����������
	~letter(); // ����������

	void move(float& time_move); // �������� ����
	void draw(RenderWindow& window); // ��������� ����
	void restart(); // ��������� ����� ���������

private:
	Font font; // ����� �������
	Text letterObj; // ������ - �����


};

