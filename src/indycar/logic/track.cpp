#include "indycar/logic/track.hpp"

namespace indycar {
    namespace logic {

        Track::Track() : Drawable()
        {
            iloscBand = 0;
            iloscDziur = 0;
            iloscTarek = 0;
            nazwaToru = "Default";
        }
        Track::Track(const Track& el) : Drawable(el)
        {
            for (int i = 0; i<int(el.elemToru.size()); i++) {
                std::vector <Obstacle*> pom;
                for (int j = 0; j<int(el.elemToru[i].size()); j++) {
                    Obstacle* nowa = new Obstacle(*el.elemToru[i][j]);
                    pom.push_back(nowa);
                }
                elemToru.push_back(pom);
            }
            iloscBand = el.iloscBand;
            iloscDziur = el.iloscDziur;
            iloscTarek = el.iloscTarek;
            nazwaToru = el.nazwaToru;
            texture = el.texture;
            etapyDl = el.etapyDl;
            etapyNz = el.etapyNz;
        }

        Track::Track(int dziury, int tarki, int bandy, std::string nazwa, std::vector<std::string> tx, std::vector<int> edL, std::vector<std::string> eNz) : Drawable()
        {
            iloscBand = bandy;
            iloscDziur = dziury;
            iloscTarek = tarki;
            nazwaToru = nazwa;
            texture = tx;
            etapyDl = edL;
            etapyNz = eNz;

        }

        Track::~Track() {
            for (int i = elemToru.size() - 1; i >= 0; i--) {
                for (int j = elemToru[i].size() - 1; j >= 0; j--) {
                    delete elemToru[i][j];
                    elemToru[i].pop_back();
                }
                elemToru.pop_back();
            }
        }
        void Track::dodajElToru(std::vector <Obstacle*>& el) {
            elemToru.push_back(el);

        }
        void Track::setIloscTarek(int ile) {
            iloscTarek = ile;
        }

        void Track::setIloscDziur(int ile) {
            iloscDziur = ile;
        }

        void Track::setIloscBand(int ile) {
            iloscBand = ile;
        }

        void Track::setNazwaToru(std::string nazwa) {
            nazwaToru = nazwa;
        }

        int Track::getIloscTarek() {
            return iloscTarek;
        }

        int Track::getIloscBand() {
            return iloscBand;
        }

        int Track::getIloscDziur() {
            return iloscDziur;
        }

        std::string Track::getNazwaToru() {
            return nazwaToru;
        }
        std::vector<std::vector<Obstacle*> > Track::getListeEelemToru() {
            return elemToru;
        }

        std::vector <std::string> Track::getTexPath() {
            return texture;
        }

        std::vector <int> Track::getEtDl() {
            return etapyDl;
        }

        std::vector <std::string> Track::getEtNz() {
            return etapyNz;
        }

    }
}
