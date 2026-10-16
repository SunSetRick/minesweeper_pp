#include <iostream>
#include "board.hpp"

int main()
{
    bool done = false;
    std::cout << "Welcome to minesweeper v.0.0.1, remind that coords indexing starts from 1\n";
    std::cout << "Please enter field scales and mines count (Y X Count): ";
    
    int x, y, count;
    std::cin >> x >> y >> count;
    Board board(x, y, count);
    // board.print_all_revealed();

    while (!done)
    {
        board.print_current();
        std::cout << "Enter coords and action (t - touch, f - flag) (x y t/f): ";
        char type;
        std::cin >> x >> y >> type;
        --x;
        --y;
        if (board.is_coords_valid(y, x))
        {
            if (type == 't')
            {
                if (!board.at(y, x).is_flagged)
                {
                    if(board.at(y, x).is_mine)
                    {
                        std::cout << "BOOM!\n";
                        board.print_all_revealed();
                        return 0;
                    }
                    else
                    {
                        board.reveal_alg(y, x);
                    }

                }
            }
            else if (type == 'f')
            {
                if(!board.at(y, x).is_revealed)
                {
                    board.at(y, x).is_flagged = !board.at(y, x).is_flagged;
                }
            }
        }
        else
        {
            std::cout << "Coords invalid!\n";
        }
        if (board.is_win())
        {
            board.print_all_revealed();
            std::cout << "YOU WOOON\n";
            return 0;
        }
        
    }
}