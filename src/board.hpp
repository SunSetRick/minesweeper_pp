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
    int mines_count_ = 0;
    int revealed_count_ = 0;
    Card** data = nullptr;
    std::string state_ = "init"; //init, in_game, win, lose
    
    void write_neighbours(int cardY, int cardX);
    void board_random_fill(int mines_count);
public:

    bool is_coords_valid(int y, int x);
    Card& at(int y, int x);
    const std::string& state();
    const int& width();
    const int& height();

    void reveal_alg(int y, int x);
    void touch_card(int y, int x);
    void flag_card(int y, int x);
    
    Board(int h, int w, int mines_count);
    Board(const Board&) = delete; 
    Board& operator=(const Board&) = delete;
    ~Board();
};