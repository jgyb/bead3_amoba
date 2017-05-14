#include "scrollbar.hpp"
#include "graphics.hpp"
#include <math.h> // round
#include <stdlib.h> // abs

#include "colors.hpp"
#include "window.hpp"

using namespace genv;

enum action
{
    nill,
    scrollRectangleMove,
    valueIncrease,
    valueDecrease
};

/// Ctor
ScrollBar::ScrollBar(int posX0, int posY0, unsigned int length, scrollBarAlignment align0, int minValue0, int maxValue0) : Widget(posX0, posY0, 0, 0)
{
    align = align0;

    setRange(minValue0, maxValue0);
    value = minValue;
    numericRange = maxValue - minValue;

    mousePressed = nill;
    keyPressed = nill;

    switchStop = true;

    valueRange = 0;

    graphicalRange = length - 2 * thickness;

    scrollRectangleLength = graphicalRange / numericRange;

    if (scrollRectangleLength < thickness / 2)
    {
        scrollRectangleLength = thickness / 2;
    }

    scrollRectanglePos = ((value - minValue) / numericRange) * (graphicalRange - scrollRectangleLength);

    if(align == vertical)
    {
        width = thickness;
        height = length;
    }
    else if(align == horizontal)
    {
        width = length;
        height = thickness;
    }

}
///

/// Getters, Setters

int ScrollBar::getMinValue() const
{
    return minValue;
}

int ScrollBar::getMaxValue() const
{
    return maxValue;
}

int ScrollBar::getValue() const
{
    return value;
}

int ScrollBar::getValueRange() const
{
    return valueRange;
}

int ScrollBar::getNumericRange() const
{
    return numericRange;
}

void ScrollBar::setValue(int newValue)
{
    if(minValue > newValue)
    {
        value = minValue;
    }
    else if(maxValue < newValue + valueRange)
    {
        value = maxValue - valueRange;
    }
    else
    {
        value = newValue;
    }

    scrollRectanglePos = (value - minValue) * (graphicalRange - scrollRectangleLength) / (numericRange - valueRange);
}

void ScrollBar::setRange(int minValue0, int maxValue0)
{
    // Felcsereli az ertekeket ha hibasan helyre lett megadva a min es a max
    if(maxValue0 < minValue0)
    {
        int temp;
        temp = maxValue0;
        maxValue0 = minValue0;
        minValue0 = temp;
    }

    minValue = minValue0;
    maxValue = maxValue0;

    numericRange = maxValue - minValue;

    if(numericRange == 0)
    {
        numericRange = 1;
    }

    if(valueRange != 0)
    {
        scrollRectangleLength = graphicalRange / numericRange * valueRange;
    }

    else if(valueRange == 0)
    {
        scrollRectangleLength = graphicalRange / numericRange;
    }

    scrollRectanglePos = (value - minValue) * (graphicalRange - scrollRectangleLength) / (numericRange - valueRange);
}

void ScrollBar::setValueRange(int newValue)
{
    if(newValue == 0)
    {
        valueRange = 1;
    }
    else if(newValue > numericRange)
    {
        valueRange = numericRange;
    }
    else
    {
        valueRange = newValue;
    }

    if(value + valueRange > maxValue)
    {
        value = minValue;
    }

    scrollRectangleLength = (graphicalRange / numericRange) * valueRange;
}
///


/// Eger es billentyuzet esemenyei
void ScrollBar::onMouseDown(int m_posX, int m_posY, char m_button)
{
    if(align == vertical)
    {
        //rectangle
        if (posY + thickness + scrollRectanglePos < m_posY && m_posY < posY + thickness + scrollRectanglePos + scrollRectangleLength)
        {
            mousePressed = scrollRectangleMove;
            previousPosition = m_posY;
            previousValue = value;
        }


        // +
        else if (posY + height - thickness < m_posY && m_posY < posY + height)
        {
            setValue(value + 1);
            mousePressed =  valueIncrease;
            waitToScrollCounter = 0;
        }

        // -
        else if(m_posY < posY + thickness && posY < m_posY)
        {
            setValue(value - 1);
            mousePressed = valueDecrease;
            waitToScrollCounter = 0;
        }
    }
    else if (align == horizontal)
    {

        // +
        if (posX + width - thickness < m_posX && m_posX < posX + width)
        {
            setValue(value + 1);
            mousePressed = valueIncrease;
            waitToScrollCounter = 0;
        }

        // -
        else if(posX < m_posX && m_posX < posX + thickness)
        {
            setValue(value - 1);
            mousePressed = valueDecrease;
            waitToScrollCounter = 0;
        }

        else if (posX + thickness + scrollRectanglePos < m_posX && m_posX < posX + thickness + scrollRectanglePos + scrollRectangleLength)
        {
            mousePressed = scrollRectangleMove;
            previousPosition = m_posX;
            previousValue = value;
        }

    }
}

void ScrollBar::onMouseUp(int m_posX, int m_posY, char m_button)
{
    mousePressed = nill;
}

void ScrollBar::onMouseMove(int m_posX, int m_posY)
{
    if(mousePressed == scrollRectangleMove)
    {
        if(align == vertical)
        {
            setValue( previousValue + round( (m_posY - previousPosition) / (graphicalRange - scrollRectangleLength) * (numericRange - valueRange) ) );
        }
        else if(align == horizontal)
        {
            setValue( previousValue + round( (m_posX - previousPosition) / (graphicalRange - scrollRectangleLength) * (numericRange - valueRange) ) );
        }
    }
}

void ScrollBar::onKeyDown(char keyCode)
{
    if(align == vertical)
    {
        if(keyCode == (char)key_pgup)
        {
            // ha nem tud tizet lepni akkor a maximumra ugrik
            if(abs(maxValue - value) < 10)
            {
                setValue(maxValue);
            }
            else
            {
                setValue(value + 10);
                keyPressed = valueIncrease;
                waitToScrollCounter = 0;
            }
        }
        else if(keyCode == (char)key_pgdn)
        {
            // ha nem tud tizet lepni akkor a minimumra ugrik
            if(abs(minValue - value) < 10)
            {
                setValue(minValue);
            }
            else
            {
                setValue(value - 10);
                keyPressed = valueDecrease;
                waitToScrollCounter = 0;
            }
        }
        else if(keyCode == (char)key_up) //!!!
        {
            setValue(value + 1);
            keyPressed = valueIncrease;
            waitToScrollCounter = 0;
        }
        else if(keyCode == (char)key_down)
        {
            setValue(value - 1);
            keyPressed = valueDecrease;
            waitToScrollCounter = 0;
        }
    }
    else if(align == horizontal)
    {
        if(keyCode == (char)key_pgup)
        {
            // ha nem tud tizet lepni akkor a maximumra ugrik
            if(abs(maxValue - value) < 10)
            {
                setValue(maxValue);
            }
            else
            {
                setValue(value + 10);
                keyPressed = valueIncrease;
                waitToScrollCounter = 0;
            }
        }
        else if(keyCode == (char)key_pgdn)
        {
            // ha nem tud tizet lepni akkor a minimumra ugrik
            if(abs(minValue - value) < 10)
            {
                setValue(minValue);
            }
            else
            {
                setValue(value - 10);
                keyPressed = valueDecrease;
                waitToScrollCounter = 0;
            }
        }
        else if(keyCode == (char)key_right) //!!!
        {
            setValue(value + 1);
            keyPressed = valueIncrease;
            waitToScrollCounter = 0;
        }
        else if(keyCode == (char)key_left)
        {
            setValue(value - 1);
            keyPressed = valueDecrease;
            waitToScrollCounter = 0;
        }
    }


}

void ScrollBar::onKeyUp(char keyCode)
{
    keyPressed = nill;
}

// timer, modositasa eseten a main-ben is kell

void ScrollBar::onHold()
{
    if(waitToScrollInterval > waitToScrollCounter * t)
    {
        waitToScrollCounter += 1;
    }
    else
    {
        if (keyPressed == valueIncrease || mousePressed == valueIncrease)
        {
            setValue(value + 1);
        }
        else if (keyPressed == valueDecrease || mousePressed == valueDecrease)
        {
            setValue(value - 1);
        }
    }
}

enum arrows
{
    facing_up,
    facing_down,
    facing_left,
    facing_right
};

void placeArrow(int posX0, int posY0, int thickness, arrows arrowDirection)
{
    setColor(black);

    if(arrowDirection == facing_up)
    {
        gout << move_to(posX0 + thickness/3, posY0 + thickness*2/3)
        << line(thickness/3, -thickness/3)
        << line(thickness/3, thickness/3);
    }
    else if(arrowDirection == facing_down)
    {
        gout << move_to(posX0 + thickness/3, posY0 + thickness/3)
        << line(thickness/3, thickness/3)
        << line(thickness/3, -thickness/3);
    }
    else if(arrowDirection == facing_left)
    {
        gout << move_to(posX0 + thickness*2/3, posY0 + thickness/3)
        << line(-thickness/3, thickness/3)
        << line(thickness/3, thickness/3);
    }
    else if(arrowDirection == facing_right)
    {
        gout << move_to(posX0 + thickness/3, posY0 + thickness/3)
        << line(thickness/3, thickness/3)
        << line(-thickness/3, thickness/3);
    }
}

void ScrollBar::draw() const
{
    if(!show)
    {
        return;
    }

    if(selected)
    {
        setColor(highlighted);
    }
    else
    {
        setColor(button);
    }

    gout << move_to(posX,posY) << box(width, height);

    if (align == vertical)
    {
        setColor(button);

        gout << move_to(posX, posY + thickness + scrollRectanglePos)
        << box(thickness, scrollRectangleLength);

        gout << move_to(posX, posY)
        << box(thickness, thickness);

        gout << move_to(posX, posY + height - thickness)
        << box(thickness, thickness);

        drawEmptyBox(posX, posY, thickness, thickness);
        drawEmptyBox(posX, posY + height - thickness, thickness, thickness);

        placeArrow(posX, posY, thickness, facing_up);
        placeArrow(posX, posY + height - thickness, thickness, facing_down);

        drawEmptyBox(posX, posY + thickness + scrollRectanglePos, thickness, scrollRectangleLength);

    }
    else if(align == horizontal)
    {
        setColor(button);

        gout << move_to(posX + thickness + scrollRectanglePos, posY)
        << box(scrollRectangleLength, thickness);

        gout << move_to(posX, posY)
        << box(thickness, thickness);

        gout << move_to(posX + width - thickness, posY)
        << box(thickness, thickness);

        drawEmptyBox(posX, posY, thickness, thickness);
        drawEmptyBox(posX + width - thickness, posY, thickness, thickness);

        placeArrow(posX, posY, thickness, facing_left);
        placeArrow(posX + width - thickness, posY, thickness, facing_right);

        drawEmptyBox(posX + thickness + scrollRectanglePos, posY, scrollRectangleLength, thickness);

    }
}
