#ifndef CONSOLE_HPP
#define CONSOLE_HPP

class Console : public sf::RectangleShape
{
public:
    //Constructors / Destructors
    Console(sf::Font &setfont);
    ~Console();
    void addText(std::string text, bool new_line);

    //Variables
    sf::Text consoleText;

private:
    //Private ariables
    sf::Font textFontArial;
    short lineCounter=1;

    //Private functions
    void drawConsole();
    void findFont(sf::Font &setfont);
    void setTextParameters();


};

#endif // CONSOLE_HPP
