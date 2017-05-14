#ifndef MENUBOX_HPP
#define MENUBOX_HPP

#include "widget.hpp"
#include <vector>
#include "statictext.hpp"
#include "scrollbar.hpp"

using namespace std;

class MenuBox : public Widget
{
    public:
        MenuBox(int posX0, int posY0, unsigned int width0, unsigned int height0, vector<string> menuItems0);
        ~MenuBox();

        /// Getters, setters

        int getPieceByList();


        string getItem(unsigned int itemFromList);
//        void addItemToList(string newItem);

        int getIndex();
        bool setIndex(unsigned int newIndex);

        /// Eger es billentyuzet esemenyei
        virtual void onMouseDown(int m_posX, int m_posY, char m_button);
        virtual void onMouseUp(int m_posX, int m_posY, char m_button);
        virtual void onMouseMove(int m_posX, int m_posY);

        virtual void onKeyDown(char keyCode);
        virtual void onKeyUp(char keyCode);

        virtual void onHold();

        virtual void draw() const;


    protected:
        ScrollBar *listScrollBar;
        unsigned int indexOfList;
        vector<StaticText*> itemList;

    private:
        static int id;
        const unsigned int itemHeight = 20;

        bool waitToScroll;
        const int waitToScrollInterval = 500;
        int waitToScrollCounter;

        char keyPressed;
};

#endif // MENUBOX_HPP
