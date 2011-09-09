#include "metronome.h"


Metronome::Metronome (int bpm, int duration, double frequency, int strongBeats)

    : Tempo (bpm, duration),
      Sound (frequency),
      animeWindow (bpm),

      strongBeats_obj(strongBeats),
      countBeats_obj(0)

{

}

/*
void Metronome::start ()
{
    //don't start the metronome when the tuner is opened
if (tuner.isOpened() == true)
    {
    return;
    }

    //carry on
Tempo::start();
}
*/

void Metronome::setBpm(int bpm)
{
animeWindow.updateBpm(bpm);

Tempo::setBpm(bpm);
}



void Metronome::firstFunction()
{
    //the strong beats only matter when >1, otherwise its always the normal state
if (strongBeats_obj != 1)
    {
    countBeats_obj++;

         //play the strong beat (on the first beat)
    if (countBeats_obj == 1)
        {
        Sound::play_strongBeat();

        animeWindow.start_strongBeat();
        }

    else
        {
        Sound::play();

        animeWindow.start();
        }


    if (countBeats_obj == strongBeats_obj)
        {
            //reset the counter
        countBeats_obj = 0;
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
strongBeats_obj = strongBeats;


    //reset the counter
countBeats_obj = 0;
}


int Metronome::getStrongBeats () const
{
return strongBeats_obj;
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


bool Metronome::isAnimeOpened () const
{
return animeWindow.isOpened();
}
