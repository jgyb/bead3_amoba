#include "gamemasternew.hpp"
#include <iostream>


GameMasterNew::GameMasterNew(int sizeX0, int sizeY0) : Window(sizeX0, sizeY0)
{
    gameCtr();
}

void GameMasterNew::gameCtr()
{
    addWidget(Button_exit = new PushButton(30, 30, 60, 25, "Exit", exitOnPush));
    addWidget(winnerText = new StaticText(300, 20, 400, 20));
    winnerText->setText("Nyertes: ");
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            addWidget(new TicTacToeBox(200 + j*15, 75 + i*15, 15, 15));
        }
    }
}

void GameMasterNew::checkWinner(std::vector<Widget*> widgets0, int currentIndex)
{
    //124 balra keresztbe lefele
    if(widgets0[currentIndex]->player==widgets0[currentIndex-21]->player)
    {
        if(widgets0[currentIndex]->player==widgets0[currentIndex-42]->player)
        {
            if(widgets0[currentIndex]->player==widgets0[currentIndex-63]->player)
            {
                if(widgets0[currentIndex]->player==widgets0[currentIndex-84]->player)
                {
                    cout << "winner is player" << widgets0[currentIndex]->player << endl;
                }
            }
        }
    }
    //124 balra keresztben felfele
    if(widgets0[currentIndex]->player==widgets0[currentIndex+21]->player)
    {
        if(widgets0[currentIndex]->player==widgets0[currentIndex+42]->player)
        {
            if(widgets0[currentIndex]->player==widgets0[currentIndex+63]->player)
            {
                if(widgets0[currentIndex]->player==widgets0[currentIndex+84]->player)
                {
                    cout << "winner is player" << widgets0[currentIndex]->player << endl;
                }
            }
        }
    }
    // egyenesen felfele
    if(widgets0[currentIndex]->player==widgets0[currentIndex-20]->player)
    {
        if(widgets0[currentIndex]->player==widgets0[currentIndex-40]->player)
        {
            if(widgets0[currentIndex]->player==widgets0[currentIndex-60]->player)
            {
                if(widgets0[currentIndex]->player==widgets0[currentIndex-80]->player)
                {
                    cout << "winner is player" << widgets0[currentIndex]->player << endl;
                }
            }
        }
    }
    //egyenesen lefele
    if(widgets0[currentIndex]->player==widgets0[currentIndex+20]->player)
    {
        if(widgets0[currentIndex]->player==widgets0[currentIndex+40]->player)
        {
            if(widgets0[currentIndex]->player==widgets0[currentIndex+60]->player)
            {
                if(widgets0[currentIndex]->player==widgets0[currentIndex+80]->player)
                {
                    cout << "winner is player" << widgets0[currentIndex]->player << endl;
                }
            }
        }
    }

    //jobbra keresztben lefele
    if(widgets0[currentIndex]->player==widgets0[currentIndex+19]->player)
    {
        if(widgets0[currentIndex]->player==widgets0[currentIndex+38]->player)
        {
            if(widgets0[currentIndex]->player==widgets0[currentIndex+57]->player)
            {
                if(widgets0[currentIndex]->player==widgets0[currentIndex+74]->player)
                {
                    cout << "winner is player" << widgets0[currentIndex]->player << endl;
                }
            }
        }
    }

    //jobbra keresztben felfele

    if(widgets0[currentIndex]->player==widgets0[currentIndex-19]->player)
    {
        if(widgets0[currentIndex]->player==widgets0[currentIndex-38]->player)
        {
            if(widgets0[currentIndex]->player==widgets0[currentIndex-57]->player)
            {
                if(widgets0[currentIndex]->player==widgets0[currentIndex-74]->player)
                {
                    cout << "winner is player" << widgets0[currentIndex]->player << endl;
                }
            }
        }
    }

    //vízszintesen balra

    if(widgets0[currentIndex]->player==widgets0[currentIndex-1]->player)
    {
        if(widgets0[currentIndex]->player==widgets0[currentIndex-2]->player)
        {
            if(widgets0[currentIndex]->player==widgets0[currentIndex-3]->player)
            {
                if(widgets0[currentIndex]->player==widgets0[currentIndex-4]->player)
                {
                    cout << "winner is player" << widgets0[currentIndex]->player << endl;
                }
            }
        }
    }

    //vízszintesen jobbra

    if(widgets0[currentIndex]->player==widgets0[currentIndex+1]->player)
    {
        if(widgets0[currentIndex]->player==widgets0[currentIndex+2]->player)
        {
            if(widgets0[currentIndex]->player==widgets0[currentIndex+3]->player)
            {
                if(widgets0[currentIndex]->player==widgets0[currentIndex+4]->player)
                {
                    cout << "winner is player" << widgets0[currentIndex]->player << endl;
                }
            }
        }
    }
}
