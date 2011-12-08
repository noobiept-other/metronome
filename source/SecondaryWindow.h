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


#ifndef SECONDARY_WINDOW_GUARD
#define SECONDARY_WINDOW_GUARD


#include <gtkmm.h>



/*
    Used in all the windows (but the main one)

    Its a Gtk::Window plus:

        - Starts the window in the middle of the screen (sort of :p)
        - Saves the window's position, so that when reopening the window, it is moved to the previous position
        - pressing the esc key hides the window


 */

class SecondaryWindow : public Gtk::Window
{
    public:

            //if setPosition() is not called, when it will set the window in the middle of the screen
        SecondaryWindow ();


        virtual void open();

        bool isOpened() const;

            //sets the window's position (doesn't move it to that position though, call open() for that)
        void setPosition (int x, int y);

            //sets the current window's position into the x and y variables (the position of the top left corner of the window)
        void getPosition (int& x, int& y);

    protected:

            // :::: Events :::: //


            //override function, that is called when the window is hidden (or closed)
        virtual void on_hide ();


        virtual bool onKeyRelease(GdkEventKey *event);


    private:

            // :::: Variables :::: //


        bool isOpened_var;

            //position in the screen of the window (the top left corner of the window)
        int x_position_var;
        int y_position_var;

};



#endif //SECONDARY_WINDOW_GUARD
