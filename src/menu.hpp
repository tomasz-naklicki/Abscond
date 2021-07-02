#ifndef MENU_HPP
#define MENU_HPP


class Menu
{
public:
    //Constructor
    Menu(sf::Font &setfont);

    //Public variables
    sf::Text menuOption[3];
    sf::Text title;
    sf::Text tutorial_text;

    //Public functions
    short getSelected();

    void moveUp();
    void moveDown();

    void Tutorial();
    void Exit(sf::RenderWindow *window);

    void drawMenu(sf::RenderWindow *window);

private:

    //Private variables
    sf::Font menuFont;
    bool isSelected[3] = {true,false,false};
    bool tutorialOpen=false;
};

#endif // MENU_HPP
