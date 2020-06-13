#ifndef GRAMATICA_H
#define GRAMATICA_H


class Gramatica
{
    public:
        Gramatica(char *numefisier);
        GenerareCuvinte(int n);
        ~Gramatica();
    private:
        int NrN;
        char *N;
        int NrT;
        char *T;
        char S;
        int NrP;
        typedef struct
        {
            char Net;
            int NrProd;
            char *prod;
            char NetProd;
        }Productii;
         Productii *P;


};

#endif
