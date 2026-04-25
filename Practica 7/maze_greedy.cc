// Adrian David Ruiz Cantillo
// 01888198J

#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>

using namespace std;

void show_matrix(int n, int m, vector<vector<char>> matrix)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << matrix[i][j];
        }
        cout << endl;
    }
}

int maze_greedy(int n, int m, vector<vector<char>> &matrix)
{
    int fila = 0;
    int columna = 0;
    int pasos = 0;

    while (matrix[0][0] != '0' && matrix[n - 1][m - 1] != '0')
    {
        if (matrix[fila][columna] == '1')
        {
            matrix[fila][columna] = '*';
            pasos++;
        }

        if (fila == n - 1 && columna == m - 1)
        {
            return pasos;
        }

        if (fila < n - 1 && columna < m - 1 && matrix[fila + 1][columna + 1] == '1')
        {
            fila++;
            columna++;
        }
        else if (fila < n - 1 && matrix[fila + 1][columna] == '1')
        {
            fila++;
        }
        else if (columna < m - 1 && matrix[fila][columna + 1] == '1')
        {
            columna++;
        }
        else
        {
            return 0;
        }
    }
    return pasos;
}

int main(int argc, char *argv[])
{
    bool argumentos[2] = {false, false};
    string fichero;
    vector<vector<char>> matrix;
    int tamaño[2];

    if (argc < 2)
    {
        cerr << "Numero de argumentos incorrecto." << endl;
        return 0;
    }

    for (int i = 0; i < argc; i++)
    {
        if (!strcmp(argv[i], "--p2D"))
        {
            argumentos[1] = true;
        }
        else if (!strcmp(argv[i], "-f"))
        {
            argumentos[0] = false;
            if (argv[i + 1] != NULL)
            {
                fichero = argv[i + 1];
                argumentos[0] = true;
            }
        }
        else if (string(argv[i])[0] == '-')
        {
            cerr << "Argumentos invalidos. Sintaxis correcta: maze_greedy [--p2D] -f \"filename\"" << endl;
            return 0;
        }
    }

    if (argumentos[0] == false)
    {
        cerr << "Nombre de fichero no encontrado." << endl;
        return 0;
    }
    else
    {
        ifstream fe(fichero);
        if (fe.is_open())
        {
            fe >> tamaño[0] >> tamaño[1];
            getline(fe, fichero);

            for (int i = 0; getline(fe, fichero); i++)
            {
                stringstream ss(fichero);
                vector<char> nuevaFila;
                char num;
                while (ss >> num)
                {
                    nuevaFila.push_back(num);
                }
                matrix.push_back(nuevaFila);
            }
        }
        else
        {
            cerr << "No se pudo encontrar el fichero." << endl;
            return 0;
        }
        fe.close();

        cout << maze_greedy(tamaño[0], tamaño[1], matrix) << endl;
        if (argumentos[1])
        {
            show_matrix(tamaño[0], tamaño[1], matrix);
        }
    }
    return 0;
}