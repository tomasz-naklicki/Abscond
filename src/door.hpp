#ifndef DOOR_HPP
#define DOOR_HPP


class Door
{
public:
    //Constructor / Destructor
    Door(short x, short y);
    ~Door();

    //Public variables
    sf::Sprite door_sprite;
    short door_global_coord_x, door_global_coord_y;
    short door_local_coord_x, door_local_coord_y;

    //Public functions
    void openDoor(std::map<std::string, sf::Texture> &texture_map);
    bool isOpen();
    void loadTexture(std::map<std::string, sf::Texture> &texture_map);

private:
    //Private variables
    bool open=false;
};

#endif // DOOR_HPP
