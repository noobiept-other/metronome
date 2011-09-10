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

        nas opcoes, se estiver um SpinButton em foco, o Esc da janela nao funciona (nao fecha a janela)


        passar os setStrongBeats() do Main para o Metronome


        a configurations, ter uma funcao friend das classes, em vez de ter set/get functions (e n ter global a variavel)

        passar o loadConfigurations() do Main para o Configurations (tem os erros ao compilar.. nao encontra as classes..)
            (e ter Main como friend class)

        window.set_icon() ou .set_icon_from_file()
            (e fazer o icon)

 */


#include <gtkmm.h>

#include <iostream>
#include <string>
#include <fstream>



#include "metronome.h"
#include "options.h"
#include "tuner.h"


class Main : public Gtk::Window, public Metronome
{
    public:

        Main();

            //saves the state of the program (which windows were open, the options, etc)
        ~Main();

        virtual void start();

        void openOptions();


        void openTuner();


    protected:

            //override from Gtk::Window
        virtual void on_hide ();

        virtual void updateTempo();

            //called when the tuner_var is closed
        void onTunerHide();


    private:

            // :::: Functions :::: //

        void loadConfigurations();

        bool bringTunerToFront();



        virtual void setStrongBeats (Gtk::RadioButton* widget, int beat);

        void setStrongBeats_fromSpinButton ();

            //hack - to cancel multiple events when changing the strong beats
        bool changingStrongBeats_var;


            // :::: Variables :::: //


        Options optionsPage_var;

        Tuner tuner_var;


            //when we open the tuner_var, we save in this variable whether the metronome was playing, so that when
            //closing the tuner window, we can restart the metronome
        bool wasPlaying_var;

            // :::: Layout :::: //

            //2 row and 2 columns
        Gtk::Table mainTable_gui;

            Gtk::Table tempoContainer_gui;

                Gtk::Label tempoName_gui;
                Gtk::SpinButton changeTempo_gui;
                Gtk::Label tempoBpm_gui;

            Gtk::Table strongBeat_gui;

                Gtk::Label strongBeatLabel_gui;

                Gtk::RadioButton oneBeat_gui;
                Gtk::RadioButton twoBeats_gui;
                Gtk::RadioButton threeBeats_gui;
                Gtk::RadioButton fourBeats_gui;
                Gtk::SpinButton otherBeat_gui;

            Gtk::HBox startStopContainer_gui;

                Gtk::Button start_gui;
                Gtk::Button stop_gui;

            Gtk::HBox otherContainer_gui;

                Gtk::Button openOptions_gui;
                Gtk::Button openTuner_gui;
                Gtk::Button openAnimation_gui;

};


#endif
