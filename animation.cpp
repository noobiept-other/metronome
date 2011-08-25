#include "animation.h"


Animation::Animation()

    : black ("black")

{
    //default: blue color
activeColor.set_rgba(0, 0, 1, 1);

strongBeatColor.set_rgba(1, 0, 1, 1);   //HERE

tempColor.set_rgba(0, 0, 0, 1);
}



void Animation::start ()
{
tempColor = activeColor;

forceReDraw();
}



void Animation::start_strongBeat()
{
tempColor = strongBeatColor;

forceReDraw();
}




void Animation::stop ()
{
tempColor = black;

forceReDraw();
}



bool Animation::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
Gtk::Allocation allocation = get_allocation();

const int width = allocation.get_width();
const int height = allocation.get_height();


//cor : .set_source_rgba()
//gravar : save() e restore()

//parar desenhar: stroke() ou fill() ou clip()

//.rectangle()

cr->set_source_rgba(tempColor.get_red(), tempColor.get_green(), tempColor.get_blue(), tempColor.get_alpha());

cr->rectangle(0, 0, width, height);

cr->fill();


return true;
}



void Animation::forceReDraw()
{
    // force our program to redraw the entire image
Glib::RefPtr<Gdk::Window> win = get_window();

if (win)
    {
    Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
    win->invalidate_rect(r, false);
    }
}



Gdk::RGBA Animation::getColor() const
{
return activeColor;
}



Gdk::RGBA Animation::getStrongColor() const
{
return strongBeatColor;
}




void Animation::setColor (Gdk::RGBA newColor)
{
activeColor = newColor;
}


void Animation::setColor (int red, int green, int blue, int alpha)
{
activeColor.set_rgba(red, green, blue, alpha);
}


void Animation::setStrongColor (Gdk::RGBA newColor)
{
strongBeatColor = newColor;
}
