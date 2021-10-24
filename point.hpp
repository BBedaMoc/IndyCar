#ifndef POINT_H
#define POINT_H

/// Wartość liczy Pi wykożystywana do obliczeń.
const double PI=3.141592653589793238462643383279;

class Point
{
public:
    /// Konstruktor domyślny.
    Point();
    /// Destruktor.
    ~Point();
    /// Współrzędna położenia X.
    double x;
    /// Współrzędna położenia Y.
    double y;
    /// Konstruktor.
    /**
     * @param x Współrzędna położenia X.
     * @param y Współrzędna położenia Y.
     */
    Point(double x, double y);
    /// Operator przypisania.
    Point& operator=(const Point& x);
    /// Obrót punktu o kąt względem pewnego punktu.
    /**
     * @param el Punkt względem ktorego obracamy.
     * @param angle Kąt obrotu.
     */
    void obrot(const Point el, float angle);

};

#endif  //  POINT_H
