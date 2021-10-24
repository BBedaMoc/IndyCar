#ifndef CAR_H
#define CAR_H

#include "obstacle.hpp"

class Gracz;
class Boot;

class Car : public Obstacle
{
    friend class Gracz;
    friend class Boot;

public:
    /// Konstuktor domyślny.
    /**
      Tworzy obiekt domyślny, wszystkie parametry ustaiwiane na zero, oprócz:
      engineCon = 100%
      tireCon = 100%
    */
    Car();
    /// Konstuktor kopiujacy.
    /**
    *@param el kopiowany element
    */
    Car(const Car &el);
    /// Destruktor.
     ~Car();
    /// Zmiana wartości przyśieszenia.
    /**
    * Im wyższa wartość to pojazd szybciej osiąga prędkość maksymalną.
    * Podana wartość ma być większa od 0.
    * @param Acc nowe rządane przyśpieszenie obiektu.
    * @see getAcc()
    * @see setDcc()
    * @see getDcc()
    */
    void setAcc(float Acc);
    /// Zmiana szybkości hamowania.
    /**
    * Im wyższa wartość to pojazd szybciej wytraca szybkość podczas hamowania.
    * Podana wartość ma być większa od 0.
    * @param Dcc nowa rządana szybkość hamowania obiektu.
    * @see getDcc()
    * @see getAcc()
    * @see setAcc()
    */
    void setDcc(float Dcc);
    /// Zmiana liczby biegów pojazdu.
    /**
    * Podana wartość ma być większa od 0.
    *@param LB nowa liczba biegów.
    */
    void setLBiegow(int LB);
    /// Zmiana aktualnego biegu.
    /**
    *@param AkB nowy rządany bieg.
    */
    void setAkBieg(int AkB);
    /// Zmiana aktualnego biegu o 1 do góry.
    /**
    * Tylko wtedy gdy nie zostanie osiągnięty limit biegów określony przez liczbę biegów.
    * @see setLBiegow()
    * @see getLBiegow()
    */
    void shiftUp();
    /// Zmiana aktualnego biegu o 1 w dół.
    /**
    * Tylko wtedy gdy nie zostanie osiągnięty bieg 0.
    * @see setLBiegow()
    * @see getLBiegow()
    */
    void shiftDown();
    /// Zmiana stanu silnika.
    /**
    * Stan silnika w %, wartość wpisana będzie z przediału <0,100> %.
    * @param EC wpisywana wartość.
    * @see getEngineCon()
    */
    void setEngineCon(float EC);
    /// Zmiana stanu opon.
    /**
     * Stan opon pojazdu w %, wartość wpisana będzie z przedziału <0,100> %.
     * @param TC wpisywana wartość.
     * @see getTireCon()
     */
    void setTireCon(float TC);
    /// Zmiana maksymalnej prędkości pojazdu.
    /**
     * @param vmax Prędkość maksymalna w km/h.
     * @see getVmax()
     */
    void setVmax(float vmax);
    /// Zmiana prędkości aktualnej pojazdu.
    /**
     * Nie da wpisać się wartości większej od vMax i mniejszej od 0.
     * @param va Nowa prędkość aktualna w km/h.
     * @see getVAkt()
     */
    void setVAkt(float va);
    /// Pobranie wartości przyśpieszenia.
    /**
     * @return Zwracany jest współczynnik przyśpieszenia pojazdu.
     * @see setAcc()
     */
    float getAcc();
    /// Pobranie wartości szybkości hamowania.
    /**
     * @return Zwracany jest współczynnik szybkości hamowania pojazdu.
     * @see setDcc()
     */
    float getDcc();
    /// Pobranie ilości biegów dostępnej dla tego pojazdu.
    /**
     * @return Zwracany jest maksymalny bieg licząc od 0.
     * @see setLBiegow()
     */
    int getLBiegow();
    /// Pobranie aktualnego biegu.
    /**
     * @return Zwracany jest aktualny bieg który włączony jest w pojeździe.
     * @see setAkBieg()
     */
    int getAktBieg();
    /// Zwraca stan silnika.
    /**
     * Stan silnika przekłada się bepośrednio na osiągi pojazdu - prędkość maksymalną i przyśpieszenie.
     * @return Zwraca stan silnika.
     * @see setEngineCon()
     */
    float getEngineCon();
    /// Zwraca stan opon pojazdu.
    /**
     * Stan opon przekłąda się na czułość pojazdu przy skręcaniu.
     * @return Zwraca stan odumienia.
     * @see setTireCon()
     */
    float getTireCon();
    /// Zwraca wartość maksymalnej prędkości pojazdu.
    /**
     * Pomimo niezmienności tego parametru podczas wyścigu, prędkosć maksymalna
     * może nie zostać osiągnięta ze względu na zbyt poważne uszkodzenia silnika.
     * @return Zwraca ustawiną wartość prędkości maksymalnej.
     * @see setVmax()
     */
    float getVmax();
    /// Zwraca aktualną prędkosć pojazdu.
    /**
     * @return Prędkość z jaką aktualnie porusza się pojazd.
     * @see setVAkt()
     */
    float getVAkt();
    /// Zwraca przemieszczenie pojazdu w danej turze obliczeń.
    /**
     * Wyznacza przemieszczenie pojazdu na podstawie podanych parametrów oraz własnej prędkości aktualnej,
     * Aktualizuje punkty narożne obiektu, położenie środka oraz aktualną rotację obiektu.
     * @param angle Zmiana kątu obrotu pojazdu.
     * @param flaga Flaga sterująca: true - obliczenia dotyczą obesrwowanego gracza, false - innego.
     * @param vg Prędkość aktualna aktualnie obserwowanego gracza w danej turze.
     * @return Przemieszczenie środka obrot pojazdu w ukłądzie XY.
     */
    Point naWprost(double angle, bool flaga, float vg);
    /// Ścieżki dostępu do tekstur pojazdu.
    /**
     * Tekstury w kolejności: skręt w lewo; skręt w prawo ; jazda na wprost
     */
    std::vector <std::string> texture;

private:
    float acc;    //Przyśpieszenie
    float dcc;    //Hamulce
    int lBiegow; //Ilosć biegów
    int aktBieg; //Aktualnie wybrany bieg
    float engineCon; //stan silnika
    float tireCon; //stan opon
    float vMax;  //pr. max
    float vAkt;

};

#endif // CAR_H
