#ifndef COLORS_HPP_INCLUDED
#define COLORS_HPP_INCLUDED

struct Colors
{
    int R, G, B;

    Colors();
    Colors(int R0, int G0, int B0);
    Colors(const Colors &color);

};


//alapveto szinek

const Colors black = Colors(0, 0, 0);
const Colors white = Colors(255, 255, 255);
const Colors red = Colors(255, 0, 0);
const Colors blue = Colors(0, 0, 255);
const Colors highlighted = Colors(11, 83, 198);
const Colors nonHighlighted = Colors(175, 204, 255);
const Colors background = Colors(68, 74, 84);
const Colors button = Colors(249, 249, 249);
const Colors buttonClicked = Colors(107, 112, 119);

void drawEmptyBox(int posX, int posY, int width, int height);
void setColor(const Colors &newColor);


#endif // COLORS_HPP_INCLUDED
