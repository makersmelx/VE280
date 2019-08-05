#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <string>
using namespace std;
class emptylist
{
};
template <class T>
class slinkList
{
private:
    struct node
    {
        T val;
        node *next;
        node(const T &x, node *n = NULL) : val(x), next(n) {}
        node() : next(0) {}
        ~node() {}
    };
    node *head;
    int curLength = 0;

public:
    slinkList()
    {
        head = new node;
    }
    slinkList(const slinkList<T> &l)
    {
        head = new node;
        copy(l.head->next);
    }
    ~slinkList()
    {
        clear();
        delete head;
    }
    bool isEmpty()
    {
        return head->next == NULL;
    }
    void remove()
    {
        if (isEmpty())
        {
            throw emptylist();
        }
        else
        {
            node *p = head->next;
            head->next = p->next;
            delete p;
            curLength--;
        }
    }
    T top()
    {
        if (isEmpty())
        {
            throw emptylist();
        }
        else
        {
            return head->next->val;
        }
    }

    void insert(const T &x)
    {
        node *tmp = new node(x);
        tmp->next = head->next;
        head->next = tmp;
        curLength++;
    }
    int size()
    {
        return curLength;
    }
    slinkList &operator=(const slinkList &l)
    {
        if (this != &l)
        {
            clear();
            copy(l.head->next);
        }
        return *this;
    }
    void transverse()
    {
        node *tmp = head->next;
        while (tmp != NULL)
        {
            cout << tmp->val << " ";
            tmp = tmp->next;
        }
        cout << endl;
    }

private:
    void clear()
    {
        node *p = head->next, *q;
        while (p != nullptr)
        {
            q = p->next;
            delete p;
            p = q;
        }
    }
    void copy(node *source)
    {
        if (!source)
        {
            return;
        }
        copy(source->next);
        insert(source->val);
    }
};
int main()
{
    int x = 3;
    slinkList<int> sj;
    sj.insert(x);
    sj.insert(2);
    sj.insert(x + 2);
    sj.transverse();
    cout << sj.size() << endl;
    slinkList<int> cpy(sj);
    cpy.transverse();
    return 0;
}