#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <bitset>

namespace c4
{
    enum class Color
    {
        RED,
        YELLOW
    };

    class Bitboard
    {
    private:
        std::bitset<42> bitboardYellow;
        std::bitset<42> bitboardRed;
    public:
        void toBits(std::array<std::array<short, 7>, 6>& board, std::bitset<42>& bitsYellow, std::bitset<42>& bitsRed)
        {
            for (int column = 0; column < 7; column++)
            {
                for (int row = 0; row < 6; row++)
                {
                    if ((board.getElement(row, column)) == 1)
                    {
                        int bitIndex = 6 * column + row;
                        bitboardYellow.set(bitIndex);
                    }
                    else if ((board.getElement(row, column)) == -1)
                    {
                        int bitIndex = 6 * column + row;
                        bitboardRed.set(bitIndex);
                    }
                }
            }
        }
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
        
        void show() const
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
                        std::cout << "  ";
                }
                std::cout << std::endl;
            }
        }
        
        void makeMove(int column, Color color)
        {
            if ((board[0][column - 1]) != 0) return;
            if (!((column >= 1) && (column <= 7))) return;
            int row = 0;
            int boardRepresent = 0;
            while (((board[row + 1][column - 1]) == 0) && (row < 5)) ++row;
            switch (color)
            {
                case Color::RED:
                    boardRepresent = -1;
                    break;
                case Color::YELLOW:
                    boardRepresent = 1;
                    break;
            }

            board[row][column - 1] = boardRepresent;
        }

        void unmakeMove(int column)
        {
            if (!((column >= 1) && (column <= 7))) return;
            if ((board[5][column - 1]) == 0) return;
            int row = 0;
            while (((board[row][column - 1]) == 0) && (row < 5)) ++row;
            board[row][column - 1] = 0;
        }

        int getElement(int row, int column) const
        {
            return board[row][column];
        }
    };

    class Movelist
    {
    private:
        std::vector<int> moves;
    public:
        void legalMoves(Board& board)
        {
            moves.clear();
            for (int column = 0; column < 7; ++column)
            {
                if ((board.getElement(0, column)) == 0) moves.push_back(column + 1);
            }
        }
        void show() const
        {
            for (const int move : moves)
            {
                std::cout << move << " ";
            }
            std::cout << std::endl;
        }
    };
}
