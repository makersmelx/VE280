#include "square.h"
Square::Square(Vaxis v, Haxis h) : v(v), h(h)
{
    p = NULL;
}

Vaxis Square::getV() const
{
    return v;
}

void Square::setV(Vaxis v)
{
    this->v = v;
}

Haxis Square::getH() const
{
    return h;
}

void Square::setH(Haxis h)
{
    this->h = h;
}

const Piece &Square::getPiece() const
{
    if (isEmpty())
        throw SquareException(*this, "not empty");
    else
        return *p;
}

void Square::setPiece(const Piece *p)
{
    this->p = p;
}

bool Square::isEmpty() const
{
    return p == NULL;
}

bool Square::isOnFirstDiagonal() const
{
    return int(v) == int(h);
}

bool Square::isOnSecondDiagonal() const
{
    return int(v) == int(3 - h);
}

std::string Square::toString() const
{
    std::string va[4] = {"A", "B", " C", "D"};
    std::string ha[4] = {"1", "2", "3", "4"};
    return va[v] + ha[h];
}