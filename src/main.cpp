#include "c4.hpp"
#include <iostream>
#include <bitset>
#include <string>

int main()
{
    c4::Board board;

    std::array<std::array<short,7>,6> pos = {{
        {0,0,0,0,0,0,0},
        {1,0,0,-1,0,0,0},
        {1,0,-1,1,0,0,0},
        {1,-1,-1,1,0,0,0},
        {-1,1,1,-1,1,-1,0},
        {1,-1,1,1,-1,1,-1}
    }};

    board.set(pos);
    board.show();

    c4::Movelist moves;
    moves.legalMoves(board);
    moves.show();

    board.makeMove(4, c4::Color::RED);
    board.show();

    moves.legalMoves(board);
    moves.show();

    std::bitset<42> bitsYellow = board.getBitboardYellow();
    std::bitset<42> bitsRed = board.getBitboardRed();
    std::bitset<42> bits = bitsYellow | bitsRed;

    for (int i=0;i<42;i++) std::cout << bits[i];
    std::cout << "\n";

    c4::Color winner;
    if (board.isFourInRow(winner))
    {
        std::string winColor;
        switch(winner)
        {
            case c4::Color::NONE:   winColor="None"; break;
            case c4::Color::RED:    winColor="Red"; break;
            case c4::Color::YELLOW: winColor="Yellow"; break;
        }
        std::cout << "Winner: " << winColor << "\n";
    }
    else
    {
        std::cout << "No winner yet\n";
    }
}
