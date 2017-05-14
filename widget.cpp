#include "widget.hpp"

/// Ctor
Widget::Widget(int posX0, int posY0, unsigned int width0, unsigned int height0)
{
    posX = posX0;
    posY = posY0;
    width = width0;
    height = height0;
    selected = false;
    show = true;
    eventOnMouseDown = [] (int posX, int posY, char button, Widget*) {} ;
}
///

bool Widget::event(genv::event &ev)
{
    if (!show)
    {
        return false;
    }
    // mindaddig megkapja az eventet ameg ki van rajzolva
    if (selected && ev.type == genv::ev_mouse && ev.button < 0)
    {
        onMouseUp(ev.pos_x, ev.pos_y, -ev.button);
        return true;
    }
    else if (ev.type == genv::ev_mouse
             && posX <= ev.pos_x
             && ev.pos_x <= posX + width
             && posY <= ev.pos_y
             && ev.pos_y <= posY + height)
    {
        if (ev.button == 0)
        {
            onMouseMove(ev.pos_x, ev.pos_y);
            return false;
        }
        else if (ev.button > 0)
        {
            onMouseDown(ev.pos_x, ev.pos_y, ev.button);
            eventOnMouseDown(posX - ev.pos_x, posY - ev.pos_y, ev.button, this);
        }
        return true;
    }
    else if (selected && ev.type == genv::ev_key)
    {
        if (ev.keycode < 0)
        {
            onKeyUp(-ev.keycode);
        }
        if (ev.keycode > 0)
        {
            onKeyDown(ev.keycode);
        }
        return true;
    }
    else if (ev.type == genv::ev_timer)
    {
        onHold();
        return false;
    }
    return false;
}

#include <sstream>

std::string intToString(int val)
{
    std::string out;
    std::stringstream ss;
    ss << val;
    ss >> out;
    return out;
}
