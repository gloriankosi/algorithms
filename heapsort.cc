/**
 * @file heapsort.cc
 * @author Glorian Kosi
 * @brief 
 * @version 0.1
 * 
 * 
 * -------Must be using at least C++17---------
 * 
 * To compile, example:
 * g++ -std=c++2a heapsort.cc -o heapsort
 * 
 * To run, supply command line arguments (must be integers, signed/unsigned both 
 * work), example using previous command:
 * ./heapsort 2122 2 1 100 4 5 63 1 10 55
 * 
 * Result is printed in terminal, this heapsort is a MIN-HEAP, so the root is the smallest, values popped
 * from the heap will be from LARGEST TO SMALLEST (TOP TO BOTTOM).
 * 
 * 
 * More on:
 * iter_swap: https://devdocs.io/cpp/algorithm/iter_swap 
 * stoi: https://devdocs.io/cpp/string/basic_string/stol 
 * range-based for loop: https://devdocs.io/cpp/language/range-for 
 * invalid_argument: https://devdocs.io/cpp/error/invalid_argument/invalid_argument 
 * vector: https://devdocs.io/cpp/container/vector 
 * auto: https://devdocs.io/cpp/language/auto 
 * iterators: https://devdocs.io/cpp/iterator/iterator
 * 
 * More On:
 * heapsorts (in general, includes good pseudocode): https://en.wikipedia.org/wiki/Heapsort
 * heapsorts (from CLRS textbook and MIT): https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/MIT6_006F11_lec04.pdf
 * 
 * 
 */
#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>
#include <cmath>
#include <random>
#include <ctime>

using std::begin;
using std::clock_t;
using std::cout;
using std::floor;
using std::invalid_argument;
using std::iter_swap;
using std::mt19937;
using std::random_device;
using std::reverse;
using std::stoi;
using std::uniform_int_distribution;
using std::vector;

int compCount = 0;

void Pushdown(vector<int> &, int, int);
void HeapSort(vector<int> &, int);
int main(int argc, char *argv[])
{
    clock_t start;
    double t;
    vector<int> userValues;
    // random_device rd;
    // mt19937 gen(rd());
    // uniform_int_distribution<> distr(0, 2500);
    for (char **i = argv; i != argv + argc; i++)
    {
        try
        {
            int val = stoi(*i);
            userValues.push_back(val);
        }
        catch (invalid_argument)
        {
            continue;
        }
    }
    // for (int i = 0; i <= 1048576; i++)
    // {
    //     // userValues.push_back(distr(gen));
    //     userValues.push_back(i);
    // }
    // reverse(userValues.begin(), userValues.end());
    start = clock();
    HeapSort(userValues, userValues.size());
    t = (clock() - start) / (double)CLOCKS_PER_SEC;
    cout << "---Time---"
         << "\n";
    cout << t << '\n';
}
/**
 * @brief Reorder heap after last element has been deleted
 * 
 * @param userValues int vector of values provided by user
 * @param n total number of nodes (size of userValues)
 * @param r root of the subtree
 */
void Pushdown(vector<int> &userValues, int n, int r)
{
    int smallest = r;
    int left = 2 * r + 1;  // Left tree
    int right = 2 * r + 2; // Right tree

    if ((left < n) && (userValues[left] < userValues[smallest]))
    {
        compCount++;
        smallest = left;
    }
    if ((right < n) && (userValues[right] < userValues[smallest]))
    {
        compCount++;
        smallest = right;
    }
    if (smallest != r)
    {
        auto leftPtr = userValues.begin() + smallest;
        auto rightPtr = userValues.begin() + r;
        iter_swap(leftPtr, rightPtr);
        Pushdown(userValues, n, smallest);
    }
}
/**
 * @brief Standard heapsort using a MIN-HEAP
 * 
 * @param userValues int vector of values provided by user
 * @param n total number of nodes (size of userValues)
 */
void HeapSort(vector<int> &userValues, int n)
{
    for (int i = floor(n / 2); i >= 0; i--)
        Pushdown(userValues, n, i);

    for (int i = n - 1; i >= 0; i--)
    {
        std::swap(userValues[0], userValues[i]);
        Pushdown(userValues, i, 0);
    }
}