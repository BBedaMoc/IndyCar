#ifndef OBSTACLE_H
#define OBSTACLE_H


#include "drawable.hpp"
#include <vector>

namespace indycar {
    namespace logic {

        class Obstacle : public Drawable
        {
        public:
            /// Konstuktor domyślny.
            Obstacle();
            /// Destruktor.
            ~Obstacle();
            /// Konstruktor kopiujący.
            Obstacle(const Obstacle& el);
            /// Konstruktor.
            /**
             * @param tireDmg Obażenia zadawane oponom przez przeszkodę przy kolizji
             * @param engineDmg Obrażenia zadawane silnikowi przez przeszkodę przy kolizji.
             * @param crossable Czy przeszkodę da się "przejechać"  - opcja nie działa.
             */
            Obstacle(float tireDmg, float engineDmg, bool crossable = false);
            /// Konstruktor.
            /**
             * @param tireDmg Obażenia zadawane oponom przez przeszkodę przy kolizji
             * @param engineDmg Obrażenia zadawane silnikowi przez przeszkodę przy kolizji.
             * @param crossable Czy przeszkodę da się "przejechać"  - opcja nie działa.
             * @param path Ścieżka do tekstury.
             */
            Obstacle(float tireDmg, float engineDmg, std::string path, bool crossable = false);
            /// Ustawienie obrażeń zadawanych oponom.
            /**
             * @param tireDmg Obrażenia w p.%.
             * @see getTireDmg()
             */
            void setTireDmg(float tireDmg);
            /// Ustawienie obrażeń zadawanych silnikowi.
            /**
             * @param engineDmg Obrażenia w p.%
             * @see getEngineDmg()
             */
            void setEngineDmg(float engineDmg);
            /// Ustawia parametr przenikalności.
            /**
             * Parametr można ustawić ale nic nie robi.
             * @param crossable Czy przeszkoda jest możliwa do "przejechania".
             * @see getCross()
             */
            void setCross(bool crossable);
            /// Zwraca wartość obrażeń zadawanych oponom.
            /**
             * @return Obrażenia zadawane w p.%.
             * @see setTireDmg()
             */
            float getTireDmg();
            /// Zwraca wartość obrażeń zadawanych silnikowi.
            /**
             * @return Obrażenia w p.%.
             * @see setEngineDmg()
             */
            float getEngineDmg();
            /// Zwraca parametr przenikalności.
            /**
             * @return true - gdy przeszkoda jest przenikalna.
             * @see setCross()
             */
            bool getCross();
            /// Sprawdzanie kolizji między obiektami.
            /**
             * Sprawdza czy któryś z wierzchołków jednego obiektu nie znajduje się w drugim.
             * @param el1 Obiekt z którym sprawdzamy kolizje.
             * @return true - gdy kolizja zachodzi.
             */
            bool sprawdzKolizje(Obstacle el1);
            /// Wyznacza położenie obiektu.
            /**
             * Wyznacza nowe położenie obiektu w ukłądzie XY, oraz wyznacza punkty wierzchołków obiektu, aktualizuje rotację.
             * @param deg Przyrost obrotu.
             * @param poX Przemieszczenie po osi X.
             * @param poY Przemieszczenie po osi Y.
             */
            void wyznaczPunkty(double deg, double poX, double poY);
            /// Pierwotne zinicjalizowanie punktów wierzchołków obiektu.
            /**
             * Ustala położenie, a akże na podstawie współrzędnych środka obrotu i wymiarów obiektu inicjalizuje jego wierzchołki.
             * @param pos Zadane położenie.
             */
            void inicjalizujPunkty(Point pos);
            /// Wierzhołki obiektu.
            std::vector <Point> punkty;
        protected:
        private:
            float tireDmg;
            float engineDmg;
            bool crossable;
            float maxXY(Obstacle el, bool czyX);
            float minXY(Obstacle el, bool czyX);

        };

    }
}

#endif // OBSTACLE_H
