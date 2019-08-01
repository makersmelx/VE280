#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
using namespace std;
//agrv1 存输入的文件夹
//argv2 存标准答案的文件夹
//argv3 混乱选项
int main(int argc, char **argv)
{
    if(argc ==4 )
    {
        string res = "-1 -2 + a -1 / a q";
        //string res = "123.456\n12,45\n,,45\n546\np\na\n+\np\na\n-\np\na\n*\np\na\n/\np\na\nc\np\na\nn\nd\nr\n+\n-\n*\n/\n0\n12\nc\n0\nr\n12\np\na\nr\na\n/\nc\n0\n0\n/\nq";
        cout << res;
        return 0;
    }

    int n = 0;
    cin >> n;
    for (int itr = 0; itr < n; itr++)
    {
        stringstream ss;
        string file_index;
        ss << itr;
        ss >> file_index;
        stack<char> marks;
        string expression, res;
        cin >> expression;
        int num_st = -1;
        int num_length = 0;
        for (int i = 0; i < expression.size(); i++)
        {
            int n = expression[i] - '0';
            if (0 <= n && n <= 9)
            {
                if (num_st == -1)
                {
                    num_st = i;
                }
                num_length++;
            }
            else
            {
                if (num_st != -1)
                {
                    string _num = expression.substr(num_st, num_length);
                    res = res + _num + "\n";
                    num_st = -1;
                    num_length = 0;
                }
                if (expression[i] == '=')
                {
                    //dir
                    string ofileName = argv[2];
                    ofileName = ofileName + "/stdAns_" + file_index;
                    ofstream ofile(ofileName);
                    ofile << expression.substr(i + 1) << endl;
                    ofile.close();
                    //cout << expression.substr(i + 1);
                    break;
                }
                char &c = expression[i];
                switch (c)
                {
                case '(':
                {
                    marks.push(c);
                    break;
                }

                case ')':
                {
                    while (marks.top() != '(')
                    {
                        char tmp = marks.top();
                        marks.pop();
                        res.push_back(tmp);
                        res.push_back('\n');
                    }
                    marks.pop();
                    break;
                }
                case '*':
                case '/':
                {
                    while (!marks.empty() && marks.top() != '(' && marks.top() != '+' && marks.top() != '-')
                    {
                        char tmp = marks.top();
                        marks.pop();
                        res.push_back(tmp);
                        res.push_back('\n');
                    }
                    marks.push(c);
                    break;
                }
                case '+':
                case '-':
                {
                    while (!marks.empty() && marks.top() != '(')
                    {
                        char tmp = marks.top();
                        marks.pop();
                        res.push_back(tmp);
                        res.push_back('\n');
                    }
                    marks.push(c);
                    break;
                }
                case 'n':
                {
                    marks.push(c);
                    break;
                }
                default:
                    break;
                }
            }
        }
        while (!marks.empty())
        {
            char tmp = marks.top();
            marks.pop();
            res.push_back(tmp);
            res.push_back('\n');
        }
        res = res + "p\nq\n";
        string ifileName = argv[1];
        ifileName = ifileName + "/" + file_index;
        ofstream file(ifileName);
        file << res;
        file.close();
    }
}