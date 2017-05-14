#ifndef STATICTEXT_HPP
#define STATICTEXT_HPP

#include "widget.hpp"

using namespace std;

enum textPosition
{
    t_left = 0,
    t_middle = 1,
    t_right = 2
};

class StaticText : public Widget
{
    public:
        int marginBySide, marginByTop;
        textPosition pos;

        bool hasBackground;
        bool doAutoSize;
        bool shouldTrimEnd;

        Colors fontColor;
        Colors fontBackgroundColor;

        StaticText(int posX0, int posY0, unsigned int width0, unsigned int height0);
        StaticText(int posX0, int posY0, unsigned int width0, unsigned int height0, string text0);

        string getText() const;
        void setText(string text0);
        void setMargins(int newMarginBySide, int newMarginByTop);

        virtual void draw() const;


        /// Absztrakcio megszuntetes miatt

        virtual void onMouseDown(int posX, int posY, char button) {}
        virtual void onMouseUp(int posX, int posY, char button) {}
        virtual void onMouseMove(int posX, int posY) {}
        virtual void onKeyDown(char keyCode) {}
        virtual void onKeyUp(char keyCode) {}
        virtual void onHold() {}

    protected:
        string Text;
        string displayedText;

        void StaticTextVarInit();
        void StaticTextDraw() const;

    private:
        static int id;
};

#endif // STATICTEXT_HPP
