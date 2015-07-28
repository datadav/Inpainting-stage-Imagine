#include <Imagine/Images.h>
#include <Imagine/Graphics.h>
#include <iostream>
#include"maillage2.h"
#include <ctime>

using namespace Imagine;
using namespace std;

typedef Image<Color> Img;



int main()
{



    vector<double> sinus(50,0.0);
    vector<double> cosinus(50,0.0);
    //on calcule et stocke les cosinus et les sinus dont on a besoin une fois pour toute
    for(int k=0;k<50;k++){
        sinus[k]=sin(double(k)*(2*M_PI/10.0));
        cosinus[k]=cos(double(k)*(2*M_PI/10.0));

    }


    //changer le chemin pour changer l'image à inpainter
    Img image1;
    if (! load(image1,srcPath("lena.png")))
        return 0;

    Window W3=openComplexWindow(image1.height(),100+image1.width(),"Impainting",3);
    showWindow(W3,0);
    display(image1,0,100);
    drawString(0,10,"cliquez sur clique gauche pour commencer ",BLUE,10);
    Event ev;
    getEvent(-1,ev);
    fillRect(0,20,500,-20,WHITE);
    showWindow(W3,1);
    setActiveWindow(W3,1);

    display(image1,0,100);






    omega om;
    vector<int> taille(11*11*11,0);
    om.remplit(image1,taille);
    //interface qui permet la création du masque
    drawString(0,10,"pour un trait d'épaisseur 1,2 ou 3 tapez 1,2 ou 3 ",BLUE,10);
    drawString(0,30,"dessinez en appuyant sur le clic gauche de la souris ",BLUE,10);
    drawString(0,50,"appuyez sur entrée pour lancer l'impainting ",BLUE,10);
    drawString(0,70,"choisissez une epaisseur ",RED,10);

    int i=0;


    // tant que l'utilisateur ne clique par sur entrée, il peut rajouter des zones à inpainter
    while(ev.key!=16777220){


        if(ev.key==49){
            fillRect(0,90,500,-30,WHITE);
            drawString(0,70,"vous avez choisi l'épaisseur 1",BLUE,10);
            getEvent(-1,ev);
            while(ev.type!=EVT_KEY_ON){

                getEvent(0,ev);

                if(ev.type==EVT_BUT_ON){
                    if(ev.button==1){

                        ev.pix.x();
                        ev.pix.y();
                        IntPoint2 p(ev.pix);

                        if(ev.pix[0]>=0 && ev.pix[0]<=image1.width() && ev.pix[1]>=100 && ev.pix[1]<=100+image1.height()){
                            drawPoint(p,WHITE);
                            drawPoint(IntPoint2(p[0],p[1]+1),WHITE);
                            drawPoint(IntPoint2(p[0],p[1]-1),WHITE);
                            drawPoint(IntPoint2(p[0]+1,p[1]+1),WHITE);
                            drawPoint(IntPoint2(p[0]+1,p[1]-1),WHITE);
                            drawPoint(IntPoint2(p[0]-1,p[1]+1),WHITE);
                            drawPoint(IntPoint2(p[0]-1,p[1]-1),WHITE);
                            om.impainting(image1,taille,p-IntPoint2(0,100));
                            om.impainting(image1,taille,IntPoint2(p[0],p[1]-100+1));
                            om.impainting(image1,taille,IntPoint2(p[0],p[1]-100-1));
                            om.impainting(image1,taille,IntPoint2(p[0]+1,p[1]-100+1));
                            om.impainting(image1,taille,IntPoint2(p[0]+1,p[1]-100-1));
                            om.impainting(image1,taille,IntPoint2(p[0]-1,p[1]-100+1));
                            om.impainting(image1,taille,IntPoint2(p[0]-1,p[1]-100-1));



                        }}}else if(ev.type==EVT_MOTION){

                    ev.pix.x();
                    ev.pix.y();
                    IntPoint2 p(ev.pix);
                    if(ev.pix[0]>=0 && ev.pix[0]<=image1.width() && ev.pix[1]>=100 && ev.pix[1]<=100+image1.height()){
                        drawPoint(p,WHITE);
                        drawPoint(IntPoint2(p[0],p[1]+1),WHITE);
                        drawPoint(IntPoint2(p[0],p[1]-1),WHITE);
                        drawPoint(IntPoint2(p[0]+1,p[1]+1),WHITE);
                        drawPoint(IntPoint2(p[0]+1,p[1]-1),WHITE);
                        drawPoint(IntPoint2(p[0]-1,p[1]+1),WHITE);
                        drawPoint(IntPoint2(p[0]-1,p[1]-1),WHITE);
                        om.impainting(image1,taille,p-IntPoint2(0,100));
                        om.impainting(image1,taille,IntPoint2(p[0],p[1]-100+1));
                        om.impainting(image1,taille,IntPoint2(p[0],p[1]-100-1));
                        om.impainting(image1,taille,IntPoint2(p[0]+1,p[1]-100+1));
                        om.impainting(image1,taille,IntPoint2(p[0]+1,p[1]-100-1));
                        om.impainting(image1,taille,IntPoint2(p[0]-1,p[1]-100+1));
                        om.impainting(image1,taille,IntPoint2(p[0]-1,p[1]-100-1));

                    }

                }

                i++;

            }fillRect(0,90,500,-30,WHITE);}//cout<<"clavier"<<ev.key<<endl;
        else if(ev.key==50){
            fillRect(0,90,500,-30,WHITE);
            drawString(0,70,"vous avez choisi l'épaisseur 2",BLUE,10);
            getEvent(-1,ev);
            while(ev.type!=EVT_KEY_ON){

                getEvent(0,ev);

                if(ev.type==EVT_BUT_ON){
                    if(ev.button==1){

                        ev.pix.x();
                        ev.pix.y();
                        IntPoint2 p(ev.pix);

                        if(ev.pix[0]>=0 && ev.pix[0]<=image1.width() && ev.pix[1]>=100 && ev.pix[1]<=100+image1.height()){
                            drawPoint(p,WHITE);
                            drawPoint(IntPoint2(p[0],p[1]+1),WHITE);
                            drawPoint(IntPoint2(p[0],p[1]-1),WHITE);
                            drawPoint(IntPoint2(p[0]+1,p[1]+1),WHITE);
                            drawPoint(IntPoint2(p[0]+1,p[1]-1),WHITE);
                            drawPoint(IntPoint2(p[0]-1,p[1]+1),WHITE);
                            drawPoint(IntPoint2(p[0]-1,p[1]-1),WHITE);
                            om.impainting(image1,taille,p-IntPoint2(0,100));
                            om.impainting(image1,taille,IntPoint2(p[0],p[1]-100+1));
                            om.impainting(image1,taille,IntPoint2(p[0],p[1]-100-1));
                            om.impainting(image1,taille,IntPoint2(p[0]+1,p[1]-100+1));
                            om.impainting(image1,taille,IntPoint2(p[0]+1,p[1]-100-1));
                            om.impainting(image1,taille,IntPoint2(p[0]-1,p[1]-100+1));
                            om.impainting(image1,taille,IntPoint2(p[0]-1,p[1]-100-1));
                            drawPoint(IntPoint2(p[0],p[1]+2),WHITE);
                            drawPoint(IntPoint2(p[0],p[1]-2),WHITE);
                            drawPoint(IntPoint2(p[0]+2,p[1]+2),WHITE);
                            drawPoint(IntPoint2(p[0]+2,p[1]-2),WHITE);
                            drawPoint(IntPoint2(p[0]-2,p[1]+2),WHITE);
                            drawPoint(IntPoint2(p[0]-2,p[1]-2),WHITE);
                            //
                            drawPoint(IntPoint2(p[0]-1,p[1]-2),WHITE);
                            drawPoint(IntPoint2(p[0]+1,p[1]+2),WHITE);
                            drawPoint(IntPoint2(p[0]+1,p[1]-2),WHITE);
                            drawPoint(IntPoint2(p[0]-1,p[1]+2),WHITE);
                            drawPoint(IntPoint2(p[0]-2,p[1]+1),WHITE);
                            drawPoint(IntPoint2(p[0]-2,p[1]-1),WHITE);
                            drawPoint(IntPoint2(p[0]+2,p[1]-1),WHITE);
                            drawPoint(IntPoint2(p[0]+2,p[1]+1),WHITE);
                            om.impainting(image1,taille,p-IntPoint2(0,100));
                            om.impainting(image1,taille,IntPoint2(p[0],p[1]-100+2));
                            om.impainting(image1,taille,IntPoint2(p[0],p[1]-100-2));
                            om.impainting(image1,taille,IntPoint2(p[0]+2,p[1]-100+2));
                            om.impainting(image1,taille,IntPoint2(p[0]+2,p[1]-100-2));
                            om.impainting(image1,taille,IntPoint2(p[0]-2,p[1]-100+2));
                            om.impainting(image1,taille,IntPoint2(p[0]-2,p[1]-100-2));
                            om.impainting(image1,taille,IntPoint2(p[0]-1,p[1]-100-2));
                            om.impainting(image1,taille,IntPoint2(p[0]+1,p[1]-100+2));
                            om.impainting(image1,taille,IntPoint2(p[0]+1,p[1]-100-2));
                            om.impainting(image1,taille,IntPoint2(p[0]-1,p[1]-100+2));
                            om.impainting(image1,taille,IntPoint2(p[0]-2,p[1]-100+1));
                            om.impainting(image1,taille,IntPoint2(p[0]-2,p[1]-100-1));
                            om.impainting(image1,taille,IntPoint2(p[0]+2,p[1]-100-1));
                            om.impainting(image1,taille,IntPoint2(p[0]+2,p[1]-100+1));


                        }}}else if(ev.type==EVT_MOTION){

                    ev.pix.x();
                    ev.pix.y();
                    IntPoint2 p(ev.pix);
                    if(ev.pix[0]>=0 && ev.pix[0]<=image1.width() && ev.pix[1]>=100 && ev.pix[1]<=100+image1.height()){
                        drawPoint(p,WHITE);
                        drawPoint(IntPoint2(p[0],p[1]+1),WHITE);
                        drawPoint(IntPoint2(p[0],p[1]-1),WHITE);
                        drawPoint(IntPoint2(p[0]+1,p[1]+1),WHITE);
                        drawPoint(IntPoint2(p[0]+1,p[1]-1),WHITE);
                        drawPoint(IntPoint2(p[0]-1,p[1]+1),WHITE);
                        drawPoint(IntPoint2(p[0]-1,p[1]-1),WHITE);
                        om.impainting(image1,taille,p-IntPoint2(0,100));
                        om.impainting(image1,taille,IntPoint2(p[0],p[1]-100+1));
                        om.impainting(image1,taille,IntPoint2(p[0],p[1]-100-1));
                        om.impainting(image1,taille,IntPoint2(p[0]+1,p[1]-100+1));
                        om.impainting(image1,taille,IntPoint2(p[0]+1,p[1]-100-1));
                        om.impainting(image1,taille,IntPoint2(p[0]-1,p[1]-100+1));
                        om.impainting(image1,taille,IntPoint2(p[0]-1,p[1]-100-1));
                        drawPoint(IntPoint2(p[0],p[1]+2),WHITE);
                        drawPoint(IntPoint2(p[0],p[1]-2),WHITE);
                        drawPoint(IntPoint2(p[0]+2,p[1]+2),WHITE);
                        drawPoint(IntPoint2(p[0]+2,p[1]-2),WHITE);
                        drawPoint(IntPoint2(p[0]-2,p[1]+2),WHITE);
                        drawPoint(IntPoint2(p[0]-2,p[1]-2),WHITE);
                        //
                        drawPoint(IntPoint2(p[0]-1,p[1]-2),WHITE);
                        drawPoint(IntPoint2(p[0]+1,p[1]+2),WHITE);
                        drawPoint(IntPoint2(p[0]+1,p[1]-2),WHITE);
                        drawPoint(IntPoint2(p[0]-1,p[1]+2),WHITE);
                        drawPoint(IntPoint2(p[0]-2,p[1]+1),WHITE);
                        drawPoint(IntPoint2(p[0]-2,p[1]-1),WHITE);
                        drawPoint(IntPoint2(p[0]+2,p[1]-1),WHITE);
                        drawPoint(IntPoint2(p[0]+2,p[1]+1),WHITE);
                        om.impainting(image1,taille,p-IntPoint2(0,100));
                        om.impainting(image1,taille,IntPoint2(p[0],p[1]-100+2));
                        om.impainting(image1,taille,IntPoint2(p[0],p[1]-100-2));
                        om.impainting(image1,taille,IntPoint2(p[0]+2,p[1]-100+2));
                        om.impainting(image1,taille,IntPoint2(p[0]+2,p[1]-100-2));
                        om.impainting(image1,taille,IntPoint2(p[0]-2,p[1]-100+2));
                        om.impainting(image1,taille,IntPoint2(p[0]-2,p[1]-100-2));
                        om.impainting(image1,taille,IntPoint2(p[0]-1,p[1]-100-2));
                        om.impainting(image1,taille,IntPoint2(p[0]+1,p[1]-100+2));
                        om.impainting(image1,taille,IntPoint2(p[0]+1,p[1]-100-2));
                        om.impainting(image1,taille,IntPoint2(p[0]-1,p[1]-100+2));
                        om.impainting(image1,taille,IntPoint2(p[0]-2,p[1]-100+1));
                        om.impainting(image1,taille,IntPoint2(p[0]-2,p[1]-100-1));
                        om.impainting(image1,taille,IntPoint2(p[0]+2,p[1]-100-1));
                        om.impainting(image1,taille,IntPoint2(p[0]+2,p[1]-100+1));
                    }

                }


            }//cout<<"clavier"<<ev.key<<endl;

            fillRect(0,90,500,-30,WHITE);










        }else if(ev.key==51){




            fillRect(0,90,500,-30,WHITE);
            drawString(0,70,"vous avez choisi l'épaisseur 3",BLUE,10);
            getEvent(-1,ev);
            while(ev.type!=EVT_KEY_ON){

                getEvent(0,ev);

                if(ev.type==EVT_BUT_ON){
                    if(ev.button==1){

                        ev.pix.x();
                        ev.pix.y();
                        IntPoint2 p(ev.pix);

                        if(ev.pix[0]>=0 && ev.pix[0]<=image1.width() && ev.pix[1]>=100 && ev.pix[1]<=100+image1.height()){
                            drawPoint(p,WHITE);
                            drawPoint(IntPoint2(p[0],p[1]+1),WHITE);
                            drawPoint(IntPoint2(p[0],p[1]-1),WHITE);
                            drawPoint(IntPoint2(p[0]+1,p[1]+1),WHITE);
                            drawPoint(IntPoint2(p[0]+1,p[1]-1),WHITE);
                            drawPoint(IntPoint2(p[0]-1,p[1]+1),WHITE);
                            drawPoint(IntPoint2(p[0]-1,p[1]-1),WHITE);
                            om.impainting(image1,taille,p-IntPoint2(0,100));

                            om.impainting(image1,taille,IntPoint2(p[0],p[1]-100+1));
                            om.impainting(image1,taille,IntPoint2(p[0],p[1]-100-1));
                            om.impainting(image1,taille,IntPoint2(p[0]+1,p[1]-100+1));
                            om.impainting(image1,taille,IntPoint2(p[0]+1,p[1]-100-1));
                            om.impainting(image1,taille,IntPoint2(p[0]-1,p[1]-100+1));
                            om.impainting(image1,taille,IntPoint2(p[0]-1,p[1]-100-1));
                            drawPoint(IntPoint2(p[0],p[1]+2),WHITE);
                            drawPoint(IntPoint2(p[0],p[1]-2),WHITE);
                            drawPoint(IntPoint2(p[0]+2,p[1]+2),WHITE);
                            drawPoint(IntPoint2(p[0]+2,p[1]-2),WHITE);
                            drawPoint(IntPoint2(p[0]-2,p[1]+2),WHITE);
                            drawPoint(IntPoint2(p[0]-2,p[1]-2),WHITE);
                            //
                            drawPoint(IntPoint2(p[0]-1,p[1]-2),WHITE);
                            drawPoint(IntPoint2(p[0]+1,p[1]+2),WHITE);
                            drawPoint(IntPoint2(p[0]+1,p[1]-2),WHITE);
                            drawPoint(IntPoint2(p[0]-1,p[1]+2),WHITE);
                            drawPoint(IntPoint2(p[0]-2,p[1]+1),WHITE);
                            drawPoint(IntPoint2(p[0]-2,p[1]-1),WHITE);
                            drawPoint(IntPoint2(p[0]+2,p[1]-1),WHITE);
                            drawPoint(IntPoint2(p[0]+2,p[1]+1),WHITE);
                            drawPoint(IntPoint2(p[0]+2,p[1]),WHITE);
                            drawPoint(IntPoint2(p[0]-2,p[1]),WHITE);
                            om.impainting(image1,taille,p-IntPoint2(0,100));
                            om.impainting(image1,taille,IntPoint2(p[0],p[1]-100+2));
                            om.impainting(image1,taille,IntPoint2(p[0],p[1]-100-2));
                            om.impainting(image1,taille,IntPoint2(p[0]+2,p[1]-100+2));
                            om.impainting(image1,taille,IntPoint2(p[0]+2,p[1]-100-2));
                            om.impainting(image1,taille,IntPoint2(p[0]-2,p[1]-100+2));
                            om.impainting(image1,taille,IntPoint2(p[0]-2,p[1]-100-2));
                            om.impainting(image1,taille,IntPoint2(p[0]-1,p[1]-100-2));
                            om.impainting(image1,taille,IntPoint2(p[0]+1,p[1]-100+2));
                            om.impainting(image1,taille,IntPoint2(p[0]+1,p[1]-100-2));
                            om.impainting(image1,taille,IntPoint2(p[0]-1,p[1]-100+2));
                            om.impainting(image1,taille,IntPoint2(p[0]-2,p[1]-100+1));
                            om.impainting(image1,taille,IntPoint2(p[0]-2,p[1]-100-1));
                            om.impainting(image1,taille,IntPoint2(p[0]+2,p[1]-100-1));
                            om.impainting(image1,taille,IntPoint2(p[0]+2,p[1]-100+1));
                            om.impainting(image1,taille,IntPoint2(p[0]+2,p[1]-100));
                            om.impainting(image1,taille,IntPoint2(p[0]-2,p[1]-100));

                            drawPoint(IntPoint2(p[0]-1,p[1]-3),WHITE);
                            drawPoint(IntPoint2(p[0]-1,p[1]+3),WHITE);
                            drawPoint(IntPoint2(p[0]+1,p[1]-3),WHITE);
                            drawPoint(IntPoint2(p[0]+1,p[1]+3),WHITE);
                            drawPoint(IntPoint2(p[0]-3,p[1]+1),WHITE);
                            drawPoint(IntPoint2(p[0]-3,p[1]-1),WHITE);
                            drawPoint(IntPoint2(p[0]+3,p[1]-1),WHITE);
                            drawPoint(IntPoint2(p[0]+3,p[1]+1),WHITE);


                            drawPoint(IntPoint2(p[0]-2,p[1]-3),WHITE);
                            drawPoint(IntPoint2(p[0]-2,p[1]+3),WHITE);
                            drawPoint(IntPoint2(p[0]+2,p[1]-3),WHITE);
                            drawPoint(IntPoint2(p[0]+2,p[1]+3),WHITE);
                            drawPoint(IntPoint2(p[0]-3,p[1]+2),WHITE);
                            drawPoint(IntPoint2(p[0]-3,p[1]-2),WHITE);
                            drawPoint(IntPoint2(p[0]+3,p[1]-2),WHITE);
                            drawPoint(IntPoint2(p[0]+3,p[1]+2),WHITE);
                            drawPoint(IntPoint2(p[0]+3,p[1]),WHITE);
                            drawPoint(IntPoint2(p[0]-3,p[1]),WHITE);
                            drawPoint(IntPoint2(p[0],p[1]+3),WHITE);
                            drawPoint(IntPoint2(p[0],p[1]-3),WHITE);

                            om.impainting(image1,taille,IntPoint2(p[0]-1,p[1]-100-3));
                            om.impainting(image1,taille,IntPoint2(p[0]-1,p[1]-100+3));
                            om.impainting(image1,taille,IntPoint2(p[0]+1,p[1]-100-3));
                            om.impainting(image1,taille,IntPoint2(p[0]+1,p[1]-100+3));
                            om.impainting(image1,taille,IntPoint2(p[0]-3,p[1]-100+1));
                            om.impainting(image1,taille,IntPoint2(p[0]-3,p[1]-100-1));
                            om.impainting(image1,taille,IntPoint2(p[0]+3,p[1]-100-1));
                            om.impainting(image1,taille,IntPoint2(p[0]+3,p[1]-100+1));
                            om.impainting(image1,taille,IntPoint2(p[0]-2,p[1]-100-3));
                            om.impainting(image1,taille,IntPoint2(p[0]-2,p[1]-100+3));
                            om.impainting(image1,taille,IntPoint2(p[0]+2,p[1]-100-3));
                            om.impainting(image1,taille,IntPoint2(p[0]+2,p[1]-100+3));
                            om.impainting(image1,taille,IntPoint2(p[0]-3,p[1]-100+2));
                            om.impainting(image1,taille,IntPoint2(p[0]-3,p[1]-100-2));
                            om.impainting(image1,taille,IntPoint2(p[0]+3,p[1]-100-2));
                            om.impainting(image1,taille,IntPoint2(p[0]+3,p[1]-100+2));
                            om.impainting(image1,taille,IntPoint2(p[0]+3,p[1]-100));
                            om.impainting(image1,taille,IntPoint2(p[0]-3,p[1]-100));
                            om.impainting(image1,taille,IntPoint2(p[0],p[1]-100+3));
                            om.impainting(image1,taille,IntPoint2(p[0],p[1]-100-3));



                        }}}else if(ev.type==EVT_MOTION){

                    ev.pix.x();
                    ev.pix.y();
                    IntPoint2 p(ev.pix);
                    if(ev.pix[0]>=0 && ev.pix[0]<=image1.width() && ev.pix[1]>=100 && ev.pix[1]<=100+image1.height()){
                        drawPoint(p,WHITE);
                        drawPoint(IntPoint2(p[0],p[1]+1),WHITE);
                        drawPoint(IntPoint2(p[0],p[1]-1),WHITE);
                        drawPoint(IntPoint2(p[0]+1,p[1]+1),WHITE);
                        drawPoint(IntPoint2(p[0]+1,p[1]-1),WHITE);
                        drawPoint(IntPoint2(p[0]-1,p[1]+1),WHITE);
                        drawPoint(IntPoint2(p[0]-1,p[1]-1),WHITE);
                        om.impainting(image1,taille,p-IntPoint2(0,100));
                        om.impainting(image1,taille,IntPoint2(p[0],p[1]-100+1));
                        om.impainting(image1,taille,IntPoint2(p[0],p[1]-100-1));
                        om.impainting(image1,taille,IntPoint2(p[0]+1,p[1]-100+1));
                        om.impainting(image1,taille,IntPoint2(p[0]+1,p[1]-100-1));
                        om.impainting(image1,taille,IntPoint2(p[0]-1,p[1]-100+1));
                        om.impainting(image1,taille,IntPoint2(p[0]-1,p[1]-100-1));
                        drawPoint(IntPoint2(p[0],p[1]+2),WHITE);
                        drawPoint(IntPoint2(p[0],p[1]-2),WHITE);
                        drawPoint(IntPoint2(p[0]+2,p[1]+2),WHITE);
                        drawPoint(IntPoint2(p[0]+2,p[1]-2),WHITE);
                        drawPoint(IntPoint2(p[0]-2,p[1]+2),WHITE);
                        drawPoint(IntPoint2(p[0]-2,p[1]-2),WHITE);
                        //
                        drawPoint(IntPoint2(p[0]-1,p[1]-2),WHITE);
                        drawPoint(IntPoint2(p[0]+1,p[1]+2),WHITE);
                        drawPoint(IntPoint2(p[0]+1,p[1]-2),WHITE);
                        drawPoint(IntPoint2(p[0]-1,p[1]+2),WHITE);
                        drawPoint(IntPoint2(p[0]-2,p[1]+1),WHITE);
                        drawPoint(IntPoint2(p[0]-2,p[1]-1),WHITE);
                        drawPoint(IntPoint2(p[0]+2,p[1]-1),WHITE);
                        drawPoint(IntPoint2(p[0]+2,p[1]+1),WHITE);
                        drawPoint(IntPoint2(p[0]+2,p[1]),WHITE);
                        drawPoint(IntPoint2(p[0]-2,p[1]),WHITE);
                        om.impainting(image1,taille,p-IntPoint2(0,100));
                        om.impainting(image1,taille,IntPoint2(p[0],p[1]-100+2));
                        om.impainting(image1,taille,IntPoint2(p[0],p[1]-100-2));
                        om.impainting(image1,taille,IntPoint2(p[0]+2,p[1]-100+2));
                        om.impainting(image1,taille,IntPoint2(p[0]+2,p[1]-100-2));
                        om.impainting(image1,taille,IntPoint2(p[0]-2,p[1]-100+2));
                        om.impainting(image1,taille,IntPoint2(p[0]-2,p[1]-100-2));
                        om.impainting(image1,taille,IntPoint2(p[0]-1,p[1]-100-2));
                        om.impainting(image1,taille,IntPoint2(p[0]+1,p[1]-100+2));
                        om.impainting(image1,taille,IntPoint2(p[0]+1,p[1]-100-2));
                        om.impainting(image1,taille,IntPoint2(p[0]-1,p[1]-100+2));
                        om.impainting(image1,taille,IntPoint2(p[0]-2,p[1]-100+1));
                        om.impainting(image1,taille,IntPoint2(p[0]-2,p[1]-100-1));
                        om.impainting(image1,taille,IntPoint2(p[0]+2,p[1]-100-1));
                        om.impainting(image1,taille,IntPoint2(p[0]+2,p[1]-100+1));
                        om.impainting(image1,taille,IntPoint2(p[0]+2,p[1]-100));
                        om.impainting(image1,taille,IntPoint2(p[0]-2,p[1]-100));

                        drawPoint(IntPoint2(p[0]-1,p[1]-3),WHITE);
                        drawPoint(IntPoint2(p[0]-1,p[1]+3),WHITE);
                        drawPoint(IntPoint2(p[0]+1,p[1]-3),WHITE);
                        drawPoint(IntPoint2(p[0]+1,p[1]+3),WHITE);
                        drawPoint(IntPoint2(p[0]-3,p[1]+1),WHITE);
                        drawPoint(IntPoint2(p[0]-3,p[1]-1),WHITE);
                        drawPoint(IntPoint2(p[0]+3,p[1]-1),WHITE);
                        drawPoint(IntPoint2(p[0]+3,p[1]+1),WHITE);


                        drawPoint(IntPoint2(p[0]-2,p[1]-3),WHITE);
                        drawPoint(IntPoint2(p[0]-2,p[1]+3),WHITE);
                        drawPoint(IntPoint2(p[0]+2,p[1]-3),WHITE);
                        drawPoint(IntPoint2(p[0]+2,p[1]+3),WHITE);
                        drawPoint(IntPoint2(p[0]-3,p[1]+2),WHITE);
                        drawPoint(IntPoint2(p[0]-3,p[1]-2),WHITE);
                        drawPoint(IntPoint2(p[0]+3,p[1]-2),WHITE);
                        drawPoint(IntPoint2(p[0]+3,p[1]+2),WHITE);
                        drawPoint(IntPoint2(p[0]+3,p[1]),WHITE);
                        drawPoint(IntPoint2(p[0]-3,p[1]),WHITE);
                        drawPoint(IntPoint2(p[0],p[1]+3),WHITE);
                        drawPoint(IntPoint2(p[0],p[1]-3),WHITE);

                        om.impainting(image1,taille,IntPoint2(p[0]-1,p[1]-100-3));
                        om.impainting(image1,taille,IntPoint2(p[0]-1,p[1]-100+3));
                        om.impainting(image1,taille,IntPoint2(p[0]+1,p[1]-100-3));
                        om.impainting(image1,taille,IntPoint2(p[0]+1,p[1]-100+3));
                        om.impainting(image1,taille,IntPoint2(p[0]-3,p[1]-100+1));
                        om.impainting(image1,taille,IntPoint2(p[0]-3,p[1]-100-1));
                        om.impainting(image1,taille,IntPoint2(p[0]+3,p[1]-100-1));
                        om.impainting(image1,taille,IntPoint2(p[0]+3,p[1]-100+1));
                        om.impainting(image1,taille,IntPoint2(p[0]-2,p[1]-100-3));
                        om.impainting(image1,taille,IntPoint2(p[0]-2,p[1]-100+3));
                        om.impainting(image1,taille,IntPoint2(p[0]+2,p[1]-100-3));
                        om.impainting(image1,taille,IntPoint2(p[0]+2,p[1]-100+3));
                        om.impainting(image1,taille,IntPoint2(p[0]-3,p[1]-100+2));
                        om.impainting(image1,taille,IntPoint2(p[0]-3,p[1]-100-2));
                        om.impainting(image1,taille,IntPoint2(p[0]+3,p[1]-100-2));
                        om.impainting(image1,taille,IntPoint2(p[0]+3,p[1]-100+2));
                        om.impainting(image1,taille,IntPoint2(p[0]+3,p[1]-100));
                        om.impainting(image1,taille,IntPoint2(p[0]-3,p[1]-100));
                        om.impainting(image1,taille,IntPoint2(p[0],p[1]-100+3));
                        om.impainting(image1,taille,IntPoint2(p[0],p[1]-100-3));


                    }

                }

                i++;
            }
            fillRect(0,90,500,-30,WHITE);









        }
        getEvent(-1,ev); }



    pixel1 q3;

    voisinage(om,image1);




    vector<pixel1> argmax(11*11*11,q3);
    vector<double> max(11*11*11,0);

    vector<double> distr(11*11*11,0);
    vector<double> distv(11*11*11,0);


    retournemax(om,distr,argmax,max,taille,image1,0.1,100000,0.99,false);
    //retourne max lance l'inpainting pour le masque que l'utilisateur a crée

    showWindow(W3,2);
    setActiveWindow(W3,2);
    drawString(0,70,"Impainting terminée ",RED,10);
    display(image1,0,100);

    endGraphics();
    return 0;
}

