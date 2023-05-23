#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "letter.h"
#include "iostream"
#include <string>
#include "Windows.h"

using namespace sf;
using namespace std;

int k = 0;// Глобальная переменная - индикатор (показать/скрыть букву)

int main()
{
    RenderWindow win(sf::VideoMode(1280, 850), L"Клавиатурный тренажёр"); // Настройка окна

    ////////// Объекты и текстуры /////////

    /// Фон ///
    Texture BG;
    BG.loadFromFile("Image/BG.png");
    RectangleShape BackGround(Vector2f(1280, 850));
    BackGround.setTexture(&BG);
    
    /// Клавиатура ///
    Texture klava;
    klava.loadFromFile("Image/Keyboard.png");
    RectangleShape keyb(Vector2f(768 * 1.2, 360 * 1.2));
    keyb.setTexture(&klava);
    keyb.setPosition(200, 490);

    /// 3 Сердца - жизни ///
    Texture heart;
    heart.loadFromFile("Image/heart4.png");
    Sprite live1 (heart), live2 (heart), live3 (heart);
    live1.setPosition(1050, 5);
    live2.setPosition(1120, 5);
    live3.setPosition(1190, 5);

    /// Кнопка старт ///
    Texture start;
    start.loadFromFile("Image/Start3.png");
    Sprite start_button(start);
    start_button.setPosition(400, 200);

    /// Кнопка выход ///
    Texture exit;
    exit.loadFromFile("Image/exit2.png");
    Sprite exit_button(exit);
    exit_button.setPosition(390, 450);

    /// Пауза ///
    Texture pause;
    pause.loadFromFile("Image/pause3.png");
    Sprite pause_sprite(pause);
    pause_sprite.setPosition(410, -120);

    /// Игра окончена ///
    Texture end;
    end.loadFromFile("Image/end.png");
    Sprite end_sprite(end);
    end_sprite.setPosition(40, 50);

    /// Счёт ///
    Texture bank;
    bank.loadFromFile("Image/points.png");
    Sprite bank_sprite(bank);
    bank_sprite.setPosition(-10, 300);
    
    /// Декорация 1 ///
    Texture note;
    note.loadFromFile("Image/note.png");
    RectangleShape notebook(Vector2f(200, 200));
    notebook.setTexture(&note);
    notebook.setPosition(50, 650);
    notebook.setRotation(-5);

    /// Декорация 2 ///
    Texture pad;
    pad.loadFromFile("Image/gamepad2.png");
    RectangleShape gamepad(Vector2f(120, 105));
    gamepad.setTexture(&pad);
    gamepad.setPosition(1050, 100);
    gamepad.setRotation(20);

    /// Декорация 3 ///
    Texture keyb_menu;
    keyb_menu.loadFromFile("Image/keyb_menu.png");
    RectangleShape keyboard_menu(Vector2f(150, 150));
    keyboard_menu.setTexture(&keyb_menu);
    keyboard_menu.setPosition(1050, 650);
    keyboard_menu.setRotation(15);

    /// Декорация 4 ///
    Texture board_menu;
    board_menu.loadFromFile("Image/white_board.png");
    RectangleShape white_board(Vector2f(150, 150));
    white_board.setTexture(&board_menu);
    white_board.setPosition(50, 100);
    white_board.setRotation(-15);

    //////////////////////////////////
    
    ////////// Шрифт и текст /////////

    /// Шрифт ///
    Font font; 
    font.loadFromFile("Font/CyrilicOld.ttf");

    /// Количество очков ///
    Text bar;
    bar.setFont(font);
    bar.setFillColor(Color::Black);
    bar.setStyle(Text::Regular);
    bar.setString("Количество очков: ");

    /// Очки ///
    Text points;
    points.setFont(font);
    points.setFillColor(Color::Black);
    points.setStyle(Text::Regular);
   
    ///////////////////////////////////

    ////////// Музыка и звуки /////////
    
    /// Фоновая музыка игры ///
    Music BackGroundMusic;
    BackGroundMusic.openFromFile("Sound/mus_clear_long.wav");
    BackGroundMusic.setVolume(0);
    BackGroundMusic.play();
    BackGroundMusic.setLoop(true);

    /// Фоновая музыка меню ///
    Music MenuMusic;
    MenuMusic.openFromFile("Sound/mus_long.wav");
    MenuMusic.setVolume(0);
    MenuMusic.play();
    MenuMusic.setLoop(true);

    /// Звук правильного нажатия ///
    SoundBuffer buf_win;
    buf_win.loadFromFile("Sound/win_simple.wav");
    Sound win_sound;
    win_sound.setBuffer(buf_win);
    win_sound.setVolume(100);

    /// Звук лопающегося сердца ///
    SoundBuffer buf_pop;
    buf_pop.loadFromFile("Sound/heart_break.wav");
    Sound pop_sound;
    pop_sound.setBuffer(buf_pop);
    pop_sound.setVolume(100);

    //////////////////////////////////////////

    ////////// Объявление переменных /////////
    Vector2f pos; // Переменная для хрнения координат объектов
    Clock clock; // Переменная хранящая время с начала работы программы
    float time, time_del = 3000; // Переменные задающие скорость движения объектов
    bool isMenu = 1; // Проверка вывода меню
    bool isLose = 0; // Проверка вывода окна проигрыша
    bool isPause = 0; // Проверка вывода паузы
    int cursor_pos; // Переменная хранящая координаты курсора мыши
    String str_point; // Переменная для записи очков (int) в текст для вывода (text)    
    letter maslet[1]; // Создание массива объектов созданных в классе (letter.h)
    int nlet = 1; // Количество объектов в массиве
    int point = 0; // Количество очков

    //////////////////////////////////////////

    while (win.isOpen()) // Пока окно открыто
    {
        sf::Event event; // Событие
        time = clock.getElapsedTime().asMicroseconds(); // Время в микросекундах
        time = time / time_del; // Время с меняющимся уменьшителем
        clock.restart(); // Перезапуск секундомера

        cursor_pos = 0; // Обнуление координат курсора

        str_point = to_string(point);
        points.setString(str_point);

        LoadKeyboardLayout(L"00000409", KLF_ACTIVATE); // Установка английской раскладки

        if (isMenu) // Если открыто меню
        {
            BackGroundMusic.setVolume(0);
            MenuMusic.setVolume(30);
            start_button.setColor(Color::White); // "Обнуление" цвета кнопки старт
            exit_button.setColor(Color::White); // "Обнуление" цвета кнопки выход
            
            while (win.pollEvent(event)) // Цикл созданный для закрытия окна на крестик
            {
                if (event.type == sf::Event::Closed) // Если крестик нажат
                    win.close();
            }

            if (IntRect(410, 315, 400, 70).contains(Mouse::getPosition(win))) // Если мышь попадает в обасть кнопки старт
            {
                start_button.setColor(Color::Blue); // Перекрасить кнопку старт в синий
                cursor_pos = 1; // Установить координату мыши равную 1
            }
            if (IntRect(410, 565, 435, 70).contains(Mouse::getPosition(win))) // Если мышь попадает в обасть кнопки выход
            {
                exit_button.setColor(Color::Blue); // Перекрасить кнопку выход в синий
                cursor_pos = 3; // Установить координату мыши равную 3
            }
            if (Mouse::isButtonPressed(Mouse::Left())) // Если левая кнопка мыши нажата
            {
                if (cursor_pos == 1) // Если курсор мыши на кнопке старт
                {
                    
                    isMenu = false; // Закрыть меню
                }
                if (cursor_pos == 3) // Если курсор мыши на кнопке выход
                {
                    win.close();
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Enter)) // Если нажата кнопка Enter в меню
            {
                isMenu = false; // Закрыть меню
            }
            /// Вывод объектов меню ///
            win.clear();
            win.draw(BackGround);
            win.draw(notebook);
            win.draw(keyboard_menu);
            win.draw(gamepad);
            win.draw(white_board);
            win.draw(start_button);
            win.draw(exit_button);
        }
        else // Если пользователь находится не в меню
        {
            if (lives < 1) // Обнуление размера сердец - жизней
            {
                live1.setScale(0.07, 0.07);
                live2.setScale(0.07, 0.07);
                live3.setScale(0.07, 0.07);
            }
            if (lives == 1) // Действия при первом промахе
            {
                pop_sound.play();
                time_del += 250;
                live1.setScale(0, 0);
                lives++;
            }

            if (lives == 3) // Действия при втором промахе
            {
                pop_sound.play();
                time_del += 250;
                live2.setScale(0, 0);
                lives++;
            }

            if (lives >= 5) // Действия при третьем промахе
            {
                live3.setScale(0, 0);
                isLose = true;
                
                if (isLose) // Если открыто окно проигрыша
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
                while (win.pollEvent(event)) // Цикл созданный для закрытия окна на крестик
                {
                    if (event.type == sf::Event::Closed) // Если крестик нажат
                        win.close();


                    if (Event::KeyPressed) // Если нажата кнопка в окне проигрыша
                    {
                       
                        if (event.key.code == Keyboard::Enter) // Если нажат Enter
                        {
                            isLose = false;
                            isMenu = false;
                            time_del = 3000;
                            point = 0;
                            lives = 0;
                        }
                        if (event.key.code == Keyboard::Escape) // Если нажат Escape
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

            if (isPause) // Пауза
            {
                MenuMusic.setVolume(30);
                BackGroundMusic.setVolume(0);
                while (win.pollEvent(event)) // Цикл созданный для закрытия окна на крестик
                {
                    if (event.type == sf::Event::Closed) // Если крестик нажат
                        win.close();
                }
                time = 0;
                if (Keyboard::isKeyPressed(Keyboard::Enter)) // Если нажат Enter в паузе
                {
                    isPause = false;
                }
                win.draw(pause_sprite);
            }

            if (!isLose && !isPause) // Если запущено окно с игрой
            {
                points.setPosition(bar.getPosition().x + 250, bar.getPosition().y);
                points.setCharacterSize(30);
                points.setFillColor(Color::Black);
                MenuMusic.setVolume(0);
                BackGroundMusic.setVolume(30);
                while (win.pollEvent(event)) // Цикл созданный для закрытия окна на крестик
                {
                    if (event.type == sf::Event::Closed) // Если крестик нажат
                        win.close();


                    if (Event::KeyPressed) // Если клавиша нажата
                    {
                        if (!isMenu)
                        {
                            if (event.key.code == letter_code) // Если нажатая клавиша совпадает с нужной буквой
                            {
                                ++point;
                                ++k;
                                win_sound.play();
                                
                            }

                            if (event.key.code == Keyboard::Escape) // Если нажат Escape в процессе игры
                            {
                                isPause = 1;
                            }
                            if (event.key.code == Keyboard::Subtract && time_del < 6000) // Если нажат "-" в процессе игры
                                time_del += 500; // Уменьшение скорости падения букв
                            if (event.key.code == Keyboard::Add && time_del > 1000) // Если нажат "+" в процессе игры
                                time_del -= 500; // Увеличение скорости падения букв
                        }
                    }

                    if (point > 0 && point % 10 == 0 && time_del > 1000 && lives != 1 && lives != 3) // Если кол-во очков кратно 10 - увеличить скорость 
                    {
                        time_del -= 250;
                    }
                }

                for (int i = 0; i < nlet; i++) // Цикл задающий движение всем элементам массива
                    maslet[i].move(time);

                /// Вывод и отрисовка объектов ///
                win.clear();
                win.draw(BackGround);
                for (int i = 0; i < nlet; i++) // Цикл отрисовывающий все элементы массива
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