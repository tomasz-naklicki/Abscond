#ifndef CHEST_HPP
#define CHEST_HPP

class Chest
{
public:
    //Constructors / Destructors
    Chest(short x, short y);
    Chest();

    //Public variables
    sf::Sprite chest_sprite;
    short chest_global_coord_x, chest_global_coord_y;
    short chest_local_coord_x, chest_local_coord_y;

    //Public functions
    void loadTexture(std::map<std::string, sf::Texture> &texture_map);
    void openChest(std::map<std::string, sf::Texture> &texture_map);
    bool isOpen();

private:

    bool open = false;
};

#endif // CHEST_HPP
