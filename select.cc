/*
Glorian Kosi

PERSONAL TODO: Investigate reserve() and generate(), using generate 
with vector<int>(XYZ) took too long, try with reserve next
to see and compare emplace_back()

Recursion on SELECT3 causes stack overflow, 1*10^6 elements too large, used alternative method instead

-------Must be using at least C++17---------

To compile, example:
g++ -std=c++2a select.cc -o select

To run:
./select

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
#include <numeric>

using std::accumulate;
using std::begin;
using std::clock_t;
using std::cout;
using std::distance;
using std::floor;
using std::invalid_argument;
using std::iter_swap;
using std::mt19937;
using std::random_device;
using std::reverse;
using std::shuffle;
using std::uniform_int_distribution;
using std::vector;

int compCount = 0;

void QuickSort(vector<int> &, int, int, int);
void QuickSelect(vector<int> &, int, int, int);

void InsertionSort(vector<int> &, int, int);
int MedianPivot(vector<vector<int>> &, vector<int>);
int Partition(vector<int> &, int, int, int);

void SELECT1(vector<int> &, int, int);
void SELECT2(vector<int> &, int, int);
void SELECT3(vector<int> &, int, int);

int main(int argc, char *argv[])
{
    uniform_int_distribution<int> dist(0, 999999);
    random_device seeder;
    mt19937 mtGen;
    mtGen.seed(dist(seeder));

    cout << "Filling small vector, n=10000..." << '\n';
    vector<int> smallVector;
    for (int i = 0; i < 10000; i++)
    {
        smallVector.emplace_back(dist(mtGen));
        mtGen.seed(dist(mtGen));
    }
    cout << "Filling medium vector, n=100000..." << '\n';
    vector<int> mediumVector;
    for (int i = 0; i < 100000; i++)
    {
        mediumVector.emplace_back(dist(mtGen));
        mtGen.seed(dist(mtGen));
    }
    cout << "Filling large vector, n=1000000..." << '\n';
    vector<int> largeVector;
    for (int i = 0; i < 1000000; i++)
    {
        largeVector.emplace_back(dist(mtGen));
        mtGen.seed(dist(mtGen));
    }

    cout << "\n\n\n\n";

    cout << "----------SELECT1 Metrics----------"
         << "\n";
    SELECT1(smallVector, smallVector.size(), floor(smallVector.size() / 2));
    SELECT1(mediumVector, mediumVector.size(), floor(mediumVector.size() / 2));
    SELECT1(largeVector, largeVector.size(), floor(largeVector.size() / 2));
    cout << "----------SELECT2 Metrics----------"
         << "\n";
    SELECT2(smallVector, smallVector.size(), floor(smallVector.size() / 2));
    SELECT2(mediumVector, mediumVector.size(), floor(mediumVector.size() / 2));
    SELECT2(largeVector, largeVector.size(), floor(largeVector.size() / 2));
    cout << "----------SELECT3 Metrics----------"
         << "\n";
    SELECT3(smallVector, smallVector.size(), floor(smallVector.size() / 2));
    SELECT3(mediumVector, mediumVector.size(), floor(mediumVector.size() / 2));
    SELECT3(largeVector, largeVector.size(), floor(largeVector.size() / 2));

    return 0;
}

int Partition(vector<int> &userValues, int lo, int hi, int pivot)
{
    int i = lo;
    for (int j = lo; j < hi; j++)
    {
        if (userValues.at(j) < pivot)
        {
            compCount++;
            auto iPtr = userValues.begin() + i;
            auto jPtr = userValues.begin() + j;
            iter_swap(iPtr, jPtr);
            i++;
        }
    }
    iter_swap(userValues.begin() + i, userValues.begin() + hi);
    return i;
}

void QuickSort(vector<int> &userValues, int lo, int hi, int k)
{
    if (lo < hi)
    {
        int pivot = userValues.at(hi);
        int p = Partition(userValues, lo, hi, pivot);
        if (k == p)
        {
            return;
        }
        QuickSort(userValues, lo, p - 1, k);
        QuickSort(userValues, p + 1, hi, k);
    }
}
void QuickSelect(vector<int> &userValues, int lo, int hi, int k)
{
    if (lo < hi)
    {
        uniform_int_distribution<int> userValuesDist(0, userValues.size());
        random_device seeder;
        mt19937 mtGen;
        mtGen.seed(userValuesDist(seeder));

        int randomIndex = userValuesDist(mtGen);
        int pivot = userValues.at(hi);
        int p = Partition(userValues, lo, hi, pivot);
        if (k == p)
        {
            return;
        }
        QuickSelect(userValues, lo, p - 1, k);
        QuickSelect(userValues, p + 1, hi, k);
    }
}

int MedianPivot(vector<vector<int>> &allRows, int index, int m) // Too many rows to do recursively, run out of memory
{
    cout << index << "\n";
    if (index == -1)
    {
        return m;
    }
    vector<int> row = allRows.at(index);
    m = row.at((row.size() - 1) / 2);
    index -= 1;
    return MedianPivot(allRows, index, m);
}
void SELECT1(vector<int> &userValues, int n, int k)
{
    clock_t start = clock();
    QuickSort(userValues, 0, userValues.size() - 1, k);
    cout << k << "th element is: " << userValues.at(k) << ". ";
    double t = (clock() - start) / (double)CLOCKS_PER_SEC;
    cout << "For n=" << n << " and k=" << k << ".Comparisons=" << compCount << ". Time: "
         << t << "\n";

    random_device shuffler;
    mt19937 g(shuffler());

    shuffle(userValues.begin(), userValues.end(), shuffler);
    compCount = 0;
}

void SELECT2(vector<int> &userValues, int n, int k)
{
    uniform_int_distribution<int> userValuesDist(0, userValues.size());
    random_device seeder;
    mt19937 mtGen;
    mtGen.seed(userValuesDist(seeder));

    int randomIndex = userValuesDist(mtGen);
    clock_t start = clock();

    QuickSort(userValues, 0, randomIndex, k);

    cout << k << "th element is: " << userValues.at(k) << ". ";

    double t = (clock() - start) / (double)CLOCKS_PER_SEC;

    cout << "For n=" << n << " and k=" << k << ".Comparisons=" << compCount << ". Time: "
         << t << "\n";

    random_device shuffler;
    mt19937 g(shuffler());

    shuffle(userValues.begin(), userValues.end(), shuffler);
    compCount = 0;
}

void SELECT3(vector<int> &userValues, int n, int k)
{
    vector<vector<int>> allRows;
    vector<int> row;
    for (int i = 0; i <= userValues.size() - 1; i++)
    {
        row.emplace_back(userValues.at(i));
        if (floor(i % 5) == 0)
        {
            row.emplace_back(userValues.at(i));
            allRows.emplace_back(row);
            row.clear();
        }
    }
    row = allRows.at((allRows.size() - 1) / 2);

    int m = row.at((row.size() - 1) / 2);

    auto it = find(userValues.begin(), userValues.end(), m);
    int ri = distance(userValues.begin(), it);

    clock_t start = clock();

    QuickSort(userValues, 0, ri, k);

    cout << k << "th element is: " << userValues.at(k) << ". ";

    double t = (clock() - start) / (double)CLOCKS_PER_SEC;

    cout << "For n=" << n << " and k=" << k << ".Comparisons=" << compCount << ". Time: "
         << t << "\n";

    random_device shuffler;
    mt19937 g(shuffler());

    shuffle(userValues.begin(), userValues.end(), shuffler);
    compCount = 0;
}