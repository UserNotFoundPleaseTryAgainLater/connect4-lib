#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <bitset>

namespace c4
{
    enum class Color
    {
        NONE,
        RED,
        YELLOW
    };
    
    void toBits(const std::array<std::array<short, 7>, 6>& board, std::bitset<42>& bitsYellow, std::bitset<42>& bitsRed);

    class Board
    {
    private:
        std::array<std::array<short, 7>, 6> board{};
        std::bitset<42> bitboardYellow;
        std::bitset<42> bitboardRed;

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
                                return false; //disc floating above empty space
                        }
                    }
                }
            }
            return true;
        }

        void updateBitboards()
        {
            toBits(board, bitboardYellow, bitboardRed);
        }

    public:
        Board() = default;
        
        void clear()
        {
            board = {}; //resets everything to 0
            updateBitboards();
        }
        
        void set(const std::array<std::array<short, 7>, 6>& newPos)
        {
            if (isValidPosition(newPos))
            {
                board = newPos;
                updateBitboards();
            }
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
                    else
                        std::cout << "  ";
                }
                std::cout << std::endl;
            }
        }
        
        void makeMove(int column, Color color)
        {
            if (column < 1 || column > 7) return;
            column--; 
            if (board[0][column] != 0) return; 

            int row = 0;
            while (row < 5 && board[row + 1][column] == 0) ++row;

            board[row][column] = (color == Color::RED) ? -1 : 1;
            updateBitboards();
        }

        void unmakeMove(int column)
        {
            if (column < 1 || column > 7) return;
            column--;
            int row = 0;
            while (row < 6 && board[row][column] != 0) ++row;
            if (row == 0) return; // nothing to unmake
            board[row - 1][column] = 0;
            updateBitboards();
        }

        int getElement(int row, int column) const
        {
            return board[row][column];
        }

        const std::bitset<42>& getBitboardYellow() const { return bitboardYellow; }
        const std::bitset<42>& getBitboardRed() const { return bitboardRed; }
        
        bool isFourInRow(Color& winningColor)
        {
            //Lambda to check horizontal 4-in-a-row
            auto horizontalCheck = [](const std::bitset<42>& bits) {
                for (int row = 0; row < 6; ++row)
                {
                    for (int col = 0; col <= 3; ++col)
                    {
                        int idx0 = 6*col + row;
                        int idx1 = 6*(col+1) + row;
                        int idx2 = 6*(col+2) + row;
                        int idx3 = 6*(col+3) + row;
                        if (bits[idx0] && bits[idx1] && bits[idx2] && bits[idx3])
                            return true;
                    }
                }
                return false;
            };

            auto verticalCheck = [](const std::bitset<42>& bits) {
                for (int col = 0; col < 7; ++col)
                {
                    for (int row = 0; row <= 2; ++row)
                    {
                        int idx0 = 6*col + row;
                        int idx1 = 6*col + (row+1);
                        int idx2 = 6*col + (row+2);
                        int idx3 = 6*col + (row+3);
                        if (bits[idx0] && bits[idx1] && bits[idx2] && bits[idx3])
                            return true;
                    }
                }
                return false;
            };

            auto diag1Check = [](const std::bitset<42>& bits) {
                for (int col = 0; col <= 3; ++col)
                {
                    for (int row = 0; row <= 2; ++row)
                    {
                        int idx0 = 6*col + row;
                        int idx1 = 6*(col+1) + (row+1);
                        int idx2 = 6*(col+2) + (row+2);
                        int idx3 = 6*(col+3) + (row+3);
                        if (bits[idx0] && bits[idx1] && bits[idx2] && bits[idx3])
                            return true;
                    }
                }
                return false;
            };

            auto diag2Check = [](const std::bitset<42>& bits) {
                for (int col = 0; col <= 3; ++col)
                {
                    for (int row = 3; row < 6; ++row)
                    {
                        int idx0 = 6*col + row;
                        int idx1 = 6*(col+1) + (row-1);
                        int idx2 = 6*(col+2) + (row-2);
                        int idx3 = 6*(col+3) + (row-3);
                        if (bits[idx0] && bits[idx1] && bits[idx2] && bits[idx3])
                            return true;
                    }
                }
                return false;
            };
            if ((horizontalCheck(bitboardYellow) || verticalCheck(bitboardYellow) || 
                diag1Check(bitboardYellow) || diag2Check(bitboardYellow)) && 
                (horizontalCheck(bitboardRed) || verticalCheck(bitboardRed) ||
                diag1Check(bitboardRed) || diag2Check(bitboardRed)))
            {
                winningColor = Color::NONE;
                return false;
            }
            if (horizontalCheck(bitboardYellow) || verticalCheck(bitboardYellow) ||
                diag1Check(bitboardYellow) || diag2Check(bitboardYellow))
            {
                winningColor = Color::YELLOW;
                return true;
            }

            if (horizontalCheck(bitboardRed) || verticalCheck(bitboardRed) ||
                diag1Check(bitboardRed) || diag2Check(bitboardRed))
            {
                winningColor = Color::RED;
                return true;
            }

            winningColor = Color::NONE;
            return false;
        }

        bool isDraw()
        {
            Color null;
            if (!isFourInRow(null) &&
                ((board[0][0] != 0) &&
                (board[0][1] != 0) &&
                (board[0][2] != 0) &&
                (board[0][3] != 0) &&
                (board[0][4] != 0) &&
                (board[0][5] != 0) &&
                (board[0][6] != 0)))
            {
                return true;
            }
            return false;
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
                if (board.getElement(0, column) == 0)
                    moves.push_back(column + 1);
            }
        }
        void show() const
        {
            for (const int move : moves)
                std::cout << move << " ";
            std::cout << std::endl;
        }
    };

    void toBits(const std::array<std::array<short, 7>, 6>& board, std::bitset<42>& bitsYellow, std::bitset<42>& bitsRed)
    {
        bitsYellow.reset();
        bitsRed.reset();
        for (int col = 0; col < 7; ++col)
        {
            for (int row = 0; row < 6; ++row)
            {
                if (board[row][col] == 1)
                    bitsYellow.set(6*col + row);
                else if (board[row][col] == -1)
                    bitsRed.set(6*col + row);
            }
        }
    }
}
