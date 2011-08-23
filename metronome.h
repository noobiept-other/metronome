#ifndef METRONOME_GUARD
#define METRONOME_GUARD

#include "sound.h"
#include "tempo.h"


#include <iostream>

using std::cout;
using std::endl;


class Metronome : public Tempo
{
    public:

        Metronome (int bpm = 60, int duration = 200, int frequency = 440);

    protected:

        virtual void firstFunction();
        virtual void secondFunction();


    private:

        Sound sound;

        //Animation animation;

};


#endif //METRONOME_GUARD
