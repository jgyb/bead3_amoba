#include "graphics.hpp"

#include "pushbutton.hpp"


void PushButton::pushButtonCtor()
{
    hasBackground = true;
    fontBackgroundColor = button;
    clicked = false;
    switchStop = true;
}

PushButton::PushButton(int posX0, int posY0, unsigned int width0, unsigned int height0, string text0, std::function<void(int, int, char, Widget*)> func0) : StaticText(posX0, posY0, width0, height0, text0)
{
    pushButtonCtor();
    eventOnMouseDown = func0;
}

PushButton::PushButton(int posX0, int posY0, unsigned int width0, unsigned int height0, string text0) : StaticText(posX0, posY0, width0, height0, text0)
{
    pushButtonCtor();
}

PushButton::PushButton(int posX0, int posY0, unsigned int width0, unsigned int height0) : StaticText(posX0, posY0, width0, height0)
{
    pushButtonCtor();
}

void drawButton(int posX, int posY, int width, int height, Colors color1, Colors color2)
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

void PushButton::draw() const
{
    StaticTextDraw();

    if(!clicked)
    {
        drawButton(posX, posY, width, height, white, buttonClicked);
    }
    else
    {
        drawButton(posX, posY, width, height, buttonClicked, white);
    }

}

void PushButton::onMouseDown(int posX, int posY, char button)
{
    clicked = true;
}

void PushButton::onMouseUp(int posX, int posY, char button)
{
    clicked = false;
}
