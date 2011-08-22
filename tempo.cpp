#include "tempo.h"


Tempo::Tempo (int bpm, int duration)

    : bpm_obj       (bpm),
      duration_obj  (duration),
      isPlaying_obj (false)

{
calculate_miliseconds(bpm);
}


void Tempo::setFunctions (void (*startFunction)(), void (*stopFunction)())
{
startFunction_obj = startFunction;
stopFunction_obj = stopFunction;
}



void Tempo::start()
{
if (isPlaying_obj == true)
    {
    return;
    }

isPlaying_obj = true;

timer_obj = Glib::signal_timeout().connect(sigc::mem_fun(*this, &Tempo::keepRunning), inMiliseconds_obj);


	// stop it after 200ms
	Glib::signal_timeout().connect(sigc::mem_fun(*this, &Tempo::stopFunction),
	                               200);
}




void Tempo::stop()
{
isPlaying_obj = false;

timer_obj.disconnect();
}




bool Tempo::keepRunning()
{
startFunction_obj();


	//stop it after 200ms
Glib::signal_timeout().connect(sigc::mem_fun(*this, &Tempo::stopFunction),
	                               200);

return true;
}


bool Tempo::stopFunction()  //HERE n devia precisar desta funcao... perguntar gtkmm
{
stopFunction_obj();

return false;
}


/*
void Tempo::startFunction()
{

}
*/


void Tempo::setBpm(int bpm)
{
if (isPlaying_obj == true)
	{
	timer_obj.disconnect();
	}

calculate_miliseconds (bpm);

timer_obj = Glib::signal_timeout().connect(sigc::mem_fun(*this, &Tempo::keepRunning), 10000);
}



int Tempo::getBpm() const
{
return bpm_obj;
}


void Tempo::operator ++ (int a)
{
setBpm (bpm_obj + 1);
}



void Tempo::operator -- (int a)
{
setBpm (bpm_obj - 1);
}



void Tempo::calculate_miliseconds (int bpm)
{
inMiliseconds_obj = bpm / 60.0 * 1000;
}
