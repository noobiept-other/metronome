#ifndef METRONOME_GUARD
#define METRONOME_GUARD

#include "sound.h"
#include "tempo.h"
#include "animeWindow.h"
#include "options.h"
#include "tuner.h"

#include <iostream>

using std::cout;
using std::endl;


//enum BeatType { normal, strong };



class Metronome : public Tempo, public Sound
{
    public:

        Metronome (int bpm = 60, int duration = 200, double frequency = 440, int strongBeats = 4);


            //overriding from Tempo (to add a bit more)
       // void start();



            //other

        void openAnimeWindow();

        //void openTuner();

        void openOptions();

        void setStrongBeats (int strongBeats);

    protected:

        virtual void firstFunction();
        virtual void secondFunction();


    private:

        //Sound sound;
        Options optionsPage;

       // Tuner tuner;

        AnimeWindow animeWindow;



        int strongBeats_obj;
        int countBeats_obj;

};


#endif //METRONOME_GUARD
