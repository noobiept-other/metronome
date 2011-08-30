#include "metronome.h"


Metronome::Metronome (int bpm, int duration, double frequency, int strongBeats)

    : Tempo (bpm, duration),
      Sound (frequency),
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



void Metronome::openAnimeWindow()
{
animeWindow.open();
}

/*
void Metronome::openTuner()
{
if (Tempo::isPlaying() == true)
    {
    this->stop();
    }

    //HERE ao fechar o tuner, era fixe se ele comeca-se a tocar o metronomo (caso estivesse nesse estado antes de abrir)
    //por enquanto simplesmente estah parado
tuner.open();
}
*/


void Metronome::openOptions()
{
optionsPage.open();
}
