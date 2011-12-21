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


#ifndef OPTIONS_GUARD
#define OPTIONS_GUARD


#include <gtkmm.h>

#include "SecondaryWindow.h"
#include "mySpinButton.h"

/*
    The options window - when a value is changed, we emit a signal with the value, so that
    that change can be set (on Main)
 */

class Options : public SecondaryWindow
{
    public:

        Options();

        void loadConfigurations ();



        sigc::signal<void, int> signal_onNormalFrequencyChange();
        sigc::signal<void, int> signal_onStrongFrequencyChange();

        sigc::signal<void, int> signal_onBeatDurationChange();


    protected:


        sigc::signal<void, int> the_signal_onNormalFrequencyChange;
        sigc::signal<void, int> the_signal_onStrongFrequencyChange;

        sigc::signal<void, int> the_signal_onBeatDurationChange;

    private:


            //events functions

        void onNormalFrequencyChange ();
        void onStrongFrequencyChange ();

        void onBeatDurationChange ();



            //layout stuff

        Gtk::Grid container_ui;

            Gtk::Label beatDurationLabel_ui;
            Gtk::Label normalLabel_ui;
            Gtk::Label strongLabel_ui;

            MySpinButton changeBeatDuration_ui;
            MySpinButton changeNormalFrequency_ui;
            MySpinButton changeStrongFrequency_ui;

            Gtk::Label milisecondsLabel_ui;
            Gtk::Label normalHz_ui;
            Gtk::Label strongHz_ui;


};



#endif //OPTIONS_GUARD
