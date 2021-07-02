#include "menu.hpp"

Menu::Menu(sf::Font &setfont){
    this->menuFont=setfont;
    for(int i=0; i<3; i++){
        this->menuOption[i].setFont(this->menuFont);
        this->menuOption[i].setCharacterSize(30);
        this->menuOption[i].setFillColor(sf::Color(255,255,255));
        this->menuOption[i].setPosition(1000.f,600+40*i);
        switch(i){
        case 0:
            this->menuOption[i].setString("Play");
            this->menuOption[i].setFillColor(sf::Color(255,0,0));
            break;
        case 1:
            this->menuOption[i].setString("Tutorial");
            this->menuOption[i].setFillColor(sf::Color(255,255,255));
            break;
        case 2:
            this->menuOption[i].setString("Exit");
            this->menuOption[i].setFillColor(sf::Color(255,255,255));
            break;
        }
    }

    this->title.setFont(this->menuFont);
    this->title.setCharacterSize(120);
    this->title.setFillColor(sf::Color(255,255,255));
    this->title.setPosition(40.f,40.f);
    this->title.setString("Abscond");

    this->tutorial_text.setFont(this->menuFont);
    this->tutorial_text.setCharacterSize(20);
    this->tutorial_text.setFillColor(sf::Color(255,255,255));
    this->tutorial_text.setPosition(40.f,300.f);
    this->tutorial_text.setString("Movement - WSAD \nOpening doors/chests / Attacking - arrow keys \nSkipping a turn - space \nEach room is separated by 2 doors \nKill the warden to unlock the way out \n...good luck");
}

void Menu::moveUp(){
    if(isSelected[0]){
        isSelected[0]=false;
        menuOption[0].setFillColor(sf::Color(255,255,255));
        isSelected[2]=true;
        menuOption[2].setFillColor(sf::Color(255,0,0));
    }
    else if(isSelected[1]){
        isSelected[1]=false;
        menuOption[1].setFillColor(sf::Color(255,255,255));
        isSelected[0]=true;
        menuOption[0].setFillColor(sf::Color(255,0,0));
    }
    else{
        isSelected[2]=false;
        menuOption[2].setFillColor(sf::Color(255,255,255));
        if(!this->tutorialOpen){
            isSelected[1]=true;
            menuOption[1].setFillColor(sf::Color(255,0,0));
        }
        else{
            isSelected[0]=true;
            menuOption[0].setFillColor(sf::Color(255,0,0));
        }
    }

}

void Menu::moveDown(){
    if(isSelected[0]){
        isSelected[0]=false;
        menuOption[0].setFillColor(sf::Color(255,255,255));
        if(!this->tutorialOpen){
            isSelected[1]=true;
            menuOption[1].setFillColor(sf::Color(255,0,0));
        }
        else{
            isSelected[2]=true;
            menuOption[2].setFillColor(sf::Color(255,0,0));
        }
    }
    else if(isSelected[1]){
        isSelected[1]=false;
        menuOption[1].setFillColor(sf::Color(255,255,255));
        isSelected[2]=true;
        menuOption[2].setFillColor(sf::Color(255,0,0));
    }
    else{
        isSelected[2]=false;
        menuOption[2].setFillColor(sf::Color(255,255,255));
        isSelected[0]=true;
        menuOption[0].setFillColor(sf::Color(255,0,0));
    }

}

void Menu::Tutorial(){
    this->moveUp();
    this->tutorialOpen=true;
}

void Menu::Exit(sf::RenderWindow *window){
    window->close();
}
void Menu::drawMenu(sf::RenderWindow *window){
    window->draw(this->title);
    window->draw(this->menuOption[0]);
    if(!this->tutorialOpen){
        window->draw(this->menuOption[1]);
    }
    else{
        window->draw(this->tutorial_text);
    }
    window->draw(this->menuOption[2]);

}


short Menu::getSelected(){
    for(short i=0; i<3; i++){
        if(isSelected[i]==true){
            return i;
        }
    }
}
