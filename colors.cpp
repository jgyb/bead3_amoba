#include "colors.hpp"
#include "graphics.hpp"

using namespace genv;

Colors::Colors()
{
    R = G = B = 0;
}
Colors::Colors(int R0, int G0, int B0)
{
    R = R0;
    G = G0;
    B = B0;
}
Colors::Colors(const Colors &newColor)
{
    R = newColor.R;
    G = newColor.G;
    B = newColor.B;
}
void setColor(const Colors &newColor)
{
    gout << color(newColor.R, newColor.G, newColor.B);
}
void drawEmptyBox(int posX, int posY, int width, int height)
{
    setColor(black);
    gout << move_to(posX, posY)
    << line(width, 0)
    << genv::line(0, height)
    << genv::line(-width,0)
    << genv::line(0, -height);
}
