/**
 * @file stringsort.cc
 * @author Glorian Kosi
 * @brief 
 * @version 0.1
 * 
 * -------Must be using at least C++20---------

 *  ---NOT WORKING PROPERLY, Needs work--

 * To compile, example:
 * g++ -std=c++2a stringsort.cc -o stringsort
 * 
 */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <ctime>
#include <fstream>
#include <map>

const int K = 20;

using std::begin;
using std::cerr;
using std::clock_t;
using std::cout;
using std::end;
using std::exception;
using std::fstream;
using std::getline;
using std::invalid_argument;
using std::map;
using std::out_of_range;
using std::runtime_error;
using std::string;
using std::vector;
using std::filesystem::exists;

const vector<vector<char>> get_multi_dimensional_vec(fstream &);
void pad_string(string &, int &);

void RadixSort(const vector<vector<char>> &);

int main(int argc, char *argv[])
{
    try
    {
        if (argc <= 2)
            throw out_of_range("Please supply the required arguments...");

        string in_file = argv[1];
        string out_file = argv[2];

        if (exists(in_file) == false)
            throw runtime_error("Input file doesn't exist...");

        fstream in_file_fstream(in_file, in_file_fstream.in);
        RadixSort(get_multi_dimensional_vec(in_file_fstream));
    }

    catch (const out_of_range &e)
    {
        cerr << e.what() << '\n';
    }
    catch (const runtime_error &e)
    {
        cerr << e.what() << '\n';
    }
    return 0;
}

const vector<vector<char>> get_multi_dimensional_vec(fstream &in_file_fstream)
{
    string line;
    vector<vector<char>> in_file_strs;

    while (getline(in_file_fstream, line, ' '))
    {
        int line_size = line.size();

        if (line_size < K)
        {
            pad_string(line, line_size);
        }
        vector<char> str_chars(line.begin(), line.end());
        in_file_strs.emplace_back(str_chars);
    }
    return in_file_strs;
}

void RadixSort(const vector<vector<char>> &in_file_strs)
{

    vector<char> P;
    const int ROW_SIZE = in_file_strs.size();
    for (int i = 0; i < ROW_SIZE; i++)
    {
        P.emplace_back(i);
    }
    for (int x = K; x >= 0; --x)
    {
        int count = 0;
        map<char, vector<int>> B;

        for (int i = 0; i < ROW_SIZE; i++)
        {
            char current_char = in_file_strs[i][x];
            B[current_char].emplace_back(P[i]);
        }

        for (int i = 0; i < 27; i++)
        {
            for (int j = 0; j < 21; j++)
            {
                if (!B[i].empty())
                {
                    P[count] = B[i][j];
                    count++;
                }
            }
        }
    }

    fstream outfile("g.txt", outfile.out | outfile.trunc);

    for (int i = 0; i < ROW_SIZE; i++)
    {
        for (int j = 0; j < in_file_strs[P[i]].size(); j++)
        {
            outfile << in_file_strs[P[i]][j];
            cout << in_file_strs[P[i]][j];
        }
        outfile << "\n";
        cout << "\n";
    }
}

void pad_string(string &line, int &current_size)
{
    line += string(K - current_size, ' ');
}