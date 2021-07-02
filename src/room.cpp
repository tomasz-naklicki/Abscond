    #include "room.hpp"

Room::Room(RoomLayout room_layout, short x, short y, bool up, bool down, bool left, bool right)
    : room_coord_x(x), room_coord_y(y)
{
    this->entrances[0]=up;
    this->entrances[1]=down;
    this->entrances[2]=left;
    this->entrances[3]=right;

    this->generateRoom(room_layout);
}

void Room::generateRoom(RoomLayout room_layout){
    for(short i=0; i<this->height; i++){
        for(short j=0; j<this->width; j++){
            if(i==0 || i==height-1 || j==0 || j==width-1){
                this->layout.emplace_back(Tile(1));
                this->occupied[j][i]=true;
            }
            else{
                this->layout.emplace_back(Tile(0));
                this->occupied[j][i]=false;
            }
            this->layout[this->width*i+j].tile_sprite.setPosition((this->room_coord_x*7+j)*32.f, (this->room_coord_y*7+i)*32.f);
        }


        if(this->entrances[0]==true){
            this->doors.emplace_back(Door(this->room_coord_x*7+3, this->room_coord_y*7));
        }

        if(this->entrances[1]==true){
            this->doors.emplace_back(Door(this->room_coord_x*7+3, this->room_coord_y*7+6));
        }

        if(this->entrances[2]==true){
            this->doors.emplace_back(Door(this->room_coord_x*7, this->room_coord_y*7+3));
        }


        if(this->entrances[3]==true){
            this->doors.emplace_back(Door(this->room_coord_x*7+6, this->room_coord_y*7+3));
        }

        //Zajmowanie pól przed drzwiami w celu zapewnienia przejścia
        this->occupied[3][1]=true;
        this->occupied[3][5]=true;
        this->occupied[1][3]=true;
        this->occupied[5][3]=true;
    }
    short x, y;
    for(int i=0; i<room_layout.number_of_enemies; i++){
        do{
            x=rand()%5+1;
            y=rand()%5+1;
        } while(this->occupied[x][y]);

        this->enemies.emplace_back(Enemy(x,y));
        this->enemies[i].enemy_global_coord_x = this->room_coord_x*7+enemies[i].getLocalCoords().first;
        this->enemies[i].enemy_global_coord_y = this->room_coord_y*7+enemies[i].getLocalCoords().second;
        this->enemies[i].enemy_sprite.setPosition(this->enemies[i].enemy_global_coord_x*32.f, this->enemies[i].enemy_global_coord_y*32.f);
        this->occupied[x][y]=true;
    }
    for(int i = 0; i<room_layout.number_of_chests; i++){
        do{
            x=rand()%5+1;
            y=rand()%5+1;
        } while(this->occupied[x][y]);

        this->chests.emplace_back(Chest(x, y));
        this->chests[i].chest_global_coord_x = this->room_coord_x*7+chests[i].chest_local_coord_x;
        this->chests[i].chest_global_coord_y = this->room_coord_y*7+chests[i].chest_local_coord_y;
        this->chests[i].chest_sprite.setPosition(this->chests[i].chest_global_coord_x*32.f, this->chests[i].chest_global_coord_y*32.f);
        this->occupied[x][y]=true;
    }
}

void Room::drawRoom(sf::RenderWindow *main_window){
    for(Tile &n : this->layout){
        main_window->draw(n.tile_sprite);
    }
}

void Room::loadTextures(std::map<std::string, sf::Texture> &texture_map){
    for(Tile &n : this->layout){
        if(n.type==0){
            n.tile_sprite.setTexture(texture_map["floor"]);
        }
        else if(n.type==1){
            n.tile_sprite.setTexture(texture_map["wall"]);
        }
    }
}

void Room::setPassing(WorldGrid &grid){
    for(Tile &n : this->layout){
        if(n.type==0){
            grid.updateSlot(n.tile_sprite.getPosition().x/32.f,n.tile_sprite.getPosition().y/32.f, true);            }
    }
    for(Enemy &n : this->enemies){
        grid.updateSlot(n.enemy_sprite.getPosition().x/32.f, n.enemy_sprite.getPosition().y/32.f, false);
    }
    for(Chest &n : this->chests){
        grid.updateSlot(n.chest_sprite.getPosition().x/32.f, n.chest_sprite.getPosition().y/32.f, false);
    }
}

bool Room::isRevealed(){
    return this->revealed;
}

void Room::revealRoom(){
    this->revealed = true;
}

std::pair<short, short> Room::getCoords(){
    return std::pair<short, short>(this->room_coord_x, this->room_coord_y);
}

void Room::addEnemy(Enemy target){
    target.enemy_global_coord_x = this->room_coord_x*7+target.getLocalCoords().first;
    target.enemy_global_coord_y = this->room_coord_y*7+target.getLocalCoords().second;
    target.enemy_sprite.setPosition(target.enemy_global_coord_x*32.f, target.enemy_global_coord_y*32.f);
    this->enemies.emplace_back(target);
}
