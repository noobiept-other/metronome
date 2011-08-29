#ifndef MAIN_GUARD
#define MAIN_GUARD

#include <gtkmm.h>
#include <gstreamermm.h>
#include "metronome.h"


class Main : public Gtk::Window
{
    public:

        Main();


    private:

Metronome metronome;
        //Gtk::Window window;

                //2 row and 2 columns
            Gtk::Table mainTable;

                Gtk::Table tempoContainer;

                    Gtk::Label tempoName;
                    Gtk::SpinButton changeTempo;
                    Gtk::Label tempoBpm;

                Gtk::Table strongBeat;

                    Gtk::Label strongBeatLabel;

                    Gtk::Button oneBeat;
                    Gtk::Button twoBeats;
                    Gtk::Button threeBeats;
                    Gtk::Button fourBeats;
                    Gtk::Entry otherBeat;

                Gtk::HBox startStopContainer;

                    Gtk::Button start;
                    Gtk::Button stop;

                Gtk::HBox otherContainer;

                    Gtk::Button openOptions;
                    Gtk::Button openTuner;
                    Gtk::Button openAnimation;

};


#endif
