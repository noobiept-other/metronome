#ifndef MAIN_GUARD
#define MAIN_GUARD

/*

    Naming conventions:

        Global variables:

            All characters capitalized
                (like, EXAMPLE)

        class name:

            First character capitalized
                (like, Example)

        gtkmm related class variables (for the buttons, containers, etc):

            ending in _gui (from, graphical user interface)
                (like example_gui)

        normal class variables (that don't conform with anything above):

            ending in _var (from, variable)
                (like, example_var)



    To doo:


        ter a possibilidade de ter diferentes tipos de som (ver audiotestsrc - gstreamer)


        window.set_icon() ou .set_icon_from_file()
            (e fazer o icon)



        reorganizar o codigo...

        a configurations, ter uma funcao friend das classes, em vez de ter set/get functions (e n ter global a variavel)


 */


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
#include "configurations.h"



class Main : public Gtk::Window, public Metronome
{
    public:

        Main();

            //saves the state of the program (which windows were open, the options, etc)
        ~Main();

        virtual void start();

        void openOptions();


        void openTuner();


        //Configurations configurations;

    protected:

            //override from Gtk::Window
        virtual void on_hide ();

        virtual void updateTempo();

            //called when the tuner is closed
        void onTunerHide();

        //void test();

    private:

            // :::: Functions :::: //

        void loadConfigurations();

        bool bringTunerToFront();



        virtual void setStrongBeats (Gtk::RadioButton* widget, int beat);

        void setStrongBeats_fromSpinButton ();

        //HERE hack - to cancel multiple events when changing the strong beats
        bool changingStrongBeats;


            // :::: Variables :::: //


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

                Gtk::Button start_gui;
                Gtk::Button stop;

            Gtk::HBox otherContainer;

                Gtk::Button openOptions_gui;
                Gtk::Button openTuner_gui;
                Gtk::Button openAnimation;

};


#endif
