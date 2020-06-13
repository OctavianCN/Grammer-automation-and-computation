#include "Gramatica.h"
#include <fstream>
#include <iostream>
using namespace std;
Gramatica::Gramatica(char *numefisier)
{
  ifstream f(numefisier);
  int i,j;
  f>>NrN;

  N=new char[NrN];
  for(i=0;i<NrN;i++);
  {
     f>>N[i];
  }
  f>>NrT;
  cout<<NrT;
  T=new char[NrT];
  for(i=0;i<NrT;i++)
    f>>T[i];
  f>>S;
  f>>NrP;

 P=new Productii[NrP];

  for(i=0;i<NrP;i++)
  {
      f>>P[i].Net;
      f>>P[i].NrProd;
      P[i].prod=new char[P[i].NrProd];
      for(j=0;j<P[i].NrProd;j++)
        f>>P[i].prod[j];
      f>>P[i].NetProd;
  }

  for(i=0;i<NrN;i++);
   cout<<N[i];
  cout<<NrT;
  for(i=0;i<NrT;i++)
    cout<<T[i];
  cout<<S;
  cout<<NrP;
  for(i=0;i<NrP;i++)
  {
      cout<<P[i].Net;
      cout<<P[i].NrProd;
      for(j=0;j<P[i].NrProd;j++)
        cout<<P[i].prod[j];
      cout<<P[i].NetProd;
  }
}
Gramatica::~Gramatica()
{
  int i;
  delete(N);
  delete(T);
   for(i=0;i<NrP;i++)
  {
     delete(P[i].prod);
  }
 delete(P);
}
Gramatica::GenerareCuvinte(int n)
{
    int i,j,NrCuvInit,l,NrCuv=0,ok=1,*poz=new int[NrP];
    int t,k=0;
    typedef struct
    {
        char *cuv;
        char net;
        int Nrlitere;
    }Cuvant;
    Cuvant *cuvant=new Cuvant[100];
    while(ok==1)
    {
     if(NrCuv!=0)
      {
         NrCuvInit=NrCuv;
         for(i=0;i<NrCuvInit;i++)
         {
             l=0;//Dec cate ori a fost gasit neterminalul cuvantului in productii;
             for(j=0;j<NrP;j++)
             {
                 if(cuvant[i].net==P[j].Net)
                 {
                     poz[l]=j;
                     l++;
                 }
             }
             if(l!=1)
             {
                 for(j=0;j<l-1;j++)
                 {
                    cuvant[NrCuv].cuv=new char[n];
                    cuvant[NrCuv].Nrlitere=cuvant[i].Nrlitere+P[poz[j]].NrProd;

                    for(t=0;t<cuvant[i].Nrlitere;t++)
                        cuvant[NrCuv].cuv[t]=cuvant[i].cuv[t];
                    for(t=cuvant[i].Nrlitere;t<cuvant[NrCuv].Nrlitere;t++)
                       {


                           cuvant[NrCuv].cuv[t]=P[poz[j]].prod[k];
                           k++;

                       }
                       cuvant[i].net=P[poz[j]].Net;
                    NrCuv++;
                 }
                 k=0;
                 for(t=cuvant[i].Nrlitere;t<cuvant[i].Nrlitere+P[poz[l-1]].NrProd;t++)
                       {


                            cuvant[i].cuv[t]=P[poz[l-1]].prod[k];
                           k++;

                       }
                 cuvant[i].net=P[poz[l-1]].Net;
                 cuvant[i].Nrlitere=cuvant[i].Nrlitere+P[poz[l-1]].NrProd;

             }
             else
             {
                 k=0;
                 for(t=cuvant[i].Nrlitere;t<cuvant[i].Nrlitere+P[poz[l-1]].NrProd;t++)
                       {
                           cuvant[i].cuv[t]=P[poz[l-1]].prod[k];
                           k++;
                       }
                 cuvant[i].net=P[poz[l-1]].Net;
                 cuvant[i].Nrlitere=cuvant[i].Nrlitere+P[poz[l-1]].NrProd;
             }
         }



      }
    else
      {
        for(j=0;j<NrP;j++)
        {
          if(P[j].Net==S)
          {
              cuvant[NrCuv].cuv=new char[n];  //ii aloc cuvantului memorie
              cuvant[NrCuv].Nrlitere=P[j].NrProd;  //ii setez numarul de litere pe care il are initial;
              for(i=0;i<P[j].NrProd;i++)
              {
                 // if((P[j].prod[i])!="#")
                  cuvant[NrCuv].cuv[i]=P[j].prod[i]; // copiez literele din productie
              }
              // sa nu uit sa verific daca e neterminal !!!
              cuvant[NrCuv].net=P[j].NetProd ;//copiez Neterminalul din productie;
              NrCuv++; //cresc numarul de cuvine
          }

        }
     }
      ok=0;
     for(j=0;j<NrCuv;j++)
     {
         if(cuvant[j].Nrlitere==n)
         {
             for(t=0;t<cuvant[j].Nrlitere;t++)
             {
                 cout<<cuvant[j].cuv[t];
             }
             cout<<"\n";
             cuvant[j].Nrlitere++;
         }
         if(cuvant[j].Nrlitere<n)
            ok=1;
     }

    }
   delete(poz);
}
