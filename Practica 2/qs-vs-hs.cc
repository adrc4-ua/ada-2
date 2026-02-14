/*Adrián David Ruiz Cantillo
01888198J

ADA. 2025-26
Practice 2: "Empirical analysis by means of program-steps account of two sorting algorithms: Middle-Quicksort and Heapsort."
*/
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

double contadorQ = 0;
double contadorH = 0;

//--------------------------------------------------------------
// Middle-Quicksort:
// The algorithm selects the middle element of the array as the "pivot".
// In a process called "partitioning", it rearranges the elements so that
// all elements smaller than the pivot are placed to its left, and
// all elements greater than the pivot are placed to its right.
// The process is then repeated recursively on the two resulting
// subarrays (left and right of the pivot).
//--------------------------------------------------------------

void middle_QuickSort(int *v, long left, long right)
{
    long i, j;
    int pivot;
    if (left < right)
    {
        i = left;
        j = right;
        pivot = v[(i + j) / 2];
        // pivot based partitioning:
        do
        {
            contadorQ++;
            while (v[i] < pivot)
            {
                contadorQ++;
                i++;
            }
            while (v[j] > pivot)
            {
                contadorQ++;
                j--;
            }
            if (i <= j)
            {
                swap(v[i], v[j]);
                i++;
                j--;
            }
        } while (i <= j);
        // Repeat for each non-empty subarray:
        if (left < j)
            middle_QuickSort(v, left, j);
        if (i < right)
            middle_QuickSort(v, i, right);
    }
}

//--------------------------------------------------------------
// Heapsort:
// The algorithm works by repeatedly selecting the largest remaining element
// and placing it at the end of the vector in its correct position.
//
// To efficiently select the largest element, it builds a max-heap.
//
// The sink procedure is used for heap construction (or reconstruction).
//--------------------------------------------------------------

void sink(int *v, size_t n, size_t i)
// Sink an element (indexed by i) in a tree to maintain the heap property.
// n is the size of the heap.
{
    size_t largest;
    size_t l, r; // indices of left and right childs

    do
    {
        contadorH++;

        largest = i;   // Initialize largest as root
        l = 2 * i + 1; // left = 2*i + 1
        r = 2 * i + 2; // right = 2*i + 2

        // If the left child exists and is larger than the root
        if (l < n && v[l] > v[largest])
            largest = l;

        // If the right child exists and is larger than the largest so far
        if (r < n && v[r] > v[largest])
            largest = r;

        // If the largest is still the root, the process is done
        if (largest == i)
            break;

        // Otherwise, swap the new largest with the current node i and repeat the process with the children
        swap(v[i], v[largest]);
        i = largest;
    } while (true);
}

//--------------------------------------------------------------
// Heapsort algorithm (ascending sorting)
void heapSort(int *v, size_t n)
{
    // Build a max-heap with the input array ("heapify"):
    // Starting from the last non-leaf node (right to left), sink each element to construct the heap.
    for (size_t i = n / 2 - 1; true; i--)
    {
        sink(v, n, i);
        if (i == 0)
            break; // As size_t is an unsigned type
    }

    // At this point, we have a max-heap. Now, sort the array:
    // Repeatedly swap the root (largest element) with the last element and rebuild the heap.
    for (size_t i = n - 1; i > 0; i--)
    {
        // Move the root (largest element) to the end by swapping it with the last element.
        swap(v[0], v[i]);
        // Rebuild the heap by sinking the new root element.
        // Note that the heap size is reduced by one in each iteration (so the element moved to the end stays there)
        sink(v, i, 0);
        // The process ends when the heap has only one element, which is the smallest and remains at the beginning of the array.
    }
}

int main()
{
    cout << "# QUICKSORT VERSUS HEAPSORT #\n"
            "#Average processing Msteps(millions of program steps)\n"
            "#Number of samples(arrays of integer) : 30\n"
            "#\t\t   RANDOM ARRAYS\t\t   SORTED ARRAYS\t      REVERSE SORTED ARRAYS\n"
            "#\t     ------------------------\t     ------------------------\t    -------------------------\n"
            "#Size          QuickSort       HeapSort        QuickSort       HeapSort       QuickSort        HeapSort\n"
            "#======================================================================================================"
         << endl;

    for (int exp = 15; exp <= 20; exp++)
    {
        size_t size = size_t(pow(2, exp));

        int *vq = new int[size];
        if (!vq)
        {
            cerr << "Error, not enough memory!" << endl;
            exit(EXIT_FAILURE);
        }

        int *vh = new int[size];
        if (!vh)
        {
            cerr << "Error, not enough memory!" << endl;
            exit(EXIT_FAILURE);
        }

        cout << size;

        for (int i = 0; i < 3; i++)
        {
            contadorQ = 0;
            contadorH = 0;

            switch (i)
            {
            case 0: // Vector aleatorio
                for (int k = 0; k < 30; k++)
                {
                    for (size_t j = 0; j < size; j++)
                    {
                        int num = rand();
                        vq[j] = num;
                        vh[j] = num;
                    }

                    middle_QuickSort(vq, 0, size - 1);
                    heapSort(vh, size);
                }

                cout << fixed << setprecision(3) << "\t\t" << ((contadorQ / 1000000) / 30);
                cout << "\t\t" << ((contadorH / 1000000) / 30);
                break;

            case 1: // Vector ordenado (creciente)
                for (size_t j = 0; j < size; j++)
                {
                    vq[j] = j;
                    vh[j] = j;
                }

                middle_QuickSort(vq, 0, size - 1);
                cout << "\t\t" << (contadorQ / 1000000);

                heapSort(vh, size);
                cout << "\t\t" << (contadorH / 1000000);
                break;

            case 2: // Vector ordenado (decreciente)
                for (size_t j = 0; j < size; j++)
                {
                    vq[j] = size - j;
                    vh[j] = size - j;
                }

                middle_QuickSort(vq, 0, size - 1);
                cout << "\t\t" << (contadorQ / 1000000);

                heapSort(vh, size);
                cout << "\t\t" << (contadorH / 1000000) << endl;
                break;

            default:
                break;
            }
        }
        delete[] vq;
        delete[] vh;
    }
    return 0;
}