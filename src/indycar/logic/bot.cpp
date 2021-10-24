#include "indycar/logic/bot.hpp"
#include <cmath>

namespace indycar {
    namespace logic {

        Bot::Bot() : Participant()
        {
            inteligencja = 1;
        }

        Bot::Bot(const Bot& el) : Participant(el)
        {
            inteligencja = el.inteligencja;
        }

        Bot::Bot(int lap) : Participant(lap)
        {
            inteligencja = 1;
        }

        Bot::~Bot()
        {

        }

        void Bot::setInt(int intel) {
            inteligencja = intel;
        }

        Point Bot::jedz(bool l, bool p, bool a, bool b, bool su, bool sd, float& vg, bool flaga, float& ang) {

            decydujGdzieIJak(l, p, a, b, su, sd);
            if (koniecWys) {
                b = true;
                a = false;
            }
            popPol2 = popPol;
            popPol.x = pojazd->getPosX();
            popPol.y = pojazd->getPosY();

            Point przysrost;
            if (su && (!sd)) {
                pojazd->shiftUp();
            }
            else if (sd && (!su)) {
                if (pojazd->vAkt <= (pojazd->vMax / pojazd->lBiegow) * (pojazd->aktBieg - 1))
                    pojazd->shiftDown();
            }
            if (l && !(b || p || a))
            {
                float pom2 = pojazd->vAkt;
                if (pojazd->vAkt > 0) {
                    pojazd->vAkt = pojazd->vAkt - (pojazd->vAkt / 300 + 0.1);
                    if (pojazd->vAkt < 0)
                        pojazd->vAkt = 0;
                }
                float pom = pojazd->vAkt;
                if (flaga) {
                    pojazd->vAkt = (pojazd->vAkt - vg) / 5;
                }
                else {
                    vg = pojazd->vAkt;
                    pojazd->vAkt = pojazd->vAkt / 5;
                }
                if (pom2 == 0 && (!flaga)) {

                }
                else {
                    przysrost = pojazd->naWprost((-(2 - pom / 200) + modSkretu) * (pojazd->getTireCon() / 100), flaga, vg);
                    ang = (-(2 - pom / 200) + modSkretu) * (pojazd->getTireCon() / 100);
                }
                pojazd->vAkt = pom;
                if (aktywnaTx != 0) {
                    aktywnaTx = 0;
                    aktualizujTx = 1;
                }
            }
            else if (p && !(b || l || a))
            {
                float pom2 = pojazd->vAkt;
                if (pojazd->vAkt > 0) {
                    pojazd->vAkt = pojazd->vAkt - (pojazd->vAkt / 300 + 0.1);
                    if (pojazd->vAkt < 0)
                        pojazd->vAkt = 0;
                }
                float pom = pojazd->vAkt;
                if (flaga) {
                    pojazd->vAkt = (pojazd->vAkt - vg) / 5;
                }
                else {
                    vg = pojazd->vAkt;
                    pojazd->vAkt = pojazd->vAkt / 5;
                }
                if (pom2 == 0 && (!flaga)) {

                }
                else {
                    przysrost = pojazd->naWprost(((2 - pom / 200) + modSkretu) * (pojazd->getTireCon() / 100), flaga, vg);
                    ang = ((2 - pom / 200) + modSkretu) * (pojazd->getTireCon() / 100);
                }
                pojazd->vAkt = pom;
                if (aktywnaTx != 1) {
                    aktywnaTx = 1;
                    aktualizujTx = 1;
                }
            }
            else if (a && !(b || l || p))
            {
                float pom2 = pojazd->vAkt;
                if (pojazd->vAkt >= 0) {
                    if (pojazd->vAkt < pojazd->vMax / pojazd->lBiegow * pojazd->aktBieg) {
                        if (pojazd->vAkt >= pojazd->vMax / pojazd->lBiegow * (pojazd->aktBieg - 1))
                            pojazd->vAkt = pojazd->vAkt + ((pojazd->acc) * (pojazd->getEngineCon() / 100) - pojazd->vAkt / 500) + modPrzyspieszenia;
                        else
                            pojazd->vAkt = pojazd->vAkt + ((pojazd->acc * (pojazd->getEngineCon() / 100) - pojazd->vAkt / 500) / 2) + modPrzyspieszenia;
                    }
                    else {
                        pojazd->vAkt = pojazd->vAkt - 1;
                    }
                    if (pojazd->vAkt < 0)
                        pojazd->vAkt = 0;
                }

                float pom = pojazd->vAkt;
                if (flaga) {
                    pojazd->vAkt = (pojazd->vAkt - vg) / 5;
                }
                else {
                    vg = pojazd->vAkt;
                    pojazd->vAkt = pojazd->vAkt / 5;
                }
                if (pom2 == 0 && (!flaga)) {

                }
                else {
                    przysrost = pojazd->naWprost(modSkretu, flaga, vg);
                    ang = (modSkretu);
                }
                pojazd->vAkt = pom;

                if (aktywnaTx != 2) {
                    aktywnaTx = 2;
                    aktualizujTx = 1;
                }
            }
            else if (b && !(a || l || p))
            {
                float pom2 = pojazd->vAkt;
                if (pojazd->vAkt > 0) {
                    pojazd->vAkt = pojazd->vAkt - pojazd->dcc + modHamowania;
                    if (pojazd->vAkt < 0)
                        pojazd->vAkt = 0;
                }
                float pom = pojazd->vAkt;
                if (flaga) {
                    pojazd->vAkt = (pojazd->vAkt - vg) / 5;
                }
                else {
                    vg = pojazd->vAkt;
                    pojazd->vAkt = pojazd->vAkt / 5;
                }
                if (pom2 == 0 && (!flaga)) {

                }
                else {
                    przysrost = pojazd->naWprost(modSkretu, flaga, vg);
                    ang = (0 + modSkretu);
                }
                pojazd->vAkt = pom;

                if (aktywnaTx != 2) {
                    aktywnaTx = 2;
                    aktualizujTx = 1;
                }
            }
            else if (a && l && !(b || p)) {
                float pom2 = pojazd->vAkt;
                if (pojazd->vAkt >= 0) {
                    if (pojazd->vAkt < pojazd->vMax / pojazd->lBiegow * pojazd->aktBieg) {
                        if (pojazd->vAkt >= pojazd->vMax / pojazd->lBiegow * (pojazd->aktBieg - 1))
                            pojazd->vAkt = pojazd->vAkt + (pojazd->acc * (pojazd->getEngineCon() / 100) - pojazd->vAkt / 500) + modPrzyspieszenia;
                        else
                            pojazd->vAkt = pojazd->vAkt + ((pojazd->acc * (pojazd->getEngineCon() / 100) - pojazd->vAkt / 500) / 2) + modPrzyspieszenia;
                    }
                    else {
                        pojazd->vAkt = pojazd->vAkt - 1;
                    }
                    if (pojazd->vAkt < 0)
                        pojazd->vAkt = 0;
                }
                float pom = pojazd->vAkt;
                if (flaga) {
                    pojazd->vAkt = (pojazd->vAkt - vg) / 5;
                }
                else {
                    vg = pojazd->vAkt;
                    pojazd->vAkt = pojazd->vAkt / 5;
                }
                if (pom2 == 0 && (!flaga)) {

                }
                else {
                    przysrost = pojazd->naWprost((-(1.9 - pom / 170) + modSkretu) * (pojazd->getTireCon() / 100), flaga, vg);
                    ang = (-(1.9 - pom / 170) + modSkretu) * (pojazd->getTireCon() / 100);
                }
                pojazd->vAkt = pom;
                if (aktywnaTx != 0) {
                    aktywnaTx = 0;
                    aktualizujTx = 1;
                }
            }
            else if (a && p && !(b || l))
            {
                float pom2 = pojazd->vAkt;
                if (pojazd->vAkt >= 0) {
                    if (pojazd->vAkt < pojazd->vMax / pojazd->lBiegow * pojazd->aktBieg) {
                        if (pojazd->vAkt >= pojazd->vMax / pojazd->lBiegow * (pojazd->aktBieg - 1))
                            pojazd->vAkt = pojazd->vAkt + (pojazd->acc * (pojazd->getEngineCon() / 100) - pojazd->vAkt / 500) + modPrzyspieszenia;
                        else
                            pojazd->vAkt = pojazd->vAkt + ((pojazd->acc * (pojazd->getEngineCon() / 100) - pojazd->vAkt / 500) / 2) + modPrzyspieszenia;
                    }
                    else {
                        pojazd->vAkt = pojazd->vAkt - 1;
                    }
                    if (pojazd->vAkt < 0)
                        pojazd->vAkt = 0;
                }
                float pom = pojazd->vAkt;
                if (flaga) {
                    pojazd->vAkt = (pojazd->vAkt - vg) / 5;
                }
                else {
                    vg = pojazd->vAkt;
                    pojazd->vAkt = pojazd->vAkt / 5;
                }
                if (pom2 == 0 && (!flaga)) {

                }
                else {
                    przysrost = pojazd->naWprost(((1.9 - pom / 170) + modSkretu) * (pojazd->getTireCon() / 100), flaga, vg);
                    ang = ((1.9 - pom / 170) + modSkretu) * (pojazd->getTireCon() / 100);
                }
                pojazd->vAkt = pom;
                if (aktywnaTx != 1) {
                    aktywnaTx = 1;
                    aktualizujTx = 1;
                }
            }
            else if (b && l && !(a || p))
            {
                float pom2 = pojazd->vAkt;
                if (pojazd->vAkt > 0) {
                    pojazd->vAkt = pojazd->vAkt - pojazd->dcc + modHamowania;
                    if (pojazd->vAkt < 0)
                        pojazd->vAkt = 0;
                }
                float pom = pojazd->vAkt;
                if (flaga) {
                    pojazd->vAkt = (pojazd->vAkt - vg) / 5;
                }
                else {
                    vg = pojazd->vAkt;
                    pojazd->vAkt = pojazd->vAkt / 5;
                }
                if (pom2 == 0 && (!flaga)) {

                }
                else {
                    przysrost = pojazd->naWprost((-(2.1 - pom / 170) + modSkretu) * (pojazd->getTireCon() / 100), flaga, vg);
                    ang = (-(2.1 - pom / 170) + modSkretu) * (pojazd->getTireCon() / 100);
                }
                pojazd->vAkt = pom;
                if (aktywnaTx != 0) {
                    aktywnaTx = 0;
                    aktualizujTx = 1;
                }
            }
            else if (b && p && !(a || l))
            {
                float pom2 = pojazd->vAkt;
                if (pojazd->vAkt > 0) {
                    pojazd->vAkt = pojazd->vAkt - pojazd->dcc + modHamowania;
                    if (pojazd->vAkt < 0)
                        pojazd->vAkt = 0;
                }
                float pom = pojazd->vAkt;
                if (flaga) {
                    pojazd->vAkt = (pojazd->vAkt - vg) / 5;
                }
                else {
                    vg = pojazd->vAkt;
                    pojazd->vAkt = pojazd->vAkt / 5;
                }
                if (pom2 == 0 && (!flaga)) {

                }
                else {
                    przysrost = pojazd->naWprost(((2.1 - pom / 170) + modSkretu) * (pojazd->getTireCon() / 100), flaga, vg);
                    ang = ((2.1 - pom / 170) + modSkretu) * (pojazd->getTireCon() / 100);
                }
                pojazd->vAkt = pom;
                if (aktywnaTx != 1) {
                    aktywnaTx = 1;
                    aktualizujTx = 1;
                }
            }
            else {
                float pom2 = pojazd->vAkt;
                if (pojazd->vAkt > 0) {
                    pojazd->vAkt = pojazd->vAkt - (pojazd->vAkt / 500 + 0.05);
                    if (pojazd->vAkt < 0)
                        pojazd->vAkt = 0;
                }
                float pom = pojazd->vAkt;
                if (flaga) {
                    pojazd->vAkt = (pojazd->vAkt - vg) / 5;
                }
                else {
                    vg = pojazd->vAkt;
                    pojazd->vAkt = pojazd->vAkt / 5;
                }
                if (pom2 == 0 && (!flaga)) {

                }
                else {
                    przysrost = pojazd->naWprost((modSkretu), flaga, vg);
                    ang = (modSkretu);
                }
                pojazd->vAkt = pom;

                if (aktywnaTx != 2) {
                    aktywnaTx = 2;
                    aktualizujTx = 1;
                }

            }
            return przysrost;
        }

        void Bot::decydujGdzieIJak(bool& l, bool& p, bool& a, bool& b, bool& su, bool& sd) {

            if (pojazd->vAkt >= pojazd->vMax / pojazd->lBiegow * pojazd->aktBieg) {
                su = true;
                sd = false;
            }
            else if (pojazd->vAkt <= pojazd->vMax / pojazd->lBiegow * (pojazd->aktBieg - 1)) {
                sd = true;
                su = false;
            }
            else {
                sd = false;
                su = false;
            }

            if (pojazd->getPosX() >= zadPol.x + 50) {
                if (pojazd->getRotation() > (-10)) {
                    if ((pojazd->vAkt > ((pojazd->vMax / pojazd->lBiegow) * (pojazd->vMax / (pojazd->lBiegow - 2)))) && (pojazd->vAkt < ((pojazd->vMax / pojazd->lBiegow) * (pojazd->vMax / (pojazd->lBiegow - 1))))) {
                        a = false;    b = false;    p = false;    l = true;
                    }
                    else if (pojazd->vAkt > ((pojazd->vMax / pojazd->lBiegow) * (pojazd->vMax / (pojazd->lBiegow - 1)))) {
                        a = false;    b = true;     p = false;    l = true;
                    }
                    else {
                        a = true;     b = false;    p = false;    l = true;
                    }
                }
                else {
                    if ((pojazd->vAkt > ((pojazd->vMax / pojazd->lBiegow) * (pojazd->vMax / (pojazd->lBiegow - 2)))) && (pojazd->vAkt < ((pojazd->vMax / pojazd->lBiegow) * (pojazd->vMax / (pojazd->lBiegow - 1))))) {
                        a = false;    b = false;    p = false;    l = false;
                    }
                    else if (pojazd->vAkt > ((pojazd->vMax / pojazd->lBiegow) * (pojazd->vMax / (pojazd->lBiegow - 1)))) {
                        a = false;    b = true;     p = false;    l = false;
                    }
                    else {
                        a = true;     b = false;    p = false;    l = false;
                    }
                }
            }
            else if ((pojazd->getPosX() >= zadPol.x + 10) && (pojazd->getPosX() < zadPol.x + 50)) {
                if (pojazd->getRotation() >= (-4)) {
                    if ((pojazd->vAkt > ((pojazd->vMax / pojazd->lBiegow) * (pojazd->vMax / (pojazd->lBiegow - 2)))) && (pojazd->vAkt < ((pojazd->vMax / pojazd->lBiegow) * (pojazd->vMax / (pojazd->lBiegow - 1))))) {
                        a = false;    b = false;    p = false;    l = true;
                    }
                    else if (pojazd->vAkt > ((pojazd->vMax / pojazd->lBiegow) * (pojazd->vMax / (pojazd->lBiegow - 1)))) {
                        a = false;    b = true;     p = false;    l = true;
                    }
                    else {
                        a = true;     b = false;    p = false;    l = true;
                    }
                }
                else if (pojazd->getRotation() < (-4)) {
                    if ((pojazd->vAkt > ((pojazd->vMax / pojazd->lBiegow) * (pojazd->vMax / (pojazd->lBiegow - 2)))) && (pojazd->vAkt < ((pojazd->vMax / pojazd->lBiegow) * (pojazd->vMax / (pojazd->lBiegow - 1))))) {
                        a = false;    b = false;    p = true;    l = false;
                    }
                    else if (pojazd->vAkt > ((pojazd->vMax / pojazd->lBiegow) * (pojazd->vMax / (pojazd->lBiegow - 1)))) {
                        a = false;    b = true;     p = true;    l = false;
                    }
                    else {
                        a = true;     b = false;    p = true;    l = false;
                    }
                }
                else {
                    if ((pojazd->vAkt > ((pojazd->vMax / pojazd->lBiegow) * (pojazd->vMax / (pojazd->lBiegow - 2)))) && (pojazd->vAkt < ((pojazd->vMax / pojazd->lBiegow) * (pojazd->vMax / (pojazd->lBiegow - 1))))) {
                        a = false;    b = false;    p = false;    l = false;
                    }
                    else if (pojazd->vAkt > ((pojazd->vMax / pojazd->lBiegow) * (pojazd->vMax / (pojazd->lBiegow - 1)))) {
                        a = false;    b = true;     p = false;    l = false;
                    }
                    else {
                        a = true;     b = false;    p = false;    l = false;
                    }
                }
            }
            else if (pojazd->getPosX() < zadPol.x - 50) {
                if (pojazd->getRotation() < 10) {
                    if ((pojazd->vAkt > ((pojazd->vMax / pojazd->lBiegow) * (pojazd->vMax / (pojazd->lBiegow - 2)))) && (pojazd->vAkt < ((pojazd->vMax / pojazd->lBiegow) * (pojazd->vMax / (pojazd->lBiegow - 1))))) {
                        a = false;    b = false;    p = true;     l = false;
                    }
                    else if (pojazd->vAkt > ((pojazd->vMax / pojazd->lBiegow) * (pojazd->vMax / (pojazd->lBiegow - 1)))) {
                        a = false;    b = true;     p = true;     l = false;
                    }
                    else {
                        a = true;     b = false;    p = true;     l = false;
                    }
                }
                else {
                    if ((pojazd->vAkt > ((pojazd->vMax / pojazd->lBiegow) * (pojazd->vMax / (pojazd->lBiegow - 2)))) && (pojazd->vAkt < ((pojazd->vMax / pojazd->lBiegow) * (pojazd->vMax / (pojazd->lBiegow - 1))))) {
                        a = false;    b = false;    p = false;    l = false;
                    }
                    else if (pojazd->vAkt > ((pojazd->vMax / pojazd->lBiegow) * (pojazd->vMax / (pojazd->lBiegow - 1)))) {
                        a = false;    b = true;     p = false;    l = false;
                    }
                    else {
                        a = true;     b = false;    p = false;    l = false;
                    }
                }
            }
            else if ((pojazd->getPosX() <= zadPol.x - 10) && (pojazd->getPosX() > zadPol.x - 50)) {
                if (pojazd->getRotation() <= (4)) {
                    if ((pojazd->vAkt > ((pojazd->vMax / pojazd->lBiegow) * (pojazd->vMax / (pojazd->lBiegow - 2)))) && (pojazd->vAkt < ((pojazd->vMax / pojazd->lBiegow) * (pojazd->vMax / (pojazd->lBiegow - 1))))) {
                        a = false;    b = false;    p = true;    l = false;
                    }
                    else if (pojazd->vAkt > ((pojazd->vMax / pojazd->lBiegow) * (pojazd->vMax / (pojazd->lBiegow - 1)))) {
                        a = false;    b = true;     p = true;    l = false;
                    }
                    else {
                        a = true;     b = false;    p = true;    l = false;
                    }
                }
                else if (pojazd->getRotation() > (4)) {
                    if ((pojazd->vAkt > ((pojazd->vMax / pojazd->lBiegow) * (pojazd->vMax / (pojazd->lBiegow - 2)))) && (pojazd->vAkt < ((pojazd->vMax / pojazd->lBiegow) * (pojazd->vMax / (pojazd->lBiegow - 1))))) {
                        a = false;    b = false;    p = false;    l = true;
                    }
                    else if (pojazd->vAkt > ((pojazd->vMax / pojazd->lBiegow) * (pojazd->vMax / (pojazd->lBiegow - 1)))) {
                        a = false;    b = true;     p = false;    l = true;
                    }
                    else {
                        a = true;     b = false;    p = false;    l = true;
                    }
                }
                else {
                    if ((pojazd->vAkt > ((pojazd->vMax / pojazd->lBiegow) * (pojazd->vMax / (pojazd->lBiegow - 2)))) && (pojazd->vAkt < ((pojazd->vMax / pojazd->lBiegow) * (pojazd->vMax / (pojazd->lBiegow - 1))))) {
                        a = false;    b = false;    p = false;    l = false;
                    }
                    else if (pojazd->vAkt > ((pojazd->vMax / pojazd->lBiegow) * (pojazd->vMax / (pojazd->lBiegow - 1)))) {
                        a = false;    b = true;     p = false;    l = false;
                    }
                    else {
                        a = true;     b = false;    p = false;    l = false;
                    }
                }
            }
            else {
                if (pojazd->getRotation() < -0.1) {
                    a = true;     b = false;    p = true;     l = false;
                }
                else if (pojazd->getRotation() > 0.1) {
                    a = true;     b = false;    p = false;    l = true;
                }
                else {
                    a = true;     b = false;    p = false;    l = false;
                }

            }
            if (pojazd->getPosY() < zadPol.y + pojazd->vAkt / 15 * 100) {
                if (abs(pojazd->getPosX() - zadPol.x) > 50) {
                    if (pojazd->getVAkt() >= 250) {
                        a = false;     b = true;
                    }
                    else if (pojazd->getVAkt() < 250 && pojazd->getVAkt() > 150) {
                        a = false;     b = true;
                    }
                    else {
                        a = true;     b = false;
                    }
                }
                else if ((abs(pojazd->getPosX() - zadPol.x) <= 50) && (abs(pojazd->getPosX() - zadPol.x) > 10)) {
                    if (pojazd->getVAkt() >= 250) {
                        a = false;     b = true;
                    }
                    else if (pojazd->getVAkt() < 250 && pojazd->getVAkt() > 150) {
                        a = false;     b = false;
                    }
                    else {
                        a = true;     b = false;
                    }
                }
                else {
                    if (pojazd->getVAkt() >= 250) {
                        a = true;     b = false;
                    }
                    else if (pojazd->getVAkt() < 250 && pojazd->getVAkt() > 150) {
                        a = true;     b = false;
                    }
                    else {
                        a = true;     b = false;
                    }
                }
            }

        }

        void Bot::setPopPol(Point a) {
            popPol = a;
        }

        void Bot::setPopPol2(Point a) {
            popPol2 = a;
        }

    }
}
