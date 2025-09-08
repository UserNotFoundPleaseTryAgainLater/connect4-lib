#include <iostream>
#include <array>
#include "c4.hpp"
int main()
{
    c4::Board board;
    std::array<std::array<short, 7>, 6> pos =
    {{
        {0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0},
        {-1,1,1,0,1,-1,0},
        {1,-1,1,0,1,1,-1}
    }};
    board.set(pos);
    board.show();
}