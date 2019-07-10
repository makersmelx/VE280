#include "player.h"
#include <iostream>
using namespace std;
int main(int argc, char **argv)
{
    Board *game_board = new Board;
    Pool *game_pool = new Pool;
    Player *p[2];
    unsigned int rand_seed = 0;
    string _argv3 = argv[3];
    rand_seed = stoi(_argv3);

    for (int i = 1; i <= 2; i++)
    {
        cout << argv[i] << endl;
        if (strcmp(argv[i], "h") == 0)
        {
            p[i - 1] = getHumanPlayer(game_board, game_pool);
        }
        else if (strcmp(argv[i], "m") == 0)
        {
            p[i - 1] = getMyopicPlayer(game_board, game_pool, rand_seed);
        }
    }

    bool game_end = false;
    int turn_mark = -1;
    while (!game_end)
    {
        //换行符我估计哪里有问题
        cout << game_board->toString() << endl;
        cout << game_pool->toString() << endl;
        cout << "Player " << (turn_mark + 1) / 2 + 1 << "'s turn to select a piece:" << endl;
        Piece &selected_piece = p[(turn_mark + 1) / 2]->selectPiece();
        selected_piece.setUsed(true);
        cout << selected_piece.toString() << " is selected." << endl;
        turn_mark *= -1;
        cout << "Player " << (turn_mark + 1) / 2 + 1 << "'s turn to select a square:" << endl;
        Square &selected_square = p[(turn_mark + 1) / 2]->selectSquare(selected_piece);
        cout << selected_square.toString() << " is selected." << endl;
        game_board->place(selected_piece, selected_square);
        if (game_board->isWinning(selected_piece, selected_square))
        {
            cout << "Player " << (turn_mark+1)/2 << " has won!" << endl;
            game_end = true;
        }
        for (int i = 0; i < 16; i++)
        {
            if (game_board->getSquare(Vaxis(i / 4), Haxis(i % 4)).isEmpty())
                break;
            if (i == 15)
            {
                cout << "It is a draw." << endl;
                game_end = true;
            }
        }
        //turn_mark *= -1;
    }
    return 0;
}