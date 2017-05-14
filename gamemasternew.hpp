#ifndef GAMEMASTERNEW_HPP
#define GAMEMASTERNEW_HPP

#include "window.hpp"


class GameMasterNew : public Window
{
    public:
        GameMasterNew(int sizeX0, int sizeY0);

        virtual void checkWinner(std::vector<Widget*> widgets0, int currentIndex);

        ///Jatek elemei
        PushButton* Button_exit;
        PushButton* Button2;
        TicTacToeBox* Box1;

    protected:
        void gameCtr();

    private:
};

void exitOnPush(int posX, int posY, char button, Widget* I);

#endif // GAMEMASTERNEW_HPP
