#include "board.h"
#include <iostream>
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
    // Piece tar;
    // if (grid[int(v)][int(h)].isEmpty())
    // {
    //     tar = p;
    // }
    // else
    // {
    //     tar = grid[int(v)][int(h)].getPiece();
    // }

    for (int mode = 0; mode < 4; mode++)
    {
        int test[4] = {int(h), int(v), int(v), int(v)};
        if (mode == 2 && !sq.isOnFirstDiagonal())
            continue;
        if (mode == 3 && !sq.isOnSecondDiagonal())
            break;
        for (int i = 0; i < 4; i++)
        {
            int test_arg[4][2] = {{int(v), i}, {i, int(h)}, {i, i}, {i, 3 - i}};
            if (grid[test_arg[mode][0]][test_arg[mode][1]].isEmpty() && i != test[mode])
            {
                empty = true;
                break;
            }
        }
        if (!empty)
        {
            int comp[4] = {0, 0, 0, 0};
            for (int i = 0; i < 4; i++)
            {
                if (i == test[mode])
                    continue;
                int arg[4][2] = {{int(v), i}, {i, int(h)}, {i, i}, {i, 3 - i}};
                const Piece &cur = grid[arg[mode][0]][arg[mode][1]].getPiece();
                comp[0] = comp[0] + int(p.compareHeight(cur));
                comp[1] = comp[1] + int(p.compareColor(cur));
                comp[2] = comp[2] + int(p.compareShape(cur));
                comp[3] = comp[3] + int(p.compareTop(cur));
            }
            win = ((comp[0] == 3) || (comp[1] == 3) || (comp[2] == 3) || (comp[3] == 3));
        }
        if (win)
            break;
        empty = false;
        // std::cout << mode << win << std::endl;
    }
    return win;
}

std::string Board::toString() const
{
    std::string res;
    res += "    1    2    3    4\n";
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