#include "gamemasternew.hpp"
#include <iostream>

GameMasterNew ticTacToe(800, 600);

void exitOnPush(int posX, int posY, char button, Widget* I)
{
    ticTacToe.setShutDownByEscape(true);
}

int main()
{
    ticTacToe.run_loop();

    return 0;
}
