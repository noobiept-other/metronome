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


#include "metronome.h"


Metronome::Metronome (int bpm, int duration, double frequency, int strongBeats)

    : Tempo       (bpm, duration),
      Sound       (frequency),
      animeWindow (bpm),

      strongBeats_var (strongBeats),
      countBeats_var  (0)

{

}



void Metronome::setBpm(int bpm)
{
animeWindow.updateBpm(bpm);

Tempo::setBpm(bpm);
}


/*
    Its called when we're on the tempo, it starts the sound and the animation
 */

void Metronome::firstFunction()
{
    //the strong beats only matter when >1, otherwise its always the normal state
if (strongBeats_var != 1)
    {
    countBeats_var++;

         //play the strong beat (on the first beat)
    if (countBeats_var == 1)
        {
        Sound::play_strongBeat();

        animeWindow.start_strongBeat();
        }

        //normal beat
    else
        {
        Sound::play();

        animeWindow.start();
        }


    if (countBeats_var == strongBeats_var)
        {
            //reset the counter
        countBeats_var = 0;
        }
    }

    //always normal state
else
    {
    Sound::play();

    animeWindow.start();
    }

}



void Metronome::secondFunction()
{
Sound::stopPlaying();

animeWindow.stop();
}


void Metronome::setStrongBeats (int strongBeats)
{
strongBeats_var = strongBeats;


    //reset the counter
countBeats_var = 0;
}


int Metronome::getStrongBeats () const
{
return strongBeats_var;
}




void Metronome::openAnimeWindow()
{
    //if the window is opened, then bring it to the front
if (animeWindow.isOpened () == true)
    {
    animeWindow.raise ();
    }

else
    {
    animeWindow.open();
    }
}

