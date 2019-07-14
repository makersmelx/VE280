//notice:two myopic with two seeds
//usage: ./generate 2019 114514
#include "player.h"
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;
int main(int argc, char **argv)
{

    auto game_board = new Board;
    auto game_pool = new Pool;
    Player *p[2];
    unsigned int rand_seed[2] = {0};

    string _argv1 = argv[1];
    rand_seed[0] = stoi(_argv1);

    string _argv2 = argv[2];
    rand_seed[1] = stoi(_argv2);

    for (int i = 0; i <= 1; i++)
    {
        p[i] = getMyopicPlayer(game_board, game_pool, rand_seed[i]);
    }

    bool game_end = false;
    int turn_mark = -1;
    while (!game_end)
    {
        //换行符我估计哪里有问题
        Piece &selected_piece = p[(turn_mark + 1) / 2]->selectPiece();
        selected_piece.setUsed(true);
        cout << selected_piece.toString() << endl;
        turn_mark *= -1;
        Square &selected_square = p[(turn_mark + 1) / 2]->selectSquare(selected_piece);
        cout << selected_square.toString() << endl;
        game_board->place(selected_piece, selected_square);
        if (game_board->isWinning(selected_piece, selected_square))
        {
            game_end = true;
        }
        if (game_pool->toString().empty())
        {
            game_end = true;
        }
        //turn_mark *= -1;
    }
    delete game_board;
    delete game_pool;
    return 0;
}