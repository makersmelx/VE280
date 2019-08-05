#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <string>
using namespace std;
class BoundsError
{
};
template <class T>
class seqList
{
private:
    T *data;
    int curLength;
    int maxSize;

public:
    seqList(int initSize = 10)
    {
        maxSize = initSize;
        data = new T[maxSize];
        curLength = 0;
    }
    seqList(const seqList<T> &l)
    {
        data = NULL;
        curLength = 0;
        maxSize = 0;
        copyFrom(l);
    }
    ~seqList() { delete[] data; }
    void insertBack(const T &x)
    {
        if (curLength == maxSize)
        {
            doubleSpace();
        }
        data[curLength] = x;
        curLength++;
    }
    void insert(int i,const T &x)
    {
        if(i < 0 || i > curLength)
        {
            throw BoundsError();
        }
        else
        {
            if(curLength == maxSize)
            {
                doubleSpace();
            }
            curLength++;
            for (int j = curLength; j > i;j--)
            {
                data[j] = data[j - 1];
            }
            data[i] = x;
        }
    }
    void removeBack()
    {
        curLength--;
    }
    void remove(int i)
    {
        if(i < 0 || i > curLength)
        {
            throw BoundsError();
        }
        else
        {
            for (int j = i; j < curLength;j++)
            {
                data[j] = data[j + 1];
            }
            curLength--;
        }
    }
    T back()
    {
        return data[curLength - 1];
    }
    int length() { return curLength; }
    seqList &operator=(const seqList &is)
    {
        if (&is != this)
        {
            copyFrom(is);
        }
        return *this;
    }
    void transverse()
    {
        for (int i = 0; i < curLength; i++)
        {
            cout << data[i] << " ";
        }
        cout << endl;
    }
    const T &operator[](int i) const
    {
        if (i >= 0 && i < curLength)
        {
            return data[i];
        }
        else
            throw - 1;
    }

    int &operator[](int i)
    {
        if (i >= 0 && i < curLength)
        {
            return data[i];
        }
        else
            throw - 1;
    }

private:
    void copyFrom(const seqList &l)
    {
        if (l.maxSize != maxSize)
        {
            delete[] data;
            maxSize = l.maxSize;
            data = new T[maxSize];
        }
        for (int i = 0; i < l.curLength; i++)
        {
            data[i] = l.data[i];
        }
        curLength = l.curLength;
    }
    void doubleSpace()
    {
        maxSize = maxSize * 2;
        int *tmp = new int[maxSize];
        for (int i = 0; i < curLength; i++)
        {
            tmp[i] = data[i];
        }
        delete[] data;
        data = tmp;
    }
};

int main()
{
    int j = 1;
    seqList<int> sj(j);
    sj.insertBack(1);
    sj.insertBack(2);
    sj.insertBack(3);
    sj.insert(1, 56);
    cout << sj.back() << endl;
    sj.transverse();
    sj.remove(2);
    sj.transverse();

    return 0;
}
