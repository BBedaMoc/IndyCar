#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
//#include "indycar/logic/obstacle.hpp"
//#include "indycar/logic/drawable.hpp"
//#include "indycar/logic/track.hpp"
//#include "indycar/logic/car.hpp"
#include "indycar/logic/game.hpp"
//#include "indycar/logic/bot.hpp"
//#include "indycar/logic/player.hpp"

namespace indycar {
    namespace gui {

        class GameWindow
        {
        public:

            GameWindow();
            GameWindow(std::string path);
            ~GameWindow();
            void grajG();

        private:
            sf::RenderWindow* window;
            logic::Game* game;
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
            std::string float2string(float lb, int prec);
            void piszTekst();
            void wskaznik();
            void rysPodp();
            std::vector <sf::RectangleShape> zakret;
            void zmienObser(int wyb);

        };
    }
}

#endif // GAMEWINDOW_H
