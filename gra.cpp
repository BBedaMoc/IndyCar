#include "gra.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <cmath>

Gra::Gra()
{
    trasa=0;
    liczbaGraczy=0;

}
Gra::~Gra(){
    delete trasa;
    for(int i=int(uczestnicy.size()-1);i>=0;i--){
        delete uczestnicy[i];
        uczestnicy.pop_back();
    }
    for(int i=int(refAuta.size()-1);i>=0;i--){
        delete refAuta[i];
        refAuta.pop_back();
    }
    for(int i=int(refTrasy.size()-1);i>=0;i--){
        delete refTrasy[i];
        refTrasy.pop_back();
    }
    for(int i=int(losowePrz.size()-1);i>=0;i--){
        delete losowePrz[i];
        losowePrz.pop_back();
    }
}

Gra::Gra(std::string param) {
    ladujCfg(param);
    ladujAuta(pathAuta+"\\auta.cfg");
    ladujTrasy(pathTrasy+"\\trasy.cfg");
    Track * tr=getRefTrasy()[defaultTor];
    trasa=new Track(0,0,0,tr->getNazwaToru(),tr->getTexPath(),tr->getEtDl(),tr->getEtNz());
}

void Gra::dodaUczestnika(Uczestnik * pom){
    uczestnicy.push_back(pom);
}


void Gra::ladujAuta(std::string param){
    std::ifstream wej;
    wej.open(param.c_str());
    wej.seekg(0,wej.beg);
    if(wej.good()){
        while(!wej.eof()){
            std::string pom;
            Car* autom=new Car();
            wej>>pom;

                std::string pom2;
                float pom3;
                for (int i=0;i<3;i++){
                    wej>>pom2;
                    wej>>pom2;
                    autom->texture.push_back(pathAuta+pom2);
                }
                for (int i=0;i<6;i++){
                    wej>>pom2;
                    wej>>pom3;
                    if(pom2=="przyspieszenie") autom->setAcc(pom3);
                    else if(pom2=="hamowanie") autom->setDcc(pom3);
                    else if(pom2=="ilosc_biegow") autom->setLBiegow(pom3);
                    else if(pom2=="v_max") autom->setVmax(pom3);
                    else if(pom2=="engine_dmg") autom->setEngineDmg(pom3);
                    else if(pom2=="tire_dmg")autom->setTireDmg(pom3);
                    else {}                }
                autom->setCross(false);


                refAuta.push_back(autom);

        }
    }
    wej.close();
}
void Gra::ladujCfg(std::string path){
    std::ifstream wej;
    wej.open(path.c_str());
    wej.seekg(0,wej.beg);
    if(wej.good()){
        while(!(wej.eof())){
            std::string pom;
            std::string pom2;
            int pom3;
            wej>>pom;
            if(pom=="auta_path"){
                wej>>pom2;
                pathAuta=pom2;
            }
            else if(pom=="trasy_path"){
                wej>>pom2;
                pathTrasy=pom2;
            }
            else if(pom=="licz_graczy"){
                wej>>pom3;
                liczbaGraczy=pom3;
            }
            else if(pom=="frame_limit"){
                wej>>pom3;
                if(pom3<1) frameRate=1;
                else if(pom3>60) frameRate=60;
                else frameRate=pom3;
            }
            else if(pom=="resolution_x"){
                wej>>pom3;
                if(pom3<=0) resX=0;
                else resX=pom3;
            }
            else if(pom=="resolution_y"){
                wej>>pom3;
                if(pom3<=0) resY=0;
                else resY=pom3;
            }
            else if(pom=="zakret_el"){
                wej>>pom3;
                if(pom3<4) doklZakr=4;
                else doklZakr=pom3;
            }
            else if(pom=="default_tor"){
                wej>>pom3;
                defaultTor=pom3;
            }
            else if(pom=="gracz"){
                wej>>pom3;
                isGracz=pom3;
            }
            else if(pom=="gracz_auto"){
                wej>>pom3;
                autoGracza=pom3;
            }            
            else if(pom=="eventPr"){
                wej>>pom3;
                if(pom3<0) eventPr=0;
                else if(pom3>5000) eventPr=5000;
                else eventPr=pom3;
            }
            else if(pom=="laps"){
                wej>>pom3;
                if(pom3<1) laps=1;
                else laps=pom3;
            }
            else if(pom=="obserw"){
                wej>>pom3;
                obs=pom3;
            }
            else {}
        }
    }
    wej.close();
}
void Gra::ladujTrasy(std::string path){
    std::ifstream wej;
    wej.open(path.c_str());
    wej.seekg(0,wej.beg);
    if(wej.good()){
        std::vector <std::string> tex;
        std::string pom;
        int pom2;
        for (int i=0;i<14;i++){
            wej>>pom; wej>>pom;
            tex.push_back(pathTrasy+pom);
        }
        for (int i=0;i<5;i++){
            wej>>pom2;
            wagiEv.push_back(pom2);
        }
        while(!(wej.eof())){
            std::string nazw;
            std::string pom2;
            std::vector <std::string> elNz;
            std::vector <int> elDl;
            int pom3=0;
            wej>>nazw;
            wej>>pom3;
                while(pom3){
                    wej>>pom2;
                    elNz.push_back(pom2);
                    elDl.push_back(pom3);
                    wej>>pom3;
                }
           Track* nowyEl=new Track(0,0,0,nazw,tex,elDl,elNz);
           refTrasy.push_back(nowyEl);
        }
    }
}

int Gra::getLiczbaGraczy(){
    return liczbaGraczy;
}

int Gra::getFrameRate(){
    return frameRate;
}

int Gra::getResX(){
    return resX;
}

int Gra::getResY(){
    return resY;
}

std::vector <Car*> Gra::getRefAuta(){
    return refAuta;
}

std::vector <Track*> Gra::getRefTrasy(){
    return refTrasy;
}

 Track* Gra::getTrasa(){
     return trasa;
 }

 void Gra::nowaGra(){

     srand(time(NULL));
    for (int i=0;i<liczbaGraczy;i++){
        Boot* pom=new Boot(laps);
        int z=refAuta.size();
        z=losujLiczbe(0,z-1);
        pom->pojazd=new Car(*refAuta[z]);
        pom->setNrAuta(z);
        pom->zadPol=Point(350,-1000000);
        pom->koniecWys=false;
        uczestnicy.push_back(pom);
    }
    if(isGracz){
        Gracz* pom=new Gracz(laps);
        pom->pojazd=new Car(*refAuta[autoGracza]);
        pom->setNrAuta(autoGracza);
        pom->koniecWys=false;
        uczestnicy.push_back(pom);
    }
    trasa=new Track(*refTrasy[defaultTor]);
    for (int i=int(uczestnicy.size())-1;i>=0;i--){
        uczestnicy[i]->pojazd->setSize(130,52);
        uczestnicy[i]->pojazd->setSrodekObr(Point(26,96));
        uczestnicy[i]->pojazd->inicjalizujPunkty(Point((5+4*(i%2))*(resX-260)/14,resY*4/5-(int(uczestnicy.size())-1-i)*100));
        int u;
        if(isGracz) u=int(uczestnicy.size())-2;
        else u=int(uczestnicy.size())-1;
        if(i<=u){
            dynamic_cast <Boot*> (uczestnicy[i])->setPopPol(Point((5+4*(i%2))*(resX-260)/14,resY*4/5-(int(uczestnicy.size())-1-i)*100));
            dynamic_cast <Boot*> (uczestnicy[i])->setPopPol2(Point((5+4*(i%2))*(resX-260)/14,resY*4/5-(int(uczestnicy.size())-1-i)*100));

        }
    }
    for (int i=0;i<int(uczestnicy.size());i++){
        uczestnicy[i]->setIter(uczestnicy[0]->pojazd->getPosY()-100-uczestnicy[i]->pojazd->getPosY());
    }
    for(int i=0;i<int(uczestnicy.size());i++){
        std::vector <bool> pom;
        for(int j=0;j<int(uczestnicy.size());j++){
            pom.push_back(false);
        }
        uczestnicy[i]->kolizja.push_back(pom);
    }
    std::vector <Obstacle*> pom11, pom22, pom33, pom44, pom55;
    trasa->dodajElToru(pom11);
    trasa->dodajElToru(pom22);
    int z=int(resY/100)+5;
    trasa->setIloscTarek(2*z);
    for (int i=0;i<2*z;i++){
       Obstacle* pom=new Obstacle(0.01,0.005,trasa->getTexPath()[1],true);
       pom->setSize(100,25);
       pom->setSrodekObr(Point(0,0));
       pom->inicjalizujPunkty(Point(100+475*(i%2),int(i/2)*100));
       pom33.push_back(pom);
    }
    trasa->dodajElToru(pom33);
     z=int(resY/75)+5;
     trasa->setIloscBand(2*z);
     for (int i=0;i<2*z;i++){
         Obstacle* pom=new Obstacle(0.1,0.05,trasa->getTexPath()[0],false);
         pom->setSize(75,50);
         pom->setSrodekObr(Point(0,0));
         pom->inicjalizujPunkty(Point((resX-310)*(i%2),int(i/2)*75));
         pom44.push_back(pom);
     }
     trasa->dodajElToru(pom44);
     trasa->dodajElToru(pom55);

     uczestnicy[uczestnicy.size()-1]->inicjalizujMojeBT(trasa->getListeEelemToru()[2],trasa->getListeEelemToru()[3]);

     for(int i=0;i<int(uczestnicy.size());i++){
         if(i!=int(uczestnicy.size())-1) uczestnicy[i]->inicjalizujMojeBT( uczestnicy[int(uczestnicy.size())-1]);
     }
     for (size_t i=0;i<uczestnicy.size();i++){
         std::vector<bool> pom;
         uczestnicy[i]->kolizja.push_back(pom);
     }

 }
 int Gra::losujLiczbe(int min, int max){     
     int pom=max-min+1;
     int pom3=rand();
     int pom2=pom3%pom;
     pom2=pom2+min;
     return pom2;
 }

Obstacle* Gra::losowyEvent(){
    int pom1=0;
    for (int i=0; i<int(wagiEv.size());i++){
        pom1=pom1+wagiEv[i];
    }
    int pom2=losujLiczbe(1,pom1);
    Obstacle* pom3;
    if(pom2>=1 && pom2<=wagiEv[0]){
        pom3= new Obstacle(1,1,true);
        pom3->setSize(98,90);
        pom3->setTex(trasa->getTexPath()[2]);

    }
    else if(pom2>wagiEv[0] &&pom2<=(wagiEv[1]+wagiEv[0])){
        pom3= new Obstacle(1,5,true);
        pom3->setSize(120,85);
        pom3->setTex(trasa->getTexPath()[3]);

    }
    else if(pom2>(wagiEv[1]+wagiEv[0])&& pom2<=(wagiEv[1]+wagiEv[0]+wagiEv[2])){
        pom3= new Obstacle(2,4,true);
        pom3->setSize(120,70);
        pom3->setTex(trasa->getTexPath()[4]);

    }
    else if(pom2>(wagiEv[1]+wagiEv[0]+wagiEv[2])&& pom2<=(wagiEv[1]+wagiEv[0]+wagiEv[2]+wagiEv[3])){
        pom3= new Obstacle(2,3,true);
        pom3->setSize(150,80);
        pom3->setTex(trasa->getTexPath()[5]);
    }
    else {
        pom3= new Obstacle(2,5,true);
        pom3->setSize(150,60);
        pom3->setTex(trasa->getTexPath()[6]);
    }    
    return pom3;
}

void Gra::czyDacEvent(Uczestnik* dr){
    int z=losujLiczbe(0,10000);

    if(z<=eventPr){
        Obstacle* nowa=losowyEvent();

        nowa->inicjalizujPunkty(Point(double(dr->pojazd->getPosX())-double(nowa->getWidth())/2,double(dr->pojazd->getPosY())-double(losujLiczbe(1000,1600))));
        bool flaga=1;
        int l=0;
        while(flaga){
            for(int i=0;i<int(uczestnicy.size());i++){
                if(!uczestnicy[i]->pojazd->sprawdzKolizje(*nowa)){
                    flaga=0;
                }
                else{
                    flaga=1;
                    Point pom;                    
                    pom.y=-losujLiczbe(100,200);
                    nowa->wyznaczPunkty(0,0,pom.y);
                    break;
                }
            }
            for(int i=0;i<int(losowePrz.size());i++){
                if(!losowePrz[i]->sprawdzKolizje(*nowa)){
                    flaga=0;
                }
                else{
                    flaga=1;
                    Point pom;
                    pom.y=-losujLiczbe(100,200);
                    nowa->wyznaczPunkty(0,0,pom.y);
                    break;
                }
            }
            l++;
            if(l>5){
                delete nowa;
                return;
            }
        }

        losowePrz.push_back(nowa);

        for(int i=0;i<int(uczestnicy.size());i++){
            uczestnicy[i]->kolizja[3].push_back(false);
        }
    }
}

std::vector <Uczestnik*> Gra::getUczestnicy(){
    return uczestnicy;
}

std::vector <Obstacle*> Gra::getLosowePrz(){
    return losowePrz;
}

void Gra::aktPozycjeWT(){
    for (int i=0; i<int(uczestnicy.size());i++){
        if(trasa->getEtNz()[uczestnicy[i]->getNrEt()]=="S"){
            uczestnicy[i]->setIter(uczestnicy[i]->getIter()+uczestnicy[i]->pojazd->getVAkt()/5);
            if(uczestnicy[i]->getIter()>=trasa->getEtDl()[uczestnicy[i]->getNrEt()]){
                if(uczestnicy[i]->getNrEt()!=(int(trasa->getEtDl().size())-1)){
                    uczestnicy[i]->setIter(uczestnicy[i]->getIter()-trasa->getEtDl()[uczestnicy[i]->getNrEt()]);
                    uczestnicy[i]->setNrEt(uczestnicy[i]->getNrEt()+1);

                }
                else{
                    uczestnicy[i]->setIter(uczestnicy[i]->getIter()-trasa->getEtDl()[uczestnicy[i]->getNrEt()]);
                    uczestnicy[i]->setNrEt(0);
                    uczestnicy[i]->setLapToGo(uczestnicy[i]->getLapToGo()-1);
                    if(uczestnicy[i]->getLapToGo()==0){
                        uczestnicy[i]->setKoniecWys(true);
                    }
                }
            }
            if(uczestnicy[i]->getIter()>trasa->getEtDl()[uczestnicy[i]->getNrEt()]-2000){
                if(uczestnicy[i]->getNrEt()!=(int(trasa->getEtNz().size())-1)){
                    if(trasa->getEtNz()[(uczestnicy[i]->getNrEt()+1)%int(trasa->getEtNz().size())]!="S"){
                        std::size_t szuk;
                        szuk=trasa->getEtNz()[(uczestnicy[i]->getNrEt()+1)%int(trasa->getEtNz().size())].find("L");
                        if(szuk!=std::string::npos){
                            usunVektor(uczestnicy[i]->zakret);
                            usunVektor(uczestnicy[i]->zakT);
                            usunVektor(uczestnicy[i]->zakB);
                            float y=uczestnicy[i]->pojazd->getPosY()-(trasa->getEtDl()[uczestnicy[i]->getNrEt()]-uczestnicy[i]->getIter());
                            uczestnicy[i]->zakret=uczestnicy[i]->getZakret(trasa->getEtDl()[uczestnicy[i]->getNrEt()+1],trasa->getEtNz()[uczestnicy[i]->getNrEt()+1],Point(575,y),doklZakr);

                        }
                        else{
                            usunVektor(uczestnicy[i]->zakret);
                            usunVektor(uczestnicy[i]->zakT);
                            usunVektor(uczestnicy[i]->zakB);
                            float y=uczestnicy[i]->pojazd->getPosY()-(trasa->getEtDl()[uczestnicy[i]->getNrEt()]-uczestnicy[i]->getIter());
                            uczestnicy[i]->zakret=uczestnicy[i]->getZakret(trasa->getEtDl()[uczestnicy[i]->getNrEt()+1],trasa->getEtNz()[uczestnicy[i]->getNrEt()+1],Point(125,y),doklZakr);

                        }
                    }
                }
                else{
                    if(trasa->getEtNz()[0]!="S"){
                        std::size_t szuk;
                        szuk=trasa->getEtNz()[uczestnicy[i]->getNrEt()+1].find("L");
                        if(szuk!=std::string::npos){
                            usunVektor(uczestnicy[i]->zakret);
                            usunVektor(uczestnicy[i]->zakT);
                            usunVektor(uczestnicy[i]->zakB);
                            float y=uczestnicy[i]->pojazd->getPosY()-(trasa->getEtDl()[uczestnicy[i]->getNrEt()]-uczestnicy[i]->getIter());
                            uczestnicy[i]->zakret=uczestnicy[i]->getZakret(trasa->getEtDl()[uczestnicy[i]->getNrEt()+1],trasa->getEtNz()[uczestnicy[i]->getNrEt()+1],Point(575,y),doklZakr);
                        }
                        else{
                            usunVektor(uczestnicy[i]->zakret);
                            usunVektor(uczestnicy[i]->zakT);
                            usunVektor(uczestnicy[i]->zakB);
                            float y=uczestnicy[i]->pojazd->getPosY()-(trasa->getEtDl()[uczestnicy[i]->getNrEt()]-uczestnicy[i]->getIter());
                            uczestnicy[i]->zakret=uczestnicy[i]->getZakret(trasa->getEtDl()[uczestnicy[i]->getNrEt()+1],trasa->getEtNz()[uczestnicy[i]->getNrEt()+1],Point(125,y),doklZakr);
                        }
                    }
                }
            }
        }
        else{
            if(uczestnicy[i]->pojazd->sprawdzKolizje(*uczestnicy[i]->zakret[int(uczestnicy[i]->zakret.size())-1])&&( !uczestnicy[i]->pojazd->sprawdzKolizje(*uczestnicy[i]->zakret[int(uczestnicy[i]->zakret.size())-2]))){
                uczestnicy[i]->setNrEt(uczestnicy[i]->getNrEt()+1);
                 uczestnicy[i]->setIter(0);

            }
        }
    }
}

bool Gra::U1wU2(int i1, int i2){
    if(uczestnicy[i1]->pojazd->getPosY()<=uczestnicy[i2]->pojazd->getPosY()) return true;
    else return false;
    /*if(uczestnicy[i1]->getLapToGo()<=uczestnicy[i2]->getLapToGo()){
        if(uczestnicy[i1]->getLapToGo()<uczestnicy[i2]->getLapToGo()) return true;
        else{
            if(uczestnicy[i1]->getNrEt()>=uczestnicy[i2]->getNrEt()){
                if(uczestnicy[i1]->getNrEt()>uczestnicy[i2]->getNrEt()) return true;
                else{
                    //if(uczestnicy[i1]->getIter()>=uczestnicy[i2]->getIter()) return true;
                    if(uczestnicy[i1]->pojazd->getPosY()<=uczestnicy[i2]->pojazd->getPosY()) return true;
                    else return false;
                }
            }
            else return false;
        }
    }
    else return false;*/
}

void Gra::aktPozycjeWG(){
    for(int i=0;i<int(uczestnicy.size());i++){
        int pom=int(uczestnicy.size())+1;
        for(int j=0;j<int(uczestnicy.size());j++){
            if(U1wU2(i,j)) pom--;
        }
        if(uczestnicy[i]->getLapToGo()) uczestnicy[i]->setPozycja(pom);
    }
}

void Gra::kolizje(bool wl){
    if(wl){
        for(int i=0;i<int(uczestnicy.size());i++){
            for(int j=0; j<int( uczestnicy[i]->mojeB.size());j++){
                if(uczestnicy[i]->pojazd->sprawdzKolizje(*uczestnicy[i]->mojeB[j])){
                    if(uczestnicy[i]->kolizja[2][j]==false){
                        uczestnicy[i]->pojazd->setEngineCon(uczestnicy[i]->pojazd->getEngineCon()-uczestnicy[i]->mojeB[j]->getEngineDmg());
                        uczestnicy[i]->pojazd->setTireCon(uczestnicy[i]->pojazd->getTireCon()-uczestnicy[i]->mojeB[j]->getTireDmg());
                        uczestnicy[i]->kolizja[2][j]=true;
                    }
                }
                else{
                    uczestnicy[i]->kolizja[2][j]=false;
                }
            }
            for(int j=0; j<int(uczestnicy[i]->mojeT.size());j++){
                if(uczestnicy[i]->pojazd->sprawdzKolizje(*uczestnicy[i]->mojeT[j])){
                    if(uczestnicy[i]->kolizja[1][j]==false){
                        uczestnicy[i]->pojazd->setEngineCon(uczestnicy[i]->pojazd->getEngineCon()-uczestnicy[i]->mojeT[j]->getEngineDmg());
                        uczestnicy[i]->pojazd->setTireCon(uczestnicy[i]->pojazd->getTireCon()-uczestnicy[i]->mojeT[j]->getTireDmg());
                        uczestnicy[i]->kolizja[1][j]=true;
                    }
                }
                else{
                    uczestnicy[i]->kolizja[1][j]=false;
                }
            }
            for(int j=0;j<int(uczestnicy.size());j++){
                if(i!=j){
                    if(uczestnicy[i]->pojazd->sprawdzKolizje(*uczestnicy[j]->pojazd)){
                        if(uczestnicy[i]->kolizja[0][j]==false){
                            uczestnicy[i]->pojazd->setEngineCon(uczestnicy[i]->pojazd->getEngineCon()-uczestnicy[j]->pojazd->getEngineDmg());
                            uczestnicy[i]->pojazd->setTireCon(uczestnicy[i]->pojazd->getTireCon()-uczestnicy[j]->pojazd->getTireDmg());
                            uczestnicy[i]->kolizja[0][j]=true;
                        }
                    }
                    else{
                        uczestnicy[i]->kolizja[0][j]=false;
                    }
                }
            }
            for(int j=0; j<int(losowePrz.size());j++){
                if(uczestnicy[i]->pojazd->sprawdzKolizje(*losowePrz[j])){
                    if(uczestnicy[i]->kolizja[3][j]==false){
                        uczestnicy[i]->pojazd->setEngineCon(uczestnicy[i]->pojazd->getEngineCon()-losowePrz[j]->getEngineDmg());
                        uczestnicy[i]->pojazd->setTireCon(uczestnicy[i]->pojazd->getTireCon()-losowePrz[j]->getTireDmg());
                        losowyEfekt(uczestnicy[i]);
                        uczestnicy[i]->kolizja[3][j]=true;
                    }
                }
                else{
                    uczestnicy[i]->kolizja[3][j]=false;
                }
            }
            if(uczestnicy[i]->pojazd->getEngineCon()<0) uczestnicy[i]->pojazd->setEngineCon(0);
            if(uczestnicy[i]->pojazd->getTireCon()<0)  uczestnicy[i]->pojazd->setTireCon(0);
            if(abs(uczestnicy[i]->modSkretu)<0.001) uczestnicy[i]->modSkretu=0;
        }
    }
}

void Gra::losowyEfekt(Uczestnik* gr){
    int z=losujLiczbe(0,100);
    if(z<10){
        int u=losujLiczbe(0,100);
        if(u<30){
            gr->modHamowania=gr->modHamowania-0.1;
        }
        else if(u>=30 && u<60){
            gr->modPrzyspieszenia=gr->modPrzyspieszenia-0.05;
        }
        else{
            if(u<80)  gr->modSkretu=gr->modSkretu-0.1;
            else gr->modSkretu=gr->modSkretu+0.1;

        }
    }
}

void Gra::aktPosEv(float angle, float poX, float poY, Point srObr){
    std::vector <int> doUs;
    for (int i=0; i<int(losowePrz.size());i++){
           losowePrz[i]->wyznaczPunkty(0, poX, poY);
           Point p(losowePrz[i]->getPosX(),losowePrz[i]->getPosY());
           p.obrot(srObr,angle);
           losowePrz[i]->wyznaczPunkty(0,p.x-losowePrz[i]->getPosX(),p.y-losowePrz[i]->getPosY());
           int poz=0;
           for(int j=0;j<int(uczestnicy.size());j++){
               if(uczestnicy[j]->getPozycja()>uczestnicy[poz]->getPozycja()){
                   poz=j;
               }
           }
           if(losowePrz[i]->getPosY()>uczestnicy[poz]->pojazd->getPosY()+600){
               doUs.push_back(i);
           }
    }
    for(int i=int(doUs.size())-1;i>=0;i--){
        delete losowePrz[doUs[i]];
        losowePrz.erase(losowePrz.begin()+doUs[i]);
        for(int j=0;j<int(uczestnicy.size());j++){
            uczestnicy[j]->kolizja[3].erase(uczestnicy[j]->kolizja[3].begin()+doUs[i]);
        }
    }
    doUs.clear();
}

int Gra::ktoraTxEv(Obstacle* el){
    int a=0;
    for (int i=0; i<5;i++){
        if(el->getTexPath()==trasa->getTexPath()[i+2]) a=i;
    }
    return a;
}

void Gra::usunVektor(std::vector <Obstacle*> &el){
    for (int i=0; i<int(el.size());i++){
        delete el[i];
    }
    el.clear();
}

void Gra::krokPodstawowy(bool u, bool d, bool l, bool p, bool su, bool sd, int aktObserUcz){
    Point delta;
    float vgl=0;
    float angl=0;
    float katN=0;
    bool flag=false;    
    delta=uczestnicy[uczestnicy.size()-1-aktObserUcz]->jedz(l,p,u,d,su,sd,vgl, flag,angl);
    if(trasa->getEtNz()[uczestnicy[uczestnicy.size()-1-aktObserUcz]->getNrEt()]=="S"){
        uczestnicy[uczestnicy.size()-1-aktObserUcz]->aktPosElToru(0,0,-delta.y,Point(0,0),false);
        aktPosEv(0,0,-delta.y,Point(0,0));
    }
    else{
        Point pozS=uczestnicy[uczestnicy.size()-1-aktObserUcz]->srodekKZak();
        Point pozN(uczestnicy[uczestnicy.size()-1-aktObserUcz]->pojazd->getPosX(),uczestnicy[uczestnicy.size()-1-aktObserUcz]->pojazd->getPosY());
        Point pozP(pozN.x+delta.x,pozN.y+delta.y);
        double A=sqrt(pow((pozP.x-pozN.x),2)+pow((pozP.y-pozN.y),2));
        double B=sqrt(pow((pozP.x-pozS.x),2)+pow((pozP.y-pozS.y),2));
        double C=sqrt(pow((pozS.x-pozN.x),2)+pow((pozS.y-pozN.y),2));
        double pomk=(pow(A,2)-pow(B,2)-pow(C,2))/(-2*B*C);
        double katR=acos(pomk);
        float katS=180*katR/PI;
        katN=katS;
        std::size_t szuk1=trasa->getEtNz()[uczestnicy[uczestnicy.size()-1-aktObserUcz]->getNrEt()].find("L");
        if(szuk1!=std::string::npos){
            uczestnicy[uczestnicy.size()-1-aktObserUcz]->aktPosElToru(katS,0,-delta.y,pozS,true);
            aktPosEv(katS,0,-delta.y,pozS);
        }
        else{
            uczestnicy[uczestnicy.size()-1-aktObserUcz]->aktPosElToru(-katS,0,-delta.y,pozS,true);
            aktPosEv(-katS,0,0,pozS);
        }

    }
    flag=true;


    //std::cout<<"Nr."<<"\t"<<"Pozycja"<<"\t"<<"VAkt"<<"\t"<<"Bieg"<<"\t"<<"ECon"<<"\t"<<"TCon"<<"\t"<<"zadX"<<"\t"<<"polX"<<"\t"<<"mod S/P/H"<<std::endl;

    for(int i=0;i<int(uczestnicy.size());i++){
        if(i!=int(uczestnicy.size())-1-aktObserUcz){
          delta=uczestnicy[i]->jedz(l,p,u,d,su,sd,vgl,flag,angl);
          if(trasa->getEtNz()[uczestnicy[i]->getNrEt()]=="S"){
              uczestnicy[i]->aktPosElToru(0,0,-delta.y,Point(0,0),false);
          }
          else{
              Point pozS=uczestnicy[i]->srodekKZak();
              Point pozN(uczestnicy[i]->pojazd->getPosX(),uczestnicy[i]->pojazd->getPosY());
              Point pozP(pozN.x+delta.x,pozN.y+delta.y);
              double A=sqrt(pow((pozP.x-pozN.x),2)+pow((pozP.y-pozN.y),2));
              double B=sqrt(pow((pozP.x-pozS.x),2)+pow((pozP.y-pozS.y),2));
              double C=sqrt(pow((pozS.x-pozN.x),2)+pow((pozS.y-pozN.y),2));
              double pomk=(pow(A,2)-pow(B,2)-pow(C,2))/(-2*B*C);
              double katR=acos(pomk);
              float katS=180*katR/PI;
              katS=katS-katN;
              std::size_t szuk1=trasa->getEtNz()[uczestnicy[i]->getNrEt()].find("L");
              if(szuk1!=std::string::npos){
                  uczestnicy[i]->aktPosElToru(katS,0,-delta.y,pozS,true);
                  //game-> aktPosEv(katS,0,-delta.y,pozS);
              }
              else{
                  uczestnicy[i]->aktPosElToru(-katS,0,-delta.y,pozS,true);
                  //game-> aktPosEv(-katS,0,0,pozS);
              }
          }
        }
        //std::cout.precision(4);
        //std::cout<<i<<"\t"<<uczestnicy[i]->getPozycja()<<"\t"<<uczestnicy[i]->pojazd->getVAkt()<<"\t"<<uczestnicy[i]->pojazd->getAktBieg()<<"\t"<<uczestnicy[i]->pojazd->getEngineCon()<<"\t"<<uczestnicy[i]->pojazd->getTireCon()<<"\t";
        Boot * pz=dynamic_cast <Boot*> (uczestnicy[i]);
        float x=0;
        if(pz){
            x=pz->zadPol.x;
        }
        //std::cout<<x<<"\t"<<uczestnicy[i]->pojazd->getPosX()<<"\t"<<uczestnicy[i]->modSkretu<<"/"<<uczestnicy[i]->modPrzyspieszenia<<"/"<<uczestnicy[i]->modHamowania<<std::endl;

        czyDacEvent(uczestnicy[i]);
    }    

    aktPozycjeWT();
    aktPozycjeWG();
    kolizje(true);
    pozycjeZadane();
}

bool Gra::czyGracz(){
    return isGracz;
}

void Gra::pozycjeZadane(){
    for(int i=0;i<int(uczestnicy.size());i++){
        Boot *pz1=dynamic_cast <Boot*> (uczestnicy[i]);
        if(pz1) pz1->zadPol.y=pz1->pojazd->getPosY()-3000;
        for(int j=0;j<int(losowePrz.size());j++){            
                if((uczestnicy[i]->pojazd->getPosX()>(losowePrz[j]->getPosX()-30))&&(uczestnicy[i]->pojazd->getPosX()<(losowePrz[j]->getPosX()+120))){
                    if(uczestnicy[i]->pojazd->getPosY()<losowePrz[j]->getPosY()+1500){
                        Boot *pz=dynamic_cast <Boot*> (uczestnicy[i]);
                        if(uczestnicy[i]->pojazd->getPosX()>=losowePrz[j]->getPosX()+losowePrz[j]->getWidth()/2){
                            if(pz!=NULL){
                                if(pz->zadPol.x<losowePrz[j]->getPosX()+120){
                                    pz->zadPol.x=pz->zadPol.x+5;
                                    pz->zadPol.y=losowePrz[j]->getPosY();
                                }
                            }

                        }
                        else{
                            if(pz!=NULL){
                                if(pz->zadPol.x>losowePrz[j]->getPosX()-30){
                                    pz->zadPol.x=pz->zadPol.x-5;
                                    pz->zadPol.y=losowePrz[j]->getPosY();
                                }
                            }
                        }
                    }
                }

        }

        for(int j=0;j<int(uczestnicy.size());j++){
            if(i!=j){
                if(uczestnicy[i]->kolizja[0][j]){
                    Boot *pz=dynamic_cast <Boot*> (uczestnicy[i]);
                    if(uczestnicy[i]->pojazd->getPosX()>=uczestnicy[j]->pojazd->getPosX()){
                        if(pz){
                            if(!(pz->zadPol.x>pz->pojazd->getPosX()+pz->pojazd->getWidth()+20)){
                                pz->zadPol.x=pz->zadPol.x+5;

                            }
                        }

                    }
                    else{
                        if(pz){
                            if(!(pz->zadPol.x>pz->pojazd->getPosX()-pz->pojazd->getWidth()-20)){
                                pz->zadPol.x=pz->zadPol.x-5;

                            }
                        }
                    }              
                }
            }
        }

        for(int j=0;j<int(uczestnicy.size());j++){
            if(i!=j){
                Boot *pz=dynamic_cast <Boot*> (uczestnicy[i]);
                if(uczestnicy[i]->pojazd->getVAkt()>=uczestnicy[j]->pojazd->getVAkt()+5){
                    if(uczestnicy[i]->pojazd->getPosY()<=uczestnicy[j]->pojazd->getPosY()+2*uczestnicy[j]->pojazd->getHeigth()){
                        if(uczestnicy[i]->pojazd->getPosX()>=uczestnicy[j]->pojazd->getPosX()){
                            if(pz){
                                if(!(pz->zadPol.x>pz->pojazd->getPosX()+pz->pojazd->getWidth()+20)){
                                    pz->zadPol.x=pz->zadPol.x+5;
                                }
                            }

                        }
                        else{
                            if(pz){
                                if(!(pz->zadPol.x>pz->pojazd->getPosX()-pz->pojazd->getWidth()-20)){
                                    pz->zadPol.x=pz->zadPol.x-5;
                                }
                            }
                        }
                    }

                }
            }
        }

        Boot *pz=dynamic_cast <Boot*> (uczestnicy[i]);
        if(pz){
            if(pz->zadPol.y==pz->pojazd->getPosY()-3000) {
                if(trasa->getEtNz()[pz->getNrEt()]=="S"){
                    if(pz->getIter()>trasa->getEtDl()[pz->getNrEt()]-1000){
                        if(trasa->getEtNz()[(pz->getNrEt()+1)%trasa->getEtNz().size()]!="S"){
                            if(trasa->getEtNz()[(pz->getNrEt()+1)%trasa->getEtNz().size()]=="L45"||trasa->getEtNz()[(pz->getNrEt()+1)%trasa->getEtNz().size()]=="L90"||trasa->getEtNz()[(pz->getNrEt()+1)%trasa->getEtNz().size()]=="L180"){
                                pz->zadPol.x=460;
                            }
                            else{
                                pz->zadPol.x=200;
                            }
                        }
                    }
                }
                else if(trasa->getEtNz()[pz->getNrEt()]=="L45"||trasa->getEtNz()[pz->getNrEt()]=="L90"||trasa->getEtNz()[pz->getNrEt()]=="L180"){
                    pz->zadPol.x=200;
                }
                else{
                    pz->zadPol.x=460;
                }
            }
        }
        if(pz){
            if(pz->zadPol.x>550){
                pz->zadPol.x=350;
            }
            else if(pz->zadPol.x<150){
               pz->zadPol.x=350;
            }
            else{

            }
        }


    }
}
