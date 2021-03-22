#include "Special_Node.h"

Special_Node::Special_Node(const Node& node, const ConsoleScreen& console_screen) : Node(node), console_screen(console_screen)
{

}

size_t Special_Node::getID() const
{
    return pos.y * console_screen.numb_row + pos.x;
}

std::vector<Special_Node*> Special_Node::neighbours(Table& table)
{
    std::vector<Special_Node*> res;
    for (const auto& neighbour : Node::neighbours())
    {
        Special_Node s_neighbour(neighbour, console_screen); // Creating a Special_Node
        if (s_neighbour.console_screen.get_value(s_neighbour.pos.x, s_neighbour.pos.y) == ' ' || //Check if the Node is on a valid Position
            s_neighbour.console_screen.get_value(s_neighbour.pos.x, s_neighbour.pos.y) == Food::sign 
           )
        {
            size_t ID = s_neighbour.getID();
            auto it = table.find(ID);
            if (it == table.end()) // no element with this id
            {
                table[ID].push_back(std::make_unique<Special_Node>(s_neighbour));
                res.push_back(table[ID].back().get());
                continue;

            }
            bool inside = false; // if the Node is in the vector

            for (auto& element : it->second)
            {
                if (element->pos == s_neighbour.pos)
                {
                    res.push_back(element.get());
                    inside = true;
                    break;
                }

            }
            if (!inside) //If the ID is present in the table but not the node (several nodes can have the same ID)
            {
                table[ID].push_back(std::make_unique<Special_Node>(s_neighbour));
                res.push_back(table[ID].back().get());
            }



        }
    }
    return res;
}