#include<iostream>
#include<queue>
#include<stack>
#include<list>
#include<algorithm>
#include<string>
#include<map>
using namespace std;
int main()
{
    map<string, int> muteki;
    pair<string, int> sb("lhs", 1234);
    sb.second = 114;
    muteki.insert(sb);
    muteki["lyl"] = 12345;
    cout << "Not find: " << (muteki.find("zzz") == muteki.end()) << endl;
    cout << "Find: " << muteki.find("lhs")->second << endl;
    cout << "erase(k) return value: " << muteki.erase("lyl") << endl;
    cout << "erase(k) return value: " << muteki.erase("lyl") << endl;
    return 0;
}