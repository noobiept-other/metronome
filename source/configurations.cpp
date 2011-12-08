#include "configurations.h"


Configurations::Configurations ()

    : frequencyLowerLimit (200),
      frequencyUpperLimit (12000),

      bpmLowerLimit (30),
      bpmUpperLimit (300),

      strongBeatsUpperLimit (10),

      beatDurationLowerLimit (50),
      beatDurationUpperLimit (300)

{
    //set the defaults
optionsWindow   = false;
tunerWindow     = false;
animationWindow = false;

mainPosition_x = -1;
mainPosition_y = -1;
optionsPosition_x = -1; //-1 because if not provided by the external file, then let the position be calculated
optionsPosition_y = -1;
tunerPosition_x = -1;
tunerPosition_y = -1;
animationPosition_x = -1;
animationPosition_y = -1;

isPlaying_metro  = true;
wasPlaying_metro = false;
bpm              = 60;
strongBeats      = 4;

beatDuration    = 200;      //200 ms
normalFrequency = 440;      //A4 - 440 Hz
strongFrequency = 587.33;   //D5 - 587.33 Hz

normalColor.set_rgba (0, 0, 1, 1);    //blue color
strongColor.set_rgba (1, 0, 0, 1);    //red color

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
    std::cout << "exception occurred, when trying the Configurations::readConfigurations()\n";
    }
}



/*
    Update the configurations with the values from the external file
 */

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
        }

        // :: Tuner window :: //

    getline (config, line);

    value = getPropertyValue(line, "tuner");


    if (value != 0)
        {
        this->tunerWindow = true;
        }

        // :: Animation window :: //


    getline (config, line);


    value = getPropertyValue(line, "animation");


    if (value != 0)
        {
        this->animationWindow = true;
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


        // :: isPlaying :: //

    getline (config, line);

    value = getPropertyValue(line, "isPlaying_metro");

    if (value == 0)
        {
        this->isPlaying_metro = false;
        }


        // :: wasPlaying :: //

    getline (config, line);

    value = getPropertyValue(line, "wasPlaying_metro");

    if (value != 0)
        {
        this->wasPlaying_metro = true;
        }

        // :: Bpm :: //

    getline (config, line);

    value = getPropertyValue(line, "bpm");

    this->bpm = checkLimits (value, bpmLowerLimit, bpmUpperLimit);



        // :: Strong beat :: //

    getline (config, line);


    value = getPropertyValue(line, "strongBeats");


    this->strongBeats = checkLimits (value, 1, strongBeatsUpperLimit);


        // :::: Options :::: //

    getline (config, line);
    getline (config, line);


        // :: beat duration :: //

    getline (config, line);

    value = getPropertyValue (line, "beatDuration");

    this->beatDuration = checkLimits (value, beatDurationLowerLimit, beatDurationUpperLimit);


        // :: normal frequency :: //

    getline (config, line);

    value_realNumber = getPropertyValue (line, "normalFrequency");

    this->normalFrequency = checkLimits (value_realNumber, frequencyLowerLimit, frequencyUpperLimit);


        // :: strong frequency :: //

    getline (config, line);

    value_realNumber = getPropertyValue (line, "strongFrequency");

    this->strongFrequency = checkLimits (value_realNumber, frequencyLowerLimit, frequencyUpperLimit);


        // :::: Animation :::: //

    getline (config, line);
    getline (config, line);

        // :: normal color :: //

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


        // :: strong color :: //

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

        // :: isPlaying_tuner :: //

    getline (config, line);

    value = getPropertyValue (line, "isPlaying_tuner");

    this->isPlaying_tuner = value;

        // :: Note frequency :: //

    getline (config, line);

    value_realNumber = getPropertyValue (line, "noteFrequency_tuner");

    this->noteFrequency_tuner = checkLimits (value_realNumber, frequencyLowerLimit, frequencyUpperLimit);


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

stream >> number;

    //abort the loading process
if (stream.fail() == true)
    {
    throw -1;
    }

return number;
}





/*
    Checks if a value is within the limits, if it passes that limit, then we return the closer limit
    (for example, if the lower limit is 200, and we have value of 100 Hz, its returned the lower limit (200))
 */

double Configurations::checkLimits (double value, double lowerLimit, double upperLimit) const
{
if (value < lowerLimit)
    {
    return lowerLimit;
    }

else if (value > upperLimit)
    {
    return upperLimit;
    }

else
    {
    return value;
    }
}
