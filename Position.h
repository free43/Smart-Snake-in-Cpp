#pragma once
#include "math.h"
#include "iostream"
enum direction{ left = 1, right, up, down };
typedef enum direction dir;
struct Position
{
    Position();
    Position(int x, int y);
    /**
        x Coordinate
    */
    int x;

    /**
        y Coordinate
    */
    int y;

    /**
        Checks if two positions are the same size.
        @param X Second position
        @return true if they are same size otherwise false will be returned
    */
    bool operator==(const Position& X)const;
   

    /**
        Returns the distance to a specific goal.
        @param goal Represents the goal
        @return Returns the distance from this to goal.
    */
    float get_distance(const Position& goal) const;

    /**
       Output of the Position.
       @param os The ostream.
       @param pos The Position which should be printed on the commandline.
       @return Returns the ostream again.
   */
    friend std::ostream& operator<<(std::ostream& os, const Position& pos);

};

