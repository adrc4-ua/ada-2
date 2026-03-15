// Adrian David Ruiz Cantillo
// 01888198J

#include <iostream>
#include <math.h>

int pasos = 0;

using namespace std;

// coste: O(n^2)
unsigned long pow_2_1(unsigned numero)
{
    unsigned long resultado = 1;

    for (unsigned int i = 0; i < numero; i++)
    {
        for (unsigned int j = 0; j < numero; j++)
        {
            if (j == i)
            {
                resultado += resultado;
                pasos++;
            }
        }
        pasos++;
    }

    return resultado;
}

// coste: O(n)
unsigned long pow_2_2(unsigned numero)
{
    if (numero == 0)
    {
        return 1;
    }
    pasos++;
    return 2 * pow_2_2(numero - 1);
}

// coste: O(log n)
unsigned long pow_2_3(unsigned n)
{

    if (n == 0)
    {
        return 1;
    }
    else
    {
        pasos++;
    }

    unsigned long mitad = pow_2_3(n / 2);

    if (n % 2 == 0)
    {
        return mitad * mitad;
    }
    else
    {
        return mitad * mitad * 2;
    }
}

int main(void)
{
    cout << "\t  POW_2_1\t\t   POW_2_2\t\t   POW_2_3\n"
            "      --------------\t       --------------\t       --------------\t\n"
            " n\t2^n    Steps\t\t2^n    Steps\t\t2^n    Steps\n"
            "======================================================================================================\n";

    for (int n = 1; n <= 16; n++)
    {
        pasos = 0;
        cout << n << "\t" << pow_2_1(n) << "\t" << pasos;
        pasos = 0;
        cout << " \t\t" << pow_2_2(n) << "\t" << pasos;
        pasos = 0;
        cout << " \t\t" << pow_2_3(n) << "\t" << pasos << endl;
    }
    return 0;
}