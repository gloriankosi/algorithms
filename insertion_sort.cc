/*


Glorian Kosi

-------Must be using at least C++20---------

To compile, example:
g++ insertion_sort.cc -o insert_sort

To run, supply command line arguments (must be integers, signed/unsigned both
work), example using previous command:
./insert_sort 5 1 2 5 10 9 9 100 12


More on:
iter_swap: https://devdocs.io/cpp/algorithm/iter_swap
stoi: https://devdocs.io/cpp/string/basic_string/stol
range-based for loop: https://devdocs.io/cpp/language/range-for
invalid_argument: https://devdocs.io/cpp/error/invalid_argument/invalid_argument
vector: https://devdocs.io/cpp/container/vector
auto: https://devdocs.io/cpp/language/auto
iterators: https://devdocs.io/cpp/iterator/iterator



*/
#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>

using std::begin;
using std::cout;
using std::end;
using std::invalid_argument;
using std::iter_swap;
using std::stoi;
using std::vector;

int main(int argc, char *argv[]) {
  vector<int> vec;
  // make an unsorted vector of integer values provided by user in command line
  // arguments
  for (char **i = argv; i != argv + argc; i++) {
    try {
      int val = stoi(*i);
      vec.push_back(val);
    } catch (invalid_argument) {
      continue;
    }
  }

  for (auto i = vec.begin(); i != vec.end(); i++) {
    if (i == vec.begin()) {
      continue;
    } else {
      auto j = i;
      while (j != (vec.begin())) {
        if (*j <= *(j - 1)) {
          iter_swap(j, j - 1);
        }
        j--;
      }
    }
  }
  // output sorted vector
  for (auto i : vec) {
    cout << i << "\n";
  }
}