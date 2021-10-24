#include "obstacle.hpp"
#include <cmath>

Obstacle::Obstacle() : Drawable()
{
    tireDmg=0;
    engineDmg=0;
    crossable=false;
}

Obstacle::~Obstacle()
{

}



Obstacle::Obstacle(const Obstacle& el) : Drawable(el)
{
    tireDmg=el.tireDmg;
    engineDmg=el.engineDmg;
    crossable=el.crossable;
    for (int i=0;i<int(el.punkty.size());i++){
        punkty.push_back(el.punkty[i]);
    }
}
Obstacle::Obstacle(float tireDmg, float engineDmg, bool crossable) : Drawable()
{
    (*this).tireDmg=tireDmg;
    (*this).engineDmg=engineDmg;
    (*this).crossable=crossable;
}
Obstacle::Obstacle(float tireDmg, float engineDmg, std::string path, bool crossable) : Drawable(0,path)
{
    (*this).tireDmg=tireDmg;
    (*this).engineDmg=engineDmg;
    (*this).crossable=crossable;
}
void Obstacle::setTireDmg(float tireDmg){
    (*this).tireDmg=tireDmg;
}
void Obstacle::setEngineDmg(float engineDmg){
    (*this).engineDmg=engineDmg;
}
void Obstacle::setCross(bool crossable){
    (*this).crossable=crossable;
}
float Obstacle::getTireDmg(){
    return (*this).tireDmg;
}
float Obstacle::getEngineDmg(){
    return (*this).engineDmg;
}
bool Obstacle::getCross(){
    return (*this).crossable;
}



void Obstacle::wyznaczPunkty(double deg, double poX, double poY){// deg stopnie o jaki ma byc pbócony, poX, poY  przesunieci srodka figury

    setPosition(getPosX()+poX,getPosY()+poY);

    for (int i=0;i<int(punkty.size());i++){
        double pomX=punkty[i].x+poX;
        double pomY=punkty[i].y+poY;
        punkty[i].x=punkty[i].x+poX;
        punkty[i].y=punkty[i].y+poY;
        if(deg){
            pomX=((punkty[i].x-getPosX())*cos(deg*PI/180)-(punkty[i].y-getPosY())*sin(deg*PI/180)+getPosX());
            pomY=((punkty[i].x-getPosX())*sin(deg*PI/180)+(punkty[i].y-getPosY())*cos(deg*PI/180)+getPosY());
        }
        punkty[i].x=pomX;
        punkty[i].y=pomY;


    }

}
bool Obstacle::sprawdzKolizje(Obstacle el1){

    float maxX1=maxXY((*this),true);
    float maxY1=maxXY((*this),false);
    float minY1=minXY((*this),false);
    float minX1=minXY((*this),true);
    float maxX2=maxXY(el1,true);
    float maxY2=maxXY(el1,false);
    float minX2=minXY(el1,true);
    float minY2=minXY(el1,false);

    bool a=(maxX2<minX1);
    bool b=(minX2>maxX1);
    bool c=(maxY2<minY1);
    bool d=(minY2>maxY1);

    bool A=(maxX2<maxX1);
    bool B=(minX2>minX1);
    bool C=(maxY2<maxY1);
    bool D=(minY2>minY1);

    if((a||b)||(c||d)) return false;
    else if(A&&B&&C&&D) return true;
    else{
        for(int i=0;i<int(punkty.size());i++){
            int iter=0;
            int pomTab[2][2];

            for(int j=0;j<int(el1.punkty.size());j++){
                bool x=((punkty[i].y<=el1.punkty[j].y)&&(punkty[i].y>=el1.punkty[(j+1)%int(el1.punkty.size())].y));
                bool y=((punkty[i].y<=el1.punkty[(j+1)%int(el1.punkty.size())].y)&&(punkty[i].y>=el1.punkty[j].y));
                if(x||y){
                    pomTab[iter][0]=j;
                    pomTab[iter][1]=(j+1)%int(el1.punkty.size());
                    iter++;
                }
            }
            if(iter==2){
                float xp, xp2;
                if(el1.punkty[pomTab[0][1]].x!=el1.punkty[pomTab[0][0]].x){
                    double a1=(el1.punkty[pomTab[0][1]].y-el1.punkty[pomTab[0][0]].y)/(el1.punkty[pomTab[0][1]].x-el1.punkty[pomTab[0][0]].x);
                    double b1=el1.punkty[pomTab[0][0]].y-a1*el1.punkty[pomTab[0][0]].x;
                    xp=(punkty[i].y-b1)/a1;
                }
                else{
                    xp=el1.punkty[pomTab[0][1]].x;
                }
                if(el1.punkty[pomTab[1][1]].x!=el1.punkty[pomTab[1][0]].x){
                    double a2=(el1.punkty[pomTab[1][1]].y-el1.punkty[pomTab[1][0]].y)/(el1.punkty[pomTab[1][1]].x-el1.punkty[pomTab[1][0]].x);
                    double b2=el1.punkty[pomTab[1][0]].y-a2*el1.punkty[pomTab[1][0]].x;
                    xp2=(punkty[i].y-b2)/a2;
                }
                else{
                    xp2=el1.punkty[pomTab[1][1]].x;
                }

                bool e=(xp>=punkty[i].x && xp2<=punkty[i].x);
                bool f=(xp<=punkty[i].x && xp2>=punkty[i].x);

                if(e||f) return true;
            }

        }
        for(int i=0;i<int(el1.punkty.size());i++){
            int iter=0;
            int pomTab[2][2];

            for(int j=0;j<int(punkty.size());j++){
                bool x=((el1.punkty[i].y<=punkty[j].y)&&(el1.punkty[i].y>=punkty[(j+1)%int(punkty.size())].y));
                bool y=((el1.punkty[i].y<=punkty[(j+1)%int(punkty.size())].y)&&(el1.punkty[i].y>=punkty[j].y));
                if(x||y){
                    pomTab[iter][0]=j;
                    pomTab[iter][1]=(j+1)%int(punkty.size());
                    iter++;
                }
            }
            if(iter==2){
                float xp, xp2;
                if(punkty[pomTab[0][1]].x!=punkty[pomTab[0][0]].x){
                    double a1=(punkty[pomTab[0][1]].y-punkty[pomTab[0][0]].y)/(punkty[pomTab[0][1]].x-punkty[pomTab[0][0]].x);
                    double b1=punkty[pomTab[0][0]].y-a1*punkty[pomTab[0][0]].x;
                    xp=(el1.punkty[i].y-b1)/a1;
                }
                else{
                    xp=punkty[pomTab[0][1]].x;
                }
                if(punkty[pomTab[1][1]].x!=punkty[pomTab[1][0]].x){
                    double a2=(punkty[pomTab[1][1]].y-punkty[pomTab[1][0]].y)/(punkty[pomTab[1][1]].x-punkty[pomTab[1][0]].x);
                    double b2=punkty[pomTab[1][0]].y-a2*punkty[pomTab[1][0]].x;
                    xp2=(el1.punkty[i].y-b2)/a2;
                }
                else{
                    xp2=punkty[pomTab[1][1]].x;
                }



                bool e=(xp>=el1.punkty[i].x && xp2<=el1.punkty[i].x);
                bool f=(xp<=el1.punkty[i].x && xp2>=el1.punkty[i].x);

                if(e||f) return true;
            }

        }
        return false ;
    }
}

float Obstacle::maxXY(Obstacle el, bool czyX){
    float max;
    if(czyX){
        if(el.punkty.size()) max=el.punkty[0].x;
        for(int i=0; i<int(el.punkty.size());i++){
            if(el.punkty[i].x>max) max=el.punkty[i].x;
        }
    }
    else{
        if(el.punkty.size()) max=el.punkty[0].y;
        for(int i=0; i<int(el.punkty.size());i++){
            if(el.punkty[i].y>max) max=el.punkty[i].y;
        }

    }
    return max;
}
float Obstacle::minXY(Obstacle el, bool czyX){
    float min;
    if(czyX){
        if(el.punkty.size()) min=el.punkty[0].x;
        for(int i=0; i<int(el.punkty.size());i++){
            if(el.punkty[i].x<min) min=el.punkty[i].x;
        }
    }
    else{
        if(el.punkty.size()) min=el.punkty[0].y;
        for(int i=0; i<int(el.punkty.size());i++){
            if(el.punkty[i].y<min) min=el.punkty[i].y;
        }

    }
    return min;
}

 void Obstacle::inicjalizujPunkty(Point pos){
     setPosition(pos.x,pos.y);
     Point p1, p2, p3, p4;
     p1.x=getPosX()-getSrodekObr().x;
     p1.y=getPosY()-getSrodekObr().y;
     p2.x=p1.x+getWidth();
     p2.y=getPosY()-getSrodekObr().y;
     p3.x=p2.x;
     p3.y=p2.y+getHeigth();
     p4.x=getPosX()-getSrodekObr().x;
     p4.y=p1.y+getHeigth();
     punkty.push_back(p1);
     punkty.push_back(p2);
     punkty.push_back(p3);
     punkty.push_back(p4);
 }
