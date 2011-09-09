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

            //window's position on the screen
        int mainPosition_x;
        int mainPosition_y;
        int optionsPosition_x;
        int optionsPosition_y;
        int tunerPosition_x;
        int tunerPosition_y;
        int animationPosition_x;
        int animationPosition_y;

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


            // :::: value's limits :::: //

        const int frequencyLowerLimit;
        const int frequencyUpperLimit;

        const int bpmLowerLimit;
        const int bpmUpperLimit;

        const int strongBeatsUpperLimit;    //there's no lower limit, since its 1 (when there's no strong beat)

        const int beatDurationLowerLimit;
        const int beatDurationUpperLimit;


    private:

        void readConfigurations ();


        double getPropertyValue (std::string line, std::string property);


            // :: Check if a variable is within the limits :: //

        double checkLimits (double value, double lowerLimit, double upperLimit) const;
};



#endif //CONFIGURATIONS_GUARD
