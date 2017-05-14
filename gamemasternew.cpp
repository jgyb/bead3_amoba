#include "gamemasternew.hpp"
#include <iostream>


GameMasterNew::GameMasterNew(int sizeX0, int sizeY0) : Window(sizeX0, sizeY0)
{
    gameCtr();
}

void GameMasterNew::gameCtr()
{
    addWidget(Button_exit = new PushButton(30, 30, 60, 25, "Exit", exitOnPush));
    addWidget(Button2 = new PushButton(100, 30, 60, 25, "Reset"));
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            addWidget(new TicTacToeBox(100 + j*15, 100 + i*15, 15, 15));
        }
    }
}

void GameMasterNew::checkWinner(std::vector<Widget*> widgets0, int currentIndex)
{

}
