#include "dlist.h"
using namespace std;
#include <iostream>
#include <string>
struct _storage
{
    int start = 0;
    string name = "";
    string level;
    int duration = 0;
    _storage(int _s, string _n, string _l, int _d)
    {
        start = _s;
        name = _n;
        level = _l;
        duration = _d;
    }
    _storage(){}
};

class CallCenter
{
private:
    Dlist<_storage> agents[4];
    Dlist<_storage> customer;
    int tick = 0, events, finish_time;
    bool busy = false;
public:
    CallCenter(){}
    ~CallCenter(){}
    void init()
    {
        cin >> events;
        for (int i = 0; i < events; i++)
        {
            int start, duration;
            string cName;
            string level;
            cin >> start >> cName >> level >> duration;
            _storage *tmp = new _storage(start, cName, level, duration);
            customer.insertBack(tmp);
        }
    }

    void loop()
    {
        while(true)
        {
            cout << "Starting tick #" << tick << endl;
            addWaitingList();
            if (busy && finish_time == tick)
            {
                busy = false;
            }
            if(!busy)
            {
                getNewCustm();
            }
            tick++;
            if(end())
            {
                break;
            }
        }
    }

private:
    int index(string str)
    {
        switch (str[0])
        {
        case 'p':
            return 0;
            break;
        case 'g':
            return 1;
            break;
        case 's':
            return 2;
            break;
        case 'r':
            return 3;
            break;
        default:
            return -1;
            break;
        }
    }

    bool end()
    {
        return agents[0].isEmpty() && agents[1].isEmpty() && agents[2].isEmpty() && agents[3].isEmpty() && customer.isEmpty() && !busy;
    }

    void addWaitingList()
    {
        while (true)
        {
            if (customer.isEmpty())
                break;
            _storage *tmp = customer.removeFront();
            if (tmp->start == tick)
            {
                agents[index(tmp->level)].insertBack(tmp);
                cout << "Call from " << tmp->name << " a " << tmp->level << " member" << endl;
            }
            else
            {
                customer.insertFront(tmp);
                break;
            }
        }
    }

    void getNewCustm()
    {
        for (int i = 0; i < 4; i++)
        {
            if (agents[i].isEmpty())
            {
                continue;
            }
             _storage *cur = agents[i].removeFront();
            finish_time = cur->duration + tick;
            cout << "Answering call from " << cur->name << endl;
            busy = true;
            delete cur;
            break;
        }
    }
};

int main()
{
    CallCenter sq;
    sq.init();
    sq.loop();
}