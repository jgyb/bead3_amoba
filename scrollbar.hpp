#ifndef SCROLLBAR_HPP
#define SCROLLBAR_HPP

#include "widget.hpp"

enum scrollBarAlignment
{
    vertical = 0,
    horizontal = 1

};

class ScrollBar : public Widget
{
    public:
        ScrollBar(int posX0, int posY0, unsigned int length, scrollBarAlignment align, int minValue, int maxValue);

        ///Getters, setters

        int getMinValue() const;
        int getMaxValue() const;

        int getValueRange() const;
        int getNumericRange() const;

        int getValue() const;
        void setValue(int newValue);

        void setRange(int minValue0, int maxValue0);

        void setValueRange(int newValue);

        /// Eger es billentyuzet esemenyei
        virtual void onMouseDown(int m_posX, int m_posY, char m_button);
        virtual void onMouseUp(int m_posX, int m_posY, char m_button);
        virtual void onMouseMove(int m_posX, int m_posY);

        virtual void onKeyDown(char keyCode);
        virtual void onKeyUp(char keyCode);

        virtual void onHold();

        virtual void draw() const;

    protected:
        int value;
        int maxValue;
        int minValue;
        int valueRange;
        scrollBarAlignment align;

    private:
        char mousePressed;
        char keyPressed;

        int previousPosition;
        int previousValue;

        bool waitToScroll;
        const int waitToScrollInterval = 500;
        int waitToScrollCounter;

        const unsigned int thickness = 20;

        double graphicalRange;
        double numericRange;

        unsigned int scrollRectangleLength;
        unsigned int scrollRectanglePos;

};

#endif // SCROLLBAR_HPP
