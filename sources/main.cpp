#include "Game.hpp"

#include <iostream>


int main()
{
    try
    {
        Game game;

    	game.run();
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "An exception has been raised: " << std::endl;
        std::cerr << e.what() << std::endl;
    }

    return 0;
}