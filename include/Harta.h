#ifndef HARTA_H
#define HARTA_H
#include "Cautator.h"

class Harta
{
    public:
        Harta();
        Harta(int copy_dim);
        virtual ~Harta();
        int** get_harta();
        int get_dim();
        void joc();
        void afisare();

    protected:

    private:
        int **maph, dim, x1, x2, x3, y1, y2, y3;
        Cautator** cautatori = new Cautator*[4]; // construiesc un vector cu toti cautatorii
};

#endif // HARTA_H
