#include "player.h"
#include <cstring>
#include <iostream>
using namespace std;
int main(int argc, char **argv)
{

    auto game_board = new Board;
    auto game_pool = new Pool;
    Player *p[2];
    unsigned int rand_seed = 0;
    if (argc == 4)
    {
        string _argv3 = argv[3];
        rand_seed = stoi(_argv3);
    }

    for (int i = 1; i <= 2; i++)
    {
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
    cout << game_board->toString() << endl;
    cout << game_pool->toString() << endl;
    while (!game_end)
    {
        cout << "Player " << (turn_mark + 1) / 2 + 1 << "'s turn to select a piece:" << endl;
        Piece &selected_piece = p[(turn_mark + 1) / 2]->selectPiece();
        selected_piece.setUsed(true);
        cout << selected_piece.toString() << " selected." << endl;
        cout << endl;
        turn_mark *= -1;
        cout << "Player " << (turn_mark + 1) / 2 + 1 << "'s turn to select a square:" << endl;
        Square &selected_square = p[(turn_mark + 1) / 2]->selectSquare(selected_piece);
        cout << selected_square.toString() << " selected." << endl;
        cout << endl;
        game_board->place(selected_piece, selected_square);
        cout << game_board->toString() << endl;
        cout << game_pool->toString() << endl;
        if (game_board->isWinning(selected_piece, selected_square))
        {
            cout << "Player " << (turn_mark + 1) / 2 + 1 << " has won!" << endl;
            game_end = true;
            break;
        }
        if (game_pool->toString().empty())
        {
            cout << "It is a draw." << endl;
            game_end = true;
        }
    }
    delete game_board;
    delete game_pool;

    return 0;
}