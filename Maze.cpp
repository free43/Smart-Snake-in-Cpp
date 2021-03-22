#include "Maze.h"



void Maze::create_labyrinth(const Position& act_pos)
{
    // Idea is from https://www.thenerdshow.com/maze.html . Implemantation is by my own.

    std::vector <size_t> direction;
    auto check = [&]() -> bool{
        bool possible = false;
        char field = value_on_pos({act_pos.x - 2, act_pos.y });
        if (act_pos.x  > 1 
            && field && field != ' ') // Left
        {
            possible = true;
            direction.push_back(left);
        }
        field = value_on_pos({ act_pos.x + 2, act_pos.y });
        if (act_pos.x  < numb_column - 1
            &&  field && field != ' ') // Right
        {
            possible = true;
            direction.push_back(right);
        }
        field = value_on_pos({ act_pos.x, act_pos.y - 2 });
        if (act_pos.y > 1 
            &&  field && field != ' ') // UP
        {
            possible = true;
            direction.push_back(up);
        }
        field = value_on_pos({act_pos.x, act_pos.y + 2 });
        if (act_pos.y  < numb_row - 1
            && field && field != ' ') // Down
        {
            possible = true;
            direction.push_back(down);
        }
        return possible;
        

    };
    while (true)
    {
        size_t n;  
        if(!check()) break;
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::minstd_rand0 generator(seed);
        n = generator() % direction.size(); 
        n = direction[n]; 
        Position new_pos;
        switch (n)// n == 1 left, n == 2 right, n == 3 up, n == 4 down
        {
        case left: 
            set_value_on_pos(' ', { act_pos.x - 2, act_pos.y });
            set_value_on_pos(' ', { act_pos.x - 1, act_pos.y });
            new_pos = { act_pos.x - 2, act_pos.y };
            break;
        case right: 
            set_value_on_pos(' ', { act_pos.x + 2, act_pos.y });
            set_value_on_pos(' ', { act_pos.x + 1, act_pos.y });
            new_pos = { act_pos.x + 2, act_pos.y };

            break;
        case up:
            set_value_on_pos(' ', { act_pos.x, act_pos.y - 2 });
            set_value_on_pos(' ', { act_pos.x, act_pos.y - 1 });
            new_pos = { act_pos.x, act_pos.y - 2 };
            break;
        case down: 
            set_value_on_pos(' ', { act_pos.x, act_pos.y + 2 });
            set_value_on_pos(' ', { act_pos.x, act_pos.y + 1 });
            new_pos = { act_pos.x, act_pos.y + 2 };
            break;
        
        default:
            break;
        }
        create_labyrinth(new_pos);
        direction.clear();
    }
    
    
    
    
}

void Maze::set_start_and_end()
{
    set_value_on_pos('E', {static_cast<int>(numb_column) / 2, 2});
    set_value_on_pos('S', { static_cast<int>(numb_column) / 2, static_cast<int>(numb_row) - 1});
}



void Maze::set_value_on_pos(char value, const Position& pos)
{
    if (pos.x >= 0 && 
        pos.x < numb_column &&
        pos.y >= 0 &&
        pos.y < numb_row)
    {
        labyrinth[pos.y][pos.x] = value;
    }
}

char Maze::value_on_pos(const Position & pos)const
{
    if (pos.x >= 0 && 
        pos.x <= numb_column - 1 &&
        pos.y >= 0 &&
        pos.y <= numb_row - 1)
    {
        return labyrinth[pos.y][pos.x];
    }
    /// Return 0 if the position is not in the labyrinth
    return 0;
    
}






