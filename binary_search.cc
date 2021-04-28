/**
 * @file binary_search.cc
 * @author Glorian Kosi
 * @brief 
 * @version 0.1
 * 
 * 
 * 
 * -------Must be using at least C++20---------
 * 
 * Binary search that returns # of 0's in an array
 * 
 * To compile, example:
 * g++ -std=c++2a binary_search.cc -o bin_search
 * 
 * To run, supply command line arguments (must be 0s first, then 1s, i.e, sorted 0s and 1s), example:
 * 
 * ./bin_search 0 0 0 0 0 0 1 1 1 1 1 1 1
 * 
 */

#include <iostream>
#include <vector>
using namespace std;

int ZeroCount(vector<int> &, int, int);

int main(int argc, char *argv[])
{
    vector<int> A;
    for (char **i = argv; i != argv + argc; i++)
    {
        try
        {
            int val = stoi(*i);
            A.emplace_back(val);
        }
        catch (invalid_argument)
        {
            continue;
        }
    }
    cout << ZeroCount(A, 0, A.size()) << '\n';
}
int ZeroCount(vector<int> &A, int left, int right)
{
    int mid = (left + right) / 2;
    if (A[mid] == 0 && A[mid + 1] == 1)
        return mid + 1; // Need to add 1 because mid is the index
    if (A[mid] == 1)
    {
        return ZeroCount(A, left, mid);
    }
    if (A[mid + 1] == 0)
    {
        return ZeroCount(A, mid, right);
    }
    return -1;
}