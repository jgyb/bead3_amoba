#include "gamemasternew.hpp"

GameMasterNew::GameMasterNew(int sizeX0, int sizeY0) : Window(sizeX0, sizeY0)
{
    addWidget(Button_exit = new PushButton(30, 30, 60, 25, "Exit"));
    addWidget(Box1 = new TicTacToeBox(100, 100, 30, 30));
}
