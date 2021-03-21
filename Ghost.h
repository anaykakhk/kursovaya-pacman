#include "Pacman.h"
#pragma once
// особое имя приведения
enum Ghost_type { Blue = 0, Red, Orange, Pink };
// состояние приведения
enum Ghost_state { Normal = 0, Scared, Eaten };

class Ghost                                  // приведение
{
protected:
    bool revived;                            // перерожденный призрак не может быть испуган повторно от одного и того же энергетика
    bool wasScare, wasEaten;                 // отвечает за единственное задание вектора движения
    float mapX, mapY;                        // координата в пикселях в приложении
    float speed;                             // скорость
    float distance;                          // расстояние до следующей координаты массива map
    short side;                              // длина текстуры
    short Px, Py, x, y;                      // координата в массиве map
    Ghost_type name;                         // особое имя приведения
    Ghost_state state;                       // состояние приведения
    std::vector<Diration> dir_vec;           // вектор движения
public:
    Ghost(Pacman& pacman, Ghost_type name, int x = 0, int y = 0);
    void draw(sf::RenderWindow& win, std::vector<std::vector<bool>> dec_arr, std::vector<std::vector<short>> dis_arr, sf::Texture& TGhostE, sf::Texture& TGhostN_0, sf::Texture& TGhostN_1, sf::Texture& TGhostS_0, sf::Texture& TGhostS_1, short& time_passed, signed char& second_scared, signed char& killed_count);
    void move(Pacman& pacman, std::vector<std::vector<bool>> dec_arr, std::vector<std::vector<short>> dis_arr, short map[29][28], unsigned int& score, unsigned int lenght, signed char& killed_count, signed char second_scared, signed char level, short& GRedX, short& GRedY, Diration Plast_dir, bool& gameOver, bool& deathPacman);
    // задание состояния приведения
    void setState(Ghost_state state);
    // задание скорости приведения
    void setSpeed(float speed);
    // задание пути приведения
    void setDir_Vec(std::vector<Diration> dir_vec);
    // получение координаты абциссы приведения
    short getX();
    // получение координаты ординаты приведения
    short getY();
    // получение скорости приведения
    float getSpeed();
};