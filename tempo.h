#ifndef TEMPO_GUARD
#define TEMPO_GUARD

#include <gtkmm.h>


class Tempo
    {
    public:

        Tempo (int bpm = 60, int duration = 200);


        void setFunctions (void (*startFunction)(), void (*stopFunction)());


        void start();
        void stop();



        void setBpm(int bpm);

        int getBpm() const;

        void operator ++ (int);
        void operator -- (int);

    private:

        bool keepRunning();

        void calculate_miliseconds(int bpm);

        bool stopFunction();


        int bpm_obj;
        int duration_obj;
        int inMiliseconds_obj;

		sigc::connection timer_obj;
		bool isPlaying_obj;


        void (*startFunction_obj) ();
        void (*stopFunction_obj) ();
    };



#endif //TEMPO_GUARD
