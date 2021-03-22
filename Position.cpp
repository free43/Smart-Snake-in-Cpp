#include "Position.h"

Position::Position() :x(0), y(0)
{}

Position::Position(int x, int y) :x(x), y(y)
{}

bool Position::operator==(const Position& X)const
{
    return this->x == X.x && this->y == X.y;
}

float Position::get_distance(const Position& goal) const
{
    Position distance = { goal.x - this->x, goal.y - this->y };
    return sqrtf(distance.x * distance.x + distance.y * distance.y);
}

std::ostream& operator<<(std::ostream& os, const Position& pos)
{
    return os << "(" << pos.x << "," << pos.y << ")";
}