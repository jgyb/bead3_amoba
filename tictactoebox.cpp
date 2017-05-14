#include "tictactoebox.hpp"

TicTacToeBox::TicTacToeBox(int posX0, int posY0, unsigned int width0, unsigned int height0) : Widget(posX0, posY0, width0, height0)
{
    currentStatus = unused;
    switchStop = true;
    hasAlreadyBeenPressed = false;
}

TicTacToeBox::TicTacToeBox(int posX0, int posY0, unsigned int width0, unsigned int height0, std::function<void(int, int, char, Widget*)> func0) : Widget(posX0, posY0, width0, height0)
{
    currentStatus = unused;
    switchStop = true;
    hasAlreadyBeenPressed = false;
    eventOnMouseDown = func0;
}

void drawBox(int posX, int posY, int width, int height, Colors color1, Colors color2)
{
    setColor(color1);

    genv::gout
            << genv::move_to(posX, posY + height)
            << genv::line(0, -height - 1)
            << genv::line(width, 0);

    setColor(color2);

    genv::gout
            << genv::line(0, height + 1)
            << genv::line(-width, 0);
}

void TicTacToeBox::draw() const
{
    if(!show)
    {
        return;
    }

    setColor(white);
    genv::gout
            << genv::move_to(posX + boxPosX, posY + boxPosY)
            << genv::box(boxWidth, boxHeight);

    drawBox(posX, posY, width, height, buttonClicked, white);

    if(currentStatus == cross)
    {
        if(player==1){
            setColor(red);
        }
        else{
            setColor(blue);
        }
        genv::gout
                << genv::move_to(posX + boxPosX + 1, posY + boxPosY + 1)
                << genv::line(boxWidth - 2, boxHeight - 2);

        genv::gout
                << genv::move_to(posX + boxPosX + 1, posY + boxPosY + boxHeight - 2)
                << genv::line(boxWidth - 2, -boxHeight + 2);
    }
}

void TicTacToeBox::onMouseUp(int posX, int posY, char button)
{
    if(!hasAlreadyBeenPressed)
    {
        currentStatus = cross;
        hasAlreadyBeenPressed = true;
    }
}
