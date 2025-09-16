#include <iostream>
#include <array>
#include <bitset>
#include <string>
#include "c4.hpp"
int main()
{
    c4::Board board;
    std::array<std::array<short, 7>, 6> pos =
    {{
        {1,0,0,0,0,0,0},
        {1,0,0,0,0,0,0},
        {1,0,0,0,0,0,0},
        {1,0,0,0,0,0,0},
        {-1,1,1,0,1,-1,0},
        {1,-1,1,0,1,1,-1}
    }};
    board.set(pos);
    board.show();
    c4::Movelist moves;
    moves.legalMoves(board);
    moves.show();
    board.makeMove(4, c4::Color::RED); //Drop red chip at column 4
    board.show();
    moves.legalMoves(board);
    move.show();
    std::bitset<42> bitsYellow;
    std::bitset<42> bitsRed;
    c4::toBits(board, bitsYellow, bitsRed);
    std::bitset<42> bits = bitsYellow | bitsRed;
    for (int idx = 0; idx < 42; idx++)
    {
        std::cout << bits[idx];
    }
    std::cout << std::endl;
    c4::Color winningColor = c4::Color::NONE;
    board.isFourInRow(winningColor);
    std::string winColor;
    switch (winningColor)
    {
        case NONE:
            winColor = "None";
            break;
        case YELLOW:
            winColor = "Yellow";
            break;
        case RED:
            winColor = "Red";
            break;
    }
    std::cout << winColor << std::endl;
}