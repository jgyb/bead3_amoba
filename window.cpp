#include "window.hpp"

int screenSizeX = 0, screenSizeY = 0;
const unsigned int t = 40;

using namespace genv;

Window::Window(int sizeX0, int sizeY0)
{
    screenSizeX = sizeX0;
    screenSizeY = sizeY0;
    index = 0;
    gout.open(screenSizeX, screenSizeY);
}

void Window::run_loop()
{
    event ev;
    gin.timer(t);

    shutDownByEscape = false;
    shutDownByStop = false;

    while(gin >> ev && !shutDownByEscape && !shutDownByStop)
    {
        screenClear();

        if (ev.type == ev_key && handleKeys(ev))
        {
            continue;
        }

        for (unsigned int i = 0; i < widgets.size(); i++)
        {
            widgets[i]->draw();
        }

        for (int i = widgets.size()-1; i >= 0; i--)
        {
            if (widgets[i]->event(ev))
            {
                setSelection(i);
                break;
            }
        }

        gout << refresh;
    }
}

void Window::stop()
{
    shutDownByStop == true;
}

void Window::addWidget(Widget *anotherWidget)
{
    widgets.push_back(anotherWidget);
}

void Window::setShutDownByEscape(bool val)
{
    shutDownByEscape = val;
}

void Window::screenClear()
{
    setColor(background);
    gout << move_to(0,0)
         << box(screenSizeX, screenSizeY);
}

bool Window::handleKeys(event &ev)
{
    if(ev.keycode == key_escape)
    {
        shutDownByEscape = true;
        return true;
    }

    if (ev.keycode == key_tab)
    {
        selectNext();
        return true;
    }
//    else if (ev.keycode == key_f3)
//    {
//        ofstream save("save.txt");
//        save << scrollBar1->getValue() << endl;
//        save << scrollBar2->getValue() << endl << endl;
//        for (unsigned int i = 0; i < menuBox1->getPieceByList(); i++)
//        {
//            save << menuBox1->getItem(i) << endl;
//        }
//        save << endl;
//        for (unsigned int i = 0; i < menuBox2->getPieceByList(); i++)
//        {
//            save << menuBox2->getItem(i) << endl;
//        }
//    }
    return false;
}

void Window::selectNext()
{
    widgets[index]->selected = false;
    while(!widgets[(++index %= widgets.size())]->switchStop)
    {
        if (index > widgets.size() * 2)
        {
            return;
        }
    }
    widgets[index]->selected = true;
};

bool Window::setSelection(int newSelection)
{
    if (!widgets[newSelection]->switchStop)
    {
        return false;
    }
    widgets[index]->selected = false;
    widgets[newSelection]->selected = true;


    if(index!=newSelection && !widgets[newSelection]->hasAlreadyBeenPressed)
    {
        widgets[newSelection]->player = (currentPlayer==1?1:0);
        currentPlayer=(currentPlayer==1?0:1);
        checkWinner(widgets, newSelection);
    }

    index = newSelection;

    return true;
}
