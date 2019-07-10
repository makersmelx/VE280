#include "pool.h"

Pool::Pool()
{
    for (int i = 0; i < NP; i++)
    {
        pieces[i] = Piece(Height(i / 8), Color((i / 4) % 2), Shape((i / 2) % 2), Top(i % 2));
    }
}

Piece &Pool::getUnusedPiece(int index) //Suppose that index is 0 to 15
{
    if (pieces[index].isUsed())
    {
        throw UsedPieceException(pieces[index]);
    }

    else
    {
        return pieces[index];
    }
}

Piece &Pool::getUnusedPiece(Height h, Color c, Shape s, Top t)
{
    return getUnusedPiece(h * 8 + c * 4 + s * 2 + t);
}

Piece &Pool::getUnusedPiece(const std::string &in)
{
    int index = ((in[0] == 'S') ? 0 : 8) + ((in[1] == 'B') ? 0 : 4) + ((in[2] == 'C') ? 0 : 2) + ((in[3] == 'H') ? 0 : 1);
    return getUnusedPiece(index);
}

std::string Pool::toString() const
{
    std::string first, second, res;
    for (int i = 0; i < 16; i++)
    {
        if (!pieces[i].isUsed())
        {
            std::string tmp = pieces[i].toString();
            first = first + tmp.substr(0, 2) + " ";
            second = second + tmp.substr(2, 2) + " ";
        }
    }
    if (first.empty())
    {
        return first;
    }
    else
    {
        first.pop_back();
        second.pop_back();
        res = "Available:\n" + first + "\n" + second;
    }
    return res;
}