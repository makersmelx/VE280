#include "player.h"
#include <iostream>
using namespace std;

class HumanPlayer : public Player
{
public:
    HumanPlayer(Board *board, Pool *pool) : Player(board, pool) {}
    Piece &selectPiece()
    {
        string input;
        int res[4] = {0, 0, 0, 0};
        while (true)
        {
            try
            {
                cout << "Enter a piece:" << endl;
                cin >> input;
                if (input.length() != 4)
                {
                    throw InvalidInputException(input);
                }
                for (int i = 0; i < 4; i++)
                {
                    if (input[i] == ALLCODE[i][0])
                    {
                        res[i] = 0;
                    }
                    else if (input[i] == ALLCODE[i][1])
                    {
                        res[i] = 1;
                    }
                    else
                    {
                        throw InvalidInputException(input);
                    }
                }
                pool->getUnusedPiece(Height(res[0]), Color(res[1]), Shape(res[2]), Top(res[3]));
                break;
            }
            catch (const InvalidInputException &e)
            {
                cout << e.what() << endl;
            }
            catch (const UsedPieceException &e)
            {
                cout << e.what() << endl;
            }
        }
        return pool->getUnusedPiece(Height(res[0]), Color(res[1]), Shape(res[2]), Top(res[3]));
    }

    Square &selectSquare(const Piece &p)
    {
        string input;
        int _v, _h;
        while (true)
        {
            try
            {
                cout << "Enter a position:" << endl;
                cin >> input;
                if (input.length() != 2)
                {
                    throw InvalidInputException(input);
                }
                char v[4] = {'A', 'B', 'C', 'D'};
                char h[4] = {'1', '2', '3', '4'};
                for (int i = 0; i < 4; i++)
                {
                    if (input[0] == v[i])
                    {
                        _v = i;
                        break;
                    }
                    if (i == 3)
                    {
                        throw InvalidInputException(input);
                    }
                }
                for (int i = 0; i < 4; i++)
                {
                    if (input[1] == h[i])
                    {
                        _h = i;
                        break;
                    }
                    if (i == 3)
                    {
                        throw InvalidInputException(input);
                    }
                }
                board->getEmptySquare(Vaxis(_v), Haxis(_h));
                break;
            }
            catch (const InvalidInputException &e)
            {
                cout << e.what() << endl;
            }
            catch (const SquareException &e)
            {
                cout << e.what() << endl;
            }
        }
        return board->getSquare(Vaxis(_v), Haxis(_h));
    }
};

class MyopicPlayer : public Player
{
    unsigned int rand_seed;

public:
    MyopicPlayer(Board *board, Pool *pool, const unsigned int &_seed) : Player(board, pool)
    {
        rand_seed = _seed;
    }

    Piece &selectPiece()
    {
        srand(rand_seed);
        int index;
        int good_array[NP];
        int good_currentLength = 0;
        int array[NP];
        int currentLength = 0;
        for (int i = 0; i < NP; i++)
        {
            try
            {
                pool->getUnusedPiece(Height(i / 8), Color((i / 4) % 2), Shape((i / 2) % 2), Top(i % 2));
            }
            catch (const UsedPieceException &e)
            {
                continue;
            }
            array[currentLength++] = i;
            Piece &p = pool->getUnusedPiece(Height(i / 8), Color((i / 4) % 2), Shape((i / 2) % 2), Top(i % 2));
            bool flag = true;
            for (int j = 0; j < NP; j++)
            {
                try
                {
                    board->getEmptySquare(Vaxis(j / 4), Haxis(j % 4));
                }
                catch (const SquareException &e)
                {
                    continue;
                }
                if (board->isWinning(p, board->getEmptySquare(Vaxis(j / 4), Haxis(j % 4))))
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                good_array[good_currentLength++] = i;
            }
        }
        index = good_currentLength == 0 ? rand() % currentLength : rand() % good_currentLength;
        return pool->getUnusedPiece(Height(array[index] / 8), Color((index / 4) % 2), Shape((array[index] / 2) % 2), Top(array[index] % 2));
    }

    Square &selectSquare(const Piece &p)
    {
        srand(rand_seed);
        int array[NP];
        int currentLength = 0;
        for (int j = 0; j < NP; j++)
        {
            try
            {
                board->getEmptySquare(Vaxis(j / 4), Haxis(j % 4));
            }
            catch (const SquareException &p)
            {
                continue;
            }
            Square &sq = board->getEmptySquare(Vaxis(j / 4), Haxis(j % 4));
            if (board->isWinning(p, sq))
            {
                return sq;
            }
            array[currentLength++] = j;
        }
        int index = rand() % currentLength;
        return board->getEmptySquare(Vaxis(array[index] / 4), Haxis(array[index] % 4));
    }
};

extern Player *getHumanPlayer(Board *b, Pool *p)
{
    Player *_p = new HumanPlayer(b, p);
    return _p;
}

extern Player *getMyopicPlayer(Board *b, Pool *p, unsigned int s)
{
    Player *_p = new MyopicPlayer(b, p, s);
    return _p;
}