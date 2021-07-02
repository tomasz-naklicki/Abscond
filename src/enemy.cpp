#include "enemy.hpp"

/* Enemy types:
 * 0 - slime
 * 1 - fly
 * 2 - goblin
 * 3 - ghost
 * 4 - warden (BOSS)
 *
*/

Enemy::Enemy(short x, short y){
    this->enemy_local_coord_x = x;
    this->enemy_local_coord_y = y;
    this->type = rand()%4;
    switch(this->type){
    case 0:
        this->name="slime";
        this->hp=7;
        this->action_time=4;
        this->hitChance=40;
        this->damage=3;
        break;
    case 1:
        this->name="fly";
        this->hp=2;
        this->action_time=2;
        this->hitChance=50;
        this->damage=1;
        break;
    case 2:
        this->name="goblin";
        this->hp=3;
        this->action_time=3;
        this->hitChance=80;
        this->damage=2;
        break;
    case 3:
        this->name="ghost";
        this->hp=4;
        this->action_time=3;
        this->hitChance=70;
        this->damage=2;
        break;
    }
}

Enemy::Enemy(short x, short y, short type){
    this->enemy_local_coord_x = x;
    this->enemy_local_coord_y = y;
    this->type = type;
    switch(this->type){
    case 0:
        this->name="slime";
        this->hp=7;
        this->action_time=4;
        this->hitChance=40;
        this->damage=3;
        break;
    case 1:
        this->name="fly";
        this->hp=2;
        this->action_time=2;
        this->hitChance=50;
        this->damage=1;
        break;
    case 2:
        this->name="goblin";
        this->hp=3;
        this->action_time=3;
        this->hitChance=80;
        this->damage=2;
        break;
    case 3:
        this->name="ghost";
        this->hp=4;
        this->action_time=3;
        this->hitChance=70;
        this->damage=2;
        break;
    case 4:
        this->name="the Warden";
        this->hp=20;
        this->action_time=3;
        this->hitChance=90;
        this->damage=5;
    }
}

Enemy::~Enemy(){

}

void Enemy::die(){
    this->alive = false;
    this->enemy_sprite.setPosition(-32.f,-32.f);
}

void Enemy::takeDamage(short damage){
    this->hp-=damage;
    if(this->hp<=0){
        this->die();
    }
}

void Enemy::loadTexture(std::map<std::string, sf::Texture> &texture_map){
    switch(this->type){
    case 0:
        this->enemy_sprite.setTexture(texture_map["slime"]);
        break;
    case 1:
        this->enemy_sprite.setTexture(texture_map["fly"]);
        break;
    case 2:
        this->enemy_sprite.setTexture(texture_map["goblin"]);
        break;
    case 3:
        this->enemy_sprite.setTexture(texture_map["ghost"]);
        break;
    case 4:
        this->enemy_sprite.setTexture(texture_map["warden"]);
        break;
    }

}

void Enemy::moveUp(){
    this->enemy_sprite.move(0.f, -32.f);
    this->enemy_global_coord_y-=1;
}

void Enemy::moveDown(){
    this->enemy_sprite.move(0.f, 32.f);
    this->enemy_global_coord_y+=1;
}

void Enemy::moveLeft(){
    this->enemy_sprite.move(-32.f,0.f);
    this->enemy_global_coord_x-=1;
}

void Enemy::moveRight(){
    this->enemy_sprite.move(32.f,0.f);
    this->enemy_global_coord_x+=1;
}

bool Enemy::isAlive(){
    return this->alive;
}

std::pair<short, short> Enemy::getLocalCoords(){
    return std::pair<short, short>(this->enemy_local_coord_x, this->enemy_local_coord_y);
}

short Enemy::getSpeed(){
    return this->action_time;
}

std::string Enemy::getName(){
    return this->name;
}

short Enemy::getHitChance(){
    return this->hitChance;
}

short Enemy::getDamage(){
    return this->damage;
}

void Enemy::updateGlobalCoords(short x, short y){
    this->enemy_global_coord_x = x;
    this->enemy_global_coord_y = y;
}
