#ifndef ROOM_HPP
#define ROOM_HPP
#include<tile.hpp>
#include<roomlayout.hpp>
#include<worldgrid.hpp>
#include<enemy.hpp>
#include<chest.hpp>
#include<door.hpp>

class Room
{
public:
    //Constructor
    Room(RoomLayout room_layout, short x, short y, bool up, bool down, bool left, bool right);

    //Public variables
    std::vector<Tile> layout;
    std::vector<Enemy> enemies;
    std::vector<Chest> chests;
    std::vector<Door> doors;
    bool first_door_opened = false;

    //Public functions
    std::pair<short, short> getCoords();
    void loadTextures(std::map<std::string, sf::Texture> &texture_map);
    void setPassing(WorldGrid &grid);
    void addEnemy(Enemy target);
    void generateRoom(RoomLayout room_layout);
    void drawRoom(sf::RenderWindow* main_window);
    void revealRoom();
    bool isRevealed();


private:
    //Private variables
    short width = 7;
    short height = 7;

    bool revealed = false;
    bool occupied[7][7];

    /*Przejścia między pokojami
     * Pozycje:
    0 - góra
    1 - dół
    2 - lewo
    3 - prawo
    */
    bool entrances[4];
    short room_coord_x, room_coord_y;



};

#endif // ROOM_HPP
