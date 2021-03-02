/**
 * @file quicksort.cc
 * @author Glorian Kosi
 * @brief 
 * @version 0.1
 * 
 * 
 * -------Must be using at least C++17---------
 * 
 * To compile, example:
 * g++ -std=c++2a quicksort.cc -o qsort
 * 
 * To run, supply command line arguments (must be integers, signed/unsigned both 
 * work), example using previous command:
 * ./msort 1 200 10 40 50 600 100 20 40 2 2 6 100
 * 
 * Result is printed in terminal, this is a quicksort using a LOMUTO PARTITION SCHEME:
 * https://en.wikipedia.org/wiki/Quicksort, see also CLRS Book Chapter 7, pg 170-179
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

void QuickSort(vector<int> &, int, int);
int Partition(vector<int> &, int, int);

int main(int argc, char *argv[])
{
  clock_t start;
  double t;
  vector<int> userValues;
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> distr(0, 2500);
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
  // for (int i = 0; i <= 1024; i++)
  // {
  //   userValues.push_back(i);
  //   // userValues.push_back(distr(gen));
  // }
  // reverse(userValues.begin(), userValues.end());
  start = clock();
  QuickSort(userValues, 0, userValues.size() - 1);
  t = (clock() - start) / (double)CLOCKS_PER_SEC;
  cout << "---Time---"
       << "\n";
  cout << t << '\n';
}

int Partition(vector<int> &userValues, int lo, int hi)
{
  int pivot = userValues.at(hi);
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

void QuickSort(vector<int> &userValues, int lo, int hi)
{
  if (lo < hi)
  {
    int p = Partition(userValues, lo, hi);
    QuickSort(userValues, lo, p - 1);
    QuickSort(userValues, p + 1, hi);
  }
}
