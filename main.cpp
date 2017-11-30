#include "Game.h"
int main() {
    std::cout << "Welcome to TankCraft" << std::endl;
    try {
        Game game;
        game.run();
    }
    catch (std::exception& e){
        std::cout << "\nEXCEPTION: " << e.what() << std::endl;
    }

}

