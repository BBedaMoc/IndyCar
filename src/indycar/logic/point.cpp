#include "indycar/logic/point.hpp"
#include <cmath>

namespace indycar {
    namespace logic {

        Point::Point()
        {
            x = 0;
            y = 0;
        }
        Point::Point(double x, double y) {
            (*this).x = x;
            (*this).y = y;
        }
        Point& Point::operator=(const Point& x) {
            (*this).x = x.x;
            (*this).y = x.y;
            return *this;
        }

        void Point::obrot(const Point el, float angle) {
            double pomX = x;
            double pomY = y;
            if (angle) {
                pomX = ((x - el.x) * cos(angle * PI / 180) - (y - el.y) * sin(angle * PI / 180) + el.x);
                pomY = ((x - el.x) * sin(angle * PI / 180) + (y - el.y) * cos(angle * PI / 180) + el.y);
            }
            x = pomX;
            y = pomY;
        }
        Point::~Point() {

        }

    }
}

