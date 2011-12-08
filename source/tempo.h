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


#ifndef TEMPO_GUARD
#define TEMPO_GUARD

#include <gtkmm.h>

/*
    Sets up a tempo that calls one function from time to time (set by the bpm - beats per minute)
    A second function is called, some time after the first function (depends on the duration)
 */

class Tempo
    {
    public:

        /*
            bpm      -> beats per minute
            duration -> of the beat (in miliseconds)
         */

        Tempo (int bpm = 60, int duration = 200);


        virtual void start();
        virtual void stop();


        virtual void setBpm (int bpm);

        int getBpm() const;


        void setDuration (int duration);

        int getDuration () const;


        void operator ++ (int);
        void operator -- (int);


        bool isPlaying() const;

    protected:

            //what is executed when we're on tempo (depends on the bpm)
        virtual void firstFunction() = 0;

            //what is executed some time later (depends on the duration)
        virtual void secondFunction() = 0;


    private:

        bool keepRunning();

        void calculateMiliseconds(int bpm);

        bool stopFunction();


        int bpm_var;
        int duration_var;
        int inMiliseconds_var;

		sigc::connection timer_var;
		bool isPlaying_var;

    };



#endif //TEMPO_GUARD
