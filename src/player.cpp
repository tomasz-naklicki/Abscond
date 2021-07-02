#include<player.hpp>

//Constructors / Destructors

Player::Player(sf::Vector2f position)
{
    this->sprite.setPosition(position);
    this->player_coord_x=position.x/32.f;
    this->player_coord_y=position.y/32.f;

}

Player::Player(short x, short y){
    this->sprite.setPosition(x*32.f, y*32.f);
    this->player_coord_x=x;
    this->player_coord_y=y;
}

Player::~Player(){

}

//Variables

//Functions

std::pair<short, short> Player::getPlayerPosition(){
    return std::pair<short, short>(player_coord_x, player_coord_y);
}

    //Poruszanie postaci gracza po wciśnięciu przycisku
void Player::moveUp(){
    this->sprite.move(0.f,-32.f);
    this->player_coord_y-=1;
}
void Player::moveDown(){
    this->sprite.move(0.f,32.f);
    this->player_coord_y+=1;
}

void Player::moveLeft(){
    this->sprite.move(-32.f,0.f);
    this->player_coord_x-=1;
}

void Player::moveRight(){
    this->sprite.move(32.f,0.f);
    this->player_coord_x+=1;
}

void Player::loadTexture(std::map<std::string, sf::Texture> &texture_map){
    this->sprite.setTexture(texture_map["player"]);
}

void Player::openChest(std::map<std::string, sf::Texture> &texture_map, Chest &chest, Console &console){
    chest.openChest(texture_map);

    Equipment treasure(this->weapon_found, this->armor_found);
    console.addText("\n>>You find a " + treasure.getName(), true);
    switch(treasure.getType()){
    case 0:
        this->damage=2;
        this->hitChance=70;
        this->weapon_found=true;
        break;
    case 1:
        this->damage=1;
        this->hitChance=80;
        this->weapon_found=true;
        break;
    case 2:
        this->damage=3;
        this->hitChance=60;
        this->weapon_found=true;
        break;
    case 3:
        this->armor_found=true;
        break;
    case 6:
        this->current_hp=this->max_hp;
        break;
    }
    this->damage+=treasure.damageMod;
    this->hitChanceMod+=treasure.hitMod;
    this->lucky_strikes=treasure.attackLuck;
    this->max_hp+=treasure.hpMod;
    this->current_hp+=treasure.hpMod;
    this->lucky_dodge=treasure.dodgeLuck;
}

void Player::attack(Enemy &target, Console &console){
    if(rand()%100+1<=this->hitChance+this->hitChanceMod){
        target.takeDamage(this->damage+this->damageMod);
        console.addText("\n>>You attacked "+target.getName() + " for " + std::to_string(this->damage+this->damageMod) + " damage", true);
        if(!target.isAlive()){
            console.addText(" and it died", false);
        }
    }
    else{
        //Rozpatrzenie przypadku szczęśliwych ataków
        if(this->lucky_strikes==true){
            if(rand()%100+1<=this->hitChance+this->hitChanceMod){
                target.takeDamage(this->damage+this->damageMod);
                console.addText("\n>>You attacked "+target.getName() + " for " + std::to_string(this->damage+this->damageMod) + " damage", true);
                if(!target.isAlive()){
                    console.addText(" and it died", false);
                }
            }
            else{
                console.addText("\n>>You attacked "+target.getName() + ", but missed", true);
            }
        }

        else{
            console.addText("\n>>You attacked "+target.getName() + ", but missed", true);
        }
    }
}

void Player::isAttacked(Enemy &target, Console &console){
    if(rand()%100+1<=target.getHitChance()){

        //Rozpatrzenie przypadku szczęśliwych uników
        if(this->lucky_dodge==true){
            if(rand()%100+1<=target.getHitChance()){

                //Pancerz nie może zmniejszyć obrażeń poniżej 1
                if(target.getDamage()-this->armor<1){
                    this->current_hp-=1;
                    console.addText("\n>>" + target.getName() + " attacked you for 1 damage", true);
                }

                else{
                    this->current_hp-=target.getDamage()-this->armor;
                    console.addText("\n>>" + target.getName() + " attacked you for " + std::to_string(target.getDamage()-this->armor) + " damage", true);
                }
            }
            else{
                console.addText("\n>>" + target.getName() + " attack you, but missed", true);
            }
        }
        else{

            //Pancerz nie może zmniejszyć obrażeń poniżej 1
            if(target.getDamage()-this->armor<1){
                this->current_hp-=1;
                console.addText("\n>>" + target.getName() + " attacked you for 1 damage", true);
            }
            else{
                this->current_hp-=target.getDamage()-this->armor;
                console.addText("\n>>" + target.getName() + " attacked you for " + std::to_string(target.getDamage()-this->armor) + " damage", true);
            }
        }
    }

    else{
        console.addText("\n>>" + target.getName() + " attack you, but missed", true);
    }
}
short Player::getCurrentHP(){
    return this->current_hp;
}

short Player::getMaxHP(){
    return this->max_hp;
}
