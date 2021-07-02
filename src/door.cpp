#include "door.hpp"

Door::Door(short x, short y){
    this->door_global_coord_x = x;
    this->door_global_coord_y = y;
    this->door_sprite.setPosition(this->door_global_coord_x*32.f, this->door_global_coord_y*32.f);
}

Door::~Door(){

}

bool Door::isOpen(){
    return this->open;
}

void Door::loadTexture(std::map<std::string, sf::Texture> &texture_map){
    this->door_sprite.setTexture(texture_map["door_closed"]);
}

void Door::openDoor(std::map<std::string, sf::Texture> &texture_map){
    this->open = true;
    this->door_sprite.setTexture(texture_map["door"]);
}
