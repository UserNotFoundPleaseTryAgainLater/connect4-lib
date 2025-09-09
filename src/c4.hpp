#pragma once
#include <iostream>
#include <vector>
#include <array>

namespace c4
{
    enum class Color
    {
        RED,
        YELLOW
    };
    class Board
    {
    private:
        std::array<std::array<short, 7>, 6> board{};

        bool isValidPosition(const std::array<std::array<short, 7>, 6>& pos)
        {
            for (int col = 0; col < 7; ++col)
            {
                for (int row = 5; row >= 0; --row)
                {
                    if (pos[row][col] == 0)
                    {
                        for (int iRow = row - 1; iRow >= 0; --iRow)
                        {
                            if (pos[iRow][col] != 0)
                            {
                                return false; // disc floating above empty space
                            }
                        }
                    }
                }
            }
            return true;
        }

    public:
        Board() = default;
        
        void clear()
        {
            board = {}; // resets everything to 0
        }
        
        void set(const std::array<std::array<short, 7>, 6>& newPos)
        {
            if (isValidPosition(newPos))
                board = newPos;
        }
        
        void show()
        {
            std::cout << "\n";
            for (int row = 0; row < 6; ++row)
            {
                for (int column = 0; column < 7; ++column)
                {
                    if (board[row][column] == -1)
                        std::cout << "\033[1;91m\u25C9\033[0m ";
                    else if (board[row][column] == 1)
                        std::cout << "\033[1;93m\u25C9\033[0m ";
                    else if (board[row][column] == 0)
                        std::cout << " ";
                }
                std::cout << std::endl;
            }
        }
        
        void MakeMove(int column, Color color)
        {
            int row = 5;
            while (((board[row][column]) != 0) && (row >= 0)) { --row; }
            switch (color)
            {
                case Color::RED:
                    int boardRepresent = -1;
                    break;
                case Color::YELLOW:
                    int boardRepresent = 1;
                    break;

            }

            board[row][column] = boardRepresent;
        }

        int GetElement(int row, int column)
        {
            return board[row][column];
        }
    };
    /*class Move
    {
    private:
        int column
    public:
        Move(int move)
        {
            if((move >= 1) && (move <= 7)) column = move - 1;
            else column = 0;
        }
    };*/
    class Movelist
    {
    private:
        std::vector<int> moves;
    public:
        void LegalMoves(Board& board)
        {
            for (int column = 0; column < 7; ++column)
            {
                if ((board.GetElement(0, column)) == 0) moves.push_back(column + 1);
            }
        }
        void show()
        {
            for (const int move : moves)
            {
                std::cout << move << " ";
            }
            std::cout << std::endl;
        }
    };
}
