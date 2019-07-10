#include "board.h"
#include "pool.h"
#include <iostream>
using namespace std;
int main()
{
    // Piece *p = new Piece;
    // Piece q(TALL, BEIGE, CIRCLE, HOLLOW);
    // Square sq;
    // cout << sq.isEmpty() << endl;
    // sq.setPiece(p);
    // cout << sq.isEmpty() << endl;
    // cout << sq.isOnFirstDiagonal() << endl;
    // cout << sq.isOnSecondDiagonal() << endl;
    // cout << sq.toString() << endl;

    try
    {
        Board b;
        cout << b.toString();
        Piece p(Height(1), Color(1), Shape(0), Top(1));
        b.place(p, b.getSquare(Vaxis(3), Haxis(3)));
        b.place(p, b.getSquare(Vaxis(2), Haxis(2)));
        b.place(p, b.getSquare(Vaxis(1), Haxis(1)));
        //b.place(p, b.getSquare(Vaxis(0), Haxis(0)));
        cout << b.toString();
        cout << b.isWinning(p, b.getSquare(Vaxis(0), Haxis(0)));
    }
    catch (const SquareException &e)
    {
        cout << e.what() << endl;
    }
}