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


#ifndef ANIME_WINDOW_GUARD
#define ANIME_WINDOW_GUARD

#include <gtkmm.h>


#include "SecondaryWindow.h"
#include "animation.h"



class AnimeWindow : public SecondaryWindow
{
    public:

        AnimeWindow(int bpm);


        void loadConfigurations ();


        void start();
        void start_strongBeat();


        void stop();



        void updateBpm (int bpm);


            //hmmm - isto ja existe no animation.h
        Gdk::RGBA getColor() const;

        Gdk::RGBA getStrongColor() const;

        void setColor (Gdk::RGBA newColor);

        void setStrongColor (Gdk::RGBA newColor);


    protected:

            // :::: Event functions :::: //

            //override base function
        virtual void on_hide();

        virtual bool onKeyRelease(GdkEventKey *event);

        bool animationEvents( GdkEventButton *event );

    private:


        void onColorSet();

        void onStrongColorSet();


        void fullScreen ();

        bool isFullScreen_var;

            // :::: Layout stuff :::: //


        Gtk::Table container_ui;

            Animation animation_ui;

            Gtk::Box buttonsContainer_ui;

                Gtk::Label currentBpm_ui;

                Gtk::Label normalColor_ui;
                Gtk::ColorButton selectNormalColor_ui;

                Gtk::Label strongBeatColor_ui;
                Gtk::ColorButton selectStrongColor_ui;

                Gtk::Button changeFullScreen_ui;

};




#endif //ANIME_WINDOW_GUARD
