#ifndef PLAYER_H
#define PLAYER_H

#include "participant.hpp"

namespace indycar {
    namespace logic {

        class Player : public Participant
        {
        public:
            /// Konstruktor domyślny.
            Player();
            /// Konstruktor kopiujący.
            Player(const Player& el);
            /// Konstruktor.
            /**
             * @param lap Okrążenia do przejechania.
             */
            Player(int lap);
            ~Player();
            /// Metoda symulująca fizykę jazdy pojazdu.
            /**
             * Odpowiaa za dynamikę poruszania się pojazdu,
             * Uwzględnia prędkość maksymalną, aktualnie włączony bieg, przyśpieszenie, szybkość hamowania, modyfikatory.
             * Parametry l, p, a, b, su i sd mogą np. pochodzić z klawiatury jako stany wciśnięcia danedo wybranego klawisza.
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
            Point jedz(bool l, bool p, bool a, bool b, bool su, bool sd, float& vg, bool flaga, float& ang);
        };

    }
}

#endif // PLAYER_H
