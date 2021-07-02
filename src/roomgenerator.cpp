#include "roomgenerator.hpp"
#include <room.hpp>

RoomGenerator::RoomGenerator()
{
    srand(time(NULL));
}

RoomLayout RoomGenerator::generateLayout(){
    RoomLayout layout;
    layout.number_of_chests = rand()%3? 0:1;
    layout.number_of_enemies = rand()%3+1;
    return layout;

}
