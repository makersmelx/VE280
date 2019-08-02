#include "dlist.h"
#include <iostream>
#include <string>
using namespace std;
class RPN_calc
{
private:
    Dlist<int> stk;
    Dlist<int> tmpRes;
    enum token
    {
        operand,
        plus,
        minus,
        times,
        divide,
        negative,
        duplicate,
        reverse,
        print,
        clear,
        printAll,
        quit
    };
    string op_str[11] = {"+", "-", "*", "/", "n", "d", "r", "p", "c", "a", "q"};
    token op;
    string cur_input;

public:
    RPN_calc() {}
    ~RPN_calc() {}

    void loop()
    {
        while (op != quit)
        {
            try
            {
                decideMode();
                if (op == quit)
                {
                    break;
                }
                process();
            }
            catch (const int &err)
            {
                errorMsg(err);
            }
        }
    }

private:
    void decideMode()
    {
        cin >> cur_input;
        //getline(cin, cur_input);
        if (cur_input.size() > 1)
        {
            int loopStart = 0;
            if (cur_input[0] == '-')
            {
                loopStart = 1;
            }
            for (int i = loopStart; i < cur_input.size(); i++)
            {
                if (cur_input[i] - '0' < 0 || cur_input[i] - '0' > 9)
                {
                    throw - 1;
                }
            }
            op = operand;
        }
        else
        {
            if (cur_input[0] - '0' >= 0 && cur_input[0] - '0' <= 9)
            {
                op = operand;
                return;
            }
            for (int i = 0; i < 11; i++)
            {
                if (cur_input == op_str[i])
                {
                    op = token(i + 1);
                    break;
                }
                if (i == 10)
                {
                    throw - 1;
                }
            }
        }
    }
    void process()
    {
        switch (op)
        {
        case operand:
        {
            int *tmp = new int(stoi(cur_input));
            stk.insertFront(tmp);
            break;
        }
        case plus:
        case minus:
        case times:
        case divide:
        {
            operandsJudge(2);
            binaryOp(op);
            break;
        }
        case negative:
        {
            operandsJudge(1);
            int *num = stk.removeFront();
            int *neg_num = new int(*num * -1);
            delete num;
            stk.insertFront(neg_num);
            break;
        }
        case duplicate:
        {
            operandsJudge(1);
            int *num = stk.removeFront();
            int *dup1 = new int(*num);
            int *dup2 = new int(*num);
            stk.insertFront(dup1);
            stk.insertFront(dup2);
            delete num;
            break;
        }
        case reverse:
        {
            operandsJudge(2);
            int *num1 = stk.removeFront();
            int *num2 = stk.removeFront();
            stk.insertFront(num1);
            stk.insertFront(num2);
            break;
        }
        case print:
        case printAll:
        {
            printStk(op);
            break;
        }
        case clear:
        {
            int *delTmp;
            while (!stk.isEmpty())
            {
                delTmp = stk.removeFront();
                delete delTmp;
            }
            break;
        }
        default:
            break;
        }
    }

    void operandsJudge(int nums) const
    {
        Dlist<int> test(stk);
        for (int i = 0; i < nums; i++)
        {
            if (test.isEmpty())
            {
                throw - 2;
            }
            int *delTmp = test.removeFront();
            delete delTmp;
        }
    }

    void binaryOp(token op)
    {
        int *res = new int;
        int *num2 = stk.removeFront();
        int *num1 = stk.removeFront();
        switch (op)
        {
        case plus:
        {
            *res = *num1 + *num2;
            break;
        }

        case minus:
        {
            *res = *num1 - *num2;
            break;
        }

        case times:
        {
            *res = (*num1) * (*num2);
            break;
        }

        case divide:
        {
            if (*num2 == 0)
            {
                delete res;
                delete num1;
                delete num2;
                throw - 3;
            }
            *res = (*num1) / (*num2);
            break;
        }

        default:
            break;
        }
        stk.insertFront(res);
        delete num1;
        delete num2;
    }

    void printStk(token op)
    {
        Dlist<int> tmp(stk);
        if (op == print)
        {
            operandsJudge(1);
            int *printTmp;
            printTmp = tmp.removeFront();
            cout << *printTmp << endl;
            delete printTmp;
        }
        else
        {
            int *printTmp;
            while (!tmp.isEmpty())
            {
                printTmp = tmp.removeFront();
                cout << *printTmp << " ";
                delete printTmp;
            }
            cout << endl;
        }
    }

    void errorMsg(int mode)
    {
        switch (mode)
        {
        case -1:
            cout << "Bad input\n";
            break;
        case -2:
            cout << "Not enough operands\n";
            break;
        case -3:
            cout << "Divide by zero\n";
            break;
        default:
            break;
        }
    }
};

int main()
{
    RPN_calc zzzCalc;
    zzzCalc.loop();
    return 0;
}
