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
    virtual void sp() = 0;
};
class foo : public spam
{
public:
    int x = 2;
    void sp()
    {
        cout << "foo" << endl;
    }
};
int main()
{
    foo *spf;
    foo k;
    spam *test = &k;
    spf = dynamic_cast<foo *>(test);
    spf->sp();
    return 0;
}