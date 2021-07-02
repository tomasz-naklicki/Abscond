#include<game.hpp>



//Constructors/Destructors
Game::Game(){
    this->initializeVariables();
    this->initializeWindow();

    //Initialize game objects
    this->loadTextures();

    this->initializeConsole();
    this->initializeRooms();
    this->initializeStairs();
    this->initializePlayers();
    this->initializeText();
    this->initializeSound();

}

Game::~ Game(){
    delete this->window;
    delete this->player;
    delete this->mainConsole;
    delete this->mainMenu;
}

//Functions

void Game::pollEvents(){
    //Event polling
    while(this->window->pollEvent(this->event)){
        switch(this->event.type){

        case sf::Event::Closed:
            this->window->close();
            break;

        case sf::Event::KeyPressed:
            if(this->gameState==0){

                //Poruszanie się i interakcja z menu głównym

                if(this->event.key.code==sf::Keyboard::Down || this->event.key.code==sf::Keyboard::S){
                    this->mainMenu->moveDown();
                }
                else if(this->event.key.code==sf::Keyboard::Up || this->event.key.code==sf::Keyboard::W){
                    this->mainMenu->moveUp();
                }
                else if(this->event.key.code==sf::Keyboard::Enter){
                    if(this->mainMenu->getSelected()==0){
                        this->gameState=1;
                    }
                    else if(this->mainMenu->getSelected()==1){
                        this->mainMenu->Tutorial();
                    }
                    else if(this->mainMenu->getSelected()==2){
                        this->mainMenu->Exit(this->window);
                    }
                }

            }
        if(this->gameState==1){
            if(!this->turnPassed){

                //Ruch gracza
                //Ruch w górę
                if(this->event.key.code == sf::Keyboard::W){
                    auto player_pos = this->player->getPlayerPosition();
                    if(player_pos.second!=0){
                        if(this->mainGrid.isPassable(player_pos.first, player_pos.second-1)){
                            this->player->moveUp();
                            this->mainGrid.updateSlot(player_pos.first, player_pos.second, true);
                            this->mainGrid.updateSlot(player_pos.first, player_pos.second-1, false);
                            this->turnPassed = true;
                        }
                    }
                }

                //Ruch w dół
                else if(this->event.key.code == sf::Keyboard::S){
                    auto player_pos = this->player->getPlayerPosition();
                    if(player_pos.second!=21){
                        if(this->mainGrid.isPassable(player_pos.first, player_pos.second+1)){
                            this->player->moveDown();
                            this->mainGrid.updateSlot(player_pos.first, player_pos.second, true);
                            this->mainGrid.updateSlot(player_pos.first, player_pos.second+1, false);
                            this->turnPassed = true;
                        }
                    }
                }

                //Ruch w lewo
                else if(this->event.key.code == sf::Keyboard::A){
                    auto player_pos = this->player->getPlayerPosition();
                    if(player_pos.first!=0){
                        if(this->mainGrid.isPassable(player_pos.first-1, player_pos.second)){
                            this->player->moveLeft();
                            this->mainGrid.updateSlot(player_pos.first, player_pos.second, true);
                            this->mainGrid.updateSlot(player_pos.first-1, player_pos.second, false);
                            this->turnPassed = true;
                        }
                    }
                }

                //Ruch w prawo
                else if(this->event.key.code == sf::Keyboard::D){
                    auto player_pos = this->player->getPlayerPosition();
                    if(player_pos.first!=28){
                        if(this->mainGrid.isPassable(player_pos.first+1, player_pos.second)){
                            this->player->moveRight();
                            this->mainGrid.updateSlot(player_pos.first, player_pos.second, true);
                            this->mainGrid.updateSlot(player_pos.first+1, player_pos.second, false);
                            this->turnPassed = true;
                        }
                    }
                }

                //Interakcje gracza
                else if(this->event.key.code == sf::Keyboard::Up){
                    for(Room &n : this->rooms){
                        //Atak
                        for(Enemy &e : n.enemies){
                            if(enemyUp(e)){
                                this->player->attack(e, *mainConsole);
                                if(!e.isAlive()){
                                    mainGrid.updateSlot(e.enemy_global_coord_x,e.enemy_global_coord_y,true);
                                    e.updateGlobalCoords(NULL, NULL);
                                }
                                this->turnPassed = true;
                            }
                        }

                        //Otwarcie drzwi
                        for(Door &d : n.doors){
                            if(doorUp(d)){
                                if(!d.isOpen()){
                                    d.openDoor(this->textures);
                                    mainGrid.updateSlot(d.door_global_coord_x,d.door_global_coord_y,true);
                                    this->turnPassed = true;
                                }
                            }
                        }

                        //Otwarcie skrzyni
                        for(Chest &c : n.chests){
                            if(chestUp(c)){
                                if(!c.isOpen()){
                                    this->player->openChest(this->textures, c, *this->mainConsole);
                                    this->turnPassed = true;
                                }
                            }
                        }
                    }
                }
                else if(this->event.key.code == sf::Keyboard::Down){
                    for(Room &n : this->rooms){
                        //Atak
                        for(Enemy &e : n.enemies){
                            if(enemyDown(e)){
                                this->player->attack(e, *mainConsole);
                                if(!e.isAlive()){
                                    mainGrid.updateSlot(e.enemy_global_coord_x,e.enemy_global_coord_y,true);
                                    e.updateGlobalCoords(NULL, NULL);
                                }
                                this->turnPassed = true;
                            }
                        }

                        //Otwarcie drzwi
                        for(Door &d : n.doors){
                            if(doorDown(d)){
                                if(!d.isOpen()){
                                    d.openDoor(this->textures);
                                    mainGrid.updateSlot(d.door_global_coord_x,d.door_global_coord_y,true);
                                    this->turnPassed = true;
                                }
                            }
                        }

                        //Otwarcie skrzyni
                        for(Chest &c : n.chests){
                            if(this->chestDown(c)){
                                if(!c.isOpen()){
                                    this->player->openChest(this->textures, c, *this->mainConsole);
                                    this->turnPassed = true;
                                }
                            }
                        }
                    }
                }
                else if(this->event.key.code == sf::Keyboard::Left){
                    for(Room &n : this->rooms){
                        //Atak
                        for(Enemy &e : n.enemies){
                            if(enemyLeft(e)){
                                this->player->attack(e, *mainConsole);
                                if(!e.isAlive()){
                                    mainGrid.updateSlot(e.enemy_global_coord_x,e.enemy_global_coord_y,true);
                                    e.updateGlobalCoords(NULL, NULL);
                                }
                                this->turnPassed = true;
                            }
                        }

                        //Otwarcie drzwi
                        for(Door &d : n.doors){
                            if(doorLeft(d)){
                                if(!d.isOpen()){
                                    d.openDoor(this->textures);
                                    mainGrid.updateSlot(d.door_global_coord_x,d.door_global_coord_y,true);
                                    this->turnPassed = true;
                                }
                            }
                        }

                        //Otwarcie skrzyni
                        for(Chest &c : n.chests){
                            if(chestLeft(c)){
                                if(!c.isOpen()){
                                    this->player->openChest(this->textures, c, *this->mainConsole);
                                    this->turnPassed = true;
                                }
                            }
                        }
                    }
                }
                else if(this->event.key.code == sf::Keyboard::Right){
                    for(Room &n : this->rooms){

                        //Atak
                        for(Enemy &e : n.enemies){
                            if(enemyRight(e)){
                                this->player->attack(e, *mainConsole);
                                if(!e.isAlive()){
                                    mainGrid.updateSlot(e.enemy_global_coord_x,e.enemy_global_coord_y,true);
                                    e.updateGlobalCoords(NULL, NULL);
                                }
                                this->turnPassed = true;
                            }
                        }

                        //Otwarcie drzwi
                        for(Door &d : n.doors){
                            if(doorRight(d)){
                                if(!d.isOpen()){
                                    d.openDoor(this->textures);
                                    mainGrid.updateSlot(d.door_global_coord_x,d.door_global_coord_y,true);
                                    this->turnPassed = true;
                                }
                            }
                        }

                        //Otwarcie skrzyni
                        for(Chest &c : n.chests){
                            if(chestRight(c)){
                                if(!c.isOpen()){
                                    this->player->openChest(this->textures, c, *this->mainConsole);
                                    this->turnPassed = true;
                                }
                            }
                        }
                    }
                }
                //Czekanie tury
                if(this->event.key.code == sf::Keyboard::Space){
                    this->mainConsole->addText("\n>>You waited", true);
                    this->turnPassed = true;
                }
            }
        }
            //Wyjście z gry
            if(this->event.key.code == sf::Keyboard::Escape){
                this->window->close();
            }
            break;
        }

    }
}
void Game::update(){
    //Event poll
    this->pollEvents();

    //Akcje przeciwników
    if(turnPassed){
        for(Room &n : this->rooms){
            if(n.isRevealed()){
                for(Enemy &e : n.enemies){
                    if(e.isAlive()){
                        //Pathfinding
                        if(!enemyAdjacent(e) && e.counter==0){
                            if(this->player->getPlayerPosition().first<e.enemy_global_coord_x && mainGrid.isPassable(e.enemy_global_coord_x-1, e.enemy_global_coord_y)){
                                mainGrid.updateSlot(e.enemy_global_coord_x, e.enemy_global_coord_y, true);
                                e.moveLeft();
                                mainGrid.updateSlot(e.enemy_global_coord_x, e.enemy_global_coord_y, false);

                            }
                            else if(this->player->getPlayerPosition().first>e.enemy_global_coord_x && mainGrid.isPassable(e.enemy_global_coord_x+1, e.enemy_global_coord_y)){
                                mainGrid.updateSlot(e.enemy_global_coord_x, e.enemy_global_coord_y, true);
                                e.moveRight();
                                mainGrid.updateSlot(e.enemy_global_coord_x, e.enemy_global_coord_y, false);
                            }
                            else if(this->player->getPlayerPosition().second<e.enemy_global_coord_y && mainGrid.isPassable(e.enemy_global_coord_x, e.enemy_global_coord_y-1)){
                                mainGrid.updateSlot(e.enemy_global_coord_x, e.enemy_global_coord_y, true);
                                e.moveUp();
                                mainGrid.updateSlot(e.enemy_global_coord_x, e.enemy_global_coord_y, false);
                            }
                            else if(this->player->getPlayerPosition().second>e.enemy_global_coord_y && mainGrid.isPassable(e.enemy_global_coord_x, e.enemy_global_coord_y+1)){
                                mainGrid.updateSlot(e.enemy_global_coord_x, e.enemy_global_coord_y, true);
                                e.moveDown();
                                mainGrid.updateSlot(e.enemy_global_coord_x, e.enemy_global_coord_y, false);
                            }
                            //Take action
                            if(enemyAdjacent(e)){
                                e.counter++;
                                if(e.counter==e.getSpeed()){
                                    this->player->isAttacked(e, *mainConsole);
                                    if(this->player->getCurrentHP()<=0){
                                        this->gameState=3;
                                    }
                                    e.counter=0;
                                }
                            }
                        }
                        else if(enemyAdjacent(e)){
                            //Take action
                            e.counter++;
                            if(e.counter==e.getSpeed()){
                                this->player->isAttacked(e, *mainConsole);
                                if(this->player->getCurrentHP()<=0){
                                    this->gameState=3;
                                }
                                e.counter=0;
                            }
                        }
                        else if(e.counter!=0){
                            //Continue taking action
                            e.counter++;
                            if(e.counter==e.getSpeed()){
                                if(enemyAdjacent(e)){
                                    this->player->isAttacked(e, *mainConsole);
                                    if(this->player->getCurrentHP()<=0){
                                        this->gameState=3;
                                    }
                                }
                                e.counter=0;
                            }
                        }
                    }
                }
            }
        }
        this->updateHpCounter();
        turnPassed=false;
    }

    //Czy gra została wygrana?
    this->gameWin();

    //Odkrywanie pokoi
    for(Room &n : this->rooms){
        for(Door &d : n.doors){
            if(d.isOpen() && !n.isRevealed()){
                n.revealRoom();
            }
        }
    }
}

void Game::render(){
    //Clear
    this->window->clear(sf::Color::Black);

    if(this->gameState==0){
        //Draw menu
        this->mainMenu->drawMenu(this->window);
    }

    else if(this->gameState==1){

        //Draw game objects
        this->window->draw(*this->mainConsole);
        this->window->draw(this->mainConsole->consoleText);
        this->window->draw(this->hpCounter);
        for(Room &n : rooms){
            if(n.isRevealed()){
                n.drawRoom(this->window);
                for(size_t i=0; i<n.doors.size(); i++){
                    this->window->draw(n.doors[i].door_sprite);
                }
                if(this->rooms[11].isRevealed()){
                    this->window->draw(this->stairs);
                }
                for(size_t i=0; i<n.enemies.size(); i++){
                    this->window->draw(n.enemies[i].enemy_sprite);
                }
                for(size_t i=0; i<n.chests.size(); i++){
                    this->window->draw(n.chests[i].chest_sprite);
                }
            }
        }
        this->window->draw(this->player->sprite);
    }

    else if(this->gameState==2){
        //Draw win game screen
        this->window->draw(this->winGameText);
    }
    else{
        //Draw game over screen
        this->window->draw(this->loseGameText);
    }

    //Display
    this->window->display();
}

bool Game::isWindowOpen() const{
    return this->window->isOpen();
}

void Game::initializeVariables(){
   this->window = nullptr;
   this->mainConsole = nullptr;
   this->player = nullptr;
   this->mainFont.loadFromFile(this->data_folder+"/arial.ttf");
   this->mainMenu = new Menu(this->mainFont);

}

void Game::initializeSound(){
    this->song.loadFromFile(data_folder+"/xDeviruchi - Mysterious Dungeon.wav");
    this->mainSound.setBuffer(this->song);
    this->mainSound.setLoop(true);
    this->mainSound.setVolume(70);
    this->mainSound.play();
}

void Game::initializeWindow(){
    //Window size
    this->videoMode.width = 1280;
    this->videoMode.height = 720;

    this->window = new sf::RenderWindow(this->videoMode, "Abscond", sf::Style::Default);

    this->window->setFramerateLimit(60);

}

void Game::initializePlayers(){
    this->player = new Player(3,3);
    this->player->loadTexture(this->textures);
}

void Game::initializeConsole(){
    this->mainConsole = new Console(this->mainFont);
}

void Game::initializeText(){
    this->hpCounter.setFont(mainFont);
    this->hpCounter.setCharacterSize(20);
    this->hpCounter.setFillColor(sf::Color(255,255,255));
    this->hpCounter.setString("HP: " + std::to_string(this->player->getCurrentHP())+"/"+std::to_string(this->player->getMaxHP()));
    this->hpCounter.setPosition(20.f,690.f);

    this->winGameText.setFont(mainFont);
    this->winGameText.setCharacterSize(20);
    this->winGameText.setFillColor(sf::Color(255,255,255));
    this->winGameText.setString("...you escaped \nPress ESC to close the game");
    this->winGameText.setPosition(1000.f,600.f);

    this->loseGameText.setFont(mainFont);
    this->loseGameText.setCharacterSize(20);
    this->loseGameText.setFillColor(sf::Color(255,255,255));
    this->loseGameText.setString("...you failed to escape \nPress ESC to close the game");
    this->loseGameText.setPosition(1000.f,600.f);
}

void Game::initializeStairs(){
    this->stairs.setTexture(this->textures["stairs"]);
    this->stairs.setPosition((24)*32.f,(17)*32.f);
}

void Game::updateHpCounter(){
    this->hpCounter.setString("HP: " + std::to_string(this->player->getCurrentHP())+"/"+std::to_string(this->player->getMaxHP()));
}

void Game::initializeRooms(){
    //Starting room
    Room next_room({0, 0}, 0, 0, false, true, false, true); //Room 0 gora dol lewo prawo
    this->rooms.emplace_back(next_room);
    //Create rooms
    next_room = Room(roomGenerator.generateLayout(), 1, 0, false, false, true, true); //Room 1
    this->rooms.emplace_back(next_room);

    next_room = Room(roomGenerator.generateLayout(), 2, 0, false, true, true, true); //Room 2
    this->rooms.emplace_back(next_room);

    next_room = Room(roomGenerator.generateLayout(), 3, 0, false, true, true, false); //Room 3
    this->rooms.emplace_back(next_room);

    next_room = Room(roomGenerator.generateLayout(), 0, 1, true, true, false, false); //Room 4
    this->rooms.emplace_back(next_room);

    next_room = Room(roomGenerator.generateLayout(), 1, 1, false, true, false, true); //Room 5
    this->rooms.emplace_back(next_room);

    next_room = Room(roomGenerator.generateLayout(), 2, 1, true, false, true, true); //Room 6
    this->rooms.emplace_back(next_room);

    next_room = Room(roomGenerator.generateLayout(), 3, 1, true, true, true, false); //Room 7
    this->rooms.emplace_back(next_room);

    next_room = Room(roomGenerator.generateLayout(), 0, 2, true, false, false, true); //Room 8
    this->rooms.emplace_back(next_room);

    next_room = Room(roomGenerator.generateLayout(), 1, 2, true, false, true, true); //Room 9
    this->rooms.emplace_back(next_room);

    next_room = Room(roomGenerator.generateLayout(), 2, 2, false, false, true, false); //Room 10
    this->rooms.emplace_back(next_room);

    next_room = Room({0,0}, 3, 2, true, false, false, false); // BOSS room
    this->rooms.emplace_back(next_room);
    Enemy boss(3,3,4);
    this->rooms[11].addEnemy(boss);

    for(Room &n : this->rooms){
        n.loadTextures(this->textures);
        n.setPassing(this->mainGrid);
        for(size_t i = 0; i<n.enemies.size(); i++){
            n.enemies[i].loadTexture(this->textures);
        }
        for(size_t i = 0; i<n.chests.size(); i++){
            n.chests[i].loadTexture(this->textures);
        }
        for(size_t i = 0; i<n.doors.size(); i++){
            n.doors[i].loadTexture(this->textures);
        }
    }
    this->rooms[0].revealRoom();
}

void Game::gameWin(){
    if(this->player->sprite.getPosition()==this->stairs.getPosition() && !this->rooms[11].enemies[0].isAlive() && this->gameState!=2){
        this->gameState = 2;
    }
}

void Game::loadTextures(){
    sf::Texture texture;

    //Ładowanie tekstury gracza
    if(!texture.loadFromFile(this->data_folder+"/player.png")){
        std::cerr<<"Could not load player texture"<<std::endl;
    }
    this->textures.emplace("player", texture);

    //Ładowanie tekstury podłogi
    if(!texture.loadFromFile(this->data_folder+"/floor.png")){
        std::cerr<<"Could not load floor texture"<<std::endl;
    }
    this->textures.emplace("floor", texture);

    //Ładowanie tekstury ściany
    if(!texture.loadFromFile(this->data_folder+"/wall.png")){
        std::cerr<<"Could not load wall texture"<<std::endl;
    }
    this->textures.emplace("wall", texture);

    //Ładowanie tekstur drzwi
    if(!texture.loadFromFile(this->data_folder+"/door.png")){
        std::cerr<<"Could not load door texture"<<std::endl;
    }
    this->textures.emplace("door", texture);

    if(!texture.loadFromFile(this->data_folder+"/door_closed.png")){
        std::cerr<<"Could not load closed door texture"<<std::endl;
    }
    this->textures.emplace("door_closed", texture);

    //Ładowanie tekstury schodów
    if(!texture.loadFromFile(this->data_folder+"/stairs.png")){
        std::cerr<<"Could not load stairs texture"<<std::endl;
    }
    this->textures.emplace("stairs", texture);

    //Ładowanie tekstur skrzyń
    if(!texture.loadFromFile(this->data_folder+"/chest_closed.png")){
        std::cerr<<"Could not load chest closed texture"<<std::endl;
    }
    this->textures.emplace("chest_closed", texture);

    if(!texture.loadFromFile(this->data_folder+"/chest_open.png")){
        std::cerr<<"Could not load chest open texture"<<std::endl;
    }
    this->textures.emplace("chest_open", texture);

    //Ładowanie tekstur przeciwników
    if(!texture.loadFromFile(this->data_folder+"/slime.png")){
        std::cerr<<"Could not load slime texture"<<std::endl;
    }
    this->textures.emplace("slime", texture);

    if(!texture.loadFromFile(this->data_folder+"/ghost.png")){
        std::cerr<<"Could not load ghost texture"<<std::endl;
    }
    this->textures.emplace("ghost", texture);

    if(!texture.loadFromFile(this->data_folder+"/fly.png")){
        std::cerr<<"Could not load fly texture"<<std::endl;
    }
    this->textures.emplace("fly", texture);

    if(!texture.loadFromFile(this->data_folder+"/goblin.png")){
        std::cerr<<"Could not load goblin texture"<<std::endl;
    }
    this->textures.emplace("goblin", texture);

    if(!texture.loadFromFile(this->data_folder+"/warden.png")){
        std::cerr<<"Could not load warden texture"<<std::endl;
    }
    this->textures.emplace("warden", texture);

}

//Predykaty związane z sąsiedztwem

bool Game::chestDown(Chest &chest){
    if(chest.chest_global_coord_y==this->player->getPlayerPosition().second + 1 && chest.chest_global_coord_x==this->player->getPlayerPosition().first){
        return true;
    }
    return false;
}

bool Game::chestUp(Chest &chest){
    if(chest.chest_global_coord_y==this->player->getPlayerPosition().second - 1 && chest.chest_global_coord_x==this->player->getPlayerPosition().first){
        return true;
    }
    return false;
}

bool Game::chestLeft(Chest &chest){
    if(chest.chest_global_coord_x==this->player->getPlayerPosition().first - 1 && chest.chest_global_coord_y==this->player->getPlayerPosition().second){
        return true;
    }
    return false;
}

bool Game::chestRight(Chest &chest){
    if(chest.chest_global_coord_x==this->player->getPlayerPosition().first + 1 && chest.chest_global_coord_y==this->player->getPlayerPosition().second){
        return true;
    }
    return false;
}

bool Game::chestAdjacent(Chest &chest){
    if(chestDown(chest) || chestLeft(chest) || chestRight(chest) || chestUp(chest)){
        return true;
    }
    return false;
}

bool Game::enemyDown(Enemy &enemy){
    if(enemy.enemy_global_coord_y==this->player->getPlayerPosition().second + 1 && enemy.enemy_global_coord_x==this->player->getPlayerPosition().first){
        return true;
    }
    return false;
}

bool Game::enemyUp(Enemy &enemy){
    if(enemy.enemy_global_coord_y==this->player->getPlayerPosition().second - 1 && enemy.enemy_global_coord_x==this->player->getPlayerPosition().first){
        return true;
    }
    return false;
}

bool Game::enemyLeft(Enemy &enemy){
    if(enemy.enemy_global_coord_x==this->player->getPlayerPosition().first - 1 && enemy.enemy_global_coord_y==this->player->getPlayerPosition().second){
        return true;
    }
    return false;
}

bool Game::enemyRight(Enemy &enemy){
    if(enemy.enemy_global_coord_x==this->player->getPlayerPosition().first + 1 && enemy.enemy_global_coord_y==this->player->getPlayerPosition().second){
        return true;
    }
    return false;
}

bool Game::enemyAdjacent(Enemy &enemy){
    if(enemyDown(enemy) || enemyLeft(enemy) || enemyUp(enemy) || enemyRight(enemy)){
        return true;
    }
    return false;
}

bool Game::doorDown(Door &door){
    if(door.door_global_coord_y==this->player->getPlayerPosition().second + 1 && door.door_global_coord_x==this->player->getPlayerPosition().first){
        return true;
    }
    return false;
}

bool Game::doorUp(Door &door){
    if(door.door_global_coord_y==this->player->getPlayerPosition().second - 1 && door.door_global_coord_x==this->player->getPlayerPosition().first){
        return true;
    }
    return false;
}

bool Game::doorRight(Door &door){
    if(door.door_global_coord_x==this->player->getPlayerPosition().first + 1 && door.door_global_coord_y==this->player->getPlayerPosition().second){
        return true;
    }
    return false;
}

bool Game::doorLeft(Door &door){
    if(door.door_global_coord_x==this->player->getPlayerPosition().first - 1 && door.door_global_coord_y==this->player->getPlayerPosition().second){
        return true;
    }
    return false;
}

bool Game::doorAdjacent(Door &door){
    if(doorDown(door) || doorUp(door) || doorLeft(door) || doorRight(door)){
        return true;
    }
    return false;
}
