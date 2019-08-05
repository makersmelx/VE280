#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <string>
using namespace std;
class spam
{
protected:
    int PrivateCannotAcc = 114;
};

class foo : public spam
{
public:
    void a()
    {
        cout << PrivateCannotAcc << endl;
    }
    void b(foo x)
    {
        cout << x.PrivateCannotAcc + 1 << endl;
    }
};
class bigSpam
{
protected:
    int val = 222;

public:
    virtual void a()
    {
        cout << val << endl;
    }
};
class bigFoo : public bigSpam
{
public:
    void a()
    {
        cout << val + 111 << endl;
    }
};
class note
{
    //Subtype: code written for its father should follow substitution principle.
};
int main()
{
    foo sj;
    spam *sb = &sj;
    spam &xx = sj;
    //sb和xx此时是spam,没有foo的方法
    sj.a();
    sj.b(sj);
    bigFoo lhs;
    lhs.a();
    bigSpam *ssb = &lhs;
    ssb->a();
    return 0;
}