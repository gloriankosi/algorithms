#include <iostream>
using namespace std;

int T = 0;
int sum(int A[], int n)
{
    if (n == 1)
    {
        return A[0];
    }
    else
    {
        T = sum(A, n - 1);
        T = T + A[n - 1];
        return T;
    }
    return -1;
}
int main()
{
    int A[] = {50, 60, 30};
    int total = sum(A, 3);
    cout << total << "\n";
}