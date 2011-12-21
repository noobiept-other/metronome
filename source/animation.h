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


#ifndef ANIMATION_GUARD
#define ANIMATION_GUARD

#include <gtkmm.h>


class Animation : public Gtk::DrawingArea
{
    public:

        Animation();

            //starts the animation
        void start();

            //starts with the alternate color (for the strong beats)
        void start_strongBeat();

            //ends it
        void stop();


        Gdk::RGBA getColor() const;

        Gdk::RGBA getStrongColor() const;


        void setColor (Gdk::RGBA newColor);

            //values from 0 to 1
        void setColor (int red, int green, int blue, int alpha);


        void setStrongColor (Gdk::RGBA newColor);


    protected:


        virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);


    private:


        void forceReDraw();

            //when we're on the tempo, change to this color
        Gdk::RGBA activeColor_var;

            //or this, when its the strong beat
        Gdk::RGBA strongBeatColor_var;

            //otherwise, just draw the black color
        const Gdk::RGBA black_var;

        Gdk::RGBA tempColor_var;

};



#endif //ANIMATION_GUARD
