#ifndef GAME_HPP
#define GAME_HPP
// Klasa renderująca grę
#include<worldgrid.hpp>
#include<console.hpp>
#include<player.hpp>
#include<roomgenerator.hpp>
#include<menu.hpp>

class Game{
public:
    //Constructor/Destructor
    Game();
    ~Game();

    //Functions
    void pollEvents();
    void update();
    void render();

    bool isWindowOpen() const;


private:
    //WAŻNE
    //USTAWIENIE ŚCIEŻKI DO FOLDERU Z ASSETAMI
    std::string data_folder = "C:/Abscond/data";

    //Private variables
    sf::RenderWindow *window;
    sf::Event event;
    sf::VideoMode videoMode;
    WorldGrid mainGrid;
    RoomGenerator roomGenerator;
    std::map<std::string, sf::Texture> textures;
    bool turnPassed = false;
    short gameState = 0; // 0 - main menu, 1 - game, 2 - game win, 3 - game over;
    Menu *mainMenu;

    //Private functions
    void loadTextures();

    void initializeVariables();
    void initializeWindow();
    void initializePlayers();
    void initializeConsole();
    void initializeRooms();
    void initializeText();
    void initializeStairs();

    void updateHpCounter();
    void gameWin();

    //Predykaty związane z sąsiedztwem
    bool chestLeft(Chest &chest);
    bool chestRight(Chest &chest);
    bool chestUp(Chest &chest);
    bool chestDown(Chest &chest);
    bool chestAdjacent(Chest &chest);

    bool enemyLeft(Enemy &enemy);
    bool enemyRight(Enemy &enemy);
    bool enemyUp(Enemy &enemy);
    bool enemyDown(Enemy &enemy);
    bool enemyAdjacent(Enemy &enemy);

    bool doorLeft(Door &door);
    bool doorRight(Door &door);
    bool doorUp(Door &door);
    bool doorDown(Door &door);
    bool doorAdjacent(Door &door);

    //Game objects
    Console *mainConsole;
    Player *player;
    std::vector<Room> rooms;
    sf::Text hpCounter, loseGameText, winGameText;
    sf::Font mainFont;
    sf::Sprite stairs;

};

#endif // GAME_HPP
