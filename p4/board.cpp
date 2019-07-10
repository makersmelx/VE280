#include "board.h"
Board::Board()
{
    for (int i = 0; i < NP; i++)
    {
        grid[i / 4][i % 4] = Square(Vaxis(i / 4), Haxis(i % 4));
    }
}

Square &Board::getSquare(Vaxis v, Haxis h)
{
    return grid[int(v)][int(h)];
}

Square &Board::getEmptySquare(Vaxis v, Haxis h)
{
    Square sq = getSquare(v, h);
    if (!sq.isEmpty())
    {
        throw SquareException(sq, "not empty");
    }
    else
    {
        return getSquare(v, h);
    }
}

Square &Board::getEmptySquare(const std::string &s)
{
    Vaxis v;
    Haxis h;
    char va[4] = {'A', 'B', 'C', 'D'};
    char ha[4] = {'1', '2', '3', '4'};
    for (int i = 0; i < 4; i++)
    {
        if (s[0] == va[i])
        {
            v = Vaxis(i);
        }
        if (s[1] == ha[i])
        {
            h = Haxis(i);
        }
    }
    return getEmptySquare(v, h);
}

void Board::place(Piece &p, Square &sq)
{
    Piece *q = &p;
    p.setUsed(true);
    sq.setPiece(q);
}

bool Board::isWinning(const Piece &p, const Square &sq)
{
    bool win = false, empty = false;
    Vaxis v = sq.getV();
    Haxis h = sq.getH();
    Piece tar;
    if (grid[int(v)][int(h)].isEmpty())
    {
        tar = p;
    }
    else
    {
        tar = grid[int(v)][int(h)].getPiece();
    }
    for (int i = 0; i < 4; i++)
    {
        if (grid[int(v)][i].isEmpty() && i != int(h))
        {
            empty = true;
            break;
        }
    }
    if (!empty)
    {
        bool comp[4] = {1, 1, 1, 1};
        for (int i = 0; i < 4 && i != int(h); i++)
        {
            comp[0] = comp[0] && (grid[int(v)][i].getPiece().compareHeight(tar));
            comp[1] = comp[1] && (grid[int(v)][i].getPiece().compareColor(tar));
            comp[2] = comp[2] && (grid[int(v)][i].getPiece().compareShape(tar));
            comp[0] = comp[3] && (grid[int(v)][i].getPiece().compareTop(tar));
        }
        win = comp[0] || comp[1] || comp[2] || comp[3];
    }
    if (win)
        return true;
    empty = false;
    for (int i = 0; i < 4; i++)
    {
        if (grid[i][int(h)].isEmpty() && i != int(v))
        {
            empty = true;
            break;
        }
    }
    if (!empty)
    {
        bool comp[4] = {1, 1, 1, 1};
        for (int i = 0; i < 4 && i != int(v); i++)
        {
            comp[0] = comp[0] && (grid[i][int(h)].getPiece().compareHeight(tar));
            comp[1] = comp[1] && (grid[i][int(h)].getPiece().compareColor(tar));
            comp[2] = comp[2] && (grid[i][int(h)].getPiece().compareShape(tar));
            comp[0] = comp[3] && (grid[i][int(h)].getPiece().compareTop(tar));
        }
        win = comp[0] || comp[1] || comp[2] || comp[3];
    }
    if (win)
        return true;
    empty = false;
    if (sq.isOnFirstDiagonal())
    {
        for (int i = 0; i < 4; i++)
        {
            if (grid[i][i].isEmpty() && i != int(v))
            {
                empty = true;
                break;
            }
        }
        if (!empty)
        {
            bool comp[4] = {1, 1, 1, 1};
            for (int i = 0; i < 4 && i != int(v); i++)
            {
                comp[0] = comp[0] && (grid[i][i].getPiece().compareHeight(tar));
                comp[1] = comp[1] && (grid[i][i].getPiece().compareColor(tar));
                comp[2] = comp[2] && (grid[i][i].getPiece().compareShape(tar));
                comp[0] = comp[3] && (grid[i][i].getPiece().compareTop(tar));
            }
            win = comp[0] || comp[1] || comp[2] || comp[3];
        }
    }
    if (win)
        return true;
    empty = false;
    if (sq.isOnSecondDiagonal())
    {
        for (int i = 0; i < 4; i++)
        {
            if (grid[i][3 - i].isEmpty() && i != int(v))
            {
                empty = true;
                break;
            }
        }
        if (!empty)
        {
            bool comp[4] = {1, 1, 1, 1};
            for (int i = 0; i < 4 && i != int(v); i++)
            {
                comp[0] = comp[0] && (grid[i][3 - i].getPiece().compareHeight(tar));
                comp[1] = comp[1] && (grid[i][3 - i].getPiece().compareColor(tar));
                comp[2] = comp[2] && (grid[i][3 - i].getPiece().compareShape(tar));
                comp[0] = comp[3] && (grid[i][3 - i].getPiece().compareTop(tar));
            }
            win = comp[0] || comp[1] || comp[2] || comp[3];
        }
    }
    return win;
}

std::string Board::toString() const
{
    std::string res;
    res += "    1    2    3    4   \n";
    res += "  +----+----+----+----+\n";
    std::string head[4] = {"a ", "b ", "c ", "d "};
    for (int j = 0; j < 4; j++)
    {
        std::string first_l;
        std::string sec_l;
        first_l += head[j];
        sec_l += "  ";
        for (int i = 0; i < 4; i++)
        {
            first_l.push_back('|');
            sec_l.push_back('|');
            std::string buff_f;
            std::string buff_d;
            if (grid[j][i].isEmpty())
            {
                buff_f = "    ";
                buff_d = "    ";
            }
            else
            {
                Square tmp = grid[j][i];
                std::string tmp_str = tmp.getPiece().toString();
                buff_f = " " + tmp_str.substr(0, 2) + " ";
                buff_d = " " + tmp_str.substr(2, 2) + " ";
            }
            first_l += buff_f;
            sec_l += buff_d;
        }
        first_l += "|\n";
        sec_l += "|\n";
        res += first_l + sec_l;
        res += "  +----+----+----+----+\n";
    }
    return res;
}