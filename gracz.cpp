#include "gracz.h"

Gracz::Gracz() : Uczestnik()
{

}

Gracz::Gracz(const Gracz &el) : Uczestnik(el)
{

}

Gracz::Gracz(int lap) : Uczestnik(lap)
{

}

Gracz::~Gracz(){

}

Point Gracz::jedz(bool l, bool p, bool a, bool b, bool su, bool sd, float &vg, bool flaga, float &ang){
    if(koniecWys){
        b=true;
        a=false;
    }
    Point przysrost;    
    if(su&& (!sd)){
        pojazd->shiftUp();
    }
    else if(sd&& (!su)){
        if(pojazd->vAkt<=(pojazd->vMax/pojazd->lBiegow)*(pojazd->aktBieg-1))
            pojazd->shiftDown();
    }
    if (l&& !(b||p||a))
    {
        float pom2=pojazd->vAkt;
        if(pojazd->vAkt>0){
           pojazd->vAkt=pojazd->vAkt-(pojazd->vAkt/300+0.1);
           if(pojazd->vAkt<0)
               pojazd->vAkt=0;
        }
        float pom=pojazd->vAkt;
        if(flaga){
            pojazd->vAkt=(pojazd->vAkt-vg)/5;
        }
        else{
           vg=pojazd->vAkt;
           pojazd->vAkt=pojazd->vAkt/5;
        }
        if(pom2==0 && (!flaga)){

        }
        else{
            przysrost=pojazd->naWprost((-(2-pom/200)+modSkretu)*(pojazd->getTireCon()/100),flaga,vg);
            ang=(-(2-pom/200)+modSkretu)*(pojazd->getTireCon()/100);
        }
         pojazd->vAkt=pom;
        if(aktywnaTx!=0){
            aktywnaTx=0;
            aktualizujTx=1;
        }
    }
    else if (p&& !(b||l||a))
    {
        float pom2=pojazd->vAkt;
        if(pojazd->vAkt>0){
            pojazd->vAkt=pojazd->vAkt-(pojazd->vAkt/300+0.1);
            if(pojazd->vAkt<0)
                pojazd->vAkt=0;
        }
        float pom=pojazd->vAkt;
        if(flaga){
            pojazd->vAkt=(pojazd->vAkt-vg)/5;
        }
        else{
           vg=pojazd->vAkt;
           pojazd->vAkt=pojazd->vAkt/5;
        }
        if(pom2==0 && (!flaga)){

        }
        else{
            przysrost=pojazd->naWprost(((2-pom/200)+modSkretu)*(pojazd->getTireCon()/100),flaga,vg);
            ang=((2-pom/200)+modSkretu)*(pojazd->getTireCon()/100);
        }
         pojazd->vAkt=pom;
        if(aktywnaTx!=1){
            aktywnaTx=1;
            aktualizujTx=1;
        }
    }
    else if (a&& !(b||l||p))
    {
        float pom2=pojazd->vAkt;
        if(pojazd->vAkt>=0){
            if(pojazd->vAkt<pojazd->vMax/pojazd->lBiegow*pojazd->aktBieg){
                if(pojazd->vAkt>=pojazd->vMax/pojazd->lBiegow*(pojazd->aktBieg-1))
                    pojazd->vAkt=pojazd->vAkt+((pojazd->acc)*(pojazd->getEngineCon()/100)-pojazd->vAkt/500)+modPrzyspieszenia;
                else
                    pojazd->vAkt=pojazd->vAkt+((pojazd->acc*(pojazd->getEngineCon()/100)-pojazd->vAkt/500)/2)+modPrzyspieszenia;
            }
            else{
                pojazd->vAkt=pojazd->vAkt-1;
            }
            if(pojazd->vAkt<0)
                pojazd->vAkt=0;
        }

        float pom=pojazd->vAkt;
        if(flaga){
            pojazd->vAkt=(pojazd->vAkt-vg)/5;
        }
        else{
            vg=pojazd->vAkt;
            pojazd->vAkt=pojazd->vAkt/5;
        }
        if(pom2==0 && (!flaga)){

        }
        else{
            przysrost=pojazd->naWprost(modSkretu,flaga,vg);
            ang=(modSkretu);
        }
        pojazd->vAkt=pom;

        if(aktywnaTx!=2){
            aktywnaTx=2;
            aktualizujTx=1;
        }
    }
    else if (b&& !(a||l||p))
    {
        float pom2=pojazd->vAkt;
        if(pojazd->vAkt>0){
            pojazd->vAkt=pojazd->vAkt-pojazd->dcc+modHamowania;
            if(pojazd->vAkt<0)
                pojazd->vAkt=0;
        }
        float pom=pojazd->vAkt;
        if(flaga){
            pojazd->vAkt=(pojazd->vAkt-vg)/5;
        }
        else{
            vg=pojazd->vAkt;
            pojazd->vAkt=pojazd->vAkt/5;
        }
        if(pom2==0 && (!flaga)){

        }
        else{
            przysrost=pojazd->naWprost(modSkretu,flaga,vg);
            ang=(0+modSkretu);
        }
        pojazd->vAkt=pom;

        if(aktywnaTx!=2){
            aktywnaTx=2;
            aktualizujTx=1;
        }
    }
    else if (a&&l&& !(b||p)){
        float pom2=pojazd->vAkt;
        if(pojazd->vAkt>=0){
            if(pojazd->vAkt<pojazd->vMax/pojazd->lBiegow*pojazd->aktBieg){
                if(pojazd->vAkt>=pojazd->vMax/pojazd->lBiegow*(pojazd->aktBieg-1))
                    pojazd->vAkt=pojazd->vAkt+(pojazd->acc*(pojazd->getEngineCon()/100)-pojazd->vAkt/500)+modPrzyspieszenia;
                else
                    pojazd->vAkt=pojazd->vAkt+((pojazd->acc*(pojazd->getEngineCon()/100)-pojazd->vAkt/500)/2)+modPrzyspieszenia;
            }
            else{
                pojazd->vAkt=pojazd->vAkt-1;
            }
            if(pojazd->vAkt<0)
                pojazd->vAkt=0;
        }
        float pom=pojazd->vAkt;
        if(flaga){
            pojazd->vAkt=(pojazd->vAkt-vg)/5;
        }
        else{
            vg=pojazd->vAkt;
            pojazd->vAkt=pojazd->vAkt/5;
        }
        if(pom2==0 && (!flaga)){

        }
        else{
            przysrost=pojazd->naWprost((-(1.9-pom/170)+modSkretu)*(pojazd->getTireCon()/100),flaga,vg);
            ang=(-(1.9-pom/170)+modSkretu)*(pojazd->getTireCon()/100);
        }
        pojazd->vAkt=pom;
        if(aktywnaTx!=0){
            aktywnaTx=0;
            aktualizujTx=1;
        }
    }
    else if (a&&p&& !(b||l))
    {
        float pom2=pojazd->vAkt;
        if(pojazd->vAkt>=0){
            if(pojazd->vAkt<pojazd->vMax/pojazd->lBiegow*pojazd->aktBieg){
                if(pojazd->vAkt>=pojazd->vMax/pojazd->lBiegow*(pojazd->aktBieg-1))
                    pojazd->vAkt=pojazd->vAkt+(pojazd->acc*(pojazd->getEngineCon()/100)-pojazd->vAkt/500)+modPrzyspieszenia;
                else
                    pojazd->vAkt=pojazd->vAkt+((pojazd->acc*(pojazd->getEngineCon()/100)-pojazd->vAkt/500)/2)+modPrzyspieszenia;
            }
            else{
                pojazd->vAkt=pojazd->vAkt-1;
            }
            if(pojazd->vAkt<0)
                pojazd->vAkt=0;
        }
        float pom=pojazd->vAkt;
        if(flaga){
            pojazd->vAkt=(pojazd->vAkt-vg)/5;
        }
        else{
            vg=pojazd->vAkt;
            pojazd->vAkt=pojazd->vAkt/5;
        }
        if(pom2==0 && (!flaga)){

        }
        else{
            przysrost=pojazd->naWprost(((1.9-pom/170)+modSkretu)*(pojazd->getTireCon()/100),flaga,vg);
            ang=((1.9-pom/170)+modSkretu)*(pojazd->getTireCon()/100);
        }
        pojazd->vAkt=pom;
        if(aktywnaTx!=1){
            aktywnaTx=1;
            aktualizujTx=1;
        }
    }
    else if (b&&l&& !(a||p))
    {
        float pom2=pojazd->vAkt;
        if(pojazd->vAkt>0){
            pojazd->vAkt=pojazd->vAkt-pojazd->dcc+modHamowania;
            if(pojazd->vAkt<0)
                pojazd->vAkt=0;
        }
        float pom=pojazd->vAkt;
        if(flaga){
            pojazd->vAkt=(pojazd->vAkt-vg)/5;
        }
        else{
            vg=pojazd->vAkt;
            pojazd->vAkt=pojazd->vAkt/5;
        }
        if(pom2==0 && (!flaga)){

        }
        else{
            przysrost=pojazd->naWprost((-(2.1-pom/170)+modSkretu)*(pojazd->getTireCon()/100),flaga,vg);
            ang=(-(2.1-pom/170)+modSkretu)*(pojazd->getTireCon()/100);
        }
        pojazd->vAkt=pom;
        if(aktywnaTx!=0){
            aktywnaTx=0;
            aktualizujTx=1;
        }
    }
    else if (b&&p&& !(a||l))
    {
        float pom2=pojazd->vAkt;
        if(pojazd->vAkt>0){
            pojazd->vAkt=pojazd->vAkt-pojazd->dcc+modHamowania;
            if(pojazd->vAkt<0)
                pojazd->vAkt=0;
        }
        float pom=pojazd->vAkt;
        if(flaga){
            pojazd->vAkt=(pojazd->vAkt-vg)/5;
        }
        else{
            vg=pojazd->vAkt;
            pojazd->vAkt=pojazd->vAkt/5;
        }
        if(pom2==0 && (!flaga)){

        }
        else{
            przysrost=pojazd->naWprost(((2.1-pom/170)+modSkretu)*(pojazd->getTireCon()/100),flaga,vg);
            ang=((2.1-pom/170)+modSkretu)*(pojazd->getTireCon()/100);
        }
        pojazd->vAkt=pom;
        if(aktywnaTx!=1){
            aktywnaTx=1;
            aktualizujTx=1;
        }
    }
    else{
        float pom2=pojazd->vAkt;
        if(pojazd->vAkt>0){
            pojazd->vAkt=pojazd->vAkt-(pojazd->vAkt/500+0.05);
            if(pojazd->vAkt<0)
                pojazd->vAkt=0;
        }
        float pom=pojazd->vAkt;
        if(flaga){
            pojazd->vAkt=(pojazd->vAkt-vg)/5;
        }
        else{
            vg=pojazd->vAkt;
            pojazd->vAkt=pojazd->vAkt/5;
        }
        if(pom2==0 && (!flaga)){

        }
        else{
            przysrost=pojazd->naWprost((modSkretu),flaga,vg);
            ang=(modSkretu);
        }
        pojazd->vAkt=pom;

        if(aktywnaTx!=2){
            aktywnaTx=2;
            aktualizujTx=1;
        }

    }
    return przysrost;
}

