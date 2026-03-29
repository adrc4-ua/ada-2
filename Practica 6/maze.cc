// Adrian David Ruiz Cantillo
// 01888198J

#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

const int MAX = 99999999;

using namespace std;

int maze_naive(const vector<vector<char>> &matriz, int n, int m)
{
    if (n < 1 || m < 1)
    {
        return MAX;
    }

    if (matriz[n - 1][m - 1] == '0')
    {
        return MAX;
    }

    if (n == 1 && m == 1)
    {
        return 1;
    }

    int diagonal = maze_naive(matriz, n - 1, m - 1);
    int arriba = maze_naive(matriz, n - 1, m);
    int izquierda = maze_naive(matriz, n, m - 1);

    int res = min({diagonal, arriba, izquierda});

    if (res >= MAX)
    {
        return MAX;
    }

    return 1 + res;
}

int maze_memo(const vector<vector<char>> &matriz, vector<vector<int>> &memo, int n, int m)
{
    if (n < 1 || m < 1)
    {
        return MAX;
    }

    if (matriz[n - 1][m - 1] == '0')
    {
        memo[n - 1][m - 1] = -2;
        return MAX;
    }

    if (memo[n - 1][m - 1] != -1)
    {
        if (memo[n - 1][m - 1] == -2)
        {
            return MAX;
        }
        return memo[n - 1][m - 1];
    }

    if (n == 1 && m == 1)
    {
        return memo[n - 1][m - 1] = 1;
    }

    int diagonal = maze_memo(matriz, memo, n - 1, m - 1);
    int arriba = maze_memo(matriz, memo, n - 1, m);
    int izquierda = maze_memo(matriz, memo, n, m - 1);

    int res = min({diagonal, arriba, izquierda});

    if (res >= MAX)
    {
        memo[n - 1][m - 1] = -2;
        return MAX;
    }
    else
    {
        memo[n - 1][m - 1] = 1 + res;
        return memo[n - 1][m - 1];
    }
}

void maze_parser(const vector<vector<char>> &matriz, const vector<vector<int>> &memo, const int n, const int m, int caso)
{
    if (caso == 0)
    {
        if (memo[n - 1][m - 1] < 1 || memo[n - 1][m - 1] >= MAX)
        {
            cout << 0 << endl;
            return;
        }

        vector<vector<char>> aux = matriz;
        int f = n - 1;
        int c = m - 1;

        while (f >= 0 && c >= 0)
        {
            int actual = memo[f][c];
            aux[f][c] = '*';

            if (f == 0 && c == 0)
            {
                break;
            }

            if (f > 0 && c > 0 && memo[f - 1][c - 1] == actual - 1)
            {
                f--;
                c--;
            }
            else if (f > 0 && memo[f - 1][c] == actual - 1)
            {
                f--;
            }
            else if (c > 0 && memo[f][c - 1] == actual - 1)
            {
                c--;
            }
            else
            {
                break;
            }
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cout << aux[i][j];
            }
            cout << endl;
        }
    }
    else
    {
        for (int fila = 0; fila < n; fila++)
        {
            for (int columna = 0; columna < m; columna++)
            {
                if (memo[fila][columna] == -1)
                {
                    cout << "-";
                }
                else if (memo[fila][columna] == -2)
                {
                    cout << "X";
                }
                else
                {
                    cout << memo[fila][columna];
                }
                if (columna < m - 1)
                {
                    cout << " ";
                }
            }
            cout << endl;
        }
    }
}

int main(int argc, char *argv[])
{
    vector<vector<char>> matriz;
    int n = 0, m = 0;
    bool arg[4] = {false};

    if (argc <= 1)
    {
        cerr << "Usage:\nmaze [-t] [--ignore-naive] -f file [--p2D]" << endl;
        return 0;
    }

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--ignore-naive") == 0)
        {
            arg[0] = true;
        }
        else if (strcmp(argv[i], "--p2D") == 0)
        {
            arg[1] = true;
        }
        else if (strcmp(argv[i], "-t") == 0)
        {
            arg[2] = true;
        }
        else if (strcmp(argv[i], "-f") == 0)
        {
            arg[3] = true;
            if (argv[i + 1] == NULL)
            {
                cerr << "ERROR: missing filename." << endl;
                cerr << "Usage:\nmaze [-t] [--ignore-naive] -f file [--p2D]" << endl;
                return 0;
            }

            string fichero = argv[i + 1];
            ifstream fe(fichero);

            if (!fe.is_open())
            {
                cerr << "ERROR: can't open file: " << fichero << "." << endl;
                cerr << "Usage:\nmaze [-t] [--ignore-naive] -f file [--p2D]" << endl;
                return 0;
            }

            fe >> n >> m;
            getline(fe, fichero);

            matriz.resize(n, vector<char>(m));

            for (int fila = 0; fila < n; fila++)
            {
                for (int col = 0; col < m; col++)
                {
                    if (!(fe >> matriz[fila][col]))
                    {
                        break;
                    }
                }
            }
            fe.close();
            i++;
        }
        else
        {
            cerr << "ERROR: unknown option " << argv[i] << "." << endl;
            cerr << "Usage:\nmaze [-t] [--ignore-naive] -f file [--p2D]" << endl;
            return 0;
        }
    }

    // Gestión de opciones

    if (arg[3] == false) // -f
    {
        cerr << "ERROR: missing filename." << endl;
        cerr << "Usage:\nmaze [-t] [--ignore-naive] -f file [--p2D]" << endl;

        return 0;
    }

    if (arg[0] == false) // --ignore-naive
    {
        int camino_naive = maze_naive(matriz, n, m);

        if (camino_naive >= MAX)
        {
            cout << "0 ";
        }
        else
        {
            cout << camino_naive << " ";
        }
    }
    else
    {
        cout << "- ";
    }

    // Impresión de resultados

    vector<vector<int>> memo(n, vector<int>(m, -1));

    int camino_memo_r = maze_memo(matriz, memo, n, m);

    if (camino_memo_r >= MAX)
    {
        cout << "0 ";
    }
    else
    {
        cout << camino_memo_r << " ";
    }

    cout << "? ?" << endl;

    if (arg[1] == true) // --p2D
    {
        maze_parser(matriz, memo, n, m, 0);
    }

    if (arg[2] == true) // -t
    {
        // cout << "Memoization table:" << endl;
        // maze_parser(matriz, memo, n, m, 1);
        cout << "?" << endl;
    }

    return 0;
}