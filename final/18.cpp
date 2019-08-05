#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <string>
using namespace std;
int main()
{
    //shallow copy
    int *yy = new int[10];
    for (int i = 0; i < 10; i++)
    {
        yy[i] = i;
    }
    int *sj = yy;
    for (int i = 0; i < 10; i++)
    {
        sj[i] = i + 100;
    }
    for (int i = 0; i < 10; i++)
    {
        cout << yy[i] << endl;
    }
    return 0;
}