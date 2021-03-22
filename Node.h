#pragma once
#include "Position.h"
#include <vector>
#include <math.h>


struct Node 
{
    Node();
   
    /**
        The actual position of the Node.
    */
    Position pos;
  
    /**
        fScore = gScore + h(n)
        n:          is the next node
        gScore:     is the cost from start node to n
        h(n):       calculates the cheapest path from n to the goal.
                    Here h(n) is the function Position::get_distance(n)
    */
    float fScore;

    /**
        gScore:     is the cost from start node to n
    */
    float gScore;

    /**
        If the Node visited all his neighbour.
    */
    bool finished;
    /**
        Represents the previous node
    */
    Node *parent;

    /**
        The direct neighbour nodes.
        @Return Returns the neighbour Nodes -> Right, Left, Up and Down from this.
    */
    std::vector <Node> neighbours();
    
    
};
