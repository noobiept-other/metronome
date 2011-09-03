#include "main.h"

#include "metronome.h"


//#include "metronome.h"

#include "animeWindow.h"


/*

    To doo:


        window.set_icon() ou .set_icon_from_file()
            (e fazer o icon)

        o tuner tem mts erros por lah


        gravar a posicao da janela no monitor e dps ao iniciar o programa mover para essa posicao
            convem verificar se essa posicao nao fica fora do monitor (por exemplo usar as mesmas configuracoes
                                                                        em 2 pcs com monitores diferentes)
                ver o tamanho maximo, e se passar esse limite ajustar os valores



        quando se tem os strong beats acima de 4, desactivar os SpinButton activo

 */








int main (int argc, char** argv)
{
Gtk::Main kit(argc, argv);

Gst::init (argc, argv);


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

    //HERE por isto num try() catch() --just in case
loadConfigurations();




    // :::: Tempo related :::: //


setBpm (configurations.bpm);

tempoName.set_label ("Tempo: ");

tempoBpm.set_label ("bpm");


    //start at 60, with limits from 30 to 300 - step is 1
Glib::RefPtr<Gtk::Adjustment> tempoAdjustment (Gtk::Adjustment::create(configurations.bpm, 30, 300, 1, 5, 0));

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


//fourBeats.set_active();
switch (configurations.strongBeats)
    {
        case 1:

            oneBeat.set_active();
            break;

        case 2:

            twoBeats.set_active();
            break;

        case 3:

            threeBeats.set_active ();
            break;

        case 4:

            fourBeats.set_active ();
            break;
    }


Metronome::setStrongBeats (configurations.strongBeats);


Glib::RefPtr<Gtk::Adjustment> otherBeatAdjustment (Gtk::Adjustment::create(configurations.strongBeats, 1, 10, 1, 2, 0));

otherBeat.set_adjustment (otherBeatAdjustment);
otherBeat.set_numeric (true);



strongBeat.attach (strongBeatLabel, 0, 1, 0, 1);
strongBeat.attach (oneBeat, 1, 2, 0, 1);
strongBeat.attach (twoBeats, 2, 3, 0, 1);
strongBeat.attach (threeBeats, 3, 4, 0, 1);
strongBeat.attach (fourBeats, 4, 5, 0, 1);
strongBeat.attach (otherBeat, 5, 6, 0, 1);



    // :::: Start/stop :::: //


start.set_label ("start");


stop.set_label ("stop");


startStopContainer.pack_start(start);
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

start.signal_clicked().connect( sigc::mem_fun(*this, &Metronome::start) );
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


if (configurations.isPlaying_metro == true)
    {
    Metronome::start();
    }


    // :::: Opened windows :::: //

if (configurations.optionsWindow == true)
    {
    openOptions ();
    }

if (configurations.tunerWindow == true)
    {
    openTuner ();
    }

if (configurations.animationWindow == true)
    {
    openAnimeWindow ();
    }
}



void Main::startMetronome()
{
    //don't start the metronome when the tuner is opened
if (tuner.isOpened() == true)
    {
    return;
    }

    //carry on
Tempo::start();
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
    int oldValue = getStrongBeats ();

    switch (oldValue)
        {
            case 1:

                oneBeat.set_active (false);
                break;

            case 2:

                twoBeats.set_active (false);
                break;

            case 3:

                threeBeats.set_active (false);
                break;

            case 4:
cout << "fourBeat\n"; //HERE nao tira o estado activo
                fourBeats.set_active (false);
                break;
        }
    }

    // (value <= 4) - set the apropriate RadioButton active
else
    {
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


cout << "Main::setStrongBeats beat: " << beat << endl;

    //one of the RadioButton was pressed
if (beat != 0)
    {
    Metronome::setStrongBeats (beat);

        //update the SpinButton
    otherBeat.set_value (beat);
    }

    //the SpinButton's value was changed
else
    {
    int value = otherBeat.get_value_as_int ();

        //cancel the active RadioButton (if there's one)
    if (value > 4)
        {
            cout << "value > 4 BEFORE .set_active(false)\n";

        int oldValue = getStrongBeats ();

        switch (oldValue)
            {
                case 1:

                    oneBeat.set_active (false);
                    break;

                case 2:

                    twoBeats.set_active (false);
                    break;

                case 3:

                    threeBeats.set_active (false);
                    break;

                case 4:

                    fourBeats.set_active (false);
                    break;
            }

        cout << "after .set_active(false)\n";
        }

        // (value <= 4) - set the apropriate RadioButton active
    else
        {
            cout << "value <= 4\n";

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

cout << "value " << value << endl;

    Metronome::setStrongBeats (value);
    }


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



void Main::loadConfigurations ()
{
    //set the defaults
configurations.optionsWindow   = false;
configurations.tunerWindow     = false;
configurations.animationWindow = false;

configurations.isPlaying_metro = true;
configurations.bpm             = 60;
configurations.strongBeats     = 4;

configurations.beatDuration    = 200;   //200 ms
configurations.normalFrequency = 440;   //A4 - 440 Hz
configurations.strongFrequency = 440 + 150; //HERE hmmm

configurations.normalColor.set_rgba (0, 0, 1, 1);    //blue color
configurations.strongColor.set_rgba (1, 0, 1, 1);   //HERE hmmm

configurations.isPlaying_tuner = false;
configurations.tunerNote.newNote (configurations.normalFrequency);






std::ifstream config;

config.open ("config.txt");

if (config.is_open() == true)
    {
    std::string line;


    int value;


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
        configurations.optionsWindow = true;
        //openOptions();
        }

        // :::: Tuner window :::: //

    getline (config, line);

    value = getPropertyValue(line, "tuner");


    if (value != 0)
        {
        configurations.tunerWindow = true;
        //openTuner();
        }

        // :::: Animation window :::: //


    getline (config, line);


    value = getPropertyValue(line, "animation");


    if (value != 0)
        {
        configurations.animationWindow = true;
        //openAnimeWindow();
        }


        // :::: Metronome :::: //

    getline (config, line);
    getline (config, line);


        // :::: isPlaying :::: //

    getline (config, line);

    value = getPropertyValue(line, "isPlaying");

    if (value == 0)
        {
        configurations.isPlaying_metro = false;
        }

        // :::: Bpm :::: //

    getline (config, line);

    value = getPropertyValue(line, "bpm");

    configurations.bpm = value;

    //setBpm (value);

//HERE melhorar a ordem disto...

    //changeTempo.set_value (value);


        // :::: Strong beat :::: //

    getline (config, line);


    value = getPropertyValue(line, "strongBeats");


    configurations.strongBeats = value;
/*
    if (value == 1)
        {
        oneBeat.set_active();
        }

    else if (value == 2)
        {
        twoBeats.set_active();
        }

    else if (value == 3)
        {
        threeBeats.set_active();
        }

    else if (value == 4)
        {
        fourBeats.set_active();
        }

    else
        {
        //HERE the Gtk::Entry otherBeat
        }

*/

    config.close();
    }
}



/*
    Searches a string for a property, and returns that property's value
        (in the form -> property: value)

 */

int Main::getPropertyValue (string line, string property)
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

string theNumber = line.substr (i);


std::stringstream stream (theNumber);

int number = 0;

stream >> number;   //HERE testar qd nao encontra um numero...

return number;
}



/*
    What is saved:

    Opened windows :

        options
        tuner
        animation

    Metronome :

        isPlaying
        bpm          (done)
        strongBeats  (done)

    Options :

        beatDuration
        normalFrequency
        strongFrequency


    Animation :

        normalColor
        strongColor

    Tuner :

        isPlaying
        tunerNote

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
    config << "    isPlaying: " << Tempo::isPlaying() << "\n";
    config << "    bpm: " << getBpm() << "\n";
    config << "    strongBeats: " << getStrongBeats() << "\n";


    config.close ();
    }

else
    {
    cout << "failed opening the config.txt file\n";
    }

}




/*

int main(int argc, char *argv[])
{
Gtk::Main kit(argc, argv);

Gst::init (argc, argv);



Gtk::Window window;


    //2 row and 2 columns
Gtk::Table mainTable (2, 2);
//Gtk::Table mainTable (2, 3);

//Gtk::VolumeButton volume;   //HERE nao existe?...

//mainTable.attach(2, 3, 0, 2);

mainTable.set_col_spacings(40);
mainTable.set_row_spacings(20);



Gtk::Table tempoContainer (1, 3);

tempoContainer.set_col_spacings(10);

Gtk::Label tempoName ("Tempo: ");


Gdk::RGBA blue("blue");
tempoName.override_color(blue);





Gtk::Label tempoBpm ("bpm");


    //start at 60, with limits from 30 to 300 - step is 1
Glib::RefPtr<Gtk::Adjustment> tempoAdjustment (Gtk::Adjustment::create(60, 30, 300, 1, 5, 0));

Gtk::SpinButton changeTempo(tempoAdjustment);
changeTempo.set_numeric (true);



tempoContainer.attach(tempoName, 0, 1, 0, 1);
tempoContainer.attach(changeTempo, 1, 2, 0, 1);
tempoContainer.attach(tempoBpm, 2, 3, 0, 1);





Gtk::Table strongBeat(1, 6);

strongBeat.set_col_spacings(10);


Gtk::Label strongBeatLabel ("Strong beat");


Gtk::Button oneBeat ("1");

Gtk::Button twoBeats ("2");

Gtk::Button threeBeats ("3");

Gtk::Button fourBeats ("4");

Gtk::Entry otherBeat;

//otherBeat.set_numeric(true);  //HERE tb devia existir para a Gtk::Entry

oneBeat.override_color(blue);
oneBeat.override_background_color(blue);


otherBeat.set_width_chars(2);
otherBeat.set_max_length(2);


strongBeat.attach (strongBeatLabel, 0, 1, 0, 1);
strongBeat.attach (oneBeat, 1, 2, 0, 1);
strongBeat.attach (twoBeats, 2, 3, 0, 1);
strongBeat.attach (threeBeats, 3, 4, 0, 1);
strongBeat.attach (fourBeats, 4, 5, 0, 1);
strongBeat.attach (otherBeat, 5, 6, 0, 1);




Gtk::HBox startStopContainer;

//startStopContainer.set_spacing(10);



Gtk::Button start ("start");



Gdk::RGBA color("blue");
start.override_background_color(color);

//HERE doesnt work
start.override_background_color(blue, Gtk::STATE_FLAG_NORMAL | Gtk::STATE_FLAG_ACTIVE | Gtk::STATE_FLAG_PRELIGHT |
                                Gtk::STATE_FLAG_SELECTED | Gtk::STATE_FLAG_INSENSITIVE | Gtk::STATE_FLAG_INCONSISTENT |
                                Gtk::STATE_FLAG_FOCUSED );

//start.override_color(blue);

Gtk::Button stop ("stop");


startStopContainer.pack_start(start);
startStopContainer.pack_start(stop);



//Gtk::VBox tunerContainer;
Gtk::HBox otherContainer;


Gtk::Button openOptions ("options");


Gtk::Button openTuner ("tuner");

Gtk::Button openAnimation ("animation");


otherContainer.pack_start(openOptions);
otherContainer.pack_start(openTuner);
otherContainer.pack_start(openAnimation);


mainTable.attach(tempoContainer, 0, 1, 0, 1);
mainTable.attach(strongBeat, 1, 2, 0, 1);
mainTable.attach(startStopContainer, 0, 1, 1, 2);
mainTable.attach(otherContainer, 1, 2, 1, 2);



Metronome metronome;
metronome.start();


    //set the events

start.signal_clicked().connect( sigc::mem_fun(metronome, &Metronome::start) );
stop.signal_clicked().connect( sigc::mem_fun(metronome, &Metronome::stop) );





changeTempo.signal_value_changed().connect (
                        sigc::bind<Metronome*, Gtk::SpinButton*>(
                                sigc::ptr_fun(update_tempo), &metronome, &changeTempo
                                       ));





oneBeat.signal_clicked().connect ( sigc::bind<int>( sigc::mem_fun(metronome, &Metronome::setStrongBeats), 1 ));

twoBeats.signal_clicked().connect ( sigc::bind<int>( sigc::mem_fun(metronome, &Metronome::setStrongBeats), 2 ));

threeBeats.signal_clicked().connect ( sigc::bind<int>( sigc::mem_fun(metronome, &Metronome::setStrongBeats), 3 ));

fourBeats.signal_clicked().connect ( sigc::bind<int>( sigc::mem_fun(metronome, &Metronome::setStrongBeats), 4 ));





openOptions.signal_clicked().connect ( sigc::mem_fun(metronome, &Metronome::openOptions) );


openTuner.signal_clicked().connect ( sigc::mem_fun(metronome, &Metronome::openTuner) );

//openAnimation.signal_clicked().connect( sigc::mem_fun(anime, &Animation::open) );
openAnimation.signal_clicked().connect( sigc::mem_fun(metronome, &Metronome::openAnimeWindow) );
//HERE abrir a janela




//m_adjustment_digits->signal_value_changed().connect( sigc::mem_fun(*this,
  //            &ExampleWindow::on_spinbutton_digits_changed) );
//m_button1.signal_clicked().connect(sigc::bind<Glib::ustring>(
  //            sigc::mem_fun(*this, &HelloWorld::on_button_clicked), "button 1"));
//start.signal_clicked().connect( sigc::mem_fun(metronome, &Metronome::start) );


window.add(mainTable);

window.set_title ("Metronome");

window.set_resizable(false);

window.set_border_width(10);

window.show_all_children();


Gtk::Main::run(window);

return EXIT_SUCCESS;
}
*/
