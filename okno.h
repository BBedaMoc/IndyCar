#ifndef OKNO_H
#define OKNO_H


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "obstacle.hpp"
#include "drawable.hpp"
#include "track.hpp"
#include "car.hpp"
#include "gra.h"
#include "boot.h"
#include "gracz.h"


class Okno
{
public:

    Okno();
    Okno(std::string path);
    ~Okno();    
    void grajG();

private:
    sf::RenderWindow *window;
    Gra* game;
    std::vector <std::vector <sf::RectangleShape*> > elTor;
    std::vector <std::vector <sf::Texture> > elTorTx;
    std::vector <sf::RectangleShape*> cars;
    std::vector <std::vector <sf::Texture> > carsTx;
    std::vector <sf::Font*> font;
    std::vector <sf::Text*> txt;
    std::vector <sf::RectangleShape*> wsk;
    std::vector <sf::ConvexShape*> wsk2;
    int aktObserUcz;
    void rysujElemToru();
    void inicjalizujElemToru();
    void aktPolElOkna();
    std::string float2string(float lb,int prec);
    void piszTekst();
    void wskaznik();
    void rysPodp();
    std::vector <sf::RectangleShape> zakret;
    void zmienObser(int wyb);



};

#endif // OKNO_H
