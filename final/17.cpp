#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <string>
using namespace std;
class note
{
    //delete只能删new的
};
int add(int a, int b = 0, int c = 145)
{
    return a + b + c;
}
int main()
{
    int sj = 10;
    int *yy = new int[sj];
    delete[] yy;
    cout << add(99) << endl;
    cout << add(1, 2, 3);
    return 0;
}