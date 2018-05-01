#include "Cautator.h"
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

Cautator::Cautator()
{
    //ctor

}

First_Cautator :: First_Cautator() //stanga sus
{
    pow = 1;
    lin = 1;
    col = 1;
}

Second_Cautator :: Second_Cautator(int dim) //dreapta sus
{
    pow = 2;
    lin = 1;
    col = dim;
}

Third_Cautator :: Third_Cautator(int dim): directie(0) //stanga jos
{
    pow = 3;
    lin = dim;
    col = 1;
}

Fourth_Cautator :: Fourth_Cautator(int dim): range(dim/8), directie(0) //dreapta jos
{
    pow = 4;
    lin = dim;
    col = dim;
}


void First_Cautator :: deplasare(int **maph, int dim, int &gasit_comoara, int &ok) //se muta pe coloane, raza de vizibilitate 1
{
    maph[lin][col] = pow;
    if(maph[lin+1][col] == 5) //verific daca se afla comoara pe vreuna din pozitiile de langa cautator
    {
        lin++;
        gasit_comoara = 1;
        ok = 1;
    }
    else
        if(maph[lin][col+1] == 5)
        {
            col++;
            gasit_comoara = 1;
            ok = 1;
        }
    else
        if(maph[lin-1][col] == 5)
        {
            lin--;
            gasit_comoara = 1;
            ok = 1;
        }
    else
        if(maph[lin][col-1] == 5)
        {
            col--;
            gasit_comoara = 1;
            ok = 1;
        }
    else
    {
        if(maph[lin][col+1] == 0)//daca nu este langa el, se muta in dreapta cat poate de mult
            col++;
        else
            if(maph[lin][col-1] == 0)//se mut cat de mult poate in stanga
                col--;
        else
            if(maph[lin+1][col] == 0)//se muta pe linia urmatoare daca nu mai poate merge la dreapta sau la stanga
                lin++;
        else
            ok = 1; //daca nu mai are nicio miscare valida, atunci iese din harta
    }
}

void Second_Cautator :: deplasare(int **maph, int dim, int &gasit_comoara, int &ok) //se muta pe linii, raza de vizibilitate 2
{
    int i, j, range;

    maph[lin][col] = pow;
    if(dim == 15) //daca dimensiunea hartii este 15, range-ul este 1
        range = 1;
    else
        range = 2; //altfel este 2

    for(i = max(0, lin - range); i <= min(lin + range, dim); i++) //verifc daca se afla o comoara in raza 2 a cautatorului
        for(j = max(0, col - range); j <= min(col + range, dim); j++)
        {
            if(maph[i][j] == 5)
            {
                if(col - j > 0) //daca comoara se afla in stanga cautatorului, se muta cu o coloana in stanga
                    col--;
                else
                    if(col - j < 0) //daca comoara se afla in dreapta cautatorului, se muta cu o coloana in dreapta
                        col++;
                else
                    if(lin - i > 0) //daca comoara se afla pe una din liniile de mai sus, se muta cu o linie in sus
                        lin--;
                else
                    if(lin - i < 0)//daca comoara se afla pe una din liniile de mai jos, se muta cu o linie in jos
                        lin++;
                if(maph[lin][col] == 5)
                {
                    ok = 1;
                    gasit_comoara = 1;
                }
                return;
            }
        }
    //daca nu gaseste o comoara in raza lui de vizibilitate, se muta pe linii
    if(maph[lin+1][col] == 0) //daca poate merge in jos
        lin++;
    else
        if(maph[lin-1][col] == 0) //daca poate merge in sus
            lin--;
    else
        if(maph[lin][col-1] == 0) //daca poate merge in stanga
            col--;
    else
        ok = 1; //daca nu se mai poate deplasa
}

void Third_Cautator :: deplasare(int **maph, int dim, int &gasit_comoara, int &ok) //se muta pe diagonala(o data la stanga, o data in sus), raza de vizibilitate 0
{
    maph[lin][col] = pow;
    if(directie == 0 && maph[lin][col-1] == 0 || maph[lin][col-1] == 5) //se muta la stanga
    {
        col--;
        directie++;
    }
    else //se muta in sus
        if(maph[lin-1][col] == 0 || maph[lin-1][col] == 5)
        {
            lin--;
            directie = 0;
        }
    else //nu se mai poate deplasa
        ok = 1;

    if(maph[lin][col] == 5)
    {
        ok = 1;
        gasit_comoara = 1;
    }
}

void Fourth_Cautator :: deplasare(int **maph, int dim, int &gasit_comoara, int &ok) //se muta nin L (una in dreapta si 3 in sus), raza de vizibilitate 1/8 din dimensiunea hartii
{
    maph[lin][col] = pow;
    int i, j;
    for(i = max(0, lin - range); i <= min(lin+range, dim); i++) //verifc daca se afla o comoara in raza range a cautatorului
        for(j = max(0, col - range); j <= min(col+range, dim); j++)
        {
            if(maph[i][j] == 5)
            {
                if(col - j > 0) //daca comoara se afla in stanga cautatorului, se muta cu o coloana in stanga
                    col--;
                else
                    if(col - j < 0) //daca comoara se afla in dreapta cautatorului, se muta cu o coloana in dreapta
                        col++;
                else
                    if(lin - i > 0) //daca comoara se afla pe una din liniile de mai sus, se muta cu o linie in sus
                        lin--;
                else
                    if(lin - i < 0)//daca comoara se afla pe una din liniile de mai jos, se muta cu o linie in jos
                        lin++;
                if(maph[lin][col] == 5)
                {
                    ok = 1;
                    gasit_comoara = 1;
                }
                return;
            }
    }

    if(directie == 0 && maph[lin][col-1] == 0) //daca nu a gasit o comoara in raza lui de vizibilitate, atunci se muta in L
    {
        col--;
        directie++;
    }
    else
        if(directie == 3 && maph[lin-1][col] == 0)
        {
            lin--;
            directie = 0;
        }
    else
        if(maph[lin-1][col] == 0)
        {
            lin--;
            directie++;
        }
    else
        ok = 1;
}

void Cautator::set_col(int col)
{
    this->col = col;
}

void Cautator::set_lin(int lin)
{
    this->lin = lin;
}

int Cautator::get_lin() const
{
    return lin;
}

int Cautator::get_col() const
{
    return col;
}

int Cautator::get_pow() const
{
    return pow;
}

Cautator::~Cautator()
{
    //dtor
}
