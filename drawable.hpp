#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <string>
#include "point.hpp"

class Drawable
{
    public:        
        Drawable();        
        Drawable(const Drawable& el);
        /// Konstruktor.
        /**
         * @param posX Położenie po osi X.
         * @param posY Położenie po osi Y.
         * @param rotation Kąt obrotu.
         * @param heigth Wysokość.
         * @param width Szerokość.
         */
        Drawable(float posX, float posY, float rotation, float heigth, float width);
        /// Konstruktor.
        /**
         * @param posX Położenie po osi X.
         * @param posY Położenie po osi Y.
         * @param rotation Kąt obrotu.
         * @param heigth Wysokość.
         * @param width Szerokość.
         * @param path Ścieżka do pliku tekstury.
         */
        Drawable(float posX, float posY, float rotation, float heigth, float width, std::string path);
        /// Konstruktor.
        /**
         * @param rotation Kąt obrotu.
         * @param path Ścieżka do pliku tekstury.
         */
        Drawable(float rotation, std::string path);
        
        ~Drawable();
        /// Ustawienie pozycji.
        /**
         * @param x Pozycja wzdłuż osi X.
         * @param y Pozycja wzdłuż osi Y.
         * @see getPosX()
         * @see getPosY()
         */
        void setPosition(float x, float y);
        /// Ustawienie rotacji obiektu.
        /**
         * @param r Zadan rotacja w deg.
         * @see getRotation()
         */
        void setRotation(float r);
        /// Ustawienie ścieżki do pliku tekstury.
        /**
         * @param path Ścieżka.
         * @see getTexPath()
         */
        void setTex(std::string path);
        /// Ustawienie wymiarów obiektu.
        /**
         * @param heigth Wysokość
         * @param width Szerokość.
         * @see getHeigth()
         * @see getWidth()
         */
        void setSize(float heigth, float width);
        /// Ustawienie środka obrotu we współrzędnych obiektu.
        /**
         * @param pos Środek obrotu.
         * @see getSrodekObr()
         */
        void setSrodekObr(Point pos);
        /// Zwraca położenie wzdłuż osi X.
        /**
         * @return Położenie po osi X.
         * @see getPosY()
         * @see setPosition()
         */
        float getPosX();
        /// Zwraca położenie wzdłuż osi Y.
        /**
         * @return Położenie po osi Y.
         * @see getPosX()
         * @see setPosition()
         */
        float getPosY();
        /// Zwraca kąt obrotu obiektu.
        /**
         * @return Kąt obrotu w deg.
         * @see setRotation()
         */
        float getRotation();
        /// Zwraca wysokość obiektu.
        /**
         * @return Wysokość obiektu.
         * @see getWidth()
         * @see setSize()
         */
        float getHeigth();
        /// Zwraca szerokość obiektu.
        /**
         * @return Szerokość obiektu.
         * @see getHeigth()
         * @see setSize()
         */
        float getWidth();
        /// Zwraca środek obrotu.
        /**
         * @return Środk obrotu we współrzędnych obiektu.
         * @see setSrodekObr()
         */
        Point getSrodekObr();
        /// Zwraca ścieżkę do pliku tekstury.
        /**
         * @return Ścieżka do pliku tekstury.
         */
        std::string getTexPath();

    protected:
    private:
        float posX;//Pozyja srodka w ukł globalnym
        float posY;
        float rotation;
        std::string texture;
        float width;
        float heigth;
        Point srodekObr;

};

#endif // DRAWABLE_H
