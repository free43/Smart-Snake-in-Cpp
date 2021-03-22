#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <chrono>
#include "Position.h"
struct Maze
{
    /**
        The height of the maze.
    */
    size_t numb_row;

    /**
        The width of the maze.
    */
    size_t numb_column;


    /**
        The labyrinth.
        ' ' -> is a possible field to stay on it.
        'S' -> is the start of the labyrinth
        'E' -> is the end of the labyrinth
        '.' -> is the path from S to E
        '!' -> shows the visited Nodes
        All other chars are walls.
    */
    //std::vector <std::string> labyrinth; 
    std::shared_ptr<wchar_t[]> labyrinth = nullptr;

    /**
        Creates a random Maze or read one from the file 
        @param file The name of the file. If the string is empty a random maze gets created.
                   
    */
    Maze(std::string file = "");
    Maze(const std::shared_ptr<wchar_t[]>& labyrinth) : labyrinth(labyrinth)
    {}
    
    /**
        Creating a random maze size depends on the variable numb_row and numb_column.
        @param act_pos The actual Position of the hammer than can tear down two walls.  
    */
    void create_labyrinth(const Position& act_pos);
    /**
        Sets the start 'S' in the lower middle and the end 'E' in the upper middle. 
    */
    void set_start_and_end();
    /**
        Finding a specific char in the maze.
        @param searched_char Character to look for.
        @return Returns the Position of the searched Character.
    */
    Position find_char(char searched_char);
    /**
        Sets a value on a specific position.
        @param value The value to be set.
        @param pos The position where to set the value.
    */
    void set_value_on_pos(char value, const Position& pos);
    /**
        Get the value on a specific position. If position isn't inside of the maze 0 is returned. 
        @param pos The position where to look in the maze.
        @return Returns the value on the asked position.
    */
    char value_on_pos(const Position & pos) const;
    /**
        Output the Maze.
        @param os The ostream.
        @param maze The maze which should be printed on the commandline.
        @return Returns the ostream again.
    */
    friend std::ostream& operator<<(std::ostream& os, const Maze& maze);
    /**
       Deletes the path from S to E and the visited nodes.
    */
    void reset();
    
    
};