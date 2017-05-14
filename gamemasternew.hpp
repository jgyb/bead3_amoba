#ifndef GAMEMASTERNEW_HPP
#define GAMEMASTERNEW_HPP

#include "window.hpp"


class GameMasterNew : public Window
{
    public:
        GameMasterNew(int sizeX0, int sizeY0);

        ///Jatek elemei
        PushButton* Button_exit;
        TicTacToeBox* Box1;

    protected:

    private:
};

#endif // GAMEMASTERNEW_HPP
