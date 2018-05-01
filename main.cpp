#include <iostream>
#include <cstring>
#include "Cautator.h"
#include "Harta.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;


int main()
{
    srand(time(NULL)); //sa genereze alte numere random pt fiecare rulare a programului

    Harta ob(15);

    ob.joc();

    cout << "Joc incheiat";

    return 0;
}
