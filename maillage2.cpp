#include <Imagine/Images.h>
#include <Imagine/Graphics.h>
#include <iostream>
#include "maillage2.h"
#include <Imagine/Images.h>
#include <Imagine/Graphics.h>
#include <vector>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <fstream>

using namespace std;

const int alpha1=0,alpha2=0,alpha3=0;//inf des intensités VBR
const int beta1=256,beta2=256,beta3=256;//sup
int n1=10,n2=10,n3=10;
int pas1=(beta1-alpha1)/n1;//discrétisation des intensités
int pas2=(beta2-alpha2)/n2;
int pas3=(beta3-alpha3)/n3;
//pour la distance de ressemblances

int n4=50;




//la classe pixel1 permet de reperer un point et de connaitre le "voisinage" et le "maillage" deux quantités utiles pour le maillage, et
//aussi de savoir si le point fait parti de la zone à inpainter ou non (app)


pixel1::pixel1(){
    coor=IntPoint2(-1,-1);
    voisinage=0;
    maillage=-1;
    app=false;
}
pixel1::pixel1(IntPoint2 q){
   voisinage=0;
   maillage=-1;
   impaint=-1;
   app=false;
    coor=q;

}

pixel1::pixel1(const pixel1& p){
    voisinage=p.voisinage;
    maillage=p.maillage;
    impaint=p.impaint;
    app=p.app;
    coor=p.coor;
}




pixel1::pixel1(IntPoint2 p, bool t,int vois,int mail,int pos){
    coor=p;
    app=t;
    maillage=mail;
    voisinage=vois;
    impaint=pos;
}
bool pixel1::operator>(pixel1 p){//pour pouvoir trier les pixels en fonction de leur voisinage
    if(voisinage==p.voisinage){
        if(coor[0]>p.coor[0]){
            return true;
        }else if(coor[0]==p.coor[0] && coor[1]>p.coor[1]){
            return true;
        }else{
            return false;
        }
    }

    return(voisinage>p.voisinage);
}

bool pixel1::operator<(pixel1 p){
    if(voisinage==p.voisinage){
        if(coor[0]<p.coor[0]){
            return true;
        }else if(coor[0]==p.coor[0] && coor[1]<p.coor[1]){
            return true;
        }else{
            return false;
        }
    }

    return(voisinage<p.voisinage);
}





//omega est un objet qui contient toutes les caractéristiques dont nous avons besoin pour l'inpainting
omega::omega(){
    domaine.clear();//contient tout les pixels de l'image
    domaine.reserve(512*512);
    impaint.clear();//zone de tout les pixels à impainter
    impaint.reserve(100*100);

}



pixel1 omega::getdom(int i){
    return domaine[i];
}


//crée les maillages et les différents vecteurs en fonction de l'image img, taille nous permet de stocker la taille de chaque "maillage"
void omega::remplit(const Image<Color> &img,vector<int> &taille){

    for(int i=0;i<img.height();i++){
        for(int j=0;j<img.width();j++){




                int red=img(i,j).r();
                int k=int((red-alpha1)/pas1);

                int blue=img(i,j).b();
                int l=int((blue-alpha2)/pas2);

                int green=img(i,j).g();
                int m=int((green-alpha3)/pas3);


                domaine.push_back(pixel1(IntPoint2(i,j),true,9,k+l*n1+m*n2*n1,-1));

                taille[k+l*n1+m*n2*n1]+=1;


            }

        }
    }

//remplit les vecteurs en fonction du masque choisi par l'utilisateur
void omega::impainting(const Image<Color> &img,vector<int> &taille,IntPoint2 a){
    if(domaine[a[0]*img.width()+a[1]].app==true){
    domaine[a[0]*img.width()+a[1]].app=false;
    domaine[a[0]*img.width()+a[1]].voisinage=0;
    impaint.push_back(pixel1(a,false,0,-1,-1));

}}




double dist(IntPoint2 p,IntPoint2 q){//distance euclidienne
    return(sqrt(pow(double((p[0]-q[0])),2.0)+pow(double((p[1]-q[1])),2.0)));
}
//fonction de distance de ressemblance entre deux pixels
double distress1(pixel1 p,pixel1 q1,const Image<Color> &img,const omega &d,const vector<double> &sinus,const vector<double> &cosinus,double gamma1){

    int n4=50;
    //on suppose que q1 appartient à domaine
    if(q1.app==true){

    int c=0;
    int n=0;
    double r=dist(p.coor,q1.coor);

    for(int k=0;k<n4;k++){

        //on trace un cercle de rayon r autour de q, et on regarde les pixels sur ce cercle qui ont une intensité proche de q
        IntPoint2 q(q1.coor[0]+r*cosinus[k]+0.5,q1.coor[1]+r*sinus[k]+0.5); //on introduit un pixel
         if(q[0]<img.width() && q[0]>=0 && q[1]<img.height() && q[1]>=0){
                 if(d.domaine[q[0]*img.width()+q[1]].app==true){

                     n++;
        if(sqrt(pow((int(img(q[0],q[1]).g())-int(img(q1.coor[0],q1.coor[1]).g())),2.0)+pow(int(img(q[0],q[1]).r())-int(img(q1.coor[0],q1.coor[1]).r()),2.0)+pow(int(img(q[0],q[1]).b())-int(img(q1.coor[0],q1.coor[1]).b()),2.0))<=7.0)  {                 //si q appartient à Wh ou Dh et norme(I(q)-I(q1))<epsilon

            c++;
    }
}}
    }
    if(n!=0){

    return (double(c)/(pow(double(r),gamma1)*double(n)));    //gamma1 un certain poids dépend de l'image

}return 0;
    }
    return 0;
}

double distress(pixel1 p,pixel1 q1,const Image<Color>& img,double gamma1,double gamma2,const omega& d,const vector<double> &sinus,const vector<double> &cosinus,bool per){
    if(per==true){
   if(!(2*q1.coor[0]-p.coor[0]<0 ||2*q1.coor[1]-p.coor[1]<0 || 2*q1.coor[0]-p.coor[0]>=img.width()||2*q1.coor[1]-p.coor[1]>=img.height() || d.domaine[(2*q1.coor[0]-p.coor[0])*img.width()+2*q1.coor[1]-p.coor[1]].app==false)){
    pixel1 q2(d.domaine[(2*q1.coor[0]-p.coor[0])*img.width()+2*q1.coor[1]-p.coor[1]]);

        return distress1(p,q1,img,d,sinus,cosinus,gamma1)+distress1(q1,q2,img,d,sinus,cosinus,gamma2);
}return distress1(p,q1,img,d,sinus,cosinus,gamma1);
}else{
        return distress1(p,q1,img,d,sinus,cosinus,gamma1);
    }}

//fonction qui determine le meilleur candidat q pour donner son intensité à p, les vectors argmax et max permettent notamment de stocker les maximum de distance de ressemblance par rapport à chaque maillage
//speed est une option qui permet de rendre l'algorithme bcp plus rapide

pixel1 elu(pixel1 p,omega &d,vector<double> &distr,vector<double> &distv,vector<pixel1> &argmax,vector<double> &max,vector<int> &taille,const Image<Color> &img,const vector<double>& sin,const vector<double> &cosinus,double gamma1,double gamma2,double lambda,bool speed){
    if(speed){
        int abs=p.coor[0];
        int ord=p.coor[1];
        int hg=std::max(0,abs-40);
        int hd=min(img.width(),abs+41);
        int bg=std::max(0,ord-40);
        int bd=min(img.height(),ord+41);
        for(int i=bg;i<bd;i++){
    for(int j=hg;j<hd;j++){
        pixel1 q(d.domaine[j*img.width()+i]);
        if(q.app==true){
        int j=q.maillage;

        double x=distress(p,q,img,gamma1,gamma2,d,sin,cosinus,false);


        if(dist(q.coor,p.coor)<=sqrt(2.0)){
           // cout<<"vois"<<endl;
            distr[j]+=1-lambda;
            distv[j]+=1-lambda;
        }
        if(x>max[j]||argmax[j].coor[0]==-1){
            //cout<<"chang"<<endl;
            argmax[j]=q;
            max[j]=x;

   }
}
    }}}else{


        for(int i=0;i<(d.domaine.size());i++){
            pixel1 q(d.domaine[i]);
            if(q.app==true){
            int j=q.maillage;

            double x=distress(p,q,img,gamma1,gamma2,d,sin,cosinus,false);


            if(taille[j]!=0)
            distr[j]+=(lambda*x/double(taille[j]));


            if(dist(q.coor,p.coor)<=sqrt(2.0)){

                distr[j]+=1-lambda;
                distv[j]+=1-lambda;
            }
            if(x>max[j]||argmax[j].coor[0]==-1){

                argmax[j]=q;
                max[j]=x;

       }
    }





    }
}
    int n=std::max_element(distr.begin(),distr.end())-distr.begin();
        cout<<distr[n]<<endl;
        cout<<distv[n]<<endl;
        cout<<max[n]<<endl;

    return argmax[n];

}
//cette fonction permet de calculer le voisinage pour chaque pixel, elle s'execute une seule fois par inpainting
void voisinage(omega &d,const Image<Color> &img){
    for(int i=0;i<(d.impaint).size();i++){
        pixel1 p=d.impaint[i];

        if(p.coor[0]==0){

            if(p.coor[1]==0){


                if(d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]+1].app==true)
                    (d.impaint[i]).voisinage+=1;

                if(d.domaine[(p.coor[0])*img.width()+p.coor[1]+1].app==true)
                    (d.impaint[i]).voisinage+=1;
                if(d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]].app==true)
                    (d.impaint[i]).voisinage+=1;

            }else if(p.coor[1]==img.height()-1){

                if(d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]].app==true)
                    (d.impaint[i]).voisinage+=1;
                if(d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]-1].app==true)
                    (d.impaint[i]).voisinage+=1;
                if(d.domaine[(p.coor[0])*img.width()+p.coor[1]-1].app==true)
                    (d.impaint[i]).voisinage+=1;

            }else{

                if(d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]].app==true)
                    (d.impaint[i]).voisinage+=1;
                if(d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]-1].app==true)
                    (d.impaint[i]).voisinage+=1;
                if(d.domaine[(p.coor[0])*img.width()+p.coor[1]-1].app==true)
                    (d.impaint[i]).voisinage+=1;


                if(d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]+1].app==true)
                    (d.impaint[i]).voisinage+=1;

                if(d.domaine[(p.coor[0])*img.width()+p.coor[1]+1].app==true)
                    (d.impaint[i]).voisinage+=1;
            }}else if(p.coor[0]==img.width()-1){
            if(p.coor[1]==0){

                if(d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]+1].app==true)
                    (d.impaint[i]).voisinage+=1;

                if(d.domaine[(p.coor[0])*img.width()+p.coor[1]+1].app==true)
                    (d.impaint[i]).voisinage+=1;
                if(d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]].app==true)
                    (d.impaint[i]).voisinage+=1;

            }else if(p.coor[1]==img.height()-1){

                if(d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]].app==true)
                    (d.impaint[i]).voisinage+=1;

                if(d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]-1].app==true)
                    (d.impaint[i]).voisinage+=1;

                if(d.domaine[(p.coor[0])*img.width()+p.coor[1]-1].app==true)
                    (d.impaint[i]).voisinage+=1;

            }else{

                if(d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]].app==true)
                    (d.impaint[i]).voisinage+=1;

                if(d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]-1].app==true)
                    (d.impaint[i]).voisinage+=1;

                if(d.domaine[(p.coor[0])*img.width()+p.coor[1]-1].app==true)
                    (d.impaint[i]).voisinage+=1;

                if(d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]+1].app==true)
                    (d.impaint[i]).voisinage+=1;

                if(d.domaine[(p.coor[0])*img.width()+p.coor[1]+1].app==true)
                    (d.impaint[i]).voisinage+=1;

            }}else if(p.coor[1]==img.height()-1){

            if(d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]].app==true)
                (d.impaint[i]).voisinage+=1;

            if(d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]-1].app==true)
                (d.impaint[i]).voisinage+=1;

            if(d.domaine[(p.coor[0])*img.width()+p.coor[1]-1].app==true)
                (d.impaint[i]).voisinage+=1;

            if(d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]].app==true)
                (d.impaint[i]).voisinage+=1;

            if(d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]-1].app==true)
                (d.impaint[i]).voisinage+=1;

        }else if(p.coor[1]==0){

            if(d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]].app==true)
                (d.impaint[i]).voisinage+=1;

            if(d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]+1].app==true)
                (d.impaint[i]).voisinage+=1;

            if(d.domaine[(p.coor[0])*img.width()+p.coor[1]+1].app==true)
                (d.impaint[i]).voisinage+=1;

            if(d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]].app==true)
                (d.impaint[i]).voisinage+=1;

            if(d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]+1].app==true)
                (d.impaint[i]).voisinage+=1;
        }else{

            if(d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]+1].app==true)
                (d.impaint[i]).voisinage+=1;

            if(d.domaine[(p.coor[0])*img.width()+p.coor[1]+1].app==true)
                (d.impaint[i]).voisinage+=1;

            if(d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]+1].app==true)
                (d.impaint[i]).voisinage+=1;

            if(d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]].app==true)
                (d.impaint[i]).voisinage+=1;

            if(d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]-1].app==true)
                (d.impaint[i]).voisinage+=1;

            if(d.domaine[(p.coor[0])*img.width()+p.coor[1]-1].app==true)
                (d.impaint[i]).voisinage+=1;

            if(d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]].app==true)
                (d.impaint[i]).voisinage+=1;

            if(d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]-1].app==true)
                (d.impaint[i]).voisinage+=1;
        }

    }

}
//cette fonction renvoie une liste avec les pixels voisins du pixel inpainté, et met à jour leur "voisinage"
void voisins(omega &d,const Image<Color> &img,pixel1 p,vector<pixel1> &listevoisins){


        if(p.coor[0]==0){

            if(p.coor[1]==0){


                d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]+1].voisinage+=1;

                listevoisins.push_back(d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]+1]);
               d.domaine[(p.coor[0])*img.width()+p.coor[1]+1].voisinage+=1;
               listevoisins.push_back(d.domaine[(p.coor[0])*img.width()+p.coor[1]+1]);

               d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]].voisinage+=1;
               listevoisins.push_back(d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]]);


            }else if(p.coor[1]==img.height()-1){

                d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]].voisinage+=1;
                listevoisins.push_back(d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]]);

                  d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]-1].voisinage+=1;
                  listevoisins.push_back(d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]-1]);

                d.domaine[(p.coor[0])*img.width()+p.coor[1]-1].voisinage+=1;
listevoisins.push_back(d.domaine[(p.coor[0])*img.width()+p.coor[1]-1]);

            }else{

                if(d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]].app==true)

                d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]-1].voisinage+=1;
                listevoisins.push_back(d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]-1]);


                d.domaine[(p.coor[0])*img.width()+p.coor[1]-1].voisinage+=1;
listevoisins.push_back(d.domaine[(p.coor[0])*img.width()+p.coor[1]-1]);


                d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]+1].voisinage+=1;
listevoisins.push_back(d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]+1]);

                d.domaine[(p.coor[0])*img.width()+p.coor[1]+1].voisinage+=1;
listevoisins.push_back(d.domaine[(p.coor[0])*img.width()+p.coor[1]+1]);


            }}else if(p.coor[0]==img.width()-1){
            if(p.coor[1]==0){

                d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]+1].voisinage+=1;
                listevoisins.push_back(d.domaine[(p.coor[0]-11)*img.width()+p.coor[1]+1]);

//
                d.domaine[(p.coor[0])*img.width()+p.coor[1]+1].voisinage+=1;
                listevoisins.push_back(d.domaine[(p.coor[0])*img.width()+p.coor[1]+1]);

               d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]].voisinage+=1;
listevoisins.push_back(d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]]);

            }else if(p.coor[1]==img.height()-1){

               d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]].voisinage+=1;
               listevoisins.push_back(d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]]);


               d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]-1].voisinage+=1;
listevoisins.push_back(d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]-1]);

               d.domaine[(p.coor[0])*img.width()+p.coor[1]-1].voisinage+=1;
listevoisins.push_back(d.domaine[(p.coor[0])*img.width()+p.coor[1]-1]);

            }else{

                d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]].voisinage+=1;
                listevoisins.push_back(d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]]);


                d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]-1].voisinage+=1;
listevoisins.push_back(d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]-1]);

                d.domaine[(p.coor[0])*img.width()+p.coor[1]-1].voisinage+=1;
listevoisins.push_back(d.domaine[(p.coor[0])*img.width()+p.coor[1]-1]);

                d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]+1].voisinage+=1;
listevoisins.push_back(d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]+1]);

               d.domaine[(p.coor[0])*img.width()+p.coor[1]+1].voisinage+=1;
listevoisins.push_back(d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]+1]);

            }}else if(p.coor[1]==img.height()-1){

            d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]].voisinage+=1;
            listevoisins.push_back(d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]]);


            d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]-1].voisinage+=1;
listevoisins.push_back(d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]-1]);

            d.domaine[(p.coor[0])*img.width()+p.coor[1]-1].voisinage+=1;
listevoisins.push_back(d.domaine[(p.coor[0])*img.width()+p.coor[1]-1]);

            d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]].voisinage+=1;
listevoisins.push_back(d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]]);

           d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]-1].voisinage+=1;
listevoisins.push_back(d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]-1]);

        }else if(p.coor[1]==0){

           d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]].voisinage+=1;
listevoisins.push_back(d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]]);

            d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]+1].voisinage+=1;
listevoisins.push_back(d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]+1]);

            d.domaine[(p.coor[0])*img.width()+p.coor[1]+1].voisinage+=1;
listevoisins.push_back(d.domaine[(p.coor[0])*img.width()+p.coor[1]+1]);

            d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]].voisinage+=1;
listevoisins.push_back(d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]]);

            d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]+1].voisinage+=1;
            listevoisins.push_back(d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]+1]);

        }else{

           d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]+1].voisinage+=1;
listevoisins.push_back(d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]+1]);

            d.domaine[(p.coor[0])*img.width()+p.coor[1]+1].voisinage+=1;
listevoisins.push_back(d.domaine[(p.coor[0])*img.width()+p.coor[1]+1]);

            d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]+1].voisinage+=1;
listevoisins.push_back(d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]+1]);

            d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]].voisinage+=1;

listevoisins.push_back(d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]]);

            d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]-1].voisinage+=1;
listevoisins.push_back(d.domaine[(p.coor[0]-1)*img.width()+p.coor[1]-1]);

            d.domaine[(p.coor[0])*img.width()+p.coor[1]-1].voisinage+=1;
listevoisins.push_back(d.domaine[(p.coor[0])*img.width()+p.coor[1]-1]);

            d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]].voisinage+=1;
listevoisins.push_back(d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]]);

            d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]-1].voisinage+=1;
listevoisins.push_back(d.domaine[(p.coor[0]+1)*img.width()+p.coor[1]-1]);
        }

    }








void retournemax(omega &d,vector<double> &distr,vector<pixel1> &argmax,vector<double> &max,vector<int> &taille,Image<Color> &img,double gamma1,double gamma2,double lambda,bool speed){
    //le principe de cette fonction est que l'on cherche à chaque fois à inpainter le pixel qui a le plus grand voisinage en appliquant la fonction elu
    double rmse=0;
    vector<double> sinus(50,0.0);
    vector<double> cosinus(50,0.0);
    for(int k=0;k<50;k++){
        sinus[k]=sin(double(k)*(2*M_PI/10.0));
        cosinus[k]=cos(double(k)*(2*M_PI/10.0));
    }
 vector<double> distv(11*11*11,0);
  int i=0;
  int j=0;
    vector<pixel1>lmax(d.impaint);
      sort(lmax.begin(),lmax.end());
  //trie lmax en fonction du voisinage
    while(i<d.impaint.size()){

      int n=lmax.size()-1;
      pixel1 q=elu(lmax[n],d,distr,distv,argmax,max,taille,img,sinus,cosinus,gamma1,gamma2,lambda,speed);
      //la fonction elu nous donne le pixel qui donnera son intensité en rouge vert bleu au pixel p que l'on cherchait à inpainter
      rmse=rmse+pow((img(lmax[n].coor[0],lmax[n].coor[1]).g()-img(q.coor[0],q.coor[1]).g()),2.0)+pow(img(lmax[n].coor[0],lmax[n].coor[1]).r()-img(q.coor[0],q.coor[1]).r(),2.0)+pow(img(lmax[n].coor[0],lmax[n].coor[1]).b()-img(q.coor[0],q.coor[1]).b(),2.0);
      //calcule la rmse au fur er à mesure, un indice de qualité de l'algorithme

        argmax=vector<pixel1>(11*11*11,pixel1());
        max=vector<double>(11*11*11,0);
      distr=vector<double>(11*11*11,0);
      distv=vector<double>(11*11*11,0);
      d.domaine[lmax[n].coor[0]*img.width()+lmax[n].coor[1]].app=true;
      d.domaine[lmax[n].coor[0]*img.width()+lmax[n].coor[1]].voisinage+=9;
      d.domaine[lmax[n].coor[0]*img.width()+lmax[n].coor[1]].maillage=q.maillage;

      img(lmax[n].coor[0],lmax[n].coor[1])=img(q.coor[0],q.coor[1]);
      //on remplace p par le pixel q d'intensités connues indiqué par la fonction elu(p)
      i++;


     vector<pixel1> listevoisins;
      voisins(d,img,lmax[n],listevoisins);
      std::vector<pixel1>::iterator low;
      lmax.pop_back();
      //on retire le dernier de lmax car il a été inpainté, et on recommence ces étapes jusqu'à que lmax soit vide
      //on met à jour la liste des pixels pour tenir compte du fait que l'on inpainté le dernier pixel de lmax, concretement cela pleut impliquer
      // que les voisins de ce pixel peuvent éventuellement changer de place dans lmax, vu que leur voisinage a augmenté de 1 et que lmax est triée selon le voisinage des pixels.
      for(int p=0;p<listevoisins.size();p++){
          q=listevoisins[p];

          low=lower_bound(lmax.begin(),lmax.end(),q);
          j=low-lmax.begin();
          if(lmax[j].coor==q.coor){

              lmax[j].voisinage+=1;
              while(q.voisinage<lmax[j+1].voisinage && j<lmax.size()-1){
                  lmax[j]=lmax[j+1];
                  lmax[j+1]=q;
                  j++;
              }


          }

      }

    }
    rmse=sqrt(rmse/(double(d.impaint.size())));
   // cout<<"rmse "<<rmse<<endl;




}

















