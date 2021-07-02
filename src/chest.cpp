#include "chest.hpp"

Chest::Chest(short x, short y){
    this->chest_local_coord_x = x;
    this->chest_local_coord_y = y;
}

void Chest::loadTexture(std::map<std::string, sf::Texture> &texture_map){
    this->chest_sprite.setTexture(texture_map["chest_closed"]);
}

bool Chest::isOpen(){
    return this->open;
}

void Chest::openChest(std::map<std::string, sf::Texture> &texture_map){
    this->chest_sprite.setTexture(texture_map["chest_open"]);
    this->open = true;
}
