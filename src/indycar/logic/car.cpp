#include "indycar/logic/car.hpp"
#include <cmath>

namespace indycar {
    namespace logic {

        Car::Car() : Obstacle()
        {
            acc = 0;
            dcc = 0;
            lBiegow = 0;
            aktBieg = 0;
            engineCon = 100;
            tireCon = 100;
            vMax = 0;
            vAkt = 0;
        }

        Car::Car(const Car& el) : Obstacle(el)
        {
            acc = el.acc;
            dcc = el.dcc;
            lBiegow = el.lBiegow;
            aktBieg = el.aktBieg;
            engineCon = el.engineCon;
            tireCon = el.tireCon;
            vMax = el.vMax;
            texture = el.texture;
            vAkt = el.vAkt;
        }

        Car::~Car() {

        }

        void Car::setAcc(float Acc) {
            if (Acc >= 0) acc = Acc;
            else acc = 0;
        }

        void Car::setDcc(float Dcc) {
            if (Dcc >= 0) dcc = Dcc;
            else dcc = 0;
        }

        void Car::setLBiegow(int LB) {
            if (LB < 1) lBiegow = 1;
            else lBiegow = LB;
        }

        void Car::setAkBieg(int AkB) {
            aktBieg = AkB;
        }

        void Car::shiftUp() {
            if (aktBieg < lBiegow) {
                aktBieg = aktBieg + 1;
            }
            else {
                aktBieg = aktBieg;
            }
        }

        void Car::shiftDown() {
            if (aktBieg > 0) {
                aktBieg = aktBieg - 1;
            }
            else {
                aktBieg = aktBieg;
            }
        }

        void Car::setEngineCon(float EC) {
            if (EC > 100) engineCon = 100;
            else if (EC < 0) engineCon = 0;
            else engineCon = EC;
        }

        void Car::setTireCon(float TC) {
            if (TC > 100) tireCon = 100;
            else if (TC < 0) tireCon = 0;
            else tireCon = TC;
        }

        void Car::setVmax(float vmax) {
            vMax = vmax;
        }

        float Car::getAcc() {
            return acc;
        }

        float Car::getDcc() {
            return dcc;
        }

        int Car::getLBiegow() {
            return lBiegow;
        }

        int Car::getAktBieg() {
            return aktBieg;
        }

        float Car::getEngineCon() {
            return engineCon;
        }

        float Car::getTireCon() {
            return tireCon;
        }

        float Car::getVmax() {
            return vMax;
        }

        Point Car::naWprost(double angle, bool flaga, float vg) {
            Point pos;
            float x, y;
            if (!flaga) x = getPosX() + vAkt * sin(getRotation() * PI / 180);
            else x = getPosX() + (vAkt + (vg / 5)) * sin(getRotation() * PI / 180);
            y = getPosY() - vAkt * cos(getRotation() * PI / 180);
            pos.x = x - getPosX();
            pos.y = y - getPosY();
            if (!flaga)wyznaczPunkty(angle, pos.x, 0);
            else wyznaczPunkty(angle, pos.x, pos.y);

            setRotation(getRotation() + float(angle));
            return pos;

        }
        void Car::setVAkt(float va) {
            if (va > vMax) vAkt = vMax;
            else if (va < 0) vAkt = 0;
            else vAkt = va;
        }

        float Car::getVAkt() {
            return vAkt;
        }

    }
}
