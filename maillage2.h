#include <Imagine/Images.h>
#include <Imagine/Graphics.h>
#include <iostream>
#include <vector>
using namespace Imagine;
using namespace std;


class pixel1{
public:
    IntPoint2 coor;
    bool app;//appartient au domaine ou a zone impating
    int voisinage;
    int maillage;
    int impaint;
    pixel1();
    pixel1(IntPoint2 q);
    pixel1(IntPoint2 p, bool t,int vois,int mail,int pos);
    pixel1(const pixel1& p);
    bool operator>(pixel1 p);
    bool operator<(pixel1 p);


};







class omega{
public:

   vector<pixel1> domaine;//zone connue
   vector<pixel1> impaint;//zone à impainter (triée en fonction du voisinage)



   pixel1 getdom(int i);
   omega();
   void remplit(const Image<Color>& img,vector<int>& taille);
   void impainting(const Image<Color>& img,vector<int>& taille,IntPoint2 a);


};

double dist(IntPoint2 p,IntPoint2 q);
double distress1(pixel1 p,pixel1 q1,const Image<Color>& img,const omega &d,const vector<double> &sinus,const vector<double> &cosinus,double gamma1);
double distress(pixel1 p,pixel1 q1,const Image<Color>& img,double gamma1,double gamma2,const omega& d,const vector<double> &sinus,const vector<double> &cosinus,bool per);
pixel1 elu(pixel1 p,omega& d,vector<double>& distr,vector<double>& distv,vector<pixel1>& argmax,vector<double> &max,vector<int>& taille,const Image<Color>& img,const vector<double> &sin,const vector<double> &cosinus,double gamma1,double gamma2,double lambda,bool speed);
void voisinage(omega& d,const Image<Color>& img);
void voisins(omega &d,const Image<Color> &img,pixel1 p,vector<pixel1> &listevoisins);
void retournemax(omega& d,vector<double>& distr,vector<pixel1>& argmax,vector<double> &max,vector<int>& taille,Image<Color>& img,double gamma1,double gamma2,double lambda,bool speed);

