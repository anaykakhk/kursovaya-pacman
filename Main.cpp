#include "Ghost.h"
#include <windows.h>
#include <string>
#define DISTANCE 21.5f                       // расстояние до следующей координаты массива map

sf::Font font;                               // шрифт
sf::Text level_text("", font, 30), score_text("", font, 30), lifes_text("", font, 30), fps_text("", font, 20), Bstart("START", font, 70), Bcontrol("CONTROL", font, 70), Bexit("EXIT", font, 70);
sf::Texture TPacman_0, TPacman_1, TPacman_2, TPacman_3, TDeathP_0, TDeathP_1, TDeathP_2, TDeathP_3, TDeathP_4, TDeathP_5, TDeathP_6, TDeathP_7, TDeathP_8,
TGhostN_0, TGhostN_1, TGhostS_0, TGhostS_1, TGhostE,
TFruit_0, TFruit_1, TFruit_2, TFruit_3, TFruit_4, TFruit_5, TFruit_6,
TMap, TPoint, TControl, TEscape, TSpace, TMenu,
TEnergy_0, TEnergy_1, TEnergy_2, TEnergy_3, TEnergy_4;
sf::Sprite SMap, SPoint, SFruit, SPacman, SMenu, SMenuP;

unsigned int score;                          // количество очков
unsigned int lifes_vertex;                   // последнее значение score, за которое добавляли жизнь
unsigned int lenght;                         // длина приложения
unsigned int width;                          // ширина приложения
short fps_value;                             // количество кадров в секунду
short energy_count;                          // количество энергетиков на карте
short time_passed;                           // значение времени в секундах для анимации
short GRedX, GRedY;                          // координата красного приведения (необходимо для логики синего приведения)
signed char lifes;                           // кол-во жизней
signed char level;                           // текущий уровень
signed char lifes_add;                       // счетчик для добавления жизней
signed char number_fruit;                    // номер текущего фрукта
signed char killed_count;                    // кол-во съеденых пакманом подряд приведений
signed char second_pause;                    // кол-во секунд, при которых игра находится остановленной
signed char second_fruit;                    // кол-во секунд, при которых фрукт виден, может быть взят
signed char second_scared;                   // кол-во секунд, при которых приведения могут быть съедены
signed char second_deathP;                   // кол-во секунд, при которых происходит анимация смерти пакмана
bool isPause;                                // пауза игры
bool isEscape;                               // выход через меню
bool gameOver;                               // переменная, перезапускающая игру
bool deathPacman;                            // переменная отвечающая за анимацию смерти пакмана
Diration Plast_dir;                          // последнее направление пакмана
short map[29][28] =                          // карта
{
    0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0,
    0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0,
    0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0,
    0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0,
    0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0,
    0, 2, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 2, 0,
    0, 2, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 2, 0,
    0, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0,
    0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 1, 1, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 2, 2, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0,
    0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0,
    0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0,
    0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0,
    0, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 0,
    0, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0,
    0, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0,
    0, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0,
    0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0,
    0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0,
    0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0
};
short energy_def[29][28] =                   // расположение энергетиков по умолчанию
{
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
    0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0,
    0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0,
    0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0,
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
    0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0,
    0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0,
    0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
    0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0,
    0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0,
    0, 2, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 2, 0,
    0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0,
    0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0,
    0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
    0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0
};
short energy[29][28];                        // текущее расположение энергетиков(точек)

Pacman pacman;                               // ПАКМАН (объект)
std::vector<Ghost> ghosts;                   // ПРИВЕДЕНИЯ (объекты)
std::vector<std::vector<bool>> dec_arr(29);  // список раскрашенных клетот карты (для алгоритма Дейкстры)
std::vector<std::vector<short>> dis_arr(29);  // класс поля (для алгоритма Дейкстры)

inline void Disposable()
{// изначальное заполнение объектов (одноразовая)
    font.loadFromFile("data/Times_New_Roman.ttf");
    level_text.setPosition(300.f, 390.f), score_text.setPosition(80.f, 715.f), lifes_text.setPosition(430.f, 715.f); fps_text.setPosition(350.f, 0.f);
    Bstart.setPosition(240.f, 300.f), Bcontrol.setPosition(185.f, 400.f), Bexit.setPosition(260.f, 500.f), SMenu.setPosition(52.5f, 20.f), SMenuP.setPosition(-30.f, -30.f);
    sf::Image Ipacman_0, Ipacman_1, Ipacman_2, Ipacman_3,
        IghostN_0, IghostN_1, IghostS_0, IghostS_1, IghostE,
        Ifruit_0, Ifruit_1, Ifruit_2, Ifruit_3, Ifruit_4, Ifruit_5, Ifruit_6,
        Ienergy_0, Ienergy_1, Ienergy_2, Ienergy_3, Ienergy_4,
        IdeathP_0, IdeathP_1, IdeathP_2, IdeathP_3, IdeathP_4, IdeathP_5, IdeathP_6, IdeathP_7, IdeathP_8,
        Imap, Ipoint, Icontrol, Iescape, Ispace, Imenu;
    Ipacman_0.loadFromFile("data/images/Pacman0.png"), Ipacman_1.loadFromFile("data/images/Pacman1.png"),
        Ipacman_2.loadFromFile("data/images/Pacman2.png"), Ipacman_3.loadFromFile("data/images/Pacman3.png"),
        IghostN_0.loadFromFile("data/images/GhostN0.png"), IghostN_1.loadFromFile("data/images/GhostN1.png"),
        IghostS_0.loadFromFile("data/images/GhostS0.png"), IghostS_1.loadFromFile("data/images/GhostS1.png"),
        IghostE.loadFromFile("data/images/GhostE.png"), Ifruit_0.loadFromFile("data/images/Fruit0.png"),
        Ifruit_1.loadFromFile("data/images/Fruit1.png"), Ifruit_2.loadFromFile("data/images/Fruit2.png"),
        Ifruit_3.loadFromFile("data/images/Fruit3.png"), Ifruit_4.loadFromFile("data/images/Fruit4.png"),
        Ifruit_5.loadFromFile("data/images/Fruit5.png"), Ifruit_6.loadFromFile("data/images/Fruit6.png"),
        Ienergy_0.loadFromFile("data/images/Energy0.png"), Ienergy_1.loadFromFile("data/images/Energy1.png"),
        Ienergy_2.loadFromFile("data/images/Energy2.png"), Ienergy_3.loadFromFile("data/images/Energy3.png"), Ienergy_4.loadFromFile("data/images/Energy4.png"),
        IdeathP_0.loadFromFile("data/images/Death0.png"), IdeathP_1.loadFromFile("data/images/Death1.png"),
        IdeathP_2.loadFromFile("data/images/Death2.png"), IdeathP_3.loadFromFile("data/images/Death3.png"),
        IdeathP_4.loadFromFile("data/images/Death4.png"), IdeathP_5.loadFromFile("data/images/Death5.png"),
        IdeathP_6.loadFromFile("data/images/Death6.png"), IdeathP_7.loadFromFile("data/images/Death7.png"), IdeathP_8.loadFromFile("data/images/Death8.png"),
        Imap.loadFromFile("data/images/Map.png"), Ipoint.loadFromFile("data/images/Point.png"),
        Imenu.loadFromFile("data/images/Menu.png"), Icontrol.loadFromFile("data/images/Control.png"),
        Iescape.loadFromFile("data/images/Escape.png"), Ispace.loadFromFile("data/images/Space.png"),
        Ipacman_0.createMaskFromColor(sf::Color::Black), Ipacman_1.createMaskFromColor(sf::Color::Black),
        Ipacman_2.createMaskFromColor(sf::Color::Black), Ipacman_3.createMaskFromColor(sf::Color::Black),
        IghostN_0.createMaskFromColor(sf::Color::Black), IghostN_1.createMaskFromColor(sf::Color::Black),
        IghostS_0.createMaskFromColor(sf::Color::Black), IghostS_1.createMaskFromColor(sf::Color::Black),
        IghostE.createMaskFromColor(sf::Color::Black), Ifruit_0.createMaskFromColor(sf::Color::Black),
        Ifruit_1.createMaskFromColor(sf::Color::Black), Ifruit_2.createMaskFromColor(sf::Color::Black),
        Ifruit_3.createMaskFromColor(sf::Color::Black), Ifruit_4.createMaskFromColor(sf::Color::Black),
        Ifruit_5.createMaskFromColor(sf::Color::Black), Ifruit_6.createMaskFromColor(sf::Color::Black),
        Ienergy_0.createMaskFromColor(sf::Color::Black), Ienergy_1.createMaskFromColor(sf::Color::Black),
        Ienergy_2.createMaskFromColor(sf::Color::Black), Ienergy_3.createMaskFromColor(sf::Color::Black),
        Ienergy_4.createMaskFromColor(sf::Color::Black), Ipoint.createMaskFromColor(sf::Color::Black),
        IdeathP_0.createMaskFromColor(sf::Color::Black), IdeathP_1.createMaskFromColor(sf::Color::Black),
        IdeathP_2.createMaskFromColor(sf::Color::Black), IdeathP_3.createMaskFromColor(sf::Color::Black),
        IdeathP_4.createMaskFromColor(sf::Color::Black), IdeathP_5.createMaskFromColor(sf::Color::Black),
        IdeathP_6.createMaskFromColor(sf::Color::Black), IdeathP_7.createMaskFromColor(sf::Color::Black), IdeathP_8.createMaskFromColor(sf::Color::Black),
        Icontrol.createMaskFromColor(sf::Color::Yellow), Iescape.createMaskFromColor(sf::Color::Yellow), Imenu.createMaskFromColor(sf::Color::Black);        TPacman_0.loadFromImage(Ipacman_0), TPacman_1.loadFromImage(Ipacman_1),
        TPacman_2.loadFromImage(Ipacman_2), TPacman_3.loadFromImage(Ipacman_3),
        TGhostN_0.loadFromImage(IghostN_0), TGhostN_1.loadFromImage(IghostN_1),
        TGhostS_0.loadFromImage(IghostS_0), TGhostS_1.loadFromImage(IghostS_1),
        TGhostE.loadFromImage(IghostE), TFruit_0.loadFromImage(Ifruit_0),
        TFruit_1.loadFromImage(Ifruit_1), TFruit_2.loadFromImage(Ifruit_2),
        TFruit_3.loadFromImage(Ifruit_3), TFruit_4.loadFromImage(Ifruit_4),
        TFruit_5.loadFromImage(Ifruit_5), TFruit_6.loadFromImage(Ifruit_6),
        TEnergy_0.loadFromImage(Ienergy_0), TEnergy_1.loadFromImage(Ienergy_1),
        TEnergy_2.loadFromImage(Ienergy_2), TEnergy_3.loadFromImage(Ienergy_3), TEnergy_4.loadFromImage(Ienergy_4),
        TDeathP_0.loadFromImage(IdeathP_0), TDeathP_1.loadFromImage(IdeathP_1),
        TDeathP_2.loadFromImage(IdeathP_2), TDeathP_3.loadFromImage(IdeathP_3),
        TDeathP_4.loadFromImage(IdeathP_4), TDeathP_5.loadFromImage(IdeathP_5),
        TDeathP_6.loadFromImage(IdeathP_6), TDeathP_7.loadFromImage(IdeathP_7), TDeathP_8.loadFromImage(IdeathP_8),
        TControl.loadFromImage(Icontrol), TEscape.loadFromImage(Iescape),
        TSpace.loadFromImage(Ispace), TMap.loadFromImage(Imap),
        TPoint.loadFromImage(Ipoint), TMenu.loadFromImage(Imenu);
    TPacman_0.setSmooth(true), TPacman_1.setSmooth(true),
        TPacman_2.setSmooth(true), TPacman_3.setSmooth(true),
        TGhostN_0.setSmooth(true), TGhostN_1.setSmooth(true),
        TGhostS_0.setSmooth(true), TGhostN_1.setSmooth(true),
        TGhostE.setSmooth(true), TFruit_0.setSmooth(true),
        TFruit_1.setSmooth(true), TFruit_2.setSmooth(true),
        TFruit_3.setSmooth(true), TFruit_4.setSmooth(true),
        TFruit_5.setSmooth(true), TFruit_6.setSmooth(true),
        TEnergy_0.setSmooth(true), TEnergy_1.setSmooth(true),
        TEnergy_2.setSmooth(true), TEnergy_3.setSmooth(true),
        TEnergy_4.setSmooth(true), TPoint.setSmooth(true);
    TDeathP_0.setSmooth(true), TDeathP_1.setSmooth(true),
        TDeathP_2.setSmooth(true), TDeathP_3.setSmooth(true),
        TDeathP_4.setSmooth(true), TDeathP_5.setSmooth(true),
        TDeathP_6.setSmooth(true), TDeathP_7.setSmooth(true), TDeathP_8.setSmooth(true),
        TControl.setSmooth(true), TEscape.setSmooth(true),
        TSpace.setSmooth(true), TMenu.setSmooth(true),
        SMap.setTexture(TMap), SPoint.setTexture(TPoint), SMenu.setTexture(TMenu), SMenuP.setTexture(TPacman_0);
    SFruit.setOrigin(15, 15), SPoint.setOrigin(15, 15);
    isPause = isEscape = false, level = char(-1), second_fruit = second_scared = killed_count = char(0), lifes_add = lifes = char(3), score = lifes_vertex = 0, fps_value = 60, time_passed = 0;
    for (short i = 0; i < 29; ++i)
        for (short j = 0; j < 28; ++j)
            map[i][j] > 0 ? (dec_arr[i].push_back(false), dis_arr[i].push_back(100)) : (dec_arr[i].push_back(true), dis_arr[i].push_back(-1));
}
inline void Setup(bool isNewGame, bool isBegin = true)
{// новая игра
    short i = 0, j = 0;
    time_passed = killed_count = second_scared = second_deathP = second_fruit = char(0), second_pause = isBegin ? char(2) : char(0), isPause = deathPacman = gameOver = false, GRedX = 12, GRedY = 10, number_fruit = char((level + 2) > 21 ? rand() % 7 : short(level + 1) % 7);
    pacman = Pacman(14, 22); SPacman.setTextureRect(sf::IntRect(0, 0, 30, 30)), SPacman.setRotation(0.f);
    ghosts.clear();
    ghosts.push_back(Ghost(pacman, Red, 12, 10)); ghosts.push_back(Ghost(pacman, Blue, 15, 10));
    ghosts.push_back(Ghost(pacman, Orange, 15, 13)); ghosts.push_back(Ghost(pacman, Pink, 12, 13));
    for (; i < 4; ++i) ghosts[i].setDir_Vec(Find_Path(dec_arr, dis_arr, ghosts[i].getX(), ghosts[i].getY(), pacman.getX(), pacman.getY(), Stop));
    if (isNewGame)
    {
        energy_count = 244, ++level;
        for (i = 0; i < 4; ++i) ghosts[i].setSpeed((level + 1) % 7 == 0 ? (level + 1) / 7 > 3 ? 2.25f : ghosts[i].getSpeed() + 0.25f : ghosts[i].getSpeed());
        for (i = 0; i < 29; ++i) for (short j = 0; j < 28; ++j) energy[i][j] = energy_def[i][j];
        switch (number_fruit)
        {
            case char(0) : SFruit.setTexture(TFruit_0); break;
                case char(1) : SFruit.setTexture(TFruit_1); break;
                    case char(2) : SFruit.setTexture(TFruit_2); break;
                        case char(3) : SFruit.setTexture(TFruit_3); break;
                            case char(4) : SFruit.setTexture(TFruit_4); break;
                                case char(5) : SFruit.setTexture(TFruit_5); break;
                                    case char(6) : SFruit.setTexture(TFruit_6); break;
        }
    }
}
inline void Draw(sf::RenderWindow& win)
{// рисовка
    short i = 0;
    sf::Sprite Senergy, Spacman(TPacman_0); Spacman.setPosition(390, 720);
    if (time_passed <= 100 || time_passed >= 900) Senergy.setTexture(TEnergy_0);
    else if ((time_passed >= 100 && time_passed <= 200) || (time_passed >= 800 && time_passed <= 900)) Senergy.setTexture(TEnergy_1);
    else if ((time_passed >= 200 && time_passed <= 300) || (time_passed >= 700 && time_passed <= 800)) Senergy.setTexture(TEnergy_2);
    else if ((time_passed >= 300 && time_passed <= 400) || (time_passed >= 600 && time_passed <= 700)) Senergy.setTexture(TEnergy_3);
    else if ((time_passed >= 400 && time_passed <= 500) || (time_passed >= 500 && time_passed <= 600)) Senergy.setTexture(TEnergy_4);
    SFruit.setPosition(585, 735), Senergy.setOrigin(15, 15);
    score_text.setString("Score " + std::to_string(score)),
        lifes_text.setString("x " + std::to_string(lifes)),
        fps_text.setString("FPS " + std::to_string(fps_value));
    level_text.setString("LEVEL " + std::to_string(level));
    win.draw(SMap), second_pause != 4 ? win.draw(level_text) : void(), win.draw(score_text), win.draw(Spacman), win.draw(lifes_text), win.draw(fps_text), win.draw(SFruit);
    if (second_fruit != char(0)) { SFruit.setPosition(352.25f, 408.f); win.draw(SFruit); }
    for (; i < 812; ++i)
    {
        if (energy[i / 28][i % 28] > 0)
        {
            SPoint.setPosition((i % 28) * DISTANCE + 62.5f, (i / 28) * DISTANCE + 64.f),
                Senergy.setPosition((i % 28) * DISTANCE + 62.5f, (i / 28) * DISTANCE + 64.f);
            energy[i / 28][i % 28] == 1 ? win.draw(SPoint) : win.draw(Senergy);
        }
    }
    pacman.draw(win, Spacman, TPacman_0, TPacman_1, TPacman_2, TPacman_3, TDeathP_0, TDeathP_1, TDeathP_2, TDeathP_3, TDeathP_4, TDeathP_5, TDeathP_6, TDeathP_7, time_passed, second_deathP, lifes, deathPacman, gameOver, isPause);
    for (i = 0; i < 4; ++i) ghosts[i].draw(win, dec_arr, dis_arr, TGhostE, TGhostN_0, TGhostN_1, TGhostS_0, TGhostS_1, time_passed, second_scared, killed_count);
}
inline void Control(sf::RenderWindow& win)
{
    sf::Sprite SControl(TControl), SEscape(TEscape), SSpace(TSpace);
    sf::Text Bback("BACK", font, 70), control("CONTROL", font, 30), escape("OPEN THE MENU", font, 30), space("PAUSE", font, 30);
    Bback.setPosition(250.f, 600.f), control.setPosition(280, 100), escape.setPosition(230, 300), space.setPosition(300, 450), SControl.setPosition(180, 150), SEscape.setPosition(320, 350), SSpace.setPosition(200, 500);
    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape) { SMenuP.setPosition(-30.f, -30.f); return; }
                if (event.key.code == sf::Keyboard::Enter)
                {
                    if (Bback.getFillColor() == sf::Color::Yellow) { SMenuP.setPosition(-30.f, -30.f); return; }
                }
            }
            if (sf::IntRect(250, 600, 200, 70).contains(sf::Mouse::getPosition(win))) Bback.getFillColor() != sf::Color::Yellow ? SMenuP.setPosition(210.f, 630.f) : void(), Bback.setFillColor(sf::Color::Yellow);
            else SMenuP.setPosition(-30.f, -30.f), Bback.setFillColor(sf::Color::White);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (Bback.getFillColor() == sf::Color::Yellow) { SMenuP.setPosition(-30.f, -30.f); return; }
            }
        }
        win.clear();
        win.draw(SMenuP);
        win.draw(control);
        win.draw(SControl);
        win.draw(escape);
        win.draw(SEscape);
        win.draw(space);
        win.draw(SSpace);
        win.draw(Bback);
        win.display();
    }
}
inline void SemiMenu(sf::RenderWindow& win)
{
    sf::Text Bcontinue("CONTINUE", font, 70), Bmenu("MENU", font, 70);
    Bcontinue.setPosition(170.f, 300.f), Bmenu.setPosition(250.f, 500.f);
    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape) { SMenuP.setPosition(-30.f, -30.f); return; }
                if (event.key.code == sf::Keyboard::Enter)
                {
                    if (Bcontinue.getFillColor() == sf::Color::Yellow) { SMenuP.setPosition(-30.f, -30.f); return; }
                    if (Bcontrol.getFillColor() == sf::Color::Yellow)  SMenuP.setPosition(-30.f, -30.f), Control(win);
                    if (Bmenu.getFillColor() == sf::Color::Yellow) { isEscape = true;  SMenuP.setPosition(-30.f, -30.f); return; }
                }
            }
            if (sf::IntRect(170, 300, 355, 70).contains(sf::Mouse::getPosition(win))) Bcontinue.getFillColor() != sf::Color::Yellow ? SMenuP.setPosition(130.f, 330.f) : void(), Bcontinue.setFillColor(sf::Color::Yellow), Bcontrol.setFillColor(sf::Color::White), Bmenu.setFillColor(sf::Color::White);
            else if (sf::IntRect(185, 400, 330, 70).contains(sf::Mouse::getPosition(win))) Bcontrol.getFillColor() != sf::Color::Yellow ? SMenuP.setPosition(145.f, 430.f) : void(), Bcontinue.setFillColor(sf::Color::White), Bcontrol.setFillColor(sf::Color::Yellow), Bmenu.setFillColor(sf::Color::White);
            else if (sf::IntRect(250, 500, 160, 70).contains(sf::Mouse::getPosition(win))) Bmenu.getFillColor() != sf::Color::Yellow ? SMenuP.setPosition(210.f, 530.f) : void(), Bcontinue.setFillColor(sf::Color::White), Bcontrol.setFillColor(sf::Color::White), Bmenu.setFillColor(sf::Color::Yellow);
            else SMenuP.setPosition(-30.f, -30.f), Bcontinue.setFillColor(sf::Color::White), Bcontrol.setFillColor(sf::Color::White), Bmenu.setFillColor(sf::Color::White);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (Bcontinue.getFillColor() == sf::Color::Yellow) { SMenuP.setPosition(-30.f, -30.f); return; }
                if (Bcontrol.getFillColor() == sf::Color::Yellow)  SMenuP.setPosition(-30.f, -30.f), Control(win);
                if (Bmenu.getFillColor() == sf::Color::Yellow) { isEscape = true;  SMenuP.setPosition(-30.f, -30.f); return; }
            }
        }
        win.clear();
        win.draw(SMenu);
        win.draw(SMenuP);
        win.draw(Bcontinue);
        win.draw(Bcontrol);
        win.draw(Bmenu);
        win.display();
    }
}
inline void Play(sf::RenderWindow& win)
{// игровой процесс
    sf::Clock clock; Setup(true, false);
    while (!isEscape && win.isOpen())
    {
        if (gameOver && deathPacman) isPause = true, time_passed = 0, gameOver = false;
        else if (gameOver && energy_count == 0) Setup(true);
        else if (gameOver) break;
        clock.restart();
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) pacman.setDiration(Up);
                if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) pacman.setDiration(Down);
                if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) pacman.setDiration(Left);
                if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) pacman.setDiration(Right);
                if (event.key.code == sf::Keyboard::Escape && second_pause == 4 && !deathPacman) SemiMenu(win);
                if (event.key.code == sf::Keyboard::Space && second_pause == 4 && !deathPacman) isPause = !isPause;
            }
        }
        win.clear();
        if (!isPause && second_pause == 4) 
        { 
            pacman.move(SFruit, Plast_dir, map, energy, lenght, score, lifes_vertex, lifes_add, energy_count, second_fruit, lifes, number_fruit, second_scared, level, gameOver); 
            for (short i = 0; i < 4; ++i) ghosts[i].move(pacman, dec_arr, dis_arr, map, score, lenght, killed_count, second_scared, level, GRedX, GRedY, Plast_dir, gameOver, deathPacman); }
        Draw(win);
        if (!isEscape) win.display();
        fps_value = short(1 / (clock.getElapsedTime().asSeconds()));
        time_passed > 1000 ? (time_passed = 0, (second_pause == 4 ? 0 : ++second_pause), (deathPacman ? ++second_deathP : 0), (second_scared == 0 ? 0 : --second_scared), second_fruit == 0 ? 0 : --second_fruit) : time_passed += clock.getElapsedTime().asMilliseconds();
    }
    score = 0, level = char(-1), second_pause = char(0), lifes = lifes_add = char(3);
}
inline void Menu()
{
    sf::Image icon; icon.loadFromFile("data/images/Pacman0.png"); icon.createMaskFromColor(sf::Color::Black);
    sf::RenderWindow window(sf::VideoMode(705, 760), "Pacman", sf::Style::None);
    window.setIcon(30, 30, icon.getPixelsPtr());
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    Disposable();
    lenght = window.getSize().x, width = window.getSize().y;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape) window.close();
                if (event.key.code == sf::Keyboard::Enter)
                {
                    if (Bstart.getFillColor() == sf::Color::Yellow) isEscape = false, Bstart.setFillColor(sf::Color::Yellow), Play(window);
                    if (Bcontrol.getFillColor() == sf::Color::Yellow) Bcontrol.setFillColor(sf::Color::Yellow), Control(window);
                    if (Bexit.getFillColor() == sf::Color::Yellow) window.close();
                }
            }
            if (sf::IntRect(250, 300, 200, 70).contains(sf::Mouse::getPosition(window))) Bstart.getFillColor() != sf::Color::Yellow ? SMenuP.setPosition(200.f, 330.f) : void(), Bstart.setFillColor(sf::Color::Yellow), Bcontrol.setFillColor(sf::Color::White), Bexit.setFillColor(sf::Color::White);
            else if (sf::IntRect(185, 400, 330, 70).contains(sf::Mouse::getPosition(window))) Bcontrol.getFillColor() != sf::Color::Yellow ? SMenuP.setPosition(145.f, 430.f) : void(), Bstart.setFillColor(sf::Color::White), Bcontrol.setFillColor(sf::Color::Yellow), Bexit.setFillColor(sf::Color::White);
            else if (sf::IntRect(260, 500, 160, 70).contains(sf::Mouse::getPosition(window))) Bexit.getFillColor() != sf::Color::Yellow ? SMenuP.setPosition(220.f, 530.f) : void(), Bstart.setFillColor(sf::Color::White), Bcontrol.setFillColor(sf::Color::White), Bexit.setFillColor(sf::Color::Yellow);
            else SMenuP.setPosition(-30.f, -30.f), Bstart.setFillColor(sf::Color::White), Bcontrol.setFillColor(sf::Color::White), Bexit.setFillColor(sf::Color::White);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (Bstart.getFillColor() == sf::Color::Yellow) isEscape = false, Bstart.setFillColor(sf::Color::Yellow), Play(window);
                if (Bcontrol.getFillColor() == sf::Color::Yellow)  SMenuP.setPosition(-30.f, -30.f), Bcontrol.setFillColor(sf::Color::Yellow), Control(window);
                if (Bexit.getFillColor() == sf::Color::Yellow) window.close();
            }
        }
        window.clear();
        window.draw(SMenu);
        window.draw(SMenuP);
        window.draw(Bstart);
        window.draw(Bcontrol);
        window.draw(Bexit);
        window.display();
    }
}

int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    Menu();
    return 0; sizeof(Place), sizeof(Pacman), sizeof(Ghost);
}
