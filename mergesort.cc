/**
 * @file mergesort.cc
 * @author Glorian Kosi
 * @brief 
 * @version 0.1
 * 
 * -------Must be using at least C++17---------
 * 
 * To compile, example:
 * g++ -std=c++2a mergesort.cc -o msort
 * 
 * To run, supply command line arguments (must be integers, signed/unsigned both 
 * work), example using previous command:
 * 
 * ./msort 1 200 10 40 50 600 100 20 40 2 2 6
 * 
 * 
 * Result is printed in terminal, this is a TOP-DOWN mergesort.
 * 
 * References and more:
 * 
 * stoi: https://devdocs.io/cpp/string/basic_string/stol 
 * range-based for loop: https://devdocs.io/cpp/language/range-for 
 * invalid_argument: https://devdocs.io/cpp/error/invalid_argument/invalid_argument 
 * vector: https://devdocs.io/cpp/container/vector 
 * 
 * mergesort(in general, very good pseudocode): https://en.wikipedia.org/wiki/Merge_sort
 * mergesort(good explanation, pseudocode and visuals, unsure which textbook they use): https://www.cs.umd.edu/users/meesh/cmsc351/mount/lectures/lect6-divide-conquer-mergesort.pdf
 * mergesort(good visuals and nice explanation along with nice pseudocode, unsure if they refer to textbook):http://www.mathcs.emory.edu/~cheung/Courses/171/Syllabus/7-Sort/merge-sort3.html
 * mergesort(great explanation, and nice walkthrough):CLRS textbook 3rd edition, chapter 2 page 34
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
#include <cstdio>
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

long compCount = 0;

void Merge(vector<int> &, vector<int> &, vector<int> &);
void Split(vector<int> &);
void MergeSort(vector<int> &);

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
    //     // userValues.push_back(i);
    // }
    start = clock();
    MergeSort(userValues);

    // for (auto &&i : userValues)
    // {
    //     cout << i << "\n";
    // }
    t = (clock() - start) / (double)CLOCKS_PER_SEC;
    cout << "---Time---"
         << "\n";
    cout << t << '\n';
}
void Merge(vector<int> &userValues, vector<int> &leftTree, vector<int> &rightTree)
{
    int leftRange = leftTree.size();
    int rightRange = rightTree.size();

    int i = 0;
    int j = 0;
    int k = 0;

    while (j < leftRange && k < rightRange)
    {
        if (leftTree[j] < rightTree[k])
        {
            compCount++; //
            userValues.at(i) = leftTree.at(j);
            j++;
        }
        else
        {
            userValues.at(i) = rightTree.at(k);
            k++;
        }
        i++;
    }
    while (j < leftRange)
    {
        userValues.at(i) = leftTree.at(j);
        j++;
        i++;
    }
    while (k < rightRange)
    {
        userValues.at(i) = rightTree.at(k);
        i++;
        k++;
    }
}
void Split(vector<int> &userValues)
{
    if (userValues.size() <= 1)
        return;

    vector<int> leftTree;
    vector<int> rightTree;

    int middleIndex = userValues.size() / 2;

    for (int i = 0; i < middleIndex; i++)
    {
        leftTree.push_back(userValues[i]);
    }
    for (int i = 0; i < (userValues.size()) - middleIndex; i++)
    {
        rightTree.push_back(userValues[i + middleIndex]);
    }
    Split(leftTree);
    Split(rightTree);
    Merge(userValues, leftTree, rightTree);
}

void MergeSort(vector<int> &userValues)
{
    Split(userValues);
}