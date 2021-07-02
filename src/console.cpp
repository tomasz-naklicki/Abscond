#include <console.hpp>
#include <game.hpp>

//Constructors / Destructors
Console::Console(sf::Font &setfont)
{
    this->drawConsole();
    this->findFont(setfont);
    this->setTextParameters();
}

Console::~Console(){

}

//Functions
void Console::drawConsole(){
    //Parametry konsoli

    //Rozmiar
    this->setSize(sf::Vector2f(348.f,716.f));

    //Pozycja
    this->setPosition(sf::Vector2f(930.f,2.f));

    //Kolory
    this->setFillColor(sf::Color::Transparent);
    this->setOutlineColor(sf::Color::White);
    this->setOutlineThickness(2.f);
}

void Console::findFont(sf::Font &setfont){
    //Funkcja ustawiająca czcionkę jako czcionkę consoleText
    this->consoleText.setFont(setfont);

}

void Console::addText(std::string text, bool new_line){
    //Dodawanie tekstu to konsoli
    this->consoleText.setString(this->consoleText.getString()+text);
    this->lineCounter++;
    if(lineCounter>51 && new_line){
        this->consoleText.move(0.f,-14.f);
    }
}

void Console::setTextParameters(){
    this->consoleText.setString(">>Escape start");
    this->consoleText.setCharacterSize(12);
    this->consoleText.setFillColor(sf::Color(255,255,255));
    this->consoleText.setStyle(sf::Text::Regular);
    this->consoleText.setPosition(930.f,4.f);
}

