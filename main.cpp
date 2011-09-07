#include "main.h"


    //global variable
Configurations CONFIGURATIONS;



int main (int argc, char** argv)
{
Gtk::Main kit(argc, argv);

Gst::init (argc, argv);


    //update the CONFIGURATIONS values with the configs set in the external file
CONFIGURATIONS.readFromFile ();

Main window;

Gtk::Main::run (window);

return 0;
}



Main::Main ()

    : changingStrongBeats (false),

      wasPlaying_var (true),

      mainTable (2, 2),
      tempoContainer (1, 3),
      strongBeat (1, 6)

{
    // :::: Tempo related :::: //


tempoName.set_label ("Tempo: ");

tempoBpm.set_label ("bpm");


    //start at 60, with limits from 30 to 300 - step is 1
Glib::RefPtr<Gtk::Adjustment> tempoAdjustment (Gtk::Adjustment::create(CONFIGURATIONS.bpm, 30, 300, 1, 5, 0));

changeTempo.set_adjustment (tempoAdjustment);
changeTempo.set_numeric (true);



tempoContainer.attach(tempoName, 0, 1, 0, 1);
tempoContainer.attach(changeTempo, 1, 2, 0, 1);
tempoContainer.attach(tempoBpm, 2, 3, 0, 1);

tempoContainer.set_col_spacings(10);



    // :::: Strong beat :::: //


strongBeat.set_col_spacings(10);


strongBeatLabel.set_label ("Strong beat");


oneBeat.set_label ("1");

twoBeats.set_label ("2");

threeBeats.set_label ("3");

fourBeats.set_label ("4");


Gtk::RadioButton::Group group = oneBeat.get_group();

twoBeats.set_group   (group);
threeBeats.set_group (group);
fourBeats.set_group  (group);


Glib::RefPtr<Gtk::Adjustment> otherBeatAdjustment (Gtk::Adjustment::create(4, 1, 10, 1, 2, 0));

otherBeat.set_adjustment (otherBeatAdjustment);
otherBeat.set_numeric (true);



strongBeat.attach (strongBeatLabel, 0, 1, 0, 1);
strongBeat.attach (oneBeat, 1, 2, 0, 1);
strongBeat.attach (twoBeats, 2, 3, 0, 1);
strongBeat.attach (threeBeats, 3, 4, 0, 1);
strongBeat.attach (fourBeats, 4, 5, 0, 1);
strongBeat.attach (otherBeat, 5, 6, 0, 1);



    // :::: Start/stop :::: //


start_gui.set_label ("start");


stop.set_label ("stop");


startStopContainer.pack_start(start_gui);
startStopContainer.pack_start(stop);



    // :::: Secondary Windows :::: //


openOptions_gui.set_label ("options");


openTuner_gui.set_label ("tuner");

openAnimation.set_label ("animation");


otherContainer.pack_start(openOptions_gui);
otherContainer.pack_start(openTuner_gui);
otherContainer.pack_start(openAnimation);




    // :::: Main container :::: //


mainTable.set_col_spacings(40);
mainTable.set_row_spacings(20);


mainTable.attach(tempoContainer, 0, 1, 0, 1);
mainTable.attach(strongBeat, 1, 2, 0, 1);
mainTable.attach(startStopContainer, 0, 1, 1, 2);
mainTable.attach(otherContainer, 1, 2, 1, 2);





    // :::: Set the events :::: //

start_gui.signal_clicked().connect( sigc::mem_fun(*this, &Main::start) );
 stop.signal_clicked().connect( sigc::mem_fun(*this, &Metronome::stop ) );




changeTempo.signal_value_changed().connect ( sigc::mem_fun ( *this, &Main::updateTempo ) );




   oneBeat.signal_clicked ().connect ( sigc::bind<Gtk::RadioButton*, int>( sigc::mem_fun(*this, &Main::setStrongBeats), &oneBeat,    1 ));
  twoBeats.signal_clicked ().connect ( sigc::bind<Gtk::RadioButton*, int>( sigc::mem_fun(*this, &Main::setStrongBeats), &twoBeats,   2 ));
threeBeats.signal_clicked ().connect ( sigc::bind<Gtk::RadioButton*, int>( sigc::mem_fun(*this, &Main::setStrongBeats), &threeBeats, 3 ));
 fourBeats.signal_clicked ().connect ( sigc::bind<Gtk::RadioButton*, int>( sigc::mem_fun(*this, &Main::setStrongBeats), &fourBeats,  4 ));

otherBeat.signal_value_changed ().connect ( sigc::mem_fun ( *this, &Main::setStrongBeats_fromSpinButton ) );



    // :::: Secondary Windows :::: //

openOptions_gui.signal_clicked().connect ( sigc::mem_fun(*this, &Main::openOptions         ) );
  openTuner_gui.signal_clicked().connect ( sigc::mem_fun(*this, &Main::openTuner           ) );
  openAnimation.signal_clicked().connect ( sigc::mem_fun(*this, &Metronome::openAnimeWindow) );


tuner.signal_hide().connect ( sigc::mem_fun ( *this, &Main::onTunerHide ) );



    // :::: Options (custom) events :::: //

optionsPage.signal_onNormalFrequencyChange ().connect ( sigc::mem_fun ( *this, &Main::setFrequency       ) );
optionsPage.signal_onStrongFrequencyChange ().connect ( sigc::mem_fun ( *this, &Main::setStrongFrequency ) );
optionsPage.signal_onBeatDurationChange    ().connect ( sigc::mem_fun ( *this, &Main::setDuration        ) );



    // :::: Main Gtk::Window :::: //

this->add(mainTable);

this->set_title ("Metronome");

this->set_resizable(false);

this->set_border_width(10);

this->show_all_children();



    // :::: Load configurations :::: //
loadConfigurations ();
}




/*
    Loads the configurations from the external file
 */

void Main::loadConfigurations()
{
    // :: Metronome :: //


setBpm (CONFIGURATIONS.bpm);

    //set the inconsistent state
if (CONFIGURATIONS.strongBeats > 4)
    {
    oneBeat.set_inconsistent (true);
    twoBeats.set_inconsistent (true);
    threeBeats.set_inconsistent (true);
    fourBeats.set_inconsistent (true);

    otherBeat.set_value (CONFIGURATIONS.strongBeats);
    }

else
    {
    switch (CONFIGURATIONS.strongBeats)
        {
        case 1:

            oneBeat.set_active ();
            break;

        case 2:

            twoBeats.set_active ();
            break;

        case 3:

            threeBeats.set_active ();
            break;

        case 4:

            fourBeats.set_active ();
            break;
        }
    }



Metronome::setStrongBeats (CONFIGURATIONS.strongBeats);


setDuration ( CONFIGURATIONS.beatDuration );

setFrequency ( CONFIGURATIONS.normalFrequency );
setStrongFrequency ( CONFIGURATIONS.strongFrequency );


if (CONFIGURATIONS.isPlaying_metro == true)
    {
    Metronome::start();
    }


    // :: Options :: //

optionsPage.loadConfigurations ();

if (CONFIGURATIONS.optionsWindow == true)
    {
    openOptions ();
    }

    // :: Animation :: //

animeWindow.loadConfigurations ();

if (CONFIGURATIONS.animationWindow == true)
    {
    openAnimeWindow ();
    }

    // :: Tuner :: //

tuner.loadConfigurations ();
/*
tuner.setNoteFrequency ( CONFIGURATIONS.noteFrequency_tuner );

    //when changing the note frequency, it triggers an event which starts the tuner
tuner.stop ();

*/

if (CONFIGURATIONS.tunerWindow == true)
    {
    openTuner (); //HERE ao fechar a janela, o metronomo esta sempre parado... (a cena do wasPlaying...)

    if (CONFIGURATIONS.isPlaying_tuner == false)
        {
        tuner.stopPlaying ();
        }

        //bring the tuner window to the front
    //tuner.raise();  //HERE n parece k resulta
    //Glib::signal_timeout().connect(sigc::mem_fun(*this, &Main::test),
	     //                          1000);
    //this->signal_realize().connect ( sigc::mem_fun (*this, &Main::test) );//HERE doesnt work as well
    Glib::signal_idle ().connect ( sigc::mem_fun (*this, &Main::test) ); //HERE melhorar isto (se calhar funcao anonima?)
    }
}


bool Main::test()
{
tuner.raise();  //HERE

    //cancel idle function
return false;
}




/*
    Checks if the tuner is opened, before starting the metronome
 */

void Main::start()
{
    //don't start the metronome when the tuner is opened
if (tuner.isOpened() == true)
    {
    return;
    }

    //carry on
Metronome::start();
}



void Main::updateTempo()
{
int value = changeTempo.get_value_as_int();

this->setBpm (value);
}




//HERE
void Main::setStrongBeats_fromSpinButton ()
{
if (changingStrongBeats == true)
    {
    return;
    }

changingStrongBeats = true;


cout << "Main::setStrongBeats_fromSpinButton\n";


int value = otherBeat.get_value_as_int ();

    //cancel the active RadioButton (if there's one)
if (value > 4)
    {
//    int oldValue = getStrongBeats ();

    oneBeat.set_inconsistent (true);
    twoBeats.set_inconsistent (true);
    threeBeats.set_inconsistent (true);
    fourBeats.set_inconsistent (true);
    }

    // (value <= 4) - set the apropriate RadioButton active
else
    {
    oneBeat.set_inconsistent (false);
    twoBeats.set_inconsistent (false);
    threeBeats.set_inconsistent (false);
    fourBeats.set_inconsistent (false);

    switch (value)
        {
            case 1:

                oneBeat.set_active (true);
                break;

            case 2:

                twoBeats.set_active (true);
                break;

            case 3:

                threeBeats.set_active (true);
                break;

            case 4:

                fourBeats.set_active (true);
                break;
        }
    }

Metronome::setStrongBeats (value);

changingStrongBeats = false;
}


/*
    Sets the strong beats (by calling the same function name in Metronome)

    When one of the Gtk::RadioButton's is set, the Gtk::SpinButton is updated
    When the Gtk::SpinButton is set (to other value than 1-4), then the Gtk::SpinButton is inactive

    Arguments:

        beat: 1 to 4, or 0 when its called from the Gtk::SpinButton
 */

void Main::setStrongBeats (Gtk::RadioButton *button, int beat)
{
    //don't do anything if the spinbutton is already working, or if this event is because of changing the state to inactive
if (changingStrongBeats == true || button->get_active() == false)
    {
    return;
    }


changingStrongBeats = true;


    //if the previous value was > 4 (which triggers the inconsistent state on the RadioButton)
    //then remove the inconsistent state
if (getStrongBeats() > 4)
    {
    oneBeat.set_inconsistent (false);
    twoBeats.set_inconsistent (false);
    threeBeats.set_inconsistent (false);
    fourBeats.set_inconsistent (false);
    }


    Metronome::setStrongBeats (beat);

    //update the SpinButton
otherBeat.set_value (beat);





changingStrongBeats = false;
}



void Main::openOptions()
{
optionsPage.open();
//Metronome::openOptions();
}




void Main::openTuner()
{
if (Tempo::isPlaying() == true) //HERE devia ter Metronome::isPlaying() - mesmo nome no Sound e Tempo
    {
    Metronome::stop();

    wasPlaying_var = true;
    }

else
    {
    wasPlaying_var = false;
    }


tuner.open();
}



void Main::onTunerHide()
{
if (wasPlaying_var == true)
    {
    Metronome::start();
    }
}




/*
    Saves the program state to a file
 */

Main::~Main ()
{
std::ofstream config;

config.open ("config.txt", std::ios::out | std::ios::trunc);

if (config.is_open() == true)
    {
    config << "Metronome - configuration file\n\n";

    config << "Opened windows\n";
    config << "    options: " << optionsPage.isOpened() << "\n";
    config << "    tuner: " << tuner.isOpened() << "\n";
    config << "    animation: " << isAnimeOpened() << "\n";

    config << "\nMetronome\n";
    config << "    isPlaying_metro: " << Tempo::isPlaying() << "\n";
    config << "    bpm: " << getBpm() << "\n";
    config << "    strongBeats: " << getStrongBeats() << "\n";

    config << "\nOptions\n";
    config << "    beatDuration: " << getDuration() << "\n";
    config << "    normalFrequency: " << getNormalFrequency() << "\n";
    config << "    strongFrequency: " << getStrongFrequency() << "\n";

    config << "\nAnimation\n";

    Gdk::RGBA color = animeWindow.getColor ();

    config << "    normalColor-red: " << color.get_red () << "\n";
    config << "    normalColor-green: " << color.get_green () << "\n";
    config << "    normalColor-blue: " << color.get_blue () << "\n";
    config << "    normalColor-alpha: " << color.get_alpha () << "\n";

    color = animeWindow.getStrongColor ();

    config << "    strongColor-red: " << color.get_red () << "\n";
    config << "    strongColor-green: " << color.get_green () << "\n";
    config << "    strongColor-blue: " << color.get_blue () << "\n";
    config << "    strongColor-alpha: " << color.get_alpha () << "\n";

    config << "\nTuner\n";

    config << "    isPlaying_tuner: " << tuner.isPlaying () << "\n";
    config << "    noteFrequency_tuner: " << tuner.getNormalFrequency () << "\n";

    config.close ();
    }

else
    {
    cout << "failed opening the config.txt file\n";
    }

}
