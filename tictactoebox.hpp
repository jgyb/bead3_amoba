#ifndef TICTACTOEBOX_HPP
#define TICTACTOEBOX_HPP

#include "widget.hpp"

enum boxStatus
{
    empty,
    cross,
    circle
};

class TicTacToeBox : public Widget
{
    public:
        boxStatus status;

        TicTacToeBox(int posX0, int posY0, unsigned int width0, unsigned int height0, std::function<void(int, int, char, Widget*)> func0);
        TicTacToeBox(int posX0, int posY0, unsigned int width0, unsigned int height0);
        void draw() const;

        virtual void onMouseDown(int posX, int posY, char button);
        virtual void onMouseUp(int posX, int posY, char button) {}
        virtual void onMouseMove(int posX, int posY) {}
        virtual void onKeyDown(char keyCode) {}
        virtual void onKeyUp(char keyCode) {}
        virtual void onHold() {}

    protected:

    private:
        const int boxWidth = 25, boxHeight = 25;
        const int boxPosX = 2, boxPosY = 2;
};

void drawBox(int posX, int posY, int width, int height, Colors color1, Colors color2);

#endif // TICTACTOEBOX_HPP
