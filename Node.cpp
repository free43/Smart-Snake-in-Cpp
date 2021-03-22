#include "Node.h"

Node::Node()
{
    fScore = INFINITY;
    gScore = INFINITY;
    parent = nullptr;
    finished = false;
}
std::vector<Node> Node::neighbours()
{
    return [this]() {
        std::vector<Node> res(4, Node());
        for (auto& x : res)
        {
            x.pos = this->pos;
        }
        res[0].pos.x += 1; // right
        res[1].pos.x -= 1; // left
        res[2].pos.y += 1; // down
        res[3].pos.y -= 1; // up
        return res;
    }();
}

