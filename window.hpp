#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "graphics.hpp"
#include <vector>
#include <fstream>

#include "widget.hpp"
#include "colors.hpp"
#include "statictext.hpp"
#include "pushbutton.hpp"
#include "tictactoebox.hpp"

extern int screenSizeX; //= 800;
extern int screenSizeY; //= 600;
extern const unsigned int t;

class Window
{
    public:
        Window(int sizeX0, int sizeY0);

        void run_loop();
        void stop();

        void addWidget(Widget *anotherWidget);
        void setShutDownByEscape(bool val);

        virtual void checkWinner(std::vector<Widget*> widgets0, int currentIndex) = 0;

    protected:
        bool shutDownByEscape;
        bool shutDownByStop;

        unsigned int index;
        int currentPlayer=0;
        std::vector<Widget*> widgets;

        void screenClear();
        bool handleKeys(genv::event &ev);
        void selectNext();
        bool setSelection(int newSelection);



    private:
};

#endif // WINDOW_HPP
