#include "worldgrid.hpp"

WorldGrid::WorldGrid()
    :grid(x*y)
{

}

bool WorldGrid::isPassable(short a, short b){
    return this->grid[b*x+a];
}

void WorldGrid::updateSlot(short a, short b, bool state){
    this->grid[b*x+a]=state;
}
