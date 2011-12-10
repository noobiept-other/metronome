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


#ifndef TUNER_GUARD
#define TUNER_GUARD

#include <gtkmm.h>

#include <sstream>

#include "SecondaryWindow.h"
#include "mySpinButton.h"

#include "sound.h"
#include "note.h"



class Tuner : public SecondaryWindow, public Sound
{
    public:

        Tuner();


            //overriding from SecondaryWindow (so that it starts playing from the start)
        virtual void open();



        void setNote( double frequency, bool updateUi );
        void setNote( std::string noteName, int octave, bool updateUi );
        void setNote( int notePosition, int octave, bool updateUi );

            //returns a string in the form: "noteName octave" or an empty string if it isn't a named note
        std::string getNote();


            //changes the arguments value to have the current note that is set
            //is it isn't a named note, when it will have negative values
        void getNote( int* notePosition, int* octave );


        void play();



    protected:

            //when the window is closed (override base function)
        virtual void on_hide();



    private:

            // :::: signals :::: //


        sigc::connection chooseFrequency_connection;


            // :::: events :::: //

            //only changes the note (not the octave - it keeps whatever value it has)
        void changeNote (std::string noteLetter);

        void onOctaveChange();

        void onFrequencyChange();


            //when updating the ui, it may trigger unwanted events
            //so we set this variable to true before changing stuff (and to false after)
        bool cancelEvents_var;


            //note chosen from the RadioButton's
        Note note_var;


            // :::: Layout elements :::: //

        Gtk::Table container_ui;

            Gtk::Box notesContainer_ui;

                Gtk::RadioButton a_ui;
                Gtk::RadioButton a_plus_ui;
                Gtk::RadioButton b_ui;
                Gtk::RadioButton c_ui;
                Gtk::RadioButton c_plus_ui;
                Gtk::RadioButton d_ui;
                Gtk::RadioButton d_plus_ui;
                Gtk::RadioButton e_ui;
                Gtk::RadioButton f_ui;
                Gtk::RadioButton f_plus_ui;
                Gtk::RadioButton g_ui;
                Gtk::RadioButton g_plus_ui;

            Gtk::Box octaveContainer_ui;

                Gtk::Label octave_ui;
                MySpinButton chooseOctave_ui;

            Gtk::Box frequencyContainer_ui;

                Gtk::Label frequency_ui;
                MySpinButton chooseFrequency_ui;
                Gtk::Label hertz_ui;

            Gtk::Box playContainer_ui;

                Gtk::Button startPlaying_ui;
                Gtk::Button stopPlaying_ui;

};


#endif //TUNER_GUARD
