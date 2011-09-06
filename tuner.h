#ifndef TUNER_GUARD
#define TUNER_GUARD

#include <gtkmm.h>

#include "SecondaryWindow.h"

#include "sound.h"
#include "note.h"


#include <iostream>

using std::cout;
using std::endl;

#include "configurations.h"

extern Configurations CONFIGURATIONS;


class Tuner : public SecondaryWindow
{
    public:

        Tuner();

        virtual void open();


        bool isPlaying () const;


        void setNoteFrequency (double frequency);
        double getNoteFrequency () const;

        void play();

        void stop();


        void loadConfigurations ();

    protected:

            //when the window is closed
        virtual void onHide();

   //     sigc::signal<void> the_signal_onTunerHide;




    private:

            //private functions



        //void calculateFrequency (std::string note, int octave);

            //only changes the note (not the octave - it keeps whatever value it has)
        void changeNote (std::string noteLetter);


            // :::: events :::: //



        void onOctaveChange();

        void onFrequencyChange();


     //   bool onKeyRelease(GdkEventKey *event);


            //variables

      //  bool isOpened_obj;



        Note note;

        Sound sound;


     //   Gtk::Window window;

            //layout elements

        Gtk::Table container;

            Gtk::HBox notesContainer;

                Gtk::RadioButton a;
                Gtk::RadioButton a_plus;
                Gtk::RadioButton b;  //HERE devia ser ToggleButton ?..
                Gtk::RadioButton c;
                Gtk::RadioButton c_plus;
                Gtk::RadioButton d;
                Gtk::RadioButton d_plus;
                Gtk::RadioButton e;
                Gtk::RadioButton f;
                Gtk::RadioButton f_plus;
                Gtk::RadioButton g;
                Gtk::RadioButton g_plus;

            Gtk::HBox octaveContainer;

                Gtk::Label octave;
                Gtk::SpinButton chooseOctave;

            Gtk::HBox frequencyContainer;

                Gtk::Label frequency;
                Gtk::SpinButton chooseFrequency;
                Gtk::Label hertz;

            Gtk::HBox playContainer;

                Gtk::Button startPlaying;   //HERE ter algo k mostre k a variavel tem a ver com o layout (no nome)
                Gtk::Button stopPlaying;



};


#endif //TUNER_GUARD
