#include "tempo.h"


Tempo::Tempo (int bpm, int duration)

    : bpm_var       (bpm),
      duration_var  (duration),
      isPlaying_var (false)

{
calculateMiliseconds(bpm);
}





void Tempo::start()
{
if (isPlaying_var == true)
    {
    return;
    }

isPlaying_var = true;

firstFunction();

    //call keepRunning accordingly to the bpm that is set (inMiliseconds_var is the bpm in miliseconds)
timer_var = Glib::signal_timeout().connect( sigc::mem_fun( *this, &Tempo::keepRunning ), inMiliseconds_var );


	// stop it after some miliseconds (the duration of the beat)
Glib::signal_timeout().connect( sigc::mem_fun( *this, &Tempo::stopFunction ), duration_var );
}




void Tempo::stop()
{
isPlaying_var = false;

timer_var.disconnect();
}




bool Tempo::keepRunning()
{
firstFunction();

	//stop it after some miliseconds (the duration of the beat)
Glib::signal_timeout().connect( sigc::mem_fun( *this, &Tempo::stopFunction ), duration_var );

    //keeps the tempo going, if we return false it stops it
return true;
}


bool Tempo::stopFunction()
{
secondFunction();

    //we only want it to run once, so we stop it (it will be setup again when the keepRunning is called)
return false;
}



void Tempo::setBpm(int bpm)
{
bpm_var = bpm;

calculateMiliseconds (bpm);


    //re-start the timer
if (isPlaying_var == true)
	{
	timer_var.disconnect();

	timer_var = Glib::signal_timeout().connect(sigc::mem_fun(*this, &Tempo::keepRunning), inMiliseconds_var);
	}

}



int Tempo::getBpm() const
{
return bpm_var;
}




void Tempo::setDuration (int duration)
{
duration_var = duration;
}




int Tempo::getDuration () const
{
return duration_var;
}




bool Tempo::isPlaying() const
{
return isPlaying_var;
}


void Tempo::operator ++ (int a)
{
setBpm (bpm_var + 1);
}



void Tempo::operator -- (int a)
{
setBpm (bpm_var - 1);
}


/*

    bpm -> beats per minute
    bps (or frequency) -> beats per second (cycles per second, actually)

    bpm / 60 -> bps (or frequency)

    interval (or period - in seconds) = 1 / frequency

    In miliseconds -> interval * 1000
 */

void Tempo::calculateMiliseconds (int bpm)
{
inMiliseconds_var = (1 / (bpm / 60.0)) * 1000;
}
