#include "indycar/logic/drawable.hpp"
#include <cmath>

namespace indycar {
    namespace logic {

        Drawable::Drawable()
        {
            (*this).posX = 0;
            (*this).posY = 0;
            (*this).rotation = 0;
            (*this).heigth = 0;
            (*this).width = 0;
            (*this).texture = "";
            srodekObr = Point(0, 0);
        }
        Drawable::Drawable(const Drawable& el) {
            posX = el.posX;
            posY = el.posY;
            rotation = el.rotation;
            texture = el.texture;
            heigth = el.heigth;
            width = el.width;
            srodekObr = el.srodekObr;

        }
        Drawable::Drawable(float posX, float posY, float rotation, float heigth, float width) {
            (*this).posX = posX;
            (*this).posY = posY;
            (*this).rotation = rotation;
            (*this).heigth = heigth;
            (*this).width = width;
            (*this).texture = "";
        }

        Drawable::Drawable(float posX, float posY, float rotation, float heigth, float width, std::string path) {
            (*this).posX = posX;
            (*this).posY = posY;
            (*this).rotation = rotation;
            (*this).heigth = heigth;
            (*this).width = width;
            (*this).texture = path;
        }

        Drawable::Drawable(float rotation, std::string path) {
            (*this).rotation = rotation;
            (*this).texture = path;
            (*this).posX = 0;
            (*this).posY = 0;
            (*this).heigth = 0;
            (*this).width = 0;
        }

        Drawable::~Drawable()
        {
            //dtor
        }
        void Drawable::setPosition(float x, float y) {
            posX = x;
            posY = y;
        }
        void Drawable::setRotation(float r) {
            rotation = r;
        }
        void Drawable::setTex(std::string path) {
            texture = path;
        }
        void Drawable::setSize(float heigth, float width) {
            (*this).heigth = heigth;
            (*this).width = width;
        }
        float Drawable::getPosX() {
            return posX;
        }
        float Drawable::getPosY() {
            return posY;
        }
        float Drawable::getRotation() {
            return rotation;
        }
        float Drawable::getHeigth() {
            return heigth;
        }
        float Drawable::getWidth() {
            return width;
        }
        std::string Drawable::getTexPath() {
            return texture;
        }
        void Drawable::setSrodekObr(Point pos) {
            srodekObr = pos;
        }
        Point Drawable::getSrodekObr() {
            return srodekObr;
        }

    }
}
