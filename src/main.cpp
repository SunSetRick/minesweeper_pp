#include <iostream>
#include "board.hpp"

void print_xo_view(Board& board)
{
    for (int i = 0; i < board.height(); ++i)
    {
        for (int j = 0; j < board.width(); ++j)
        {
            if (board.at(i, j).is_mine)
            {
                std::cout << "X ";
            }
            else
            {
                std::cout << "O ";
            }
        }
        std::cout << "\n";
    }
}

void print_all_revealed(Board& board)
{
    for (int i = 0; i < board.height(); ++i)
    {
        for (int j = 0; j < board.width(); ++j)
        {
            if (board.at(i, j).is_mine)
            {
                std::cout << "X ";
            }
            else
            {
                std::cout << board.at(i, j).neighbours << " ";
            }
            // std::cout << board.at(i, j).neighbours;
        }
        std::cout << "\n";
    }
}

void print_current(Board& board)
{
    for (int i = 0; i < board.height(); ++i)
    {
        for (int j = 0; j < board.width(); ++j)
        {
            if (board.at(i, j).is_revealed)
            {
                std::cout << board.at(i, j).neighbours << " ";
            }
            else
            {
                if (board.at(i, j).is_flagged)
                {
                    std::cout << "f ";
                }
                else
                {
                    std::cout << ". ";
                }
            }
        }
        std::cout << "\n";
    }
}


int main()
{
    bool done = false;
    std::cout << "Welcome to minesweeper v.0.0.2, remind that coords indexing starts from 1\n";
    std::cout << "Please enter field scales and mines count (X Y Count): ";
    
    int x, y, count;
    char type;
    std::cin >> x >> y >> count;
    Board board(y, x, count);
    // board.print_all_revealed();

    while (!done)
    {
        print_current(board);
        // print_all_revealed(board);
        std::cout << "Enter coords and action (t - touch, f - flag) (x y t/f): ";
    
        if (std::cin >> x >> y >> type)
        {
            --x;
            --y;
            if (board.is_coords_valid(y, x))
            {
                if (type == 't')
                {
                    board.touch_card(y, x);
                }
                else if (type == 'f')
                {
                    board.flag_card(y, x);
                }
            }
            else
            {
                std::cout << "Coords invalid!\n";
            }
            if (board.state() == "win")
            {
                print_all_revealed(board);
                std::cout << "YOU WOOON\n";
                done = true;
            }
            else if (board.state() == "lose")
            {
                print_all_revealed(board);
                std::cout << "YOU LOSE\n";
                done = true;
            }

        }
        
    }
}