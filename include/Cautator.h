#ifndef CAUTATOR_H
#define CAUTATOR_H

class Cautator //creez o clasa de baza din care derivez cei 4 cautatori
{
    public:
        Cautator();
        virtual ~Cautator();
        virtual void deplasare(int **maph, int dim, int &comori_gasite, int &ok) = 0; //fiecare cautator va avea un mod de deplasare
        virtual int get_pow() const; //fiecare cautator va avea o putere cu care va marca casutele pe care a fost
        virtual int get_lin() const;
        virtual int get_col() const;
        virtual void set_lin(int lin);
        virtual void set_col(int col);
    protected:
        int pow, lin, col;
};

class First_Cautator:public Cautator
{
    public:
        First_Cautator();
        void deplasare(int **maph, int dim, int &comori_gasite, int &ok);
};

class Second_Cautator:public Cautator
{
    public:
        Second_Cautator(int dim);
        void deplasare(int **maph, int dim, int &comori_gasite, int &ok);
};

class Third_Cautator:public Cautator
{
    public:
        Third_Cautator(int dim);
        void deplasare(int **maph, int dim, int &comori_gasite, int &ok);
    private:
        int directie;
};

class Fourth_Cautator:public Cautator
{
    public:
        Fourth_Cautator(int dim);
        void deplasare(int **maph, int dim, int &comori_gasite, int &ok);
    private:
        int range, directie;
};

#endif // CAUTATOR_H
