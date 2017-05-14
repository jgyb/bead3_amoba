#ifndef PUSHBUTTON_HPP
#define PUSHBUTTON_HPP

#include "statictext.hpp"


class PushButton : public StaticText
{
    public:
        PushButton(int posX0, int posY0, unsigned int width0, unsigned int height0, string text0, std::function<void(int, int, char, Widget*)> func0);
        PushButton(int posX0, int posY0, unsigned int width0, unsigned int height0, string text0);
        PushButton(int posX0, int posY0, unsigned int width0, unsigned int height0);

        virtual void draw() const;

        virtual void onMouseDown(int posX, int posY, char button);
        virtual void onMouseUp(int posX, int posY, char button);
        virtual void onMouseMove(int posX, int posY) {}
        virtual void onKeyDown(char keyCode) {}
        virtual void onKeyUp(char keyCode) {}
        virtual void onHold() {}

    protected:
        std::string label;

        bool clicked;

        void pushButtonCtor();

    private:
};

void drawButton(int posX, int posY, int width, int height, Colors color1, Colors color2);

#endif // PUSHBUTTON_HPP
