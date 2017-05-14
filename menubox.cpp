#include "graphics.hpp"

#include "menubox.hpp"
#include "window.hpp"

using namespace std;
using namespace genv;

int MenuBox::id;

enum action
{
    nill,
    valueIncrease,
    valueDecrease
};

MenuBox::MenuBox(int posX0, int posY0, unsigned int width0, unsigned int height0, vector<string> menuItems0) :Widget(posX0, posY0, width0, height0)
{
    id++;

    height -= height % itemHeight;
    switchStop = true;

    listScrollBar = new ScrollBar(posX + width, posY, height, vertical, 0, menuItems0.size());
    listScrollBar-> posX -= listScrollBar->width;

    listScrollBar->setValueRange(height / itemHeight);

    for (unsigned int i = 0; i < menuItems0.size(); i++)
    {
        if(listScrollBar->show)
        {
            itemList.push_back(new StaticText(posX, posY, width - listScrollBar->width, itemHeight, menuItems0[i]));
        }
        else
        {
            itemList.push_back(new StaticText(posX, posY, width, itemHeight, menuItems0[i]));
        }
        itemList[i]->setMargins(5, 0);
        itemList[i]->hasBackground = true;
    }

    indexOfList = 0;
}
MenuBox::~MenuBox()
{
    for (unsigned int i = 0; i < itemList.size(); i++)
    {
        delete itemList[i];
    }
    delete listScrollBar;
}

/// Getters, setters

string MenuBox::getItem(unsigned int itemFromList)
{
    return itemList[itemFromList]->getText();
}

int MenuBox::getPieceByList()
{
    return itemList.size();
}

int MenuBox::getIndex()
{
    return indexOfList;
}

bool MenuBox::setIndex(unsigned int newValue)
{
    if(itemList.size() > newValue)
    {
        indexOfList = newValue;
        return true;
    }
    else
    {
        indexOfList = itemList.size() - 1;
        return false;
    }
}

/// Eger es bill

void MenuBox::onMouseDown(int m_posX, int m_posY, char m_button)
{
    if (listScrollBar->posX <= m_posX
            && m_posX <= listScrollBar->posX + listScrollBar->width
            && listScrollBar->posY <= m_posY
            && posY <= listScrollBar->posY + listScrollBar->height)
    {
        listScrollBar->onMouseDown(m_posX, m_posY, m_button);
    }

    if(posX + width + listScrollBar->width > m_posX || !listScrollBar->show)
    {
        for (unsigned int i = 0; i < itemList.size(); i++)
        {
            if (itemList[i]->show && itemList[i]->posY < m_posY && m_posY < itemList[i]->posY + itemHeight)
            {
                indexOfList = i;
                break;
            }
        }
    }
}

void MenuBox::onMouseUp(int m_posX, int m_posY, char m_button)
{
    listScrollBar->onMouseUp(m_posX, m_posY, m_button);
}

void MenuBox::onMouseMove(int m_posX, int m_posY)
{
    if (listScrollBar->posX <= m_posX && m_posX <= listScrollBar->posX + listScrollBar->width &&
            listScrollBar->posY <= m_posY && m_posY <= listScrollBar->posY + listScrollBar->height)
        listScrollBar->onMouseMove(m_posX, m_posY);
}

void MenuBox::onKeyDown(char keyCode)
{

    if(keyCode == (char)key_pgup)
    {
        indexOfList = 0;
        if (listScrollBar->getValue()) listScrollBar->setValue(0);
    }
    else if(keyCode == (char)key_pgdn)
    {
        indexOfList = itemList.size() - 1;
        if (listScrollBar->getValue() < listScrollBar->getMaxValue() - listScrollBar->getValueRange())
        {
            listScrollBar->setValue(listScrollBar->getMaxValue() - listScrollBar->getValueRange());
        }
    }
    else if(keyCode == (char)key_up)
    {
        if (0 < indexOfList)
        {
            indexOfList--;
        }
        if (indexOfList < listScrollBar->getValue()) listScrollBar->setValue(listScrollBar->getValue() - 1);
        {
            keyPressed = valueDecrease;
            waitToScrollCounter = 0;
        }
    }
    else if(keyCode == (char)key_down)
    {
        if (indexOfList < itemList.size() - 1)
        {
            indexOfList++;
        }
        if (listScrollBar->getValue() + listScrollBar->getValueRange() <= indexOfList)
        {
            listScrollBar->setValue(listScrollBar->getValue() + 1);
            keyPressed = valueIncrease;
            waitToScrollCounter = 0;
        }
    }
}
void MenuBox::onKeyUp(char keyCode)
{
    keyPressed = nill;
}

void MenuBox::onHold()
{
    listScrollBar->onHold();

    if(waitToScrollInterval > waitToScrollCounter * t)
    {
        waitToScrollCounter += 1;
    }
    else
    {
        if(keyPressed == valueIncrease)
        {
            if (indexOfList < itemList.size() - 1)
            {
                indexOfList++;
            }
            if (listScrollBar->getValue() + listScrollBar->getValueRange() <= indexOfList)
            {
                listScrollBar->setValue(listScrollBar->getValue() + 1);
            }
        }
        else if(keyPressed == valueDecrease)
        {
            if (indexOfList > 0)
            {
                indexOfList--;
                if (indexOfList < listScrollBar->getValue())
                {
                    listScrollBar->setValue(listScrollBar->getValue() - 1);
                }
            }
        }
    }

}





void MenuBox::draw() const
{
    if(!show)
    {
        return;
    }

    setColor(white);
    gout << move_to(posX, posY) << box(width, height);

    if(listScrollBar->show)
    {
        for (unsigned int i = 0; i < listScrollBar->getValue(); i++)
        {
            itemList[i]->show = false;
        }

        for (unsigned int i = listScrollBar->getValue(); i < listScrollBar->getValue() + listScrollBar->getValueRange(); i++)
        {
            if (indexOfList == i && show)
            {
                itemList[i]->fontBackgroundColor = Colors(highlighted);
            }
            else if (indexOfList == i)
            {
                itemList[i]->fontBackgroundColor = Colors(nonHighlighted);
            }
            else
            {
                itemList[i]->fontBackgroundColor = Colors(white);
            }
            itemList[i]->posY = posY + (i - listScrollBar->getValue())*itemHeight;
            itemList[i]->draw();
            itemList[i]->show = true;
        }

        for (unsigned int i = listScrollBar->getValue() + listScrollBar->getValueRange(); i < itemList.size(); i++)
        {
            itemList[i]->show = false;
        }
    }
    else
    {
        for (unsigned int i = 0; i < itemList.size(); i++)
        {
            if (indexOfList == i && show)
            {
                itemList[i]->fontBackgroundColor = Colors(highlighted);
            }
            else if (indexOfList == i)
            {
                itemList[i]->fontBackgroundColor = Colors(nonHighlighted);
            }
            else
            {
                itemList[i]->fontBackgroundColor = Colors(white);
            }
            itemList[i]->posY = posY + (i - listScrollBar->getValue())*itemHeight;
            itemList[i]->draw();
            itemList[i]->show = true;
        }
    }
        drawEmptyBox(posX, posY, width, height);
        listScrollBar->draw();
}
