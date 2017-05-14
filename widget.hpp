#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "graphics.hpp"
#include "colors.hpp"
#include <functional>
#include <vector>

class Widget
{
    public:
        /// Ctor
        Widget(int posX0, int posY0, unsigned int width0, unsigned int height0);

        /// Event & kirajzolas
        bool event(genv::event &ev);
        bool switchStop;
        bool selected;
        int player;
        virtual void draw() const = 0; // tiszta virtualis fuggveny, mivel az ososztaly egy peldanyat sem rajzoljuk ki

        bool hasAlreadyBeenPressed;

        /// Eger es billentyuzet esemenyei
        virtual void onMouseDown(int m_posX, int m_posY, char m_button) = 0;
        virtual void onMouseUp(int m_posX, int m_posY, char m_button) = 0;
        virtual void onMouseMove(int m_posX, int m_posY) = 0;
        virtual void onKeyDown(char keyCode) = 0;
        virtual void onKeyUp(char keyCode) = 0;
        virtual void onHold() = 0;

        int posX;
        int posY;

        unsigned int width;
        unsigned int height;

        bool show;

        std::function<void(int, int, char, Widget*)> eventOnMouseDown;

    protected:

    private:
};

//extern std::vector<Widget*> widgets;

std::string intToString(int val);

#endif // WIDGET_HPP
