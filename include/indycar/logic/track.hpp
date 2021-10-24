#ifndef TRACK_H
#define TRACK_H

#include "obstacle.hpp"

namespace indycar {
    namespace logic {

        class Track : public Drawable
        {
        public:
            /// Konstruktor domyślny.
            Track();
            /// Konstruktor kpiujący.
            Track(const Track& el);
            /// Konstruktor.
            /**
             * @param driury Ilość dziur w torze - parametr historyczny.
             * @param tarki Ilość tarek w torze.
             * @param bandy Ilość band w torze.
             * @param nazwa Nazwa toru.
             * @param tx Tekstury toru.
             * @param edL Wektor długości poszczególnych etapów.
             * @param eNz Wektor nazw poszczególnych etapó.
             */
            Track(int driury, int tarki, int bandy, std::string nazwa, std::vector<std::string> tx, std::vector<int> edL, std::vector<std::string> eNz);
            /// Destruktor.
            ~Track();
            /// Dodaje element do toru.
            /**
             * @param el Wskażnik na element który chcemy dodać.
             */
            void dodajElToru(std::vector<Obstacle*>& el);
            /// Ustawienie ilości tarek.
            /**
             * @param ile Ilość tarek.
             * @see getIloscTarek()
             */
            void setIloscTarek(int ile);
            /// Ustawienie ilości dziur.
            /**
             * @param ile Ilość dziur.
             * @see getIloscDziur()
             */
            void setIloscDziur(int ile);
            /// Ustawienie ilości band.
            /**
             * @param ile Ilość band.
             * @see getIloscBand()
             */
            void setIloscBand(int ile);
            /// Ustawienie nazwy toru.
            /**
             * @param nazwa Nowa nazwa toru.
             * @see getNazwaToru()
             */
            void setNazwaToru(std::string nazwa);
            /// Zwraca ilość tarek.
            /**
             * @return Ilość tarek.
             * @see setIloscTarek()
             */
            int getIloscTarek();
            /// Zwraca ilość band.
            /**
             * @return Ilość band.
             * @see setIloscBand()
             */
            int getIloscBand();
            /// Zwraca ilość dziur.
            /**
             * @return Ilość dziur.
             * @see setIloscDziur()
             */
            int getIloscDziur();
            /// Zwraca nazwę toru.
            /**
             * @return Nazwa toru.
             * @see setNazwaToru()
             */
            std::string getNazwaToru();
            /// Zwraca wektor ścieżek do tekstur.
            /**
             * @return Ścieżki do tekstur toru.
             */
            std::vector <std::string> getTexPath();
            /// Zwraca wektor długośi kolejnych etapów.
            /**
             * @return Długgości kolejnych etapów.
             */
            std::vector <int> getEtDl();
            /// Zwraca wektor nazw kolejnych etapów.
            /**
             * @return Nazwy kolejnych etapów.
             */
            std::vector <std::string> getEtNz();
            /// Zwraca wektor elementów toru.
            /**
             * Wszystkie elementy toru - bandy, tarki, dziury.
             * @return Wektor elementów toru.
             */
            std::vector <std::vector <Obstacle*> > getListeEelemToru();

        private:
            std::vector <std::vector <Obstacle*> > elemToru;
            int iloscTarek;
            int iloscDziur;
            int iloscBand;
            std::string nazwaToru;
            std::vector <std::string> texture;
            std::vector <int> etapyDl;
            std::vector <std::string> etapyNz;

        };

    }
}

#endif // TRACK_H
