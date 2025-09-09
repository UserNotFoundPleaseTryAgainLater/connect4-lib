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
    board.MakeMove(4, Color::RED)
    board.show();
}