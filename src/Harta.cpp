#include "Harta.h"
#include <iostream>
#include <cstring>
#include "Cautator.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace std;

Harta::Harta(int copy_dim): x1(rand() % (copy_dim - 1) + 1), y1(rand() % (copy_dim - 1) + 1), x2(rand() % (copy_dim - 1) + 1), y2(rand() % (copy_dim - 1) + 1), x3(rand() % (copy_dim - 1) + 1), y3(rand() % (copy_dim - 1) + 1)
{
    //ctor

    dim = copy_dim;
    int i;

    maph = new int*[dim+2];
    for(i = 0; i < dim + 2; i++)
        maph[i] = new int[dim+2];

    for(i = 1; i <= dim; i++)
        for(int j = 1; j <= dim; j++)
            maph[i][j] = 0;

    for(i = 0; i < dim + 2; i++) //bordez matricea cu -1
    {
        maph[0][i] = maph[dim + 1][i] = -1;
        maph[i][0] = maph[i][dim + 1] = -1;
    }

    //pun random cele 3 comori astfel incat sa nu se afle pe prima/ultima linie/coloana
    maph[x1][y1] = 5;
    maph[x2][y2] = 5;
    maph[x3][y3] = 5;

    cautatori[0] = new First_Cautator();
    cautatori[1] = new Second_Cautator(dim);
    cautatori[2] = new Third_Cautator(dim);
    cautatori[3] = new Fourth_Cautator(dim);
}

Harta::Harta(){}

void Harta::afisare()
{
    cout << '\n';
    for(int i = 1; i <= dim; i++)
    {
        for(int j = 1; j <= dim; j++)
            cout << maph[i][j] << " ";
        cout << '\n';
    }

    cout << '\n' << '\n';
}

int** Harta::get_harta()
{
    return maph;
}
int Harta::get_dim()
{
    return dim;
}

void Harta::joc()
{
    int i,j;

    static int nr_runda = 0;

    int total_comori_gasite = 0, ok[] = {0, 0, 0, 0}, sum = 0, nr;
    int gasit_comoara[] = {0, 0, 0, 0};
    int *pow;
    int *lin; //linia curenta a cautatorilor
    int *col; //coloana curenta a cautatorilor

    lin = new int[4];
    col = new int[4];
    pow = new int[4];

    memset(lin, 0, sizeof(int)*4);
    memset(col, 0, sizeof(int)*4);

    for(i = 0; i < 4; i++)
        pow[i] = cautatori[i]->get_pow();

    while(sum != 4 && total_comori_gasite < 3) //continui cat timp sunt comori si cautatori ce se pot muta
    {
        nr_runda++;
        cout << "Runda curenta este: " << nr_runda << '\n';

        //pun in vectori pozitiile curente, puterile si deplasez
        for(i = 0; i < 4; i++)
        {
            if(ok[i] == 0)
                cautatori[i]->deplasare(maph, dim, gasit_comoara[i], ok[i]);
            lin[i] = cautatori[i]->get_lin();
            col[i] = cautatori[i]->get_col();
        }

        for(i = 0; i < 3; i++) //confruntare 2 sau mai multi cautatori
            for(j = i+1; j < 4; j++)
                if(lin[i] == lin[j] && col[i] == col[j]) //daca se afla pe aceeasi pozitie
                {
                    nr = rand()%2;
                    if(nr == 1) //daca numarul ales random e 1, atunci i pierde
                    {
                        if(ok[i] == 1) //daca pe pozitia pe care se afla pierzatorul este o comoara,
                        {
                            ok[i] = 0;
                            gasit_comoara[i] = 0;
                        }

                        //mut pierzatorul pe o pozitie pe care a mai fost
                        if(maph[lin[i]][col[i] - 1] == pow[i])
                            cautatori[i]->set_col(col[i] - 1);
                        else
                            if(maph[lin[i]][col[i] + 1] == pow[i])
                                cautatori[i]->set_col(col[i] + 1);
                        else
                            if(maph[lin[i] + 1][col[i]] == pow[i])
                                cautatori[i]->set_lin(lin[i] + 1);
                        else
                            if(maph[lin[i] - 1][col[i]] == pow[i])
                                cautatori[i]->set_lin(lin[i] - 1);
                    }
                    else
                    {
                        if(ok[j] == 1) //daca pe pozitia pe care se afla pierzatorul este o comoara,
                        {
                            ok[j] = 0;
                            gasit_comoara[j] = 0;
                        }

                        //mut pierzatorul pe o pozitie pe care a mai fost
                        if(maph[lin[j]][col[j] - 1] == pow[j])
                            cautatori[j]->set_col(col[j] - 1);
                        else
                            if(maph[lin[j]][col[j] + 1] == pow[j])
                                cautatori[j]->set_col(col[j] + 1);
                        else
                            if(maph[lin[j] + 1][col[j]] == pow[j])
                                cautatori[j]->set_lin(lin[j] + 1);
                        else
                            if(maph[lin[j] - 1][col[j]] == pow[j])
                                cautatori[j]->set_lin(lin[j] - 1);
                    }
                }

        sum = 0;
        total_comori_gasite = 0;
        for(i = 0; i < 4; i++) //numar cati cautatori au iesit de pe harta si cati cautatori au gasit comoara
        {
            sum += ok[i];
            total_comori_gasite += gasit_comoara[i];
        }

        for(i = 0; i < 4; i++) //marchez pozitia fiecaruia dupa noile schimbari
        {
            maph[lin[i]][col[i]] = pow[i];
            if(ok[i] == 0)
                cout << "Cautatorul " << i + 1 << " se muta pe linia " << lin[i] << " coloana " << col[i] << '\n';
            else
            {
                if(gasit_comoara[i] == 1)
                    cout << "Cautatorul " << i + 1 << " a gasit comoara" << '\n';
                else
                    if(gasit_comoara[i] == 0)
                        cout << "Cautatorul " << i + 1 << " nu mai are mutari valide" << '\n';

                gasit_comoara[i] = -1; //afisez ca a gasit comoara/nu mai are mutari valide doar in prima runda in care se intampla asta
            }
        }
        afisare();
    }

    delete[] lin; //dezaloc memoria
    delete[] col;
    delete[] pow;
}

Harta::~Harta()
{
    //dtor
    for(int i = 0; i < dim + 2; i++) //dezaloc harta
        delete[] maph[i];
    delete[] maph;

    for(int i = 0; i < 4; i++)
        delete[] cautatori;
    delete[] cautatori;

}
