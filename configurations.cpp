#include "configurations.h"


Configurations::Configurations ()
{
    //set the defaults
optionsWindow   = false;
tunerWindow     = false;
animationWindow = false;

mainPosition_x = -1;
mainPosition_y = -1;
optionsPosition_x = -1; //-1 because if not provided by the external file, then let the position be calculated
optionsPosition_y = -1;     //HERE uma class para isto?..
tunerPosition_x = -1;
tunerPosition_y = -1;
animationPosition_x = -1;
animationPosition_y = -1;

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
    readConfigurations();
    }

catch (...)
    {
    cout << "exception occurred, when trying the Main::loadConfigurations()\n";
    }
}





void Configurations::readConfigurations ()
{
std::ifstream config;

config.open ("config.txt");

if (config.is_open() == true)
    {
    std::string line;

    int value;
    double value_realNumber;


    // :::: Opened windows :::: //

//HERE melhorar isto
        //useless lines
    getline (config, line);
    getline (config, line);
    getline (config, line);

        // :: Options window :: //

    getline (config, line);

    value = getPropertyValue(line, "options");


        //we open the animation window
    if (value != 0)
        {
        this->optionsWindow = true;
        //openOptions();
        }

        // :: Tuner window :: //

    getline (config, line);

    value = getPropertyValue(line, "tuner");


    if (value != 0)
        {
        this->tunerWindow = true;
        //openTuner();
        }

        // :: Animation window :: //


    getline (config, line);


    value = getPropertyValue(line, "animation");


    if (value != 0)
        {
        this->animationWindow = true;
        //openAnimeWindow();
        }


        // :::: Window's position :::: //

    getline (config, line);
    getline (config, line);

        // :: Main position :: //

    getline (config, line);

    mainPosition_x = getPropertyValue (line, "main-x");

    getline (config, line);

    mainPosition_y = getPropertyValue (line, "main-y");


        // :: Options position :: //

    getline (config, line);

    optionsPosition_x = getPropertyValue (line, "options-x");

    getline (config, line);

    optionsPosition_y = getPropertyValue (line, "options-y");


        // :: Tuner position :: //

    getline (config, line);

    tunerPosition_x = getPropertyValue (line, "tuner-x");

    getline (config, line);

    tunerPosition_y = getPropertyValue (line, "tuner-y");


        // :: Animation position :: //

    getline (config, line);

    animationPosition_x = getPropertyValue (line, "animation-x");

    getline (config, line);

    animationPosition_y = getPropertyValue (line, "animation-y");



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
void Configurations::loadConfigurations (Main& main)
{
    // :: Metronome :: //


main.setBpm (this->bpm);

    //set the inconsistent state
if (this->strongBeats > 4)
    {
    main.oneBeat.set_inconsistent (true);
    main.twoBeats.set_inconsistent (true);
    main.threeBeats.set_inconsistent (true);
    main.fourBeats.set_inconsistent (true);

    main.otherBeat.set_value (this->strongBeats);
    }

else
    {
    switch (this->strongBeats)
        {
        case 1:

            main.oneBeat.set_active ();
            break;

        case 2:

            main.twoBeats.set_active ();
            break;

        case 3:

            main.threeBeats.set_active ();
            break;

        case 4:

            main.fourBeats.set_active ();
            break;
        }
    }



main.Metronome::setStrongBeats (this->strongBeats);


main.setDuration ( this->beatDuration );

main.setFrequency ( this->normalFrequency );
main.setStrongFrequency ( this->strongFrequency );


if (this->isPlaying_metro == true)
    {
    main.Metronome::start();
    }


    // :: Options :: //

main.optionsPage.loadConfigurations ();

if (this->optionsWindow == true)
    {
    main.openOptions ();
    }

    // :: Animation :: //

main.animeWindow.loadConfigurations ();

if (this->animationWindow == true)
    {
    main.openAnimeWindow ();
    }

    // :: Tuner :: //

main.tuner.setNoteFrequency ( this->noteFrequency_tuner );

    //when changing the note frequency, it triggers an event which starts the tuner
main.tuner.stop ();



if (this->tunerWindow == true)
    {
    main.openTuner (); //HERE ao fechar a janela, o metronomo esta sempre parado... (a cena do wasPlaying...)

    if (this->isPlaying_tuner == false)
        {
        main.tuner.stop ();
        }

        //bring the tuner window to the front
    //tuner.raise();  //HERE n parece k resulta
    //Glib::signal_timeout().connect(sigc::mem_fun(*this, &Main::test),
	     //                          1000);
    //this->signal_realize().connect ( sigc::mem_fun (*this, &Main::test) );//HERE doesnt work as well
    Glib::signal_idle ().connect ( sigc::bind<Main&> (sigc::mem_fun (*this, &Configurations::test), main) ); //HERE melhorar isto (se calhar funcao anonima?)
    }

}


bool Configurations::test(Main& main)
{
main.tuner.raise();  //HERE

    //cancel idle function
return false;
}

*/





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
