#include <iostream>
#include <array>
#include "c4.hpp"
int main()
{
    c4::Board board;
    std::array<std::array<short, 7>, 6> pos =
    {{
        {1,0,0,0,0,0,0},
        {1,0,0,0,0,0,0},
        {-1,0,0,0,0,0,0},
        {1,0,0,0,0,0,0},
        {-1,1,1,0,1,-1,0},
        {1,-1,1,0,1,1,-1}
    }};
    board.set(pos);
    board.show();
    c4::Movelist moves;
    moves.LegalMoves(board);
    moves.show();
    board.MakeMove(4, c4::Color::RED); //Drop red chip at column 4
    board.show();
    moves.LegalMoves(board);
    moves.show();
    board.UnmakeMove(4); //Remove top chip at column 4
    board.show();
    moves.LegalMoves(board);
    moves.show();
}