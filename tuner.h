#ifndef TUNER_GUARD
#define TUNER_GUARD

#include <gtkmm.h>

#include "SecondaryWindow.h"

#include "sound.h"
#include "note.h"



class Tuner : public SecondaryWindow, public Sound
{
    public:

        Tuner();

            //overriding from SecondaryWindow (so that it starts playing from the start)
        virtual void open();



        void setNoteFrequency (double frequency);


        void play();


        void loadConfigurations ();


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



            //note chosen from the RadioButton's
        Note note_var;

            //note chosen on the SpinButton (changing the sound frequency)
        Note freeNote_var;


            // :::: Layout elements :::: //

        Gtk::Table container_gui;

            Gtk::HBox notesContainer_gui;

                Gtk::RadioButton a_gui;
                Gtk::RadioButton a_plus_gui;
                Gtk::RadioButton b_gui;
                Gtk::RadioButton c_gui;
                Gtk::RadioButton c_plus_gui;
                Gtk::RadioButton d_gui;
                Gtk::RadioButton d_plus_gui;
                Gtk::RadioButton e_gui;
                Gtk::RadioButton f_gui;
                Gtk::RadioButton f_plus_gui;
                Gtk::RadioButton g_gui;
                Gtk::RadioButton g_plus_gui;

            Gtk::HBox octaveContainer_gui;

                Gtk::Label octave_gui;
                Gtk::SpinButton chooseOctave_gui;

            Gtk::HBox frequencyContainer_gui;

                Gtk::Label frequency_gui;
                Gtk::SpinButton chooseFrequency_gui;
                Gtk::Label hertz_gui;

            Gtk::HBox playContainer_gui;

                Gtk::Button startPlaying_gui;
                Gtk::Button stopPlaying_gui;

};


#endif //TUNER_GUARD
