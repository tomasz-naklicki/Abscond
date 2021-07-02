#ifndef ENEMY_HPP
#define ENEMY_HPP

class Enemy
{
public:
    //Constructor / Destructor
    Enemy(short x, short y);
    Enemy(short x, short y, short type);
    ~Enemy();

    //Public variables
    sf::Sprite enemy_sprite;
    short enemy_global_coord_x, enemy_global_coord_y;
    short counter = 0;

    //Public functions
    void loadTexture(std::map<std::string, sf::Texture> &texture_map);
    bool isAlive();
    std::pair<short, short> getLocalCoords();
    void takeDamage(short damage);
    void die();
    short getHp();
    short getSpeed();
    short getHitChance();
    short getDamage();
    std::string getName();
    void updateGlobalCoords(short x, short y);

    //Movement functions
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

private:
    //Private variables
    short type;
    short hp;
    bool alive = true;
    short enemy_local_coord_x, enemy_local_coord_y;
    short action_time, hitChance, damage;
    std::string name;
};

#endif // ENEMY_HPP
