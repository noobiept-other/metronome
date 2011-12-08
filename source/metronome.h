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


#ifndef METRONOME_GUARD
#define METRONOME_GUARD

#include "sound.h"
#include "tempo.h"
#include "animeWindow.h"



class Metronome : public Tempo, public Sound
{
    public:

        Metronome (int bpm = 60, int duration = 200, double frequency = 440, int strongBeats = 4);



        void openAnimeWindow();



        virtual void setStrongBeats (int strongBeats);

        int getStrongBeats () const;



        AnimeWindow animeWindow;


    protected:

            //overriding the Tempo functions
        virtual void firstFunction();
        virtual void secondFunction();

        virtual void setBpm(int bpm);


    private:

        int strongBeats_var;
        int countBeats_var;

};


#endif //METRONOME_GUARD
