#include "metronome.h"


Metronome::Metronome (int bpm, int duration, int frequency)

    : Tempo (bpm, duration),
      sound (frequency)

{

}




void Metronome::firstFunction()
{
sound.play();
}


void Metronome::secondFunction()
{
sound.stop();
}


