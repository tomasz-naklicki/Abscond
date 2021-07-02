#include <game.hpp>
#include <roomgenerator.hpp>

int main(){
    //Initialize game
    Game game;

    //Game loop    
    while(game.isWindowOpen()){
        //Update
        game.update();

        //Render
        game.render();
    }
    return EXIT_SUCCESS;
}


