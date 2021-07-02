#ifndef TILE_HPP
#define TILE_HPP

class Tile
{
public:
    //Constructor
    Tile(short type);

    //Variables
    sf::Sprite tile_sprite;
    short type;

private:

    //Private variables
    float height = 32.f;
    float width = 32.f;
    short tile_coord_x, tile_coord_y;
    short tile_coord_x_local, tile_coord_y_local;
};

#endif // TILE_HPP
