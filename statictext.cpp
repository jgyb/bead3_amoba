#include "statictext.hpp"
#include "graphics.hpp"

using namespace genv;

int StaticText::id;

void StaticText::StaticTextVarInit()
{
    id++;

    marginBySide = 10;
    marginByTop = 7;

    show = true;
    doAutoSize = false;
    hasBackground = false;
    switchStop = false;
    shouldTrimEnd = false;

    fontColor = Colors(black);
    fontBackgroundColor = Colors(white);

    pos = t_left;
}

StaticText::StaticText(int posX0, int posY0, unsigned int width0, unsigned int height0) : Widget(posX0, posY0, width0, height0)
{
    StaticTextVarInit();
    setText("Label" + intToString(id));
}

StaticText::StaticText(int posX0, int posY0, unsigned int width0, unsigned int height0, string text0) : Widget(posX0, posY0, width0, height0)
{
    StaticTextVarInit();
    setText(text0);
}


/// Getters, setters

string StaticText::getText() const
{
    return Text;
}

void StaticText::setText(string text0)
{
    Text = text0;
    displayedText = text0;

    if(doAutoSize)
    {
        width = marginBySide * 2 + gout.twidth(text0);
    }
    else if(marginBySide * 2 + gout.twidth(text0) > width)
    {
        if(shouldTrimEnd)
        {
            for (unsigned int i = text0.length()-1; i > 0 ; i--)
            {
                displayedText = "..." + text0.substr(i, text0.length());
                if (width < marginBySide * 2 + gout.twidth(displayedText) + 4)
                {
                    break;
                }
            }
        }
        else
        {
            for (unsigned int i = text0.length()-1; i > 0 ; i--)
            {
                displayedText = text0.substr(0,i) + "...";
                if (width > marginBySide + gout.twidth(displayedText) + 4)
                {
                   break;
                }
            }
        }
    }
}

void StaticText::setMargins(int newMarginBySide, int newMarginByTop)
{
    marginBySide = newMarginBySide;
    marginByTop = newMarginByTop;
}

void StaticText::StaticTextDraw() const
{
    if(hasBackground)
    {
        setColor(fontBackgroundColor);
        gout << move_to(posX, posY) << box(width, height);
    }

    setColor(fontColor);

    if(pos == t_left)
    {
        gout << move_to(posX + marginBySide, posY + marginByTop + gout.cascent())
        << text(displayedText);
    }
    else if (pos == t_middle)
    {
        gout << move_to(posX + (width - gout.twidth(displayedText))/2, posY + marginByTop + gout.cascent())
        << text(displayedText);
    }
    else if (pos == t_right)
    {
        gout << move_to(posX + width - gout.twidth(displayedText)  - marginBySide, posY + marginByTop + gout.cascent())
        << text(displayedText);
    }

}

void StaticText::draw() const
{
    if(show)
    {
        StaticTextDraw();
    }
}
