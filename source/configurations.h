/*

	Copyright - 2011 - Pedro Ferreira

	This file is part of Metronome.

    Metronome is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Metronome is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Metronome.  If not, see <http://www.gnu.org/licenses/>.

 */


#ifndef CONFIGURATIONS_GUARD
#define CONFIGURATIONS_GUARD

#include <gtkmm.h>

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
        bool wasPlaying_metro;
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
        int notePosition_tuner;
        int noteOctave_tuner;
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
