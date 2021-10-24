// IndiCar.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "indycar/gui/gamewindow.hpp"

int main()
{
    indycar::gui::GameWindow okno("IndyData\\config.cfg");
    okno.grajG();

    return EXIT_SUCCESS;
}
