#include "indycar/gui/gamewindow.hpp"
#include <sstream>

namespace indycar {
    namespace gui {

        GameWindow::GameWindow()
        {


        }

        GameWindow::GameWindow(std::string path)
        {
            game = new logic::Game(path);
            aktObserUcz = 0;
            game->nowaGra();
            window = new sf::RenderWindow(sf::VideoMode(game->getResX(), game->getResY()), "IndyCar R - " + game->getTrasa()->getNazwaToru());
            window->setFramerateLimit(game->getFrameRate());

        }

        GameWindow::~GameWindow() {
            delete window;
            delete game;
            for (int i = 0; i<int(elTor.size()); i++) {
                for (int j = 0; j<int(elTor[i].size()); j++) {
                    delete elTor[i][j];
                }
                elTor[i].clear();
            }
            elTor.clear();

            for (int i = 0; i<int(cars.size()); i++) {
                delete cars[i];
            }
            cars.clear();

            for (int i = 0; i<int(font.size()); i++) {
                delete font[i];
            }
            font.clear();

            for (int i = 0; i<int(txt.size()); i++) {
                delete txt[i];
            }
            txt.clear();

            for (int i = 0; i<int(wsk.size()); i++) {
                delete wsk[i];
            }
            wsk.clear();

            for (int i = 0; i<int(wsk2.size()); i++) {
                delete wsk2[i];
            }
            wsk2.clear();
        }

        void GameWindow::grajG() {
            inicjalizujElemToru();
            zmienObser(game->obs);
            bool tabW[3]; tabW[0] = 0; tabW[1] = 0; tabW[2] = 0;
            bool pause = false;
            while (window->isOpen())
            {
                sf::Event event;
                while (window->pollEvent(event))
                {
                    if (event.type == sf::Event::Closed) {
                        window->close();

                    }
                }
                bool l = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
                bool p = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
                bool a = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
                bool b = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
                bool su = false;
                bool sd = false;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                    if (!tabW[0]) {
                        su = true;
                        tabW[0] = true;
                    }
                }
                else tabW[0] = false;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                    if (!tabW[1]) {
                        sd = true;
                        tabW[1] = true;
                    }
                }
                else tabW[1] = false;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                    if (!tabW[2]) {
                        if (pause) pause = false;
                        else pause = true;
                        tabW[2] = true;
                    }
                }
                else tabW[2] = false;

                if (!pause) {
                    bool pb = game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->koniecWys;
                    bool pc = game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getVAkt() == 0;
                    if (!(pb && pc)) {
                        game->krokPodstawowy(a, b, l, p, su, sd, aktObserUcz);
                        for (int i = 0; i<int(game->getUczestnicy().size()); i++) {
                            if (game->getUczestnicy()[i]->aktualizujTx) {
                                cars[i]->setTexture(&carsTx[i][game->getUczestnicy()[i]->getAktywnaTx()]);
                                game->getUczestnicy()[i]->aktualizujTx = false;
                            }
                        }
                        aktPolElOkna();
                        piszTekst();
                        wskaznik();
                        rysPodp();



                        window->clear();

                        rysujElemToru();

                        window->display();
                    }
                    else {
                        sf::RectangleShape rect(sf::Vector2f(700, 100));
                        rect.setPosition(sf::Vector2f(0, 220));
                        rect.setFillColor(sf::Color(100, 150, 50));
                        sf::Text text("Finish", *font[1], 90);
                        text.setPosition(sf::Vector2f(180, 210));
                        window->draw(rect);
                        window->draw(text);
                        window->display();
                    }
                }
                else {
                    sf::RectangleShape rect(sf::Vector2f(150, 75));
                    rect.setFillColor(sf::Color(100, 150, 50));
                    sf::Text text("Pause", *font[1], 50);
                    window->draw(rect);
                    window->draw(text);
                    window->display();

                }
            }
        }

        void GameWindow::rysujElemToru() {
            if (game->getTrasa()->getEtNz()[game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->getNrEt()] == "S") {
                for (int i = 0; i<int(elTor.size()); i++) {
                    for (int j = 0; j<int(elTor[i].size()); j++) {
                        window->draw(*elTor[i][j]);
                    }
                    if (i == 1 && (game->getTrasa()->getEtNz()[(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->getNrEt() + 1) % int(game->getTrasa()->getEtNz().size())] != "S")) {
                        if (game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->getIter() >= game->getTrasa()->getEtDl()[game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->getNrEt()] - 2000) {
                            if (zakret.size() != 0) {
                                for (int i = 0; i<int(zakret.size()); i++) {
                                    window->draw(zakret[i]);
                                }
                            }
                        }
                    }
                }
            }
            else {
                for (int i = 0; i<int(elTor.size()); i++) {
                    if (i != 1 && i != 2 && i != 3) {
                        for (int j = 0; j<int(elTor[i].size()); j++) {
                            window->draw(*elTor[i][j]);
                        }
                    }
                    else {
                        for (int i = 0; i<int(zakret.size()); i++) {
                            window->draw(zakret[i]);
                        }

                    }
                }

            }
            for (int i = 0; i<int(cars.size()); i++) {
                window->draw(*cars[i]);
            }
            sf::RectangleShape p(sf::Vector2f(260, 560));
            p.setPosition(sf::Vector2f(700, 0));
            p.setFillColor(sf::Color::Black);
            window->draw(p);
            for (int i = 0; i<int(txt.size()); i++) {
                window->draw(*txt[i]);
            }
            for (int i = 0; i<int(wsk.size()); i++) {
                window->draw(*wsk[i]);
            }
            for (int i = 0; i<int(wsk2.size()); i++) {
                window->draw(*wsk2[i]);
            }
        }

        void GameWindow::inicjalizujElemToru() {
            std::vector <sf::RectangleShape*> pom1;
            sf::RectangleShape* trawa = new sf::RectangleShape(sf::Vector2f(game->getResX() - 260, game->getResY()));
            trawa->setOrigin(0, 0);
            trawa->setPosition(0, 0);
            sf::Texture tx;
            std::vector <sf::Texture> pomTx;
            tx.loadFromFile(game->getTrasa()->getTexPath()[9]);
            pomTx.push_back(tx);
            elTorTx.push_back(pomTx);
            pom1.push_back(trawa);
            elTor.push_back(pom1);
            std::vector <sf::RectangleShape*> pom2;
            sf::Texture tx2;
            std::vector <sf::Texture> pomTx2;
            tx2.loadFromFile(game->getTrasa()->getTexPath()[7]);
            pomTx2.push_back(tx2);
            elTorTx.push_back(pomTx2);
            for (int i = 0; i < 3; i++) {
                sf::RectangleShape* droga = new sf::RectangleShape(sf::Vector2f(game->getResX() - 510, game->getResY()));
                droga->setOrigin(0, 0);
                droga->setPosition(125, 0 - i * game->getResY());
                pom2.push_back(droga);
            }
            elTor.push_back(pom2);
            std::vector <sf::RectangleShape*> pom3;
            sf::Texture tx3;
            std::vector <sf::Texture> pomTx3;
            tx3.loadFromFile(game->getTrasa()->getTexPath()[1]);
            pomTx3.push_back(tx3);
            elTorTx.push_back(pomTx3);
            for (int i = 0; i<int(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->mojeT.size()); i++) {
                sf::RectangleShape* tarka = new sf::RectangleShape(sf::Vector2f(25, 100));
                tarka->setOrigin(0, 0);
                tarka->setPosition(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->mojeT[i]->getPosX(), game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->mojeT[i]->getPosY());
                pom3.push_back(tarka);
            }
            elTor.push_back(pom3);
            std::vector <sf::RectangleShape*> pom4;
            sf::Texture tx4;
            std::vector <sf::Texture> pomTx4;
            tx4.loadFromFile(game->getTrasa()->getTexPath()[0]);
            pomTx4.push_back(tx4);
            elTorTx.push_back(pomTx4);
            for (int i = 0; i<int(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->mojeB.size()); i++) {
                sf::RectangleShape* banda = new sf::RectangleShape(sf::Vector2f(50, 75));
                banda->setOrigin(0, 0);
                banda->setPosition(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->mojeB[i]->getPosX(), game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->mojeB[i]->getPosY());
                pom4.push_back(banda);
            }
            elTor.push_back(pom4);
            std::vector <sf::RectangleShape*> pom5, pom6;
            std::vector <sf::Texture> pomTx5;
            for (int i = 0; i < 5; i++) {
                sf::Texture txpo;
                txpo.loadFromFile(game->getTrasa()->getTexPath()[2 + i]);
                pomTx5.push_back(txpo);
            }
            elTorTx.push_back(pomTx5);
            std::vector <sf::Texture> pomTx6;
            for (int i = 0; i < 2; i++) {
                sf::Texture* txpo = new sf::Texture;
                txpo->loadFromFile(game->getTrasa()->getTexPath()[10 + i]);
                pomTx6.push_back(*txpo);
            }
            sf::Texture start;
            start.loadFromFile(game->getTrasa()->getTexPath()[8]);
            pomTx6.push_back(start);
            elTorTx.push_back(pomTx6);
            sf::RectangleShape* st = new sf::RectangleShape(sf::Vector2f(game->getResX() - 510, 50));
            pom6.push_back(st);
            elTor.push_back(pom5);
            elTor.push_back(pom6);
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j<int(elTor[i].size()); j++) {
                    elTor[i][j]->setTexture(&elTorTx[i][0]);
                }
            }


            for (int i = 0; i<int(game->getUczestnicy().size()); i++) {
                sf::RectangleShape* car = new sf::RectangleShape(sf::Vector2f(52, 130));
                car->setOrigin(game->getUczestnicy()[i]->pojazd->getSrodekObr().x, game->getUczestnicy()[i]->pojazd->getSrodekObr().y);
                car->setPosition(game->getUczestnicy()[i]->pojazd->getPosX(), game->getUczestnicy()[i]->pojazd->getPosY());
                sf::Texture tx5, tx6, tx7;
                tx5.loadFromFile(game->getUczestnicy()[i]->pojazd->texture[0]);
                tx6.loadFromFile(game->getUczestnicy()[i]->pojazd->texture[1]);
                tx7.loadFromFile(game->getUczestnicy()[i]->pojazd->texture[2]);
                std::vector <sf::Texture> pomTx6;
                pomTx6.push_back(tx5);
                pomTx6.push_back(tx6);
                pomTx6.push_back(tx7);
                carsTx.push_back(pomTx6);
                game->getUczestnicy()[i]->aktualizujTx = false;
                cars.push_back(car);
            }
            for (int i = 0; i<int(cars.size()); i++) {
                cars[i]->setTexture(&carsTx[i][2]);
            }
            sf::Font* f1, * f2;
            f1 = new sf::Font();
            f2 = new sf::Font();
            f1->loadFromFile(game->getTrasa()->getTexPath()[12]);
            f2->loadFromFile(game->getTrasa()->getTexPath()[13]);
            font.push_back(f1);
            font.push_back(f2);


            elTor[5][0]->setPosition(125, game->getUczestnicy()[0]->pojazd->getPosY() - 100);
            elTor[5][0]->setTexture(&elTorTx[5][2]);

        }



        void GameWindow::aktPolElOkna() {
            for (int i = 0; i<int(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->mojeB.size()); i++) {
                elTor[3][i]->setPosition(sf::Vector2f(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->mojeB[i]->getPosX(), game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->mojeB[i]->getPosY()));
            }
            for (int i = 0; i<int(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->mojeT.size()); i++) {
                elTor[2][i]->setPosition(sf::Vector2f(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->mojeT[i]->getPosX(), game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->mojeT[i]->getPosY()));
            }
            for (int i = 0; i<int(game->getLosowePrz().size()); i++) {
                if (i == 0) {
                    for (int j = 0; j<int(elTor[4].size()); j++) {
                        delete elTor[4][j];
                    }
                    elTor[4].clear();
                }
                sf::RectangleShape* pom = new sf::RectangleShape(sf::Vector2f(game->getLosowePrz()[i]->getWidth(), game->getLosowePrz()[i]->getHeigth()));
                pom->setPosition(sf::Vector2f(game->getLosowePrz()[i]->getPosX(), game->getLosowePrz()[i]->getPosY()));
                elTor[4].push_back(pom);
                elTor[4][i]->setTexture(&elTorTx[4][game->ktoraTxEv(game->getLosowePrz()[i])]);
            }
            if (((game->getUczestnicy()[int(game->getUczestnicy().size()) - 1 - aktObserUcz]->getNrEt() == (int(game->getTrasa()->getEtDl().size()) - 1))) && (game->getUczestnicy()[int(game->getUczestnicy().size()) - 1 - aktObserUcz]->getIter() / 5 > (game->getTrasa()->getEtDl()[game->getTrasa()->getEtDl().size() - 1] / 5 - 500))) {
                elTor[5][0]->setPosition(sf::Vector2f(125, game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getPosY() - (game->getTrasa()->getEtDl()[game->getTrasa()->getEtDl().size() - 1]) + game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->getIter()));

            }

            else   elTor[5][0]->setPosition(sf::Vector2f(125, game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getVAkt() / 5 + elTor[5][0]->getPosition().y));

            for (int i = 0; i<int(cars.size()); i++) {
                cars[i]->setPosition(game->getUczestnicy()[i]->pojazd->getPosX(), game->getUczestnicy()[i]->pojazd->getPosY());
                cars[i]->setRotation(game->getUczestnicy()[i]->pojazd->getRotation());
            }
            if (game->getTrasa()->getEtNz()[game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->getNrEt()] == "S") {
                if (elTor.size() >= 8) {
                    for (int i = 0; i<int(elTor[7].size()); i++) {
                        delete elTor[7][i];
                    }
                    elTor[7].clear();
                    elTor.pop_back();
                    for (int i = 0; i<int(elTor[6].size()); i++) {
                        delete elTor[6][i];
                    }
                    elTor[6].clear();
                    elTor.pop_back();
                }
                for (int i = 0; i<int(elTor[1].size()); i++) {
                    if ((game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getVAkt() / 5 + elTor[1][i]->getPosition().y) > 560)
                        elTor[1][i]->setPosition(sf::Vector2f(125, (game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getVAkt()) / 5 + elTor[1][i]->getPosition().y - 1100));
                    else elTor[1][i]->setPosition(sf::Vector2f(125, (game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getVAkt()) / 5 + elTor[1][i]->getPosition().y));
                    if (i == 1 && (game->getTrasa()->getEtNz()[(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->getNrEt() + 1) % int(game->getTrasa()->getEtNz().size())] != "S")) {
                        if (game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->getIter() >= game->getTrasa()->getEtDl()[game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->getNrEt()] - 2000) {
                            if (int(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->zakret.size()) != 0) {
                                zakret.clear();
                                for (int i = 0; i<int(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->zakret.size()); i++) {
                                    sf::RectangleShape pom(sf::Vector2f(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->zakret[i]->getWidth(), game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->zakret[i]->getHeigth()));
                                    pom.setPosition(sf::Vector2f(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->zakret[i]->getPosX(), game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->zakret[i]->getPosY()));
                                    pom.setOrigin(sf::Vector2f(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->zakret[i]->getSrodekObr().x, game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->zakret[i]->getSrodekObr().y));
                                    pom.setRotation(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->zakret[i]->getRotation());
                                    zakret.push_back(pom);
                                    zakret[i].setTexture(&elTorTx[1][0]);
                                }
                            }
                        }
                    }
                }
            }
            else {
                zakret.clear();
                for (int i = 0; i<int(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->zakret.size()); i++) {
                    sf::RectangleShape pom(sf::Vector2f(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->zakret[i]->getWidth(), game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->zakret[i]->getHeigth()));
                    pom.setPosition(sf::Vector2f(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->zakret[i]->getPosX(), game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->zakret[i]->getPosY()));
                    pom.setOrigin(sf::Vector2f(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->zakret[i]->getSrodekObr().x, game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->zakret[i]->getSrodekObr().y));
                    pom.setRotation(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->zakret[i]->getRotation());
                    zakret.push_back(pom);
                    zakret[i].setTexture(&elTorTx[1][0]);
                }
                if (elTor.size() >= 8) {
                    for (int i = 0; i<int(elTor[7].size()); i++) {
                        delete elTor[7][i];
                    }
                    elTor[7].clear();
                    elTor.pop_back();
                    for (int i = 0; i<int(elTor[6].size()); i++) {
                        delete elTor[6][i];
                    }
                    elTor[6].clear();
                    elTor.pop_back();
                }
                std::vector <sf::RectangleShape*> B;
                for (int i = 0; i<int(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->zakT.size()); i++) {
                    sf::RectangleShape* pom = new sf::RectangleShape(sf::Vector2f(25, 100));
                    pom->setPosition(sf::Vector2f(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->zakT[i]->getPosX(), game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->zakT[i]->getPosY()));
                    pom->setRotation(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->zakT[i]->getRotation());
                    B.push_back(pom);
                    B[i]->setTexture(&elTorTx[2][0]);
                }
                elTor.push_back(B);
                std::vector <sf::RectangleShape*> C;
                for (int i = 0; i<int(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->zakB.size()); i++) {
                    sf::RectangleShape* pom = new sf::RectangleShape(sf::Vector2f(50, 75));
                    pom->setPosition(sf::Vector2f(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->zakB[i]->getPosX(), game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->zakB[i]->getPosY()));
                    pom->setRotation(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->zakB[i]->getRotation());
                    C.push_back(pom);
                    C[i]->setTexture(&elTorTx[3][0]);
                }
                elTor.push_back(C);
            }
        }

        std::string GameWindow::float2string(float lb, int prec) {
            std::stringstream stream;
            stream.precision(prec);
            stream << lb;
            return stream.str();
        }

        void GameWindow::piszTekst() {
            if (int(txt.size()) == 0) {
                std::string pom = float2string(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getVAkt(), 4);
                sf::Text* tx1 = new sf::Text(pom, *font[0], 60);
                tx1->setPosition(sf::Vector2f(750, 450));
                txt.push_back(tx1);
                sf::Text* tx2 = new sf::Text(float2string(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getAktBieg(), 1), *font[0], 60);
                tx2->setPosition(sf::Vector2f(900, 370));
                txt.push_back(tx2);
                pom = float2string(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getTireCon(), 3);
                pom = pom + "%";
                sf::Text* tx3 = new sf::Text(pom, *font[0], 50);
                tx3->setPosition(sf::Vector2f(850, 240));
                txt.push_back(tx3);
                pom = float2string(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getEngineCon(), 3);
                pom = pom + "%";
                sf::Text* tx4 = new sf::Text(pom, *font[0], 50);
                tx4->setPosition(sf::Vector2f(850, 300));
                txt.push_back(tx4);
                sf::Text* tx5 = new sf::Text(" km/h", *font[0], 30);
                tx5->setPosition(sf::Vector2f(880, 480));
                txt.push_back(tx5);
                //
                sf::Text* tx6 = new sf::Text(float2string(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->getLapToGo(), 2), *font[1], 50);
                tx6->setPosition(sf::Vector2f(890, 130));
                txt.push_back(tx6);
                sf::Text* tx7 = new sf::Text("Laps to go:", *font[1], 25);
                tx7->setPosition(sf::Vector2f(710, 140));
                txt.push_back(tx7);
                sf::Text* tx8 = new sf::Text(float2string(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->getPozycja(), 2), *font[1], 70);
                tx8->setPosition(sf::Vector2f(860, 30));
                txt.push_back(tx8);
                sf::Text* tx9 = new sf::Text("Pozycja: ", *font[1], 30);
                tx9->setPosition(sf::Vector2f(710, 50));
                txt.push_back(tx9);
            }
            else {
                txt[0]->setString(float2string(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getVAkt(), 4));
                txt[1]->setString(float2string(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getAktBieg(), 1));
                std::string pom = float2string(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getTireCon(), 3);
                pom = pom + "%";
                txt[2]->setString(pom);
                pom = float2string(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getEngineCon(), 3);
                pom = pom + "%";
                txt[3]->setString(pom);
                txt[5]->setString(float2string(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->getLapToGo(), 2));
                txt[7]->setString(float2string(game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->getPozycja(), 2));
            }

        }

        void GameWindow::wskaznik() {
            if (int(wsk.size()) == 0) {
                sf::RectangleShape* r1, * r2, * r3, * r4, * i1, * i2, * i3, * i4;
                r1 = new sf::RectangleShape(sf::Vector2f(20, 40));
                r1->setPosition(sf::Vector2f(750, 390));
                r2 = new sf::RectangleShape(sf::Vector2f(20, 40));
                r2->setPosition(sf::Vector2f(770, 390));
                r3 = new sf::RectangleShape(sf::Vector2f(20, 40));
                r3->setPosition(sf::Vector2f(790, 390));
                r4 = new sf::RectangleShape(sf::Vector2f(20, 40));
                r4->setPosition(sf::Vector2f(810, 390));

                i1 = new sf::RectangleShape(sf::Vector2f(40, 40));
                i1->setPosition(sf::Vector2f(770, 250));
                i2 = new sf::RectangleShape(sf::Vector2f(40, 40));
                i2->setPosition(sf::Vector2f(770, 250));
                i3 = new sf::RectangleShape(sf::Vector2f(40, 40));
                i3->setPosition(sf::Vector2f(770, 310));
                i4 = new sf::RectangleShape(sf::Vector2f(40, 40));
                i4->setPosition(sf::Vector2f(770, 310));
                wsk.push_back(r1);
                wsk.push_back(r2);
                wsk.push_back(r3);
                wsk.push_back(r4);
                wsk.push_back(i1);
                wsk.push_back(i2);
                wsk.push_back(i3);
                wsk.push_back(i4);
                wsk[5]->setTexture(&elTorTx[5][1]);
                wsk[7]->setTexture(&elTorTx[5][0]);
            }

            if (int(wsk2.size()) == 0) {
                sf::ConvexShape* c1, * c2;
                c1 = new sf::ConvexShape(3);
                c2 = new sf::ConvexShape(3);
                c1->setPoint(0, sf::Vector2f(715, 395));
                c1->setPoint(1, sf::Vector2f(735, 395));
                c1->setPoint(2, sf::Vector2f(725, 425));
                c2->setPoint(0, sf::Vector2f(845, 425));
                c2->setPoint(1, sf::Vector2f(865, 425));
                c2->setPoint(2, sf::Vector2f(855, 395));
                wsk2.push_back(c1);
                wsk2.push_back(c2);
            }

            if (game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getTireCon() <= 50 && game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getTireCon() > 25)
                wsk[4]->setFillColor(sf::Color::Yellow);
            else if (game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getTireCon() <= 25)
                wsk[4]->setFillColor(sf::Color::Red);
            else
                wsk[4]->setFillColor(sf::Color::Green);

            if (game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getEngineCon() <= 50 && game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getEngineCon() > 25)
                wsk[6]->setFillColor(sf::Color::Yellow);
            else if (game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getEngineCon() <= 25)
                wsk[6]->setFillColor(sf::Color::Red);
            else
                wsk[6]->setFillColor(sf::Color::Green);

            float x = (game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getVmax() /
                game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getLBiegow()) / 4;
            float u = (game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getVmax() /
                game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getLBiegow() *
                (game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getAktBieg() - 1));
            if (game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getVAkt() < u)
                wsk2[0]->setFillColor(sf::Color::Yellow);
            else
                wsk2[0]->setFillColor(sf::Color::Black);
            if (game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getVAkt() >= u + 4 * x) {
                if (game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getAktBieg() != game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getLBiegow())
                    wsk2[1]->setFillColor(sf::Color::Yellow);
            }
            else
                wsk2[1]->setFillColor(sf::Color::Black);
            if (game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getVAkt() >= u)
                wsk[0]->setFillColor(sf::Color::Green);
            else
                wsk[0]->setFillColor(sf::Color::Black);
            if (game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getVAkt() >= u + x)
                wsk[1]->setFillColor(sf::Color::Green);
            else
                wsk[1]->setFillColor(sf::Color::Black);
            if (game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getVAkt() >= u + 2 * x)
                wsk[2]->setFillColor(sf::Color::Yellow);
            else
                wsk[2]->setFillColor(sf::Color::Black);
            if (game->getUczestnicy()[game->getUczestnicy().size() - 1 - aktObserUcz]->pojazd->getVAkt() >= u + 3 * x)
                wsk[3]->setFillColor(sf::Color::Red);
            else
                wsk[3]->setFillColor(sf::Color::Black);

        }

        void GameWindow::rysPodp() {
            if (int(wsk2.size()) > 2) {
                for (int i = int(wsk2.size()) - 1; i >= 2; i--) {
                    delete wsk2[i];
                    wsk2.pop_back();
                }
            }
            for (int i = 0; i<int(game->getLosowePrz().size()); i++) {
                if (game->getLosowePrz()[i]->getPosY() < (0 - game->getLosowePrz()[i]->getHeigth() / 2)) {
                    sf::ConvexShape* pom;
                    pom = new sf::ConvexShape(4);
                    pom->setPoint(0, sf::Vector2f(game->getLosowePrz()[i]->getPosX() + game->getLosowePrz()[i]->getWidth() / 2, 20));
                    pom->setPoint(1, sf::Vector2f(game->getLosowePrz()[i]->getPosX() - 15 + game->getLosowePrz()[i]->getWidth() / 2, 35));
                    pom->setPoint(2, sf::Vector2f(game->getLosowePrz()[i]->getPosX() + game->getLosowePrz()[i]->getWidth() / 2, 5));
                    pom->setPoint(3, sf::Vector2f(game->getLosowePrz()[i]->getPosX() + 15 + game->getLosowePrz()[i]->getWidth() / 2, 35));
                    pom->setFillColor(sf::Color(255, 152, 105));
                    wsk2.push_back(pom);
                }
            }
        }

        void GameWindow::zmienObser(int wyb) {
            if (wyb >= 0 && wyb<int(game->getUczestnicy().size())) {
                if (wyb != aktObserUcz) {
                    float poY = (4 * game->getResY()) / 5 - game->getUczestnicy()[int(game->getUczestnicy().size()) - wyb - 1]->pojazd->getPosY();
                    for (int i = 0; i<int(game->getUczestnicy().size()); i++) {
                        game->getUczestnicy()[i]->pojazd->wyznaczPunkty(0, 0, poY);
                        for (int j = 0; j<int(game->getUczestnicy()[i]->mojeB.size()); j++) {
                            game->getUczestnicy()[i]->mojeB[j]->wyznaczPunkty(0, 0, poY);
                        }
                        for (int j = 0; j<int(game->getUczestnicy()[i]->mojeT.size()); j++) {
                            game->getUczestnicy()[i]->mojeT[j]->wyznaczPunkty(0, 0, poY);
                        }
                    }
                    for (int i = 0; i<int(game->getLosowePrz().size()); i++) {
                        game->getLosowePrz()[i]->wyznaczPunkty(0, 0, poY);
                    }
                    aktObserUcz = wyb;
                }
            }
        }

    }
}

