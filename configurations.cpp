#include "configurations.h"


Configurations::Configurations ()
{
    //set the defaults
optionsWindow   = false;
tunerWindow     = false;
animationWindow = false;

isPlaying_metro = true;
bpm             = 60;
strongBeats     = 4;

beatDuration    = 200;   //200 ms
normalFrequency = 440;   //A4 - 440 Hz
strongFrequency = 440 + 150; //HERE hmmm

normalColor.set_rgba (0, 0, 1, 1);    //blue color
strongColor.set_rgba (1, 0, 1, 1);   //HERE hmmm

isPlaying_tuner = false;
noteFrequency_tuner = 440;
}



void Configurations::readFromFile ()
{
try
    {
    loadConfigurations();
    }

catch (...)
    {
    cout << "exception occurred, when trying the Main::loadConfigurations()\n";
    }
}





void Configurations::loadConfigurations ()
{
std::ifstream config;

config.open ("config.txt");

if (config.is_open() == true)
    {
    std::string line;

    int value;
    double value_realNumber;



//HERE melhorar isto
        //useless lines
    getline (config, line);
    getline (config, line);
    getline (config, line);

        // :::: Options window :::: //

    getline (config, line);

    value = getPropertyValue(line, "options");


        //we open the animation window
    if (value != 0)
        {
        this->optionsWindow = true;
        //openOptions();
        }

        // :::: Tuner window :::: //

    getline (config, line);

    value = getPropertyValue(line, "tuner");


    if (value != 0)
        {
        this->tunerWindow = true;
        //openTuner();
        }

        // :::: Animation window :::: //


    getline (config, line);


    value = getPropertyValue(line, "animation");


    if (value != 0)
        {
        this->animationWindow = true;
        //openAnimeWindow();
        }


        // :::: Metronome :::: //

    getline (config, line);
    getline (config, line);


        // :::: isPlaying :::: //

    getline (config, line);

    value = getPropertyValue(line, "isPlaying_metro");

    if (value == 0)
        {
        this->isPlaying_metro = false;
        }

        // :::: Bpm :::: //

    getline (config, line);

    value = getPropertyValue(line, "bpm");

    this->bpm = value;



        // :::: Strong beat :::: //

    getline (config, line);


    value = getPropertyValue(line, "strongBeats");


    this->strongBeats = value;


        // :::: Options :::: //

    getline (config, line);
    getline (config, line);


        // :::: beat duration :::: //

    getline (config, line);

    value = getPropertyValue (line, "beatDuration");

    this->beatDuration = value;


        // :::: normal frequency :::: //

    getline (config, line);

    value_realNumber = getPropertyValue (line, "normalFrequency");

    this->normalFrequency = value_realNumber;


        // :::: strong frequency :::: //

    getline (config, line);

    value_realNumber = getPropertyValue (line, "strongFrequency");

    this->strongFrequency = value_realNumber;


        // :::: Animation :::: //

    getline (config, line);
    getline (config, line);

        // :::: normal color :::: //

    double red, green, blue, alpha;


    getline (config, line);

    red = getPropertyValue (line, "normalColor-red");


    getline (config, line);

    green = getPropertyValue (line, "normalColor-green");


    getline (config, line);

    blue = getPropertyValue (line, "normalColor-blue");


    getline (config, line);

    alpha = getPropertyValue (line, "normalColor-alpha");


    this->normalColor.set_rgba (red, green, blue, alpha);


        // :::: strong color :::: //

    getline (config, line);

    red = getPropertyValue (line, "strongColor-red");


    getline (config, line);

    green = getPropertyValue (line, "strongColor-green");


    getline (config, line);

    blue = getPropertyValue (line, "strongColor-blue");


    getline (config, line);

    alpha = getPropertyValue (line, "strongColor-alpha");


    this->strongColor.set_rgba (red, green, blue, alpha);


        // :::: Tuner :::: //

    getline (config, line);
    getline (config, line);

        // :::: isPlaying_tuner :::: //

    getline (config, line);

    value = getPropertyValue (line, "isPlaying_tuner");

    this->isPlaying_tuner = value;

        // :::: Note frequency :::: //

    getline (config, line);

    value_realNumber = getPropertyValue (line, "noteFrequency_tuner");

    this->noteFrequency_tuner = value_realNumber;


    config.close();
    }
}



/*
    Searches a string for a property, and returns that property's value
        (in the form -> property: value)

 */

double Configurations::getPropertyValue (std::string line, std::string property)
{
int i = line.find (property);


i += property.length();

    //remove the ':' and spaces
while (true)
    {
    if (line.at (i) != ':' && line.at (i) != ' ')
        {
        break;
        }

    i++;
    }

std::string theNumber = line.substr (i);


std::stringstream stream (theNumber);

double number = 0;

stream >> number;   //HERE testar qd nao encontra um numero...

return number;
}
