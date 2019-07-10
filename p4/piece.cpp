#include "piece.h"
Piece::Piece(Height h,Color c,Shape s,Top t):h(h),c(c),s(s),t(t)
{
    used = false;
}

bool Piece::compareHeight(const Piece &p) const
{
    return p.h == h;
}
bool Piece::compareColor(const Piece &p) const
{
    return p.c == c;
}
bool Piece::compareShape(const Piece &p) const
{
    return p.s == s;
}
bool Piece::compareTop(const Piece &p) const
{
    return p.t == t;
}
bool Piece::isUsed() const
{
    return used;
}

void Piece::setUsed(bool u)
{
    used = u;
}

std::string Piece::toString() const
{
    std::string res;
    res.push_back(HCODE[h]);
    res.push_back(CCODE[c]);
    res.push_back(SCODE[s]);
    res.push_back(TCODE[t]);
    return res;
}