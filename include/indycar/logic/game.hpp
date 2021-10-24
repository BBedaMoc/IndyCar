#ifndef GAME_H
#define GAME_H

#include "car.hpp"
#include "track.hpp"
#include "bot.hpp"
#include "player.hpp"

namespace indycar {
    namespace logic {

        class Game
        {

        public:
            /// Konstruktor domyślny.
            Game();
            /// Destruktor domyślny.
            ~Game();
            /// Konstruktor.
            /**
             * Tworzy nowy obiekt klasy Gra i inicjalizuje elementy na podstawie wartości zamieszczonych w plikach danych i konfiguracyjnych.
             * @param param Ścieżka dostępu do pliku config.cfg
             */
            Game(std::string param);
            /// Dodawanie uczestnika do gry.
            /**
             * @param pom Uczestnik którech chcemy dodać.
             */
            void dodaUczestnika(Participant* pom);
            /// Zwraca liczbę graczy.
            /**
             * Parametr ustawiany w pliku config.cfg "licz_graczy" i tylko w ten sposób można go zmodyfikować.
             * @return Liczba graczy uczestniczących w wyścigu.
             */
            int getLiczbaGraczy();
            /// Zwraca wartość fps.
            /**
             * Parametr ustawiany w pliku config.cfg "frame_limit" i tylko w ten sposób można go zmodyfikować.
             * @return Zadana wartość fps.
             */
            int getFrameRate();
            /// Zwraca rozdzielczość ekranu, szerokość.
            /**
             * Parametr ustawiany w pliku config.cfg "resolution_x" i tylko w ten sposób można go zmodyfikować.
             * Nie zaleca się zmieniać wartości domyślnej 960.
             * @return Rozdzielczość po osi X.
             */
            int getResX();
            /// Zwraca rozdzielczość ekranu, wysokość.
            /**
             * Parametr ustawiany w pliku config.cfg "resolution_y" i tylko w ten sposób można go zmodyfikować.
             * Nie zaleca się zmieniać wartości domyślnej 540.
             * @return Rozdzielczość po osi Y.
             */
            int getResY();
            /// Zwraca zbiór wszystkich uczestników gry.
            /**
             * @return Vector wskażników do uczestników.
             */
            std::vector <Participant*> getUczestnicy();
            /// Zwraca zbiór wszystkich losowych przeszkód obecnych na torze.
            /**
             * @return Vector wskażników do losowych przeszkód.
             */
            std::vector <Obstacle*> getLosowePrz();
            /// Zwraca zbiór wszystkich referencyjnych aut.
            /**
             * Tworzone na podstawie pliku auta.cfg
             * @return Vector wskażników do referencyjnych aut.
             */
            std::vector <Car*> getRefAuta();
            /// Zwraca zbiór wszystkich referencyjnych tras.
            /**
             * Tworzone na podstawie pliku trasy.cfg
             * @return Vector wskażników do referencyjnych tras.
             */
            std::vector <Track*> getRefTrasy();
            /// Zwraca wskaźnik do aktualnie wybranej trasy.
            /**
             * Parametr ustawiany w pliku config.cfg "default_tor" i tylko w ten sposób można go zmodyfikować.
             * Należy podać numer trasy takiej kolejności jak są definiowane w pliku trasy.cfg, zaczynając numerację od 0.
             * @return Wskaźnik do wybranej trasy.
             */
            Track* getTrasa();
            /// Utworzenie i inicjalizacja obiektów należących do obiektu Gra.
            /**
             * Na podstawie danych załadowanych wcześniej przez konstruktor.
             * @see Gra(std::string param)
             */
            void nowaGra();
            /// Sprawdzenie szansy pojawienia się losowej przeszkoda.
            /**
             * Prawdopodobieństwo pojawienia się eventu dla danego uczestnika w danej klatce wynosi: x/10000, gdzie x to parametr "eventPr" znajdujący się w pliku config.cfg
             * Prawdopodobieństwa wystąpienia danego rodzaju eventu gdy już wiadomo że event sam w sobie się pojawia zawarte jest w pliku trasy.cfg, zesaw 5 liczb tuż pod ścieżkami dostępu do tekstur toru.
             * Domyślnie: 35 10 15 25 15
             * @param dr Wskaźnik do uczestnika dla którego przeprowadzamy próbę.
             */
            void czyDacEvent(Participant* dr);
            /// Aktualizacja położenia wszystnich uczestników względem toru.
            void aktPozycjeWT();
            /// Wyznacza pozycje uczestników względem siebie nawzajem.
            void aktPozycjeWG();
            /// Obsługa kolizji.
            /**
             * Wykrywanie, aktualizowanie stanu oraz obsługa zniszczeń przy kolizjach.
             * @param wl Flaga zezwalająca, true - kolizje włączone, false - wyłączone.
             */
            void kolizje(bool wl);
            /// Aktualizuje położenie losowych eventów.
            /**
             * Wywoływany tylko dla gracza obserwowanego.
             * @param angle Przyrost kąta obrotu.
             * @param poX Przemieszczenie wzdłuż osi X.
             * @param poY Przemieszczenie wzdłuż osi Y.
             * @param srObr Środek obrotu.
             */
            void aktPosEv(float angle, float poX, float poY, Point srObr);
            /// Zwraca numer tekstury lowowej przeszkoda.
            /**
             * Pomaga zidentyfikować obiekt.
             * @param el Wskaźnik do przeszkody.
             * @return Numer przeszkody.
             */
            int ktoraTxEv(Obstacle* el);
            /// Czyśi vector Przeszkód.
            void usunVektor(std::vector <Obstacle*>& el);
            /// Obsłóga gry.
            /**
             * Wywoływana przy każdej pętli programu.
             * Przed pierwszym użyciem należy wywołać konstruktor z ścieżką do pliku config oraz metodę nowaGra().
             * @param u Setrowanie zewnętrzne - przyśpieszenie.
             * @param d Setrowanie zewnętrzne - hamowanie.
             * @param l Setrowanie zewnętrzne - skręt w lewo.
             * @param p Setrowanie zewnętrzne - skręt w prawo.
             * @param su Setrowanie zewnętrzne - bieg do góry.
             * @param sd Setrowanie zewnętrzne - bieg w dół.
             * @param aktObserUcz Licząc od końca, numer uczestnika który jest obserwowany.
             */
            void krokPodstawowy(bool u, bool d, bool l, bool p, bool su, bool sd, int aktObserUcz);
            /// Zwraca informację czy w grze występuje gracz sterowany zewnętrznie czy nie.
            /**
             * Parametr ustawiany w pliku config.cfg "gracz" i tylko w ten sposób można go zmodyfikować.
             * 1 - Gracz sterowany zewnętrznie występuje,
             * 0 - Gracz sterowany zewnętrznie nie występuje.
             * @return True - występuje grcz ster. zewnętrznie, false - nie występuje.
             */
            bool czyGracz();
            /// Numer obserwowanego gracza.
            /**
             * Parametr ustawiany w pliku config.cfg "obserw" i tylko w ten sposób można go zmodyfikować.
             */
            int obs;
        private:
            bool isGracz;
            int autoGracza;
            int liczbaGraczy;
            int frameRate;
            int resX;
            int resY;
            int doklZakr;
            int defaultTor;
            int laps;
            double eventPr;
            std::string pathAuta;
            std::string pathTrasy;
            std::vector <Participant*> uczestnicy;
            std::vector <Car*> refAuta;
            std::vector <Track*> refTrasy;
            Track* trasa;
            std::vector <int> wagiEv;
            std::vector <Obstacle*> losowePrz;


            void ladujAuta(std::string param);
            void ladujCfg(std::string path);
            void ladujTrasy(std::string path);
            int losujLiczbe(int min, int max);
            bool U1wU2(int i1, int i2);
            Obstacle* losowyEvent();
            void losowyEfekt(Participant* gr);
            void pozycjeZadane();


        };

    }
}

#endif // GAME_H
