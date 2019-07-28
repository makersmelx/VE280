#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    int num = stoi(argv[1]);
    srand((unsigned)time(nullptr));
    int time = 0;
    string name[30] = {"Tom", "Mike", "Jim", "Jerry",
                       "YYA", "YY", "WG", "JY", "SJ",
                       "BJ", "ZDK", "AO", "DOU", "F",
                       "MinatoYukina", "DonaldTrump", "David", "M",
                       "Tommy", "MZQ", "MDD", "Zhen",
                       "Horst", "MJX", "LYL", "HatsuneMiku",
                       "ToyamaKasumi", "SQ", "ZZZ", "HYC"};
    string level[4] = {"platinum", "gold", "silver", "regular"};
    cout << num << endl;
    for (int i = 0; i < num; i++)
    {
        cout << time << " " << name[rand() % 30] << " " << level[rand() % 4] << " " << rand() % 20 + 1 << endl;
        time += rand() % 10;
    }
    return 0;
}
