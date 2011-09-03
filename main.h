#ifndef MAIN_GUARD
#define MAIN_GUARD

#include <gtkmm.h>
#include <gstreamermm.h>

#include <iostream>
#include <string>
#include <fstream>


using std::cout;
using std::endl;

using std::string;

#include "metronome.h"
#include "tuner.h"
#include "note.h"

    //has all the configurations loaded from the external file (or simply the defaults)
struct Configurations
{
        //opened windows
    bool optionsWindow;
    bool tunerWindow;
    bool animationWindow;

        //metronome
    bool isPlaying_metro;
    int bpm;
    int strongBeats;

        //options
    int beatDuration;
    double normalFrequency;
    double strongFrequency;

        //animation
    Gdk::RGBA normalColor;
    Gdk::RGBA strongColor;

        //tuner
    bool isPlaying_tuner;
    Note tunerNote;

};



class Main : public Gtk::Window, public Metronome
{
    public:

        Main();

            //saves the state of the program (which windows were open, the options, etc)
        ~Main();

        void startMetronome();

        void openOptions();


        void openTuner();


    protected:


        virtual void updateTempo();

            //override Tuner::onTunerHide event
        void onTunerHide();

        //void test();

    private:

            // :::: Functions :::: //

        void loadConfigurations();

        int getPropertyValue (string line, string property);


        virtual void setStrongBeats (Gtk::RadioButton* widget, int beat);

        void setStrongBeats_fromSpinButton ();

        //HERE hack - to cancel multiple events when changing the strong beats
        bool changingStrongBeats;


            // :::: Variables :::: //

        Configurations configurations;

        Options optionsPage;

        Tuner tuner;
        //Metronome metronome;
            //when we open the tuner, we save in this variable whether the metronome was playing, so that when
            //closing the tuner window, we can restart the metronome
        bool wasPlaying_var;

            // :::: Layout :::: //

            //2 row and 2 columns
        Gtk::Table mainTable;

            Gtk::Table tempoContainer;

                Gtk::Label tempoName;
                Gtk::SpinButton changeTempo;
                Gtk::Label tempoBpm;

            Gtk::Table strongBeat;

                Gtk::Label strongBeatLabel;

                Gtk::RadioButton oneBeat;
                Gtk::RadioButton twoBeats;
                Gtk::RadioButton threeBeats;
                Gtk::RadioButton fourBeats;
                Gtk::SpinButton otherBeat;

            Gtk::HBox startStopContainer;

                Gtk::Button start;
                Gtk::Button stop;

            Gtk::HBox otherContainer;

                Gtk::Button openOptions_gui;
                Gtk::Button openTuner_gui;
                Gtk::Button openAnimation;

};


#endif
