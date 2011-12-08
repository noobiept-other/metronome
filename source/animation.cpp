/*

	Copyright - 2011 - Pedro Ferreira

	This file is part of Metronome.

    Metronome is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Metronome is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Metronome.  If not, see <http://www.gnu.org/licenses/>.

 */


#include "animation.h"


Animation::Animation()

    : black_var ("black")

{
    //default: blue color
activeColor_var.set_rgba(0, 0, 1, 1);

    //default: red color
strongBeatColor_var.set_rgba(1, 0, 0, 1);

tempColor_var.set_rgba(0, 0, 0, 1);
}




void Animation::start ()
{
tempColor_var = activeColor_var;

forceReDraw();
}



void Animation::start_strongBeat()
{
tempColor_var = strongBeatColor_var;

forceReDraw();
}




void Animation::stop ()
{
tempColor_var = black_var;

forceReDraw();
}


/*
    Draws a rectangle with a color (whatver is in tempColor_var)
 */

bool Animation::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
Gtk::Allocation allocation = get_allocation();

const int width = allocation.get_width();
const int height = allocation.get_height();


    //set the color
cr->set_source_rgba(tempColor_var.get_red(),
                    tempColor_var.get_green(),
                    tempColor_var.get_blue(),
                    tempColor_var.get_alpha());

    //and make a rectangle, that covers the whole DrawingArea
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
return activeColor_var;
}



Gdk::RGBA Animation::getStrongColor() const
{
return strongBeatColor_var;
}




void Animation::setColor (Gdk::RGBA newColor)
{
activeColor_var = newColor;
}


void Animation::setColor (int red, int green, int blue, int alpha)
{
activeColor_var.set_rgba(red, green, blue, alpha);
}


void Animation::setStrongColor (Gdk::RGBA newColor)
{
strongBeatColor_var = newColor;
}
