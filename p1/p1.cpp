#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int test_one(int n)
{
    int tmp = n * 2;
    int i = 0;
    while ((i * i) < tmp)
        i++;
    //cout << "!" << i << endl;
    if (i * (i - 1) == tmp)
        return 1;
    else
    {
        return 0;
    }
}

int test_two(int n)
{
    string num = to_string(n);
    int digit = num.length();
    if (digit == 1)
        cout << "1" << endl;
    for (int i = 0; i < digit / 2; i++)
    {
        if (num[i] != num[digit - i - 1])
        {
            return 0;
        }
    }
    return 1;
}

int test_three(int n)
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
        return 1;
    else
        return 0;
}

int test_four(int n)
{
    string num = to_string(n);
    int digit = num.length();
    int frac_count = 0;
    for (int i = 2; i <= n; i++)
    {
        int i_count = 0;
        int digit_of_i = 0;
        int tmp_i = i;
        while (tmp_i != 0)
        {
            tmp_i /= 10;
            digit_of_i++;
        }

        if (n % i == 0)
            frac_count += digit_of_i;
        else
            continue;
        while (n % i == 0)
        {
            n /= i;
            i_count++;
        }
        if (i_count >= 2)
        {
            string i_num = to_string(i_count);
            frac_count += i_num.length();
        }
    }
    if (digit < frac_count)
        return 1;
    else
        return 0;
}

int main()
{
    int n, type;
    while (true)
    {
        cout << "Please enter the integer and the test number: ";
        cin >> n >> type;
        if (n > 10000000 || n < 0)
            continue;
        if (type < 1 || type > 4)
            continue;

        break;
    }
    if (type == 1)
    {
        cout << test_one(n);
    }
    else if (type == 2)
    {
        cout << test_two(n);
    }
    else if (type == 3)
    {
        cout << test_three(n);
    }
    else if (type == 4)
    {
        cout << test_four(n);
    }
}