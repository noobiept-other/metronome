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
