#ifndef PLAYER_HPP
#define PLAYER_HPP
#include<chest.hpp>
#include<console.hpp>
#include<equipment.hpp>
#include<enemy.hpp>

//Klasa gracza


class Player
{
public:
    //Constructors / Destructors
    Player(sf::Vector2f position);
    Player(short x, short y);
    virtual ~Player();

    //Variables
    sf::Sprite sprite;

    //Functions
    std::pair<short, short> getPlayerPosition();
    void loadTexture(std::map<std::string, sf::Texture> &texture_map);
    short getCurrentHP();
    short getMaxHP();

    //Movement functions
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    //Action functions
    void openChest(std::map<std::string, sf::Texture> &texture_map, Chest &chest, Console &console);
    void attack(Enemy &target, Console &console);
    void isAttacked(Enemy &target, Console &console);



private:
    //Private variables
    short player_coord_x, player_coord_y;
    bool weapon_found=false, armor_found=false;
    
    //Defence
    short max_hp = 10;
    short current_hp = max_hp;
    short armor = 0;
    bool lucky_dodge = false;
    
    //Offense 
    short damage = 1;
    short hitChance = 70;
    short damageMod = 0;
    short hitChanceMod = 0;
    bool lucky_strikes = false;
   
};

#endif // PLAYER_HPP
