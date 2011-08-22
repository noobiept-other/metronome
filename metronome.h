#ifndef METRONOME_GUARD
#define METRONOME_GUARD

#include "sound.h"
#include "tempo.h"




class Metronome : public Tempo
{
    public:

        Metronome (int bpm = 60, int duration = 200, int frequency = 440);

    private:

        friend void firstFunction ();
        friend void secondFunction ();

        //Sound sound;
};


#endif //METRONOME_GUARD
