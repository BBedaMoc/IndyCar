#ifndef UCZESTNIK_H
#define UCZESTNIK_H

#include "car.hpp"
class Car;

class Uczestnik
{
public:
    /// Konstruktoe domyśłny.
    Uczestnik();
    /// Konstruktor.
    /**
     * @param modS Modyfikator skrętu.
     * @param modP Modyfikator przyśpieszenia.
     * @param modH Modyfikator hamowania.
     */
    Uczestnik(float modS, float modP, float modH);
    /// Konstruktor.
    /**
     * @param lap Ilość okrążeń do przejechania.
     */
    Uczestnik(int lap);
    /// Konstruktor kopiujący.
    Uczestnik(const Uczestnik& el);
    /// Destruktor.
    virtual ~Uczestnik();
    /// Metoda symulująca fizykę jazdy pojazdu.
    /**
     * Odpowiaa za dynamikę poruszania się pojazdu,
     * Uwzględnia prędkość maksymalną, aktualnie włączony bieg, przyśpieszenie, szybkość hamowania, modyfikatory.
     * Parametry l, p, a, b, su i sd mogą np. pochodzić z klawiatury jako stany wciśnięcia danedo wybranego klawisza.
     * @param l Czy skręt w lewo.
     * @param p Czy skręt w prawo.
     * @param a Czy przyśpieszanie.
     * @param b Czy hamowanie.
     * @param su Czy bieg do góry.
     * @param sd Czy bieg w dół.
     * @param vg Prędkość obserwowanego gracza.
     * @param flaga Czy to wywołanie odnośi się do obserwowanego gracza.
     * @param ang Przyrost kąta obrotu w tej turze.
     * @return  Przemieszczenie środka pojazdu w układzie XY.
     */
    virtual Point jedz(bool l, bool p, bool a, bool b, bool su, bool sd, float &vg, bool flaga, float &ang) = 0;
    /// Pojazd należący do danego uczesnika.
    Car* pojazd;
    /// Flaga aktualizacji tekstury.
    /**
     * true - tekstura zostanie zaktualizowana przy następnej pętli obliczeniowej,
     * false - tekstura nie zostanie zmieniona.
     */
    bool aktualizujTx;
    /// Ustawienie numery referencyjnego pojazdu uczestnika.
    /**
     * Pozwala dostać się do tekstur odpowiedniego referencyjnego auta.
     * @param i Numer referencyjny.
     */
    void setNrAuta(int i);
    /// Ustawienie ilości okrążeń do końca wyścigu.
    /**
     * Po osiągnięciu wartości 0 wyścig się zakończy.
     * @param i Ilość okrążeń.
     * @see getLapToGo()
     */
    void setLapToGo(int i);
    /// Ustawienie numeru aktualnie używanej tekstury.
    /**
     * @param i Numer teksury który ma stać się aktualnym numerem.
     * @see getAktywnaTx()
     */
    void setAktywnaTx(int i);
    /// Ustawienie pozycji uczestnika względem innych uczestników wyścigu.
    /**
     * @param i Ustawiana pozycja.
     * @see getPozycja()
     */
    void setPozycja(int i);
    /// Ustawienie pozycji uczestnika względem aktualnego etapu okrążenia.
    /**
     * Pozwala określić w którym miejscu toru znajduje się uczestnik.
     * @param i Iterator.
     * @see getIter()
     */
    void setIter(float i);
    /// Ustawienie numeru etapu.
    /**
     * Ich ilość zależy od wybranego toru.
     * @param nr Numer etapu.
     * @see getNrEt()
     */
    void setNrEt(int nr);
    /// Zwraca ilość okrążeń do końca.
    /**
     * @return Okrązenia do końca wyścigu.
     * @see setLapToGo()
     */
    int getLapToGo();
    /// Zwraca numer aktualnie używanej tekstury.
    /**
     * @return Aktywna tkstur pojazdu.
     * @see setAktywnaTx()
     */
    int getAktywnaTx();
    /// Zwraca pozycję uczestnika w wyścigu.
    /**
     * @return Pozycja uczestnika.
     * @see setPozycja()
     */
    int getPozycja();
    /// Zwraca położenie uczestnika na torze.
    /**
     * @return Położenie uczestnika na torze.
     * @see setIter()
     */
    float getIter();
    /// Zwraca numer etapu na którym znajduje się obecnie uczestnik.
    /**
     * @return Numer etapu.
     * @see setNrEt()
     */
    int getNrEt();
    /// Ustawia flagę końca wyścigu.
    /**
     * @param w true - koniec, false - jeszcze nie.
     */
    void setKoniecWys(bool w);
    /// Bandy należące do danego uczestnika.
    std::vector <Obstacle *> mojeB;
    /// Tarki należące do danegu uczestnika.
    std::vector <Obstacle *> mojeT;
    /// Zakręt należący do danegu uczestnika.
    std::vector <Obstacle *> zakret;
    /// Bandy na zakręcie należące do danego uczestnika.
    std::vector <Obstacle *> zakB;
    /// Tarki na zakręcie należące do danego uczestnika.
    std::vector <Obstacle *> zakT;
    /// Modyfikator skrętu.
    /**
     * Wpływa na możliwość skrętu pojazdu, modyfikowany przez kolizje z przeszkodami losowymi.
     */
    float modSkretu;
    /// Modyfikator przyśpieszenia.
    /**
     * Wpływa na możliwość skrętu pojazdu, modyfikowany przez kolizje z przeszkodami losowymi.
     */
    float modPrzyspieszenia;
    /// Modyfikator hamowania.
    /**
     * Wpływa na możliwość skrętu pojazdu, modyfikowany przez kolizje z przeszkodami losowymi.
     */
    float modHamowania;
    /// Inicjalizuje elementy mojeB i mojeT.
    /**
     * Tworzone są odpowiednie przeszkody i rozmieszczane w ściśle określonym miejscu wokół pojazdu.
     * @param ref Referencyjn uczetnik, na podstawie którego generowane są tarki i bandy.
     */
    void inicjalizujMojeBT(Uczestnik *ref);
    /// Inicjalizuje elementy mojeB i mojeT.
    /**
     * Tworzone są odpowiednie przeszkody i rozmieszczane w ściśle określonym miejscu wokół pojazdu.
     * @param T Tarki należące do toru.
     * @param B Bandy należące do toru.
     */
    void inicjalizujMojeBT(std::vector <Obstacle*> T, std::vector <Obstacle*> B);
    /// Aktualizuje położenie wszystkich elementów toru należących do danego uczestnika.
    /**
     * Parametry poX i poY powinny pochodzić z moetody "jedz()".
     * @param angle Przyrost kąta obrotu pojadu w tej turze.
     * @param poX Pryrost wzdłuż osi X.
     * @param poY Pryrost wzdłuż osi Y.
     * @param srObr Środek obrotu dla zakrętu.
     * @param zak Flaga obecności uczestnika na zakręcie.
     * @see jedz()
     */
    void aktPosElToru(float angle, float poX, float poY, Point srObr, bool zak);
    /// Wyznacza zakręt.
    /**
     * Każdy uczestnik generuje so bie sam zakręty, ma to swoje dobre i złe strony.
     * Rozpoznawane jest 6 rodzajów zakrętów, L/P - lewy/prawy, 45/90/180 - kąt zakrętu, odpowiednio:
     * L45, L90, L180, P45, P90, P180.
     * @param dl Parametr długości pojedynczego elementu zakrętu.
     * @param rdz Nazwa zakrętu.
     * @param pocz Punkt oczątku zakrętu.
     * @param dokl Ilość elementów składających się na zakręt.
     * @return Zbiór prostokątnych przeszkód tworzących zakręt.
     */
    std::vector <Obstacle *> getZakret(int dl,std::string rdz, Point pocz, int dokl);
    /// Wyznacza środek krzywizny zakrętu.
    /**
     * Aby był sens użycia tej metody, najpierw trzeba wygenerować zakręt.
     * @return Punkt będący środkiem krzywizny zakrętu.
     */
    Point srodekKZak();
    /// Zbiór flag kolizji z elementami toru.
    /**
     * Element 0 - kolizje z innymi uczestnikami,
     * Element 1 - kolizje z tarkami,
     * Element 2 - kolizje z bandami,
     * Element 3 - kolizje z losowymi przeszkodami.
     * Dzięki temu przeszkoda zadaje ibrażenia tylko raz.
     */
    std::vector <std::vector <bool> > kolizja;
    bool koniecWys;
protected:    
    float iter;
    int nrEt;
    int lapToGo;    
    int aktywnaTx;
    int nrAuta;
    int pozycja;

private:
    float minXY(std::vector <Obstacle*> el, float wspX , bool czyX);

};

#endif // UCZESTNIK_H
