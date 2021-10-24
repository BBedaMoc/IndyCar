#include "indycar/logic/participant.hpp"

namespace indycar {
    namespace logic {

        Participant::Participant()
        {
            modHamowania = 0;
            modPrzyspieszenia = 0;
            modSkretu = 0;
            aktualizujTx = 1;
            aktywnaTx = 2;
            lapToGo = 0;
            nrEt = 0;
            iter = 0;
            pozycja = 99;
        }

        Participant::Participant(float modS, float modP, float modH) {
            modHamowania = modH;
            modPrzyspieszenia = modP;
            modSkretu = modS;
            aktualizujTx = 1;
            aktywnaTx = 2;
            lapToGo = 0;
            nrEt = 0;
            iter = 0;
            pozycja = 99;
        }

        Participant::Participant(const Participant& el) {
            modHamowania = el.modHamowania;
            modPrzyspieszenia = el.modPrzyspieszenia;
            modSkretu = el.modSkretu;
            aktualizujTx = el.aktualizujTx;
            aktywnaTx = el.aktywnaTx;
            pojazd = new Car(*el.pojazd);
            lapToGo = el.lapToGo;
            nrEt = el.nrEt;
            iter = el.iter;
            pozycja = el.pozycja;
        }

        Participant::Participant(int lap) {
            modHamowania = 0;
            modPrzyspieszenia = 0;
            modSkretu = 0;
            aktualizujTx = 1;
            aktywnaTx = 2;
            lapToGo = lap;
            nrEt = 0;
            iter = 0;
            pozycja = 99;
        }

        Participant::~Participant() {
            delete pojazd;
            for (int i = 0; i<int(mojeB.size()); i++) {
                delete mojeB[i];
            }
            mojeB.clear();

            for (int i = 0; i<int(mojeT.size()); i++) {
                delete mojeT[i];
            }
            mojeT.clear();

            for (int i = 0; i<int(zakret.size()); i++) {
                delete zakret[i];
            }
            zakret.clear();

            for (int i = 0; i<int(zakB.size()); i++) {
                delete zakB[i];
            }
            zakB.clear();

            for (int i = 0; i<int(zakT.size()); i++) {
                delete zakT[i];
            }
            zakT.clear();
        }

        void Participant::setNrAuta(int i) {
            nrAuta = i;
        }
        void Participant::setLapToGo(int i) {
            lapToGo = i;
        }

        void Participant::setAktywnaTx(int i) {
            aktywnaTx = i;
        }

        void Participant::setPozycja(int i) {
            pozycja = i;
        }

        int Participant::getLapToGo() {
            return lapToGo;
        }

        int Participant::getAktywnaTx() {
            return aktywnaTx;
        }

        int Participant::getPozycja() {
            return pozycja;
        }
        void Participant::setIter(float i) {
            iter = i;
        }

        void Participant::setNrEt(int nr) {
            nrEt = nr;
        }

        float Participant::getIter() {
            return iter;
        }

        int Participant::getNrEt() {
            return nrEt;
        }

        void Participant::setKoniecWys(bool w) {
            koniecWys = w;
        }
        void Participant::inicjalizujMojeBT(Participant* ref) {
            std::vector <Obstacle*> pomT, pomB;
            std::vector <bool> kolT, kolB;
            float poY = ref->pojazd->getPosY() - pojazd->getPosY();
            for (int i = 0; i<int(ref->mojeT.size()); i++) {
                Obstacle* pom = new Obstacle(*ref->mojeT[i]);
                pom->wyznaczPunkty(0, 0, -poY);
                pomT.push_back(pom);
                kolT.push_back(false);
            }
            for (int i = 0; i<int(ref->mojeB.size()); i++) {
                Obstacle* pom = new Obstacle(*ref->mojeB[i]);
                pom->wyznaczPunkty(0, 0, -poY);
                pomB.push_back(pom);
                kolB.push_back(false);
            }
            mojeT = pomT;
            mojeB = pomB;
            kolizja.push_back(kolT);
            kolizja.push_back(kolB);
        }
        void Participant::inicjalizujMojeBT(std::vector <Obstacle*> T, std::vector <Obstacle*> B) {
            std::vector <Obstacle*> pomT, pomB;
            std::vector <bool> kolT, kolB;
            for (int i = 0; i<int(T.size()); i++) {
                Obstacle* pom = new Obstacle(*T[i]);
                pomT.push_back(pom);
                kolT.push_back(false);
            }
            for (int i = 0; i<int(B.size()); i++) {
                Obstacle* pom = new Obstacle(*B[i]);
                pomB.push_back(pom);
                kolB.push_back(false);
            }
            mojeT = pomT;
            mojeB = pomB;
            kolizja.push_back(kolT);
            kolizja.push_back(kolB);
        }

        void Participant::aktPosElToru(float angle, float poX, float poY, Point srObr, bool zak) {
            if (!zak)
            {
                for (int i = 0; i<int(mojeB.size()); i++) {
                    if (mojeB[i]->getPosY() + poY > pojazd->getPosY() + 200) {
                        mojeB[i]->wyznaczPunkty(0, poX, minXY(mojeB, mojeB[i]->getPosX(), false) - mojeB[i]->getPosY() + poY - mojeB[i]->getHeigth());
                    }
                    else
                        mojeB[i]->wyznaczPunkty(0, poX, poY);
                }
                for (int i = 0; i<int(mojeT.size()); i++) {
                    if (mojeT[i]->getPosY() + poY > pojazd->getPosY() + 200) {
                        mojeT[i]->wyznaczPunkty(0, poX, minXY(mojeT, mojeT[i]->getPosX(), false) - mojeT[i]->getPosY() + poY - mojeT[i]->getHeigth());
                    }
                    else
                        mojeT[i]->wyznaczPunkty(0, poX, poY);
                }
            }

            for (int i = 0; i<int(zakret.size()); i++) {

                for (int j = 0; j<int(zakret[i]->punkty.size()); j++) {
                    zakret[i]->punkty[j].obrot(srObr, angle);
                }
                Point p(zakret[i]->getPosX(), zakret[i]->getPosY());
                p.obrot(srObr, angle);
                zakret[i]->setPosition(p.x, p.y);
                zakret[i]->setRotation(zakret[i]->getRotation() + angle);

            }
            for (int i = 0; i<int(zakT.size()); i++) {
                for (int j = 0; j<int(zakT[i]->punkty.size()); j++) {
                    zakT[i]->punkty[j].obrot(srObr, angle);
                }
                Point p(zakT[i]->getPosX(), zakT[i]->getPosY());
                p.obrot(srObr, angle);
                zakT[i]->setPosition(p.x, p.y);
                zakT[i]->setRotation(zakT[i]->getRotation() + angle);
            }
        }

        float Participant::minXY(std::vector <Obstacle*> el, float wspX, bool czyX) {
            float min;
            if (czyX) {
                min = el[0]->getPosX();
                for (int i = 0; i<int(el.size()); i++) {
                    if (min > el[i]->getPosX()) {
                        min = el[i]->getPosX();
                    }
                }
            }
            else {
                float x = 0;
                while (true) {
                    if (el[x]->getPosX() == wspX) {
                        min = el[x]->getPosY();
                        break;
                    }
                    x++;
                }
                for (int i = 0; i<int(el.size()); i++) {
                    if ((min > el[i]->getPosY()) && (el[i]->getPosX() == wspX)) {
                        min = el[i]->getPosY();
                    }
                }
            }
            return min;
        }

        std::vector <Obstacle*> Participant::getZakret(int dl, std::string rdz, Point pocz, int dokl) {
            std::vector <Point> pom;
            std::vector <Obstacle*> zak;
            pom.push_back(pocz);
            if (rdz == "L45") {
                for (int i = 0; i <= dokl + 1; i++) {
                    Point pom2(pom[i].x, pom[i].y - dl);
                    Obstacle* xx = new Obstacle();

                    if (i <= dokl) {
                        xx->setSrodekObr(Point(450, dl));
                        xx->setSize(dl, 450);
                        xx->inicjalizujPunkty(Point(pom[i].x, pom[i].y));
                        pom2.obrot(pom[i], 360 - i * 45 / dokl);
                        xx->wyznaczPunkty(360 - i * 45 / dokl, 0, 0);
                        xx->setRotation(360 - i * 45 / dokl);
                    }
                    else {
                        xx->setSrodekObr(Point(450, 600));
                        xx->setSize(600, 450);
                        xx->inicjalizujPunkty(Point(pom[i].x, pom[i].y));
                        pom2.obrot(pom[i], 360 - 45);
                        xx->wyznaczPunkty(360 - 45, 0, 0);
                        xx->setRotation(360 - 45);
                        for (int j = 0; j < 12; j++) {
                            Obstacle* x2 = new Obstacle(0.01, 0.005, "", true);
                            x2->setSrodekObr(Point(25, dl));
                            x2->setSize(100, 25);
                            Point c((pom[i].x - (475 * (j % 2))), (pom[i].y - int(j / 2) * 100));
                            x2->inicjalizujPunkty(c);
                            for (int z = 0; z<int(x2->punkty.size()); z++) {
                                x2->punkty[z].obrot(pom[i], 360 - 45);
                            }
                            c.obrot(pom[i], 360 - 45);
                            x2->setPosition(c.x, c.y);
                            x2->setRotation(360 - 45);
                            zakT.push_back(x2);
                        }
                    }
                    pom.push_back(pom2);
                    zak.push_back(xx);
                }
            }
            else if (rdz == "L90") {
                for (int i = 0; i <= dokl + 1; i++) {
                    Point pom2(pom[i].x, pom[i].y - dl);
                    Obstacle* xx = new Obstacle();

                    if (i <= dokl) {
                        xx->setSrodekObr(Point(450, dl));
                        xx->setSize(dl, 450);
                        xx->inicjalizujPunkty(Point(pom[i].x, pom[i].y));
                        pom2.obrot(pom[i], 360 - i * 90 / dokl);
                        xx->wyznaczPunkty(360 - i * 90 / dokl, 0, 0);
                        xx->setRotation(360 - i * 90 / dokl);
                    }
                    else {
                        xx->setSrodekObr(Point(450, 600));
                        xx->setSize(600, 450);
                        xx->inicjalizujPunkty(Point(pom[i].x, pom[i].y));
                        pom2.obrot(pom[i], 360 - 90);
                        xx->wyznaczPunkty(360 - 90, 0, 0);
                        xx->setRotation(360 - 90);
                        for (int j = 0; j < 12; j++) {
                            Obstacle* x2 = new Obstacle(0.01, 0.005, "", true);
                            x2->setSrodekObr(Point(25, dl));
                            x2->setSize(100, 25);
                            Point c((pom[i].x - (475 * (j % 2))), (pom[i].y - int(j / 2) * 100));
                            x2->inicjalizujPunkty(c);
                            for (int z = 0; z<int(x2->punkty.size()); z++) {
                                x2->punkty[z].obrot(pom[i], 360 - 90);
                            }
                            c.obrot(pom[i], 360 - 90);
                            x2->setPosition(c.x, c.y);
                            x2->setRotation(360 - 90);
                            zakT.push_back(x2);
                        }
                    }
                    pom.push_back(pom2);
                    zak.push_back(xx);
                }
            }
            else if (rdz == "L180") {
                for (int i = 0; i <= dokl + 1; i++) {
                    Point pom2(pom[i].x, pom[i].y - dl);
                    Obstacle* xx = new Obstacle();
                    if (i <= dokl) {
                        xx->setSrodekObr(Point(450, dl));
                        xx->setSize(dl, 450);
                        xx->inicjalizujPunkty(Point(pom[i].x, pom[i].y));
                        pom2.obrot(pom[i], 360 - i * 180 / dokl);
                        xx->wyznaczPunkty(360 - i * 180 / dokl, 0, 0);
                        xx->setRotation(360 - i * 180 / dokl);
                    }
                    else {
                        xx->setSrodekObr(Point(450, 600));
                        xx->setSize(600, 450);
                        xx->inicjalizujPunkty(Point(pom[i].x, pom[i].y));
                        pom2.obrot(pom[i], 360 - 180);
                        xx->wyznaczPunkty(360 - 180, 0, 0);
                        xx->setRotation(360 - 180);
                        for (int j = 0; j < 12; j++) {
                            Obstacle* x2 = new Obstacle(0.01, 0.005, "", true);
                            x2->setSrodekObr(Point(25, dl));
                            x2->setSize(100, 25);
                            Point c((pom[i].x - (475 * (j % 2))), (pom[i].y - int(j / 2) * 100));
                            x2->inicjalizujPunkty(c);
                            for (int z = 0; z<int(x2->punkty.size()); z++) {
                                x2->punkty[z].obrot(pom[i], 360 - 180);
                            }
                            c.obrot(pom[i], 360 - 180);
                            x2->setPosition(c.x, c.y);
                            x2->setRotation(360 - 180);
                            zakT.push_back(x2);
                        }
                    }
                    pom.push_back(pom2);
                    zak.push_back(xx);
                }
            }
            else if (rdz == "P45") {
                for (int i = 0; i <= dokl + 1; i++) {
                    Point pom2(pom[i].x, pom[i].y - dl);
                    Obstacle* xx = new Obstacle();
                    if (i <= dokl) {
                        xx->setSrodekObr(Point(0, dl));
                        xx->setSize(dl, 450);
                        xx->inicjalizujPunkty(Point(pom[i].x, pom[i].y));
                        pom2.obrot(pom[i], i * 45 / dokl);
                        xx->wyznaczPunkty(i * 45 / dokl, 0, 0);
                        xx->setRotation(i * 45 / dokl);
                    }
                    else {
                        xx->setSrodekObr(Point(0, 600));
                        xx->setSize(600, 450);
                        xx->inicjalizujPunkty(Point(pom[i].x, pom[i].y));
                        pom2.obrot(pom[i], 45);
                        xx->wyznaczPunkty(45, 0, 0);
                        xx->setRotation(45);
                        for (int j = 0; j < 12; j++) {
                            Obstacle* x2 = new Obstacle(0.01, 0.005, "", true);
                            x2->setSrodekObr(Point(25, dl));
                            x2->setSize(100, 25);
                            Point c((pom[i].x - 25 + (475 * (j % 2))), (pom[i].y - int(j / 2) * 100));
                            x2->inicjalizujPunkty(c);
                            for (int z = 0; z<int(x2->punkty.size()); z++) {
                                x2->punkty[z].obrot(pom[i], 45);
                            }
                            c.obrot(pom[i], 45);
                            x2->setPosition(c.x, c.y);
                            x2->setRotation(45);
                            zakT.push_back(x2);
                        }
                    }
                    pom.push_back(pom2);
                    zak.push_back(xx);
                }
            }
            else if (rdz == "P90") {
                for (int i = 0; i <= dokl + 1; i++) {
                    Point pom2(pom[i].x, pom[i].y - dl);
                    Obstacle* xx = new Obstacle();
                    if (i <= dokl) {

                        xx->setSrodekObr(Point(0, dl));
                        xx->setSize(dl, 450);
                        xx->inicjalizujPunkty(Point(pom[i].x, pom[i].y));
                        pom2.obrot(pom[i], i * 90 / dokl);
                        xx->wyznaczPunkty(i * 90 / dokl, 0, 0);
                        xx->setRotation(i * 90 / dokl);
                    }
                    else {
                        xx->setSrodekObr(Point(0, 600));
                        xx->setSize(600, 450);
                        xx->inicjalizujPunkty(Point(pom[i].x, pom[i].y));
                        pom2.obrot(pom[i], 90);
                        xx->wyznaczPunkty(90, 0, 0);
                        xx->setRotation(90);
                        for (int j = 0; j < 12; j++) {
                            Obstacle* x2 = new Obstacle(0.01, 0.005, "", true);
                            x2->setSrodekObr(Point(25, dl));
                            x2->setSize(100, 25);
                            Point c((pom[i].x - 25 + (475 * (j % 2))), (pom[i].y - int(j / 2) * 100));
                            x2->inicjalizujPunkty(c);
                            for (int z = 0; z<int(x2->punkty.size()); z++) {
                                x2->punkty[z].obrot(pom[i], 90);
                            }
                            c.obrot(pom[i], 90);
                            x2->setPosition(c.x, c.y);
                            x2->setRotation(90);
                            zakT.push_back(x2);
                        }
                        for (int j = 0; j < 16; j++) {
                            Obstacle* x2 = new Obstacle(0.1, 0.05, "", false);
                            x2->setSrodekObr(Point(50, 75));
                            x2->setSize(75, 50);
                            Point c((pom[i].x - 125 + (650 * (j % 2))), (pom[i].y - int(j / 2) * 75));
                            x2->inicjalizujPunkty(c);
                            for (int z = 0; z<int(x2->punkty.size()); z++) {
                                x2->punkty[z].obrot(pom[i], 90);
                            }
                            c.obrot(pom[i], 90);
                            x2->setPosition(c.x, c.y);
                            x2->setRotation(90);
                            zakB.push_back(x2);
                        }

                    }
                    pom.push_back(pom2);
                    zak.push_back(xx);
                }

            }
            else if (rdz == "P180") {
                for (int i = 0; i <= dokl + 1; i++) {
                    Point pom2(pom[i].x, pom[i].y - dl);
                    Obstacle* xx = new Obstacle();
                    if (i <= dokl) {
                        xx->setSrodekObr(Point(0, dl));
                        xx->setSize(dl, 450);
                        xx->inicjalizujPunkty(Point(pom[i].x, pom[i].y));
                        pom2.obrot(pom[i], i * 180 / dokl);
                        xx->wyznaczPunkty(i * 180 / dokl, 0, 0);
                        xx->setRotation(i * 180 / dokl);
                    }
                    else {
                        xx->setSrodekObr(Point(0, 600));
                        xx->setSize(600, 450);
                        xx->inicjalizujPunkty(Point(pom[i].x, pom[i].y));
                        pom2.obrot(pom[i], 180);
                        xx->wyznaczPunkty(180, 0, 0);
                        xx->setRotation(180);
                        for (int j = 0; j < 12; j++) {
                            Obstacle* x2 = new Obstacle(0.01, 0.005, "", true);
                            x2->setSrodekObr(Point(25, dl));
                            x2->setSize(100, 25);
                            Point c((pom[i].x - 25 + (475 * (j % 2))), (pom[i].y - int(j / 2) * 100));
                            x2->inicjalizujPunkty(c);
                            for (int z = 0; z<int(x2->punkty.size()); z++) {
                                x2->punkty[z].obrot(pom[i], 180);
                            }
                            c.obrot(pom[i], 180);
                            x2->setPosition(c.x, c.y);
                            x2->setRotation(180);
                            zakT.push_back(x2);
                        }
                    }
                    pom.push_back(pom2);
                    zak.push_back(xx);
                }
            }

            return zak;
        }

        Point Participant::srodekKZak() {
            Point pom;
            if (zakret.size() > 0) {
                if ((zakret[1]->punkty[2].x != zakret[1]->punkty[3].x) && (zakret[int(zakret.size()) - int(int(zakret.size()) * 3 / 4)]->punkty[2].x != zakret[int(zakret.size()) - int(int(zakret.size()) * 3 / 4)]->punkty[3].x)) {
                    float a, b;
                    a = (zakret[1]->punkty[2].y - zakret[1]->punkty[3].y) / (zakret[1]->punkty[2].x - zakret[1]->punkty[3].x);
                    b = zakret[1]->punkty[3].y - a * zakret[1]->punkty[3].x;
                    float aa, bb;
                    aa = (zakret[int(zakret.size()) - int(int(zakret.size()) * 3 / 4)]->punkty[2].y - zakret[int(zakret.size()) - int(int(zakret.size()) * 3 / 4)]->punkty[3].y) / (zakret[int(zakret.size()) - int(int(zakret.size()) * 3 / 4)]->punkty[2].x - zakret[int(zakret.size()) - int(int(zakret.size()) * 3 / 4)]->punkty[3].x);
                    bb = zakret[int(zakret.size()) - int(int(zakret.size()) * 3 / 4)]->punkty[3].y - aa * zakret[int(zakret.size()) - int(int(zakret.size()) * 3 / 4)]->punkty[3].x;
                    pom.x = (bb - b) / (a - aa);
                    pom.y = a * pom.x + b;
                    return pom;
                }
                else if ((zakret[1]->punkty[2].x == zakret[1]->punkty[3].x) && (zakret[int(zakret.size()) - int(int(zakret.size()) * 3 / 4)]->punkty[2].x != zakret[int(zakret.size()) - int(int(zakret.size()) * 3 / 4)]->punkty[3].x)) {
                    float aa, bb;
                    aa = (zakret[int(zakret.size()) - int(int(zakret.size()) * 3 / 4)]->punkty[2].y - zakret[int(zakret.size()) - int(int(zakret.size()) * 3 / 4)]->punkty[3].y) / (zakret[int(zakret.size()) - int(int(zakret.size()) * 3 / 4)]->punkty[2].x - zakret[int(zakret.size()) - int(int(zakret.size()) * 3 / 4)]->punkty[3].x);
                    bb = zakret[int(zakret.size()) - int(int(zakret.size()) * 3 / 4)]->punkty[3].y - aa * zakret[int(zakret.size()) - int(int(zakret.size()) * 3 / 4)]->punkty[3].x;
                    pom.x = zakret[1]->punkty[2].x;
                    pom.y = aa * pom.x + bb;
                    return pom;
                }
                else if ((zakret[1]->punkty[2].x != zakret[1]->punkty[3].x) && (zakret[int(zakret.size()) - int(int(zakret.size()) * 3 / 4)]->punkty[2].x == zakret[int(zakret.size()) - int(int(zakret.size()) * 3 / 4)]->punkty[3].x)) {
                    float a, b;
                    a = (zakret[1]->punkty[2].y - zakret[1]->punkty[3].y) / (zakret[1]->punkty[2].x - zakret[1]->punkty[3].x);
                    b = zakret[1]->punkty[3].y - a * zakret[1]->punkty[3].x;
                    pom.x = zakret[int(zakret.size()) - int(int(zakret.size()) * 3 / 4)]->punkty[2].x;
                    pom.y = a * pom.x + b;
                    return pom;
                }
                else {
                    //Nie przewiduje aby taka mliwosc mogla zajsc
                }
            }
            return Point(pojazd->getPosX(), pojazd->getPosY());
        }

    }
}
