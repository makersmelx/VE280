#include <iostream>
#include <string>
using namespace std;
int main()
{
    int n, type;
    while (true)
    {
        cout << "Please enter the integer and the test number: ";
        try
        {
            cin >> n >> type;
            if (n > 10000000 || n < 0)
                throw n;
            if (type < 1 || type > 4)
                throw type;
        }
        catch (int &n)
        {
            continue;
        }
        break;
    }
    if (type == 1)
    {
        int tmp = n * 2;
        int i = 0;
        while ((i * i) < tmp)
            i++;
        //cout << "!" << i << endl;
        if (i * (i - 1) == tmp)
            cout << "1" << endl;
        else
        {
            cout << "0" << endl;
        }
    }
    else if (type == 2)
    {
        string num = to_string(n);
        int digit = num.length();
        if (digit == 1)
            cout << "1" << endl;
        for (int i = 0; i < digit / 2; i++)
        {

            if (num[i] != num[digit - i - 1])
            {
                cout << "0" << endl;
                break;
            }
            if (i == digit / 2 - 1)
                cout << "1" << endl;
        }
    }
    else if (type == 3)
    {
        string bin;
        int tmp = n;
        int count = 0;
        while (tmp > 2)
        {
            int remain = tmp % 2;
            char add = remain + '0';
            bin.push_back(add);
            tmp = tmp / 2;
        }
        bin.push_back('1');
        //cout << bin << endl;
        for (int i = 0; i < bin.length(); i++)
        {
            if (bin[i] == '1')
                count++;
        }
        if (count % 2 == 1)
            cout << "1" << endl;
        else
            cout << "0" << endl;
    }
    else if (type == 4)
    {
        string num = to_string(n);
        int digit = num.length();
        int frac_count = 0;
        for (int i = 2; i <= n; i++)
        {
            int i_count = 0;
            if (n % i == 0)
                frac_count++;
            else
                continue;
            while (n % i == 0)
            {
                n /= i;
                i_count++;
            }
            if (i_count >= 2)
                frac_count++;
        }
        if (digit < frac_count)
            cout << "1" << endl;
        else
            cout << "0" << endl;
    }
}