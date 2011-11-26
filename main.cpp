#include "main.h"

#include "configurations.h"


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

    : changingStrongBeats_var (false),

      wasPlaying_var (false),

      mainTable_ui (2, 2),
      tempoContainer_ui (1, 3),
      strongBeat_ui (1, 6)

{
    // :::: Tempo related :::: //


tempoName_ui.set_label ("Tempo: ");

tempoBpm_ui.set_label ("bpm");


    //start at 60, with limits from 30 to 300 - step is 1
Glib::RefPtr<Gtk::Adjustment> tempoAdjustment (

       Gtk::Adjustment::create (CONFIGURATIONS.bpm,
                                CONFIGURATIONS.bpmLowerLimit,
                                CONFIGURATIONS.bpmUpperLimit, 1, 5, 0)

                                              );

changeTempo_ui.set_adjustment (tempoAdjustment);
changeTempo_ui.set_numeric (true);



tempoContainer_ui.attach (tempoName_ui, 0, 1, 0, 1);
tempoContainer_ui.attach (changeTempo_ui, 1, 2, 0, 1);
tempoContainer_ui.attach (tempoBpm_ui, 2, 3, 0, 1);

tempoContainer_ui.set_col_spacings (10);



    // :::: Strong beat :::: //


strongBeat_ui.set_col_spacings (10);


strongBeatLabel_ui.set_label ("Strong beat");


oneBeat_ui.set_label ("1");

twoBeats_ui.set_label ("2");

threeBeats_ui.set_label ("3");

fourBeats_ui.set_label ("4");


Gtk::RadioButton::Group group = oneBeat_ui.get_group();

twoBeats_ui.set_group   (group);
threeBeats_ui.set_group (group);
fourBeats_ui.set_group  (group);


Glib::RefPtr<Gtk::Adjustment> otherBeatAdjustment (

       Gtk::Adjustment::create(CONFIGURATIONS.strongBeats,
                               1,               //the lower limit
                               CONFIGURATIONS.strongBeatsUpperLimit, 1, 2, 0)

                                                  );

otherBeat_ui.set_adjustment (otherBeatAdjustment);
otherBeat_ui.set_numeric (true);



strongBeat_ui.attach (strongBeatLabel_ui, 0, 1, 0, 1);
strongBeat_ui.attach (oneBeat_ui, 1, 2, 0, 1);
strongBeat_ui.attach (twoBeats_ui, 2, 3, 0, 1);
strongBeat_ui.attach (threeBeats_ui, 3, 4, 0, 1);
strongBeat_ui.attach (fourBeats_ui, 4, 5, 0, 1);
strongBeat_ui.attach (otherBeat_ui, 5, 6, 0, 1);



    // :::: Start/stop_ui :::: //


start_ui.set_label ("start");


stop_ui.set_label ("stop");


startStopContainer_ui.pack_start(start_ui);
startStopContainer_ui.pack_start(stop_ui);



    // :::: Secondary Windows :::: //


openOptions_ui.set_label ("options");


openTuner_ui.set_label ("tuner");

openAnimation_ui.set_label ("animation");


otherContainer_ui.pack_start (openOptions_ui);
otherContainer_ui.pack_start (openTuner_ui);
otherContainer_ui.pack_start (openAnimation_ui);




    // :::: Main container :::: //


mainTable_ui.set_col_spacings (40);
mainTable_ui.set_row_spacings (20);


mainTable_ui.attach (tempoContainer_ui, 0, 1, 0, 1);
mainTable_ui.attach (strongBeat_ui, 1, 2, 0, 1);
mainTable_ui.attach (startStopContainer_ui, 0, 1, 1, 2);
mainTable_ui.attach (otherContainer_ui, 1, 2, 1, 2);





    // :::: Set the events :::: //

start_ui.signal_clicked().connect ( sigc::mem_fun(*this, &Main::start) );
 stop_ui.signal_clicked().connect ( sigc::mem_fun(*this, &Metronome::stop ) );




changeTempo_ui.signal_value_changed().connect ( sigc::mem_fun ( *this, &Main::updateTempo ) );




   oneBeat_ui.signal_clicked ().connect ( sigc::bind<Gtk::RadioButton*, int>( sigc::mem_fun(*this, &Main::setStrongBeats), &oneBeat_ui,    1 ));
  twoBeats_ui.signal_clicked ().connect ( sigc::bind<Gtk::RadioButton*, int>( sigc::mem_fun(*this, &Main::setStrongBeats), &twoBeats_ui,   2 ));
threeBeats_ui.signal_clicked ().connect ( sigc::bind<Gtk::RadioButton*, int>( sigc::mem_fun(*this, &Main::setStrongBeats), &threeBeats_ui, 3 ));
 fourBeats_ui.signal_clicked ().connect ( sigc::bind<Gtk::RadioButton*, int>( sigc::mem_fun(*this, &Main::setStrongBeats), &fourBeats_ui,  4 ));

otherBeat_ui.signal_value_changed ().connect ( sigc::mem_fun ( *this, &Main::setStrongBeats_fromSpinButton ) );



    // :::: Secondary Windows :::: //

  openOptions_ui.signal_clicked().connect ( sigc::mem_fun(*this, &Main::openOptions         ) );
    openTuner_ui.signal_clicked().connect ( sigc::mem_fun(*this, &Main::openTuner           ) );
openAnimation_ui.signal_clicked().connect ( sigc::mem_fun(*this, &Metronome::openAnimeWindow) );


tuner_var.signal_hide().connect ( sigc::mem_fun ( *this, &Main::onTunerHide ) );



    // :::: Options (custom) events :::: //

optionsPage_var.signal_onNormalFrequencyChange ().connect ( sigc::mem_fun ( *this, &Main::setFrequency       ) );
optionsPage_var.signal_onStrongFrequencyChange ().connect ( sigc::mem_fun ( *this, &Main::setStrongFrequency ) );
optionsPage_var.signal_onBeatDurationChange    ().connect ( sigc::mem_fun ( *this, &Main::setDuration        ) );



    // :::: Main Gtk::Window :::: //

this->add (mainTable_ui);

this->set_title ("Metronome");

this->set_resizable (false);

this->set_border_width (10);

this->show_all_children();



    // :::: Load configurations :::: //

loadConfigurations ();
}




/*
    Loads the configurations from the global variable CONFIGURATIONS
 */

void Main::loadConfigurations()
{
    // :: Main window :: //

    //means it has a valid position for the main window
if (CONFIGURATIONS.mainPosition_x >= 0)
    {
    this->move (CONFIGURATIONS.mainPosition_x, CONFIGURATIONS.mainPosition_y);
    }

    // :: Metronome :: //


setBpm (CONFIGURATIONS.bpm);

    //set the inconsistent state
if (CONFIGURATIONS.strongBeats > 4)
    {
    oneBeat_ui.set_inconsistent (true);
    twoBeats_ui.set_inconsistent (true);
    threeBeats_ui.set_inconsistent (true);
    fourBeats_ui.set_inconsistent (true);

    otherBeat_ui.set_value (CONFIGURATIONS.strongBeats);
    }

else
    {
    switch (CONFIGURATIONS.strongBeats)
        {
        case 1:

            oneBeat_ui.set_active ();
            break;

        case 2:

            twoBeats_ui.set_active ();
            break;

        case 3:

            threeBeats_ui.set_active ();
            break;

        case 4:

            fourBeats_ui.set_active ();
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

optionsPage_var.loadConfigurations ();


    //when there's no configuration file, this will have the -1 value
if (CONFIGURATIONS.optionsPosition_x >= 0)
    {
    optionsPage_var.setPosition (CONFIGURATIONS.optionsPosition_x, CONFIGURATIONS.optionsPosition_y);
    }



if (CONFIGURATIONS.optionsWindow == true)
    {
    openOptions ();
    }

    // :: Animation :: //

animeWindow.loadConfigurations ();


    //when there's no configuration file, this will have the -1 value
if (CONFIGURATIONS.animationPosition_x >= 0)
    {
    animeWindow.setPosition (CONFIGURATIONS.animationPosition_x, CONFIGURATIONS.animationPosition_y);
    }



if (CONFIGURATIONS.animationWindow == true)
    {
    openAnimeWindow ();
    }

    // :: Tuner :: //

tuner_var.loadConfigurations ();


    //when there's no configuration file, this will have the -1 value
if (CONFIGURATIONS.tunerPosition_x >= 0)
    {
    tuner_var.setPosition (CONFIGURATIONS.tunerPosition_x, CONFIGURATIONS.tunerPosition_y);
    }


    //open the tuner window from the start
if (CONFIGURATIONS.tunerWindow == true)
    {
    openTuner ();

        //the metronome could have been playing (before opening the tuner window, so lets just update the variable)
    this->wasPlaying_var = CONFIGURATIONS.wasPlaying_metro;


    if (CONFIGURATIONS.isPlaying_tuner == false)
        {
        tuner_var.stopPlaying ();
        }

        //bring the tuner window to the front (since the main window is still not done, we're attaching a function
        //to be called whenever there's nothing to do)
        //HERE could use an anonymous function here, but doesn't seem to work with sigc
    Glib::signal_idle ().connect ( sigc::mem_fun (*this, &Main::bringTunerToFront) );
    //Glib::signal_idle ().connect ( sigc::ptr_fun ( [this] () -> bool { this->tuner.raise (); return false; } ) );
    }
}


bool Main::bringTunerToFront()
{
tuner_var.raise();

    //cancel idle function
return false;
}




/*
    Checks if the tuner is opened, before starting the metronome
 */

void Main::start()
{
    //don't start the metronome when the tuner is opened
if (tuner_var.isOpened() == true)
    {
    return;
    }

    //carry on
Metronome::start();
}



void Main::updateTempo()
{
int value = changeTempo_ui.get_value_as_int();

this->setBpm (value);
}





/*
    //HERE o setStrongBeats esta separado em 2 funcoes, devido a ao alterar os valores, activar os eventos
    dos RadioButton. Assim controla-se isso, com uma flag (changingStrongBeats_var)
 */

void Main::setStrongBeats_fromSpinButton ()
{
if (changingStrongBeats_var == true)
    {
    return;
    }

changingStrongBeats_var = true;



int value = otherBeat_ui.get_value_as_int ();

    //cancel the active RadioButton (if there's one)
if (value > 4)
    {
    oneBeat_ui.set_inconsistent (true);
    twoBeats_ui.set_inconsistent (true);
    threeBeats_ui.set_inconsistent (true);
    fourBeats_ui.set_inconsistent (true);
    }

    // (value <= 4) - set the apropriate RadioButton active
else
    {
    oneBeat_ui.set_inconsistent (false);
    twoBeats_ui.set_inconsistent (false);
    threeBeats_ui.set_inconsistent (false);
    fourBeats_ui.set_inconsistent (false);

    switch (value)
        {
            case 1:

                oneBeat_ui.set_active (true);
                break;

            case 2:

                twoBeats_ui.set_active (true);
                break;

            case 3:

                threeBeats_ui.set_active (true);
                break;

            case 4:

                fourBeats_ui.set_active (true);
                break;
        }
    }

Metronome::setStrongBeats (value);

changingStrongBeats_var = false;
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
if (changingStrongBeats_var == true || button->get_active() == false)
    {
    return;
    }


changingStrongBeats_var = true;


    //if the previous value was > 4 (which triggers the inconsistent state on the RadioButton)
    //then remove the inconsistent state
if (getStrongBeats() > 4)
    {
    oneBeat_ui.set_inconsistent (false);
    twoBeats_ui.set_inconsistent (false);
    threeBeats_ui.set_inconsistent (false);
    fourBeats_ui.set_inconsistent (false);
    }


    Metronome::setStrongBeats (beat);

    //update the SpinButton
otherBeat_ui.set_value (beat);



changingStrongBeats_var = false;
}





void Main::openOptions()
{
    //if the window is already opened, just bring it to the front
if (optionsPage_var.isOpened() == true)
    {
    optionsPage_var.raise ();
    }

else
    {
    optionsPage_var.open();
    }
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


    //if the window is opened, then bring it to the front
if (tuner_var.isOpened () == true)
    {
    tuner_var.raise ();
    }

else
    {
    tuner_var.open();
    }
}



void Main::onTunerHide()
{
if (wasPlaying_var == true)
    {
    Metronome::start();
    }
}




/*
    Called when the main window is closed.
    saves the position of the window
 */

void Main::on_hide ()
{
int x, y;

this->get_position (x, y);

CONFIGURATIONS.mainPosition_x = x;
CONFIGURATIONS.mainPosition_y = y;


Gtk::Window::on_hide ();
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
    int x, y;

    config << "Metronome - configuration file\n\n";

    config << "Opened windows\n";
    config << "    options: " << optionsPage_var.isOpened() << "\n";
    config << "    tuner: " << tuner_var.isOpened() << "\n";
    config << "    animation: " << animeWindow.isOpened() << "\n";

    config << "\nWindow's position\n";

        //this is updated on the on_hide() function (called when the main window is closed)
    config << "    main-x: " << CONFIGURATIONS.mainPosition_x << "\n";
    config << "    main-y: " << CONFIGURATIONS.mainPosition_y << "\n";

        //get the position of the window
    if (optionsPage_var.isOpened() == true)
        {
        optionsPage_var.getPosition (x, y);
        }

        //let the window go to the default position next time the program starts
    else
        {
        x = -1;
        y = -1;
        }


    config << "    options-x: " << x << "\n";
    config << "    options-y: " << y << "\n";

        //get the position of the window
    if (tuner_var.isOpened() == true)
        {
        tuner_var.getPosition (x, y);
        }

        //let the window go to the default position next time the program starts
    else
        {
        x = -1;
        y = -1;
        }


    config << "    tuner-x: " << x << "\n";
    config << "    tuner-y: " << y << "\n";


            //get the position of the window
    if (animeWindow.isOpened() == true)
        {
        animeWindow.getPosition (x, y);
        }

        //let the window go to the default position next time the program starts
    else
        {
        x = -1;
        y = -1;
        }

    config << "    animation-x: " << x << "\n";
    config << "    animation-y: " << y << "\n";

    config << "\nMetronome\n";
    config << "    isPlaying_metro: " << Tempo::isPlaying() << "\n";
    config << "    wasPlaying_metro: " << this->wasPlaying_var << "\n";
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

    config << "    isPlaying_tuner: " << tuner_var.isPlaying () << "\n";
    config << "    noteFrequency_tuner: " << tuner_var.getNormalFrequency () << "\n";

    config.close ();
    }

else
    {
    std::cout << "failed opening the config.txt file\n";
    }

}
