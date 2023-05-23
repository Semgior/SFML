#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "letter.h"
#include "iostream"
#include <string>
#include "Windows.h"

using namespace sf;
using namespace std;

int k = 0;// ���������� ���������� - ��������� (��������/������ �����)

int main()
{
    RenderWindow win(sf::VideoMode(1280, 850), L"������������ �������"); // ��������� ����

    ////////// ������� � �������� /////////

    /// ��� ///
    Texture BG;
    BG.loadFromFile("Image/BG.png");
    RectangleShape BackGround(Vector2f(1280, 850));
    BackGround.setTexture(&BG);
    
    /// ���������� ///
    Texture klava;
    klava.loadFromFile("Image/Keyboard.png");
    RectangleShape keyb(Vector2f(768 * 1.2, 360 * 1.2));
    keyb.setTexture(&klava);
    keyb.setPosition(200, 490);

    /// 3 ������ - ����� ///
    Texture heart;
    heart.loadFromFile("Image/heart4.png");
    Sprite live1 (heart), live2 (heart), live3 (heart);
    live1.setPosition(1050, 5);
    live2.setPosition(1120, 5);
    live3.setPosition(1190, 5);

    /// ������ ����� ///
    Texture start;
    start.loadFromFile("Image/Start3.png");
    Sprite start_button(start);
    start_button.setPosition(400, 200);

    /// ������ ����� ///
    Texture exit;
    exit.loadFromFile("Image/exit2.png");
    Sprite exit_button(exit);
    exit_button.setPosition(390, 450);

    /// ����� ///
    Texture pause;
    pause.loadFromFile("Image/pause3.png");
    Sprite pause_sprite(pause);
    pause_sprite.setPosition(410, -120);

    /// ���� �������� ///
    Texture end;
    end.loadFromFile("Image/end.png");
    Sprite end_sprite(end);
    end_sprite.setPosition(40, 50);

    /// ���� ///
    Texture bank;
    bank.loadFromFile("Image/points.png");
    Sprite bank_sprite(bank);
    bank_sprite.setPosition(-10, 300);
    
    /// ��������� 1 ///
    Texture note;
    note.loadFromFile("Image/note.png");
    RectangleShape notebook(Vector2f(200, 200));
    notebook.setTexture(&note);
    notebook.setPosition(50, 650);
    notebook.setRotation(-5);

    /// ��������� 2 ///
    Texture pad;
    pad.loadFromFile("Image/gamepad2.png");
    RectangleShape gamepad(Vector2f(120, 105));
    gamepad.setTexture(&pad);
    gamepad.setPosition(1050, 100);
    gamepad.setRotation(20);

    /// ��������� 3 ///
    Texture keyb_menu;
    keyb_menu.loadFromFile("Image/keyb_menu.png");
    RectangleShape keyboard_menu(Vector2f(150, 150));
    keyboard_menu.setTexture(&keyb_menu);
    keyboard_menu.setPosition(1050, 650);
    keyboard_menu.setRotation(15);

    /// ��������� 4 ///
    Texture board_menu;
    board_menu.loadFromFile("Image/white_board.png");
    RectangleShape white_board(Vector2f(150, 150));
    white_board.setTexture(&board_menu);
    white_board.setPosition(50, 100);
    white_board.setRotation(-15);

    //////////////////////////////////
    
    ////////// ����� � ����� /////////

    /// ����� ///
    Font font; 
    font.loadFromFile("Font/CyrilicOld.ttf");

    /// ���������� ����� ///
    Text bar;
    bar.setFont(font);
    bar.setFillColor(Color::Black);
    bar.setStyle(Text::Regular);
    bar.setString("���������� �����: ");

    /// ���� ///
    Text points;
    points.setFont(font);
    points.setFillColor(Color::Black);
    points.setStyle(Text::Regular);
   
    ///////////////////////////////////

    ////////// ������ � ����� /////////
    
    /// ������� ������ ���� ///
    Music BackGroundMusic;
    BackGroundMusic.openFromFile("Sound/mus_clear_long.wav");
    BackGroundMusic.setVolume(0);
    BackGroundMusic.play();
    BackGroundMusic.setLoop(true);

    /// ������� ������ ���� ///
    Music MenuMusic;
    MenuMusic.openFromFile("Sound/mus_long.wav");
    MenuMusic.setVolume(0);
    MenuMusic.play();
    MenuMusic.setLoop(true);

    /// ���� ����������� ������� ///
    SoundBuffer buf_win;
    buf_win.loadFromFile("Sound/win_simple.wav");
    Sound win_sound;
    win_sound.setBuffer(buf_win);
    win_sound.setVolume(100);

    /// ���� ����������� ������ ///
    SoundBuffer buf_pop;
    buf_pop.loadFromFile("Sound/heart_break.wav");
    Sound pop_sound;
    pop_sound.setBuffer(buf_pop);
    pop_sound.setVolume(100);

    //////////////////////////////////////////

    ////////// ���������� ���������� /////////
    Vector2f pos; // ���������� ��� ������� ��������� ��������
    Clock clock; // ���������� �������� ����� � ������ ������ ���������
    float time, time_del = 3000; // ���������� �������� �������� �������� ��������
    bool isMenu = 1; // �������� ������ ����
    bool isLose = 0; // �������� ������ ���� ���������
    bool isPause = 0; // �������� ������ �����
    int cursor_pos; // ���������� �������� ���������� ������� ����
    String str_point; // ���������� ��� ������ ����� (int) � ����� ��� ������ (text)    
    letter maslet[1]; // �������� ������� �������� ��������� � ������ (letter.h)
    int nlet = 1; // ���������� �������� � �������
    int point = 0; // ���������� �����

    //////////////////////////////////////////

    while (win.isOpen()) // ���� ���� �������
    {
        sf::Event event; // �������
        time = clock.getElapsedTime().asMicroseconds(); // ����� � �������������
        time = time / time_del; // ����� � ���������� ������������
        clock.restart(); // ���������� �����������

        cursor_pos = 0; // ��������� ��������� �������

        str_point = to_string(point);
        points.setString(str_point);

        LoadKeyboardLayout(L"00000409", KLF_ACTIVATE); // ��������� ���������� ���������

        if (isMenu) // ���� ������� ����
        {
            BackGroundMusic.setVolume(0);
            MenuMusic.setVolume(30);
            start_button.setColor(Color::White); // "���������" ����� ������ �����
            exit_button.setColor(Color::White); // "���������" ����� ������ �����
            
            while (win.pollEvent(event)) // ���� ��������� ��� �������� ���� �� �������
            {
                if (event.type == sf::Event::Closed) // ���� ������� �����
                    win.close();
            }

            if (IntRect(410, 315, 400, 70).contains(Mouse::getPosition(win))) // ���� ���� �������� � ������ ������ �����
            {
                start_button.setColor(Color::Blue); // ����������� ������ ����� � �����
                cursor_pos = 1; // ���������� ���������� ���� ������ 1
            }
            if (IntRect(410, 565, 435, 70).contains(Mouse::getPosition(win))) // ���� ���� �������� � ������ ������ �����
            {
                exit_button.setColor(Color::Blue); // ����������� ������ ����� � �����
                cursor_pos = 3; // ���������� ���������� ���� ������ 3
            }
            if (Mouse::isButtonPressed(Mouse::Left())) // ���� ����� ������ ���� ������
            {
                if (cursor_pos == 1) // ���� ������ ���� �� ������ �����
                {
                    
                    isMenu = false; // ������� ����
                }
                if (cursor_pos == 3) // ���� ������ ���� �� ������ �����
                {
                    win.close();
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Enter)) // ���� ������ ������ Enter � ����
            {
                isMenu = false; // ������� ����
            }
            /// ����� �������� ���� ///
            win.clear();
            win.draw(BackGround);
            win.draw(notebook);
            win.draw(keyboard_menu);
            win.draw(gamepad);
            win.draw(white_board);
            win.draw(start_button);
            win.draw(exit_button);
        }
        else // ���� ������������ ��������� �� � ����
        {
            if (lives < 1) // ��������� ������� ������ - ������
            {
                live1.setScale(0.07, 0.07);
                live2.setScale(0.07, 0.07);
                live3.setScale(0.07, 0.07);
            }
            if (lives == 1) // �������� ��� ������ �������
            {
                pop_sound.play();
                time_del += 250;
                live1.setScale(0, 0);
                lives++;
            }

            if (lives == 3) // �������� ��� ������ �������
            {
                pop_sound.play();
                time_del += 250;
                live2.setScale(0, 0);
                lives++;
            }

            if (lives >= 5) // �������� ��� ������� �������
            {
                live3.setScale(0, 0);
                isLose = true;
                
                if (isLose) // ���� ������� ���� ���������
                {
                    MenuMusic.setVolume(0);
                    BackGroundMusic.setVolume(0);
                    points.setCharacterSize(80);
                    points.setFillColor(Color::White);
                    points.setPosition(810, 405);
                    win.clear();
                    win.draw(BackGround);
                    win.draw(end_sprite);
                    win.draw(bank_sprite);
                    win.draw(points);
                }
                while (win.pollEvent(event)) // ���� ��������� ��� �������� ���� �� �������
                {
                    if (event.type == sf::Event::Closed) // ���� ������� �����
                        win.close();


                    if (Event::KeyPressed) // ���� ������ ������ � ���� ���������
                    {
                       
                        if (event.key.code == Keyboard::Enter) // ���� ����� Enter
                        {
                            isLose = false;
                            isMenu = false;
                            time_del = 3000;
                            point = 0;
                            lives = 0;
                        }
                        if (event.key.code == Keyboard::Escape) // ���� ����� Escape
                        {
                            isLose = false;
                            isMenu = true;
                            time_del = 3000;
                            point = 0;
                            lives = 0;
                        }

                    }
                }
            }

            if (isPause) // �����
            {
                MenuMusic.setVolume(30);
                BackGroundMusic.setVolume(0);
                while (win.pollEvent(event)) // ���� ��������� ��� �������� ���� �� �������
                {
                    if (event.type == sf::Event::Closed) // ���� ������� �����
                        win.close();
                }
                time = 0;
                if (Keyboard::isKeyPressed(Keyboard::Enter)) // ���� ����� Enter � �����
                {
                    isPause = false;
                }
                win.draw(pause_sprite);
            }

            if (!isLose && !isPause) // ���� �������� ���� � �����
            {
                points.setPosition(bar.getPosition().x + 250, bar.getPosition().y);
                points.setCharacterSize(30);
                points.setFillColor(Color::Black);
                MenuMusic.setVolume(0);
                BackGroundMusic.setVolume(30);
                while (win.pollEvent(event)) // ���� ��������� ��� �������� ���� �� �������
                {
                    if (event.type == sf::Event::Closed) // ���� ������� �����
                        win.close();


                    if (Event::KeyPressed) // ���� ������� ������
                    {
                        if (!isMenu)
                        {
                            if (event.key.code == letter_code) // ���� ������� ������� ��������� � ������ ������
                            {
                                ++point;
                                ++k;
                                win_sound.play();
                                
                            }

                            if (event.key.code == Keyboard::Escape) // ���� ����� Escape � �������� ����
                            {
                                isPause = 1;
                            }
                            if (event.key.code == Keyboard::Subtract && time_del < 6000) // ���� ����� "-" � �������� ����
                                time_del += 500; // ���������� �������� ������� ����
                            if (event.key.code == Keyboard::Add && time_del > 1000) // ���� ����� "+" � �������� ����
                                time_del -= 500; // ���������� �������� ������� ����
                        }
                    }

                    if (point > 0 && point % 10 == 0 && time_del > 1000 && lives != 1 && lives != 3) // ���� ���-�� ����� ������ 10 - ��������� �������� 
                    {
                        time_del -= 250;
                    }
                }

                for (int i = 0; i < nlet; i++) // ���� �������� �������� ���� ��������� �������
                    maslet[i].move(time);

                /// ����� � ��������� �������� ///
                win.clear();
                win.draw(BackGround);
                for (int i = 0; i < nlet; i++) // ���� �������������� ��� �������� �������
                    maslet[i].draw(win);
                win.draw(bar);
                win.draw(live1);
                win.draw(live2);
                win.draw(live3);
                win.draw(keyb);
                win.draw(points);
            }
        }
        win.display();
    }

    return 0;
}