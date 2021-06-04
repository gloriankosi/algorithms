/**
 * @file heaps-algorithm.cc
 * @brief Recursive implementation of Heap's Algorithm
 * NOTE: This algorithm has nothing to do with heaps, instead it's for 
 * generating all possible permutations of k objects.
 * 
 * Link to more info on Heap's Algorithm:
 * https://en.wikipedia.org/wiki/Heap%27s_algorithm 
 * 
 */
#include <iostream>
#include <vector>

using std::cout;
using std::swap;
using std::vector;

void Generate(int, vector<int> &);

int main(int argc, char *argv[])
{
    vector<int> A = {0, 2, 3, 4}; // Add or remove elements in vector A to get permutations
    int k = A.size();             // Size of A
    Generate(k, A);
    return -1;
}
/**
 * @brief Recursively generates all possible permutations of the elements in vector A.
 * 
 * @param k Initially equal to length of A
 * @param A Vector of k elements of type integer
 */
void Generate(int k, vector<int> &A)
{
    if (k == 1)
    {
        for (auto i : A)
        {
            cout << i << " ";
        }
        cout << "\n";
        return;
    }
    else
    {
        Generate(k - 1, A);
        for (int i = 0; i < k - 1; i++)
        {
            if (k % 2 == 0) // If k is an even number, swap A[i] with A[k-1]
            {
                swap(A[i], A[k - 1]);
            }
            else // If k is an odd number, swap A[0] with A[k-1]
            {
                swap(A[0], A[k - 1]);
            }
            Generate(k - 1, A);
        }
    }
}