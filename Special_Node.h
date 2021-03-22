#pragma once
#include "Node.h"
#include <map>
#include <memory>
#include "ConsoleScreen.h"
#include "Food.h"
struct Special_Node : Node
{
    /**
    Represents the actual Maze.
    
    */
    const ConsoleScreen& console_screen;
    Special_Node(const Node& node, const ConsoleScreen& console_screen);
    /**
        Returns the ID of the actual Node.
        @return Returns the ID of the Node.
    
    */
    size_t getID() const;
    using Table = std::map < size_t, std::vector< std::unique_ptr<Special_Node>> >;
    /**
        Gets or sets value in the Table. The key of the map is the ID from the Node. 
        There can be several nodes with the same ID. 
        @Return Returns a vector of Adresses from Special_Nodes (the values are stored in the Table) 
    */
    std::vector<Special_Node*> neighbours(Table& table);
    


};
