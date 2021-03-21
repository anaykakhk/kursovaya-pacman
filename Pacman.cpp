#include "Pacman.h"

inline void Setup(bool isNewGame, bool isBegin = true);

Pacman::Pacman(int x, int y)
    {// конструктор по умолчанию
        this->x = x;
        this->y = y;
        mapX = x * DISTANCE + 62.5f;
        mapY = y * DISTANCE + 64.f;
        distance = DISTANCE;
        speed = 2.f;
        side = 30;
        dir = next_dir = Stop;
    }

void Pacman::draw(sf::RenderWindow& win, sf::Sprite& SPacman, sf::Texture& TPacman_0, sf::Texture& TPacman_1, sf::Texture& TPacman_2, sf::Texture& TPacman_3, sf::Texture& TDeathP_0, sf::Texture& TDeathP_1, sf::Texture& TDeathP_2, sf::Texture& TDeathP_3,
    sf::Texture& TDeathP_4, sf::Texture& TDeathP_5, sf::Texture& TDeathP_6, sf::Texture& TDeathP_7, short time_passed, signed short second_deathP, signed char& lifes, bool& deathPacman, bool& gameOver, bool isPause)
    {// рисовка пакмана
        if (deathPacman && isPause)
        {// анимация смерти
            if (time_passed >= 0 && time_passed <= 200 && second_deathP == 0) SPacman.setTexture(TDeathP_0);
            else if (time_passed >= 200 && time_passed <= 400 && second_deathP == 0) SPacman.setTexture(TDeathP_1);
            else if (time_passed >= 400 && time_passed <= 600 && second_deathP == 0) SPacman.setTexture(TDeathP_2);
            else if (time_passed >= 600 && time_passed <= 800 && second_deathP == 0) SPacman.setTexture(TDeathP_3);
            else if (time_passed >= 800 && time_passed <= 1000 && second_deathP == 1) SPacman.setTexture(TDeathP_4);
            else if (time_passed >= 0 && time_passed <= 200 && second_deathP == 1) SPacman.setTexture(TDeathP_5);
            else if (time_passed >= 200 && time_passed <= 400 && second_deathP == 1) SPacman.setTexture(TDeathP_6);
            else if (time_passed >= 400 && time_passed <= 600 && second_deathP == 1) SPacman.setTexture(TDeathP_7);
            else if (time_passed >= 600 && second_deathP == 1) --lifes, Setup(false);
            if (lifes == 0) deathPacman = false, gameOver = true;
        }// анимация движения
        else if ((distance >= 18.8125f && distance <= 21.5f) || (distance >= 0.f && distance <= 2.6875f))
            SPacman.setTexture(TPacman_0);
        else if ((distance >= 16.125f && distance <= 18.8125f) || (distance >= 2.6875f && distance <= 5.375f))
            SPacman.setTexture(TPacman_1);
        else if ((distance >= 13.4375 && distance <= 16.125f) || (distance >= 5.375f && distance <= 8.0625f))
            SPacman.setTexture(TPacman_2);
        else if ((distance >= 10.75f && distance <= 13.4375) || (distance >= 8.0625f && distance <= 10.75f))
            SPacman.setTexture(TPacman_3);
        SPacman.setPosition(mapX, mapY);
        SPacman.setOrigin(side / 2.f, side / 2.f);
        switch (dir)
        {// поворот картинки
        case Right: SPacman.setTextureRect(sf::IntRect(0, 0, side, side)), SPacman.setRotation(0.f); break;
        case Left: SPacman.setTextureRect(sf::IntRect(side, 0, -1 * side, side)), SPacman.setRotation(0.f); break;
        case Down: SPacman.getTextureRect() == sf::IntRect(0, 0, side, side) ? SPacman.setRotation(90.f) : SPacman.setRotation(-90.f); break;
        case Up: SPacman.getTextureRect() == sf::IntRect(0, 0, side, side) ? SPacman.setRotation(-90.f) : SPacman.setRotation(90.f); break;
        }
        win.draw(SPacman);
    }

void Pacman::move(sf::Sprite& SFruit, Diration Plast_dir, short map[29][28], short energy[29][28], unsigned int lenght, unsigned int& score, unsigned int& lifes_vertex, signed char& lifes_add,
    short& energy_count, signed char& second_fruit, signed char& lifes, signed char number_fruit, signed char& second_scared, signed char& level, bool& gameOver)
    {// логика пакмана
        short i = 0, Nspeed = short(speed / STEP);
        if (energy[y][x] > 0) // съедение энергетиков
        {
            energy[y][x] == 1 ? score += 10 : (score += 50, second_scared = 9, second_scared -= (level + 1) / 7 > 2 ? 6 : (level + 1) / 7 * 2); energy[y][x] = 0; --energy_count; if (energy_count == 180 || energy_count == 60) second_fruit += 10; if (energy_count == 0) gameOver = true;
        }
        if (std::abs(mapX - SFruit.getPosition().x) < 15.f && mapY == SFruit.getPosition().y && second_fruit != char(0))
        {// съедение фрукта
            switch (number_fruit)
            {
                case char(0) : score += 100; break;
                    case char(1) : score += 200; break;
                        case char(2) : score += 500; break;
                            case char(3) : score += 700; break;
                                case char(4) : score += 1000; break;
                                    case char(5) : score += 2000; break;
                                        case char(6) : score += 5000; break;
            }
            second_fruit = char(0);
        }// добавление жизни при определенном кол-ве очков 
        if (score - lifes_vertex >= unsigned(lifes_add - 3) * 5000 + 10000) lifes_vertex += (lifes_add - 3) * 5000 + 10000, ++lifes, ++lifes_add;
        if (dir != Stop) Plast_dir = dir;
        switch (next_dir)
        {// изменение направления движения, если это возможно
        case Right:
            if (dir != next_dir && map[y][x + 1] == 2)
            {
                if (dir == Left) { x == 0 ? x = 27 : x == 27 ? x = 0 : --x; distance = DISTANCE - distance; dir = next_dir; }
                else if (distance == DISTANCE) dir = next_dir;
            }
            break;
        case Left:
            if (dir != next_dir && map[y][x - 1] == 2)
            {
                if (dir == Right) { x == 0 ? x = 27 : x == 27 ? x = 0 : ++x; distance = DISTANCE - distance; dir = next_dir; }
                else if (distance == DISTANCE) dir = next_dir;
            }
            break;
        case Down:
            if (dir != next_dir && map[y + 1][x] == 2)
            {
                if (dir == Up) { --y; distance = DISTANCE - distance; dir = next_dir; }
                else if (distance == DISTANCE) dir = next_dir;
            }
            break;
        case Up:
            if (dir != next_dir && map[y - 1][x] == 2)
            {
                if (dir == Down) { ++y; distance = DISTANCE - distance; dir = next_dir; }
                else if (distance == DISTANCE) dir = next_dir;
            }
            break;
        }
        switch (dir)
        {// движение по карте при определнном напрвлении
        case Right:
            if (x == 27)
            {
                if (distance < DISTANCE / 2) mapX = 62.5f + -1 * distance;
                for (; i < Nspeed; ++i) distance != 0 ? (mapX += STEP, distance -= STEP) : (distance = DISTANCE, x = 0, i = Nspeed);
            }
            else if (map[y][x + 1] == 2)
                for (; i < Nspeed; ++i) distance != 0 ? (mapX += STEP, distance -= STEP) : (distance = DISTANCE, ++x, i = Nspeed);
            else
                dir = Stop;
            break;
        case Left:
            if (x == 0)
            {
                if (distance < DISTANCE / 2) mapX = lenght - 62.5f + distance;
                for (; i < Nspeed; ++i) distance != 0 ? (mapX -= STEP, distance -= STEP) : (distance = DISTANCE, x = 27, i = Nspeed);
            }
            else if (map[y][x - 1] == 2)
                for (; i < Nspeed; ++i) distance != 0 ? (mapX -= STEP, distance -= STEP) : (distance = DISTANCE, --x, i = Nspeed);
            else
                dir = Stop;
            break;
        case Down:
            if (map[y + 1][x] == 2)
                for (; i < Nspeed; ++i) distance != 0 ? (mapY += STEP, distance -= STEP) : (distance = DISTANCE, ++y, i = Nspeed);
            else
                dir = Stop;
            break;
        case Up:
            if (map[y - 1][x] == 2)
                for (; i < Nspeed; ++i) distance != 0 ? (mapY -= STEP, distance -= STEP) : (distance = DISTANCE, --y, i = Nspeed);
            else
                dir = Stop;
            break;
        }
    }

void Pacman::setDiration(Diration next_dir) { this->next_dir = next_dir; }

void Pacman::setDistance(float distance) { this->distance = distance; }

Diration Pacman::getDiration() const { return dir; }

float Pacman::getDistance() const { return distance; }

short Pacman::getX() const { return x; }

short Pacman::getY() const { return y; }

float Pacman::getMapX() const { return mapX; }

float Pacman::getMapY() const { return mapY; }