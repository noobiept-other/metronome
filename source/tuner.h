#ifndef TUNER_GUARD
#define TUNER_GUARD

#include <gtkmm.h>

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

        Gtk::Table container_ui;

            Gtk::HBox notesContainer_ui;

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

            Gtk::HBox octaveContainer_ui;

                Gtk::Label octave_ui;
                MySpinButton chooseOctave_ui;

            Gtk::HBox frequencyContainer_ui;

                Gtk::Label frequency_ui;
                MySpinButton chooseFrequency_ui;
                Gtk::Label hertz_ui;

            Gtk::HBox playContainer_ui;

                Gtk::Button startPlaying_ui;
                Gtk::Button stopPlaying_ui;

};


#endif //TUNER_GUARD
