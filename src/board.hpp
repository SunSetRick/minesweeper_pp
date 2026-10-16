#pragma once

#include <string>

struct Card
{
    bool is_mine = false;
    bool is_flagged = false;
    bool is_revealed = false;
    int neighbours = 0;
};

class Board
{
private:
    int width_ = 0;
    int height_ = 0;
    Card** data = nullptr;

    Card trash_object;
    
    void write_neighbours(int cardY, int cardX);
    void board_random_fill(int mines_count);
public:
    void print_xo_view();
    void print_all_revealed();
    void print_current();

    bool is_coords_valid(int y, int x);
    Card& at(int y, int x);
    
    Board(int w, int h, int mines_count);
    Board(std::string filename);
    ~Board();
};