#include "board.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <queue>

Board::Board(int h, int w, int mines_count) : 
width_(w), height_(h), mines_count_(mines_count)
{
    if (!(width_ > 0 && height_ > 0 && width_ * height_ > mines_count_))
    {
        throw std::invalid_argument("Board constraction invalid args");
    }
    
    data = new Card*[height_];
    for (int i = 0; i < height_; ++i)
    {
        data[i] = new Card[width_];
    }

    board_random_fill(mines_count);

    for (int i = 0; i < height_; ++i)
    {
        for (int j = 0; j < width_; ++j)
        {
            write_neighbours(i, j);
        }
    }
}


Board::~Board()
{
    if (data != nullptr)
    {
        for (int i = 0; i < height_; ++i)
        {
            delete[] data[i];
        }
        delete[] data;
    }
}

void Board::print_xo_view()
{
    for (int i = 0; i < height_; ++i)
    {
        for (int j = 0; j < width_; ++j)
        {
            if (data[i][j].is_mine)
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

void Board::print_all_revealed()
{
    for (int i = 0; i < height_; ++i)
    {
        for (int j = 0; j < width_; ++j)
        {
            if (data[i][j].is_mine)
            {
                std::cout << "X ";
            }
            else
            {
                std::cout << data[i][j].neighbours << " ";
            }
            // std::cout << data[i][j].neighbours;
        }
        std::cout << "\n";
    }
}

void Board::print_current()
{
    for (int i = 0; i < height_; ++i)
    {
        for (int j = 0; j < width_; ++j)
        {
            if (data[i][j].is_revealed)
            {
                std::cout << data[i][j].neighbours << " ";
            }
            else
            {
                if (data[i][j].is_flagged)
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

bool Board::is_coords_valid(int y, int x)
{
    return (0 <= y && y < height_ && 0 <= x && x < width_);
}

Card& Board::at(int y, int x)
{
    if (is_coords_valid(y, x))
    {
        return data[y][x];
    }
    return trash_object;
}

void Board::write_neighbours(int card_y, int card_x)
{
    int count = 0;

    for (int dy = -1; dy <= 1; ++dy)
    {
        for (int dx = -1; dx <= 1; ++dx)
        {
            if (at(card_y + dy, card_x + dx).is_mine)
            {
                ++count;
            }
        }
    }

    data[card_y][card_x].neighbours = count;
}

void Board::reveal_alg(int y, int x)
{
    std::queue<std::pair<int, int>> q{};

    if (at(y, x).is_revealed)
    {
        return;
    }

    q.push({y, x});
    while (!q.empty())
    {
        std::pair<int, int> coords = q.front();
        Card& current_card = at(coords.first, coords.second);

        if (current_card.is_flagged || current_card.is_mine || current_card.is_revealed)
        {
            q.pop();
        }
        else
        {
            current_card.is_revealed = true;
            q.pop();
            if (current_card.neighbours == 0)
            {
                for (int dy = -1; dy <= 1; ++dy)
                {
                    for (int dx = -1; dx <= 1; ++dx)
                    {
                        if (is_coords_valid(coords.first + dy, coords.second + dx))
                        {
                            q.push({coords.first + dy, coords.second + dx});
                        }
                    }
                }
            }
            
        }
        
    }
}

void Board::board_random_fill(int mines_count)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> h_dis(0, height_ - 1);
    std::uniform_int_distribution<> w_dis(0, width_ - 1);

    while (mines_count != 0)
    {
        int rand_y = h_dis(gen);
        int rand_x = w_dis(gen);

        if (!data[rand_y][rand_x].is_mine)
        {
            data[rand_y][rand_x].is_mine = true;
            mines_count--;
        }
    }
}

bool Board::is_win()
{
    int revealed_count = 0;
    for (int i = 0; i < height_; ++i)
    {
        for (int j = 0; j < width_; ++j)
        {
            if (data[i][j].is_revealed)
            {
                revealed_count++;
            }
        }
    }

    if (height_ * width_ - mines_count_ == revealed_count)
    {
        return true;
    }
    return false;
}