#ifndef BOT_H
#define BOT_H

#include "participant.hpp"

namespace indycar {
    namespace logic {

        class Bot : public Participant
        {
        public:
            /// Konstuktor domyślny.
            Bot();
            /// Konstuktor kopiujący.
            Bot(const Bot& el);
            /// Konstuktor.
            /**
             * @param lap Liczba okrażeń do przejeczania.
             */
            Bot(int lap);
            /// Destruktor
            ~Bot();
            /// Metoda symulująca fizykę jazdy pojazdu.
            /**
             * Odpowiaa za dynamikę poruszania się pojazdu,
             * Uwzględnia prędkość maksymalną, aktualnie włączony bieg, przyśpieszenie, szybkość hamowania, modyfikatory.
             * Parametry l, p, a, b, su i sd nie są aktywne.
             * @param l Czy skręt w lewo.
             * @param p Czy skręt w prawo.
             * @param a Czy przyśpieszanie.
             * @param b Czy hamowanie.
             * @param su Czy bieg do góry.
             * @param sd Czy bieg w dół.
             * @param vg Prędkość obserwowanego gracza.
             * @param flaga Czy to wywołanie odnośi się do obserwowanego gracza.
             * @param ang Przyrost kąta obrotu w tej turze.
             * @return  Przemieszczenie środka pojazdu w układzie XY.
             */
            virtual Point jedz(bool l, bool p, bool a, bool b, bool su, bool sd, float& vg, bool flaga, float& ang);
            void setInt(int intel);
            void setPopPol(Point a);
            void setPopPol2(Point a);
            /// Zadane polożenie jakie ma uzyskać pojazd.
            /**
             * Zaimplementowana logika sprubuje doprowadzić pojazd do tego położenia, omijając przy tym przeszkody i innych uczestników.
             */
            Point zadPol;

        private:
            int inteligencja;
            void decydujGdzieIJak(bool& l, bool& p, bool& a, bool& b, bool& su, bool& sd);
            Point popPol;
            Point popPol2;

        };

    }
}

#endif // BOT_H
