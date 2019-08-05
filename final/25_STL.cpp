#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <string>
using namespace std;
template<class T>
void transverse(vector<T> &v)
{
    for (unsigned int i = 0; i < v.size();i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}
int main()
{
    vector<int> sj(100, 0);
    sj[0] = 1;
    sj[1] = 2;
    vector<int>::iterator itr = sj.erase(sj.begin());
    cout << *itr << endl;
    cout << (itr == sj.begin()) << endl;
    for (vector<int>::size_type ix = 0; ix != 10;ix++)
    {
        sj[ix] = ix;
    }
    for (int i = 0; i < 10;i++)
    {
        cout << sj[i] << " ";
    }
    cout << endl;
    vector<int> lhs(itr, itr + 10);//copy
    transverse(lhs);
    int a[] = {1, 4, 5, 6, 7};
    vector<int> lyl(a, a + sizeof(a) / sizeof(int));
    lyl.insert(lyl.begin(), 67);
    transverse(lyl);
    deque<int> mjx(sj.begin(), sj.end());
    cout << mjx[8] << endl;
    return 0;
}