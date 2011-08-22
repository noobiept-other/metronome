#include "metronome.h"

/*
extern Sound* test;
//HERE testttttttttttttt


void firstCall()
{
    test->play();
}

void secondCall()
{
    test->stop();
}*/
/*
//HERE como chamar estas funcoes?..
void firstFunction ()
{
sound.play();
}


void secondFunction ()
{
sound.stop();
}


*/

Metronome::Metronome (int bpm, int duration, int frequency)

    : Tempo (bpm, duration),
      sound (frequency)

{

}




void Metronome::firstFunction()
{
sound.play();
    cout << "function1" << endl;
}


void Metronome::secondFunction()
{
    sound.stop();
    cout << "function2" << endl;
}


