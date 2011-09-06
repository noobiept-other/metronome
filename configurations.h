#ifndef CONFIGURATIONS_GUARD
#define CONFIGURATIONS_GUARD

#include <gtkmm.h>
#include "note.h"

#include <string>
#include <iostream>
#include <fstream>

    //has all the configurations loaded from the external file (or simply the defaults)
class Configurations
{
    public:

        Configurations ();

        void readFromFile ();

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
        double noteFrequency_tuner;


    private:

        void readConfigurations ();

        double getPropertyValue (std::string line, std::string property);

};



#endif //CONFIGURATIONS_GUARD
