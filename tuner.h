#ifndef TUNER_GUARD
#define TUNER_GUARD

#include <gtkmm.h>

#include "sound.h"
#include "note.h"


#include <iostream>

using std::cout;
using std::endl;


class Tuner //: public Gtk::Window//, public Sound
{
    public:

        Tuner();

        void open();

        bool isOpened() const;


        sigc::signal<void> signal_onTunerHide();

    protected:

            //when the window is closed
        void onTunerHide();

        sigc::signal<void> the_signal_onTunerHide;




    private:

            //private functions

        void play();

        void stop();

        //void calculateFrequency (std::string note, int octave);

            //only changes the note (not the octave - it keeps whatever value it has)
        void changeNote (std::string noteLetter);


            // :::: events :::: //



        void onOctaveChange();

        void onFrequencyChange();


            //variables

        bool isOpened_obj;



        Note note;

        Sound sound;


        Gtk::Window window;

            //layout elements

        Gtk::Table container;

            Gtk::HBox notesContainer;

                Gtk::Button a;
                Gtk::Button a_plus;
                Gtk::Button b;  //HERE devia ser ToggleButton ?..
                Gtk::Button c;
                Gtk::Button c_plus;
                Gtk::Button d;
                Gtk::Button d_plus;
                Gtk::Button e;
                Gtk::Button f;
                Gtk::Button f_plus;
                Gtk::Button g;
                Gtk::Button g_plus;

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
