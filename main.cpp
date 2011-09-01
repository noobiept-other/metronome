#include "main.h"

#include "metronome.h"


//#include "metronome.h"

#include "animeWindow.h"


/*

    To doo:

        ver como se consegue mudar o layout (estilo css.. style dos elementos)


        gravar o estado das janelas (se a animacao estava aberta... etc)

        Opcoes:

            beat duration
            normal frequency
            strong frequency


            bpm
            strong beats

            normal color
            strong color

            is animation open
            is tuner open
                which note

            is options open


        window.set_icon() ou .set_icon_from_file()
            (e fazer o icon)

        o tuner tem mts erros por lah


        criar uma classe de base para a Window, k controla a isOpened_var e poe os atalhos de teclado (esc fecha a janela), etc


        ter um objecto com as opcoes normais (default) - assim qd esta a ler do ficheiro, se falhar alguma coisa ele le deste objecto...


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

    : wasPlaying_var (true),
      mainTable (2, 2),
      tempoContainer (1, 3),
      strongBeat (1, 6)


{
mainTable.set_col_spacings(40);
mainTable.set_row_spacings(20);


tempoContainer.set_col_spacings(10);

tempoName.set_label ("Tempo: ");

tempoBpm.set_label ("bpm");


    //start at 60, with limits from 30 to 300 - step is 1
Glib::RefPtr<Gtk::Adjustment> tempoAdjustment (Gtk::Adjustment::create(60, 30, 300, 1, 5, 0));

changeTempo.set_adjustment (tempoAdjustment);
changeTempo.set_numeric (true);



tempoContainer.attach(tempoName, 0, 1, 0, 1);
tempoContainer.attach(changeTempo, 1, 2, 0, 1);
tempoContainer.attach(tempoBpm, 2, 3, 0, 1);



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


fourBeats.set_active();
//otherBeat.set_numeric(true);  //HERE tb devia existir para a Gtk::Entry

//oneBeat.override_color(blue);
//oneBeat.override_background_color(blue);


otherBeat.set_width_chars(2);
otherBeat.set_max_length(2);


strongBeat.attach (strongBeatLabel, 0, 1, 0, 1);
strongBeat.attach (oneBeat, 1, 2, 0, 1);
strongBeat.attach (twoBeats, 2, 3, 0, 1);
strongBeat.attach (threeBeats, 3, 4, 0, 1);
strongBeat.attach (fourBeats, 4, 5, 0, 1);
strongBeat.attach (otherBeat, 5, 6, 0, 1);



start.set_label ("start");



Gdk::RGBA color("blue");
start.override_background_color(color);

//HERE doesnt work
start.override_background_color(color, Gtk::STATE_FLAG_NORMAL | Gtk::STATE_FLAG_ACTIVE | Gtk::STATE_FLAG_PRELIGHT |
                                Gtk::STATE_FLAG_SELECTED | Gtk::STATE_FLAG_INSENSITIVE | Gtk::STATE_FLAG_INCONSISTENT |
                                Gtk::STATE_FLAG_FOCUSED );

//start.override_color(blue);

stop.set_label ("stop");


startStopContainer.pack_start(start);
startStopContainer.pack_start(stop);


openOptions_gui.set_label ("options");


openTuner_gui.set_label ("tuner");

openAnimation.set_label ("animation");


otherContainer.pack_start(openOptions_gui);
otherContainer.pack_start(openTuner_gui);
otherContainer.pack_start(openAnimation);


mainTable.attach(tempoContainer, 0, 1, 0, 1);
mainTable.attach(strongBeat, 1, 2, 0, 1);
mainTable.attach(startStopContainer, 0, 1, 1, 2);
mainTable.attach(otherContainer, 1, 2, 1, 2);





    //set the events

start.signal_clicked().connect( sigc::mem_fun(*this, &Metronome::start) );
stop.signal_clicked().connect( sigc::mem_fun(*this, &Metronome::stop) );





//changeTempo.signal_value_changed().connect (
  //                      sigc::bind<Main*, Gtk::SpinButton*>(
    //                            sigc::ptr_fun(update_tempo), this, &changeTempo
      //                                 ));
changeTempo.signal_value_changed().connect ( sigc::mem_fun ( *this, &Main::updateTempo ) );




oneBeat.signal_clicked().connect ( sigc::bind<int>( sigc::mem_fun(*this, &Metronome::setStrongBeats), 1 ));

twoBeats.signal_clicked().connect ( sigc::bind<int>( sigc::mem_fun(*this, &Metronome::setStrongBeats), 2 ));

threeBeats.signal_clicked().connect ( sigc::bind<int>( sigc::mem_fun(*this, &Metronome::setStrongBeats), 3 ));

fourBeats.signal_clicked().connect ( sigc::bind<int>( sigc::mem_fun(*this, &Metronome::setStrongBeats), 4 ));





openOptions_gui.signal_clicked().connect ( sigc::mem_fun(*this, &Main::openOptions) );


openTuner_gui.signal_clicked().connect ( sigc::mem_fun(*this, &Main::openTuner) );

//openAnimation.signal_clicked().connect( sigc::mem_fun(anime, &Animation::open) );
openAnimation.signal_clicked().connect( sigc::mem_fun(*this, &Metronome::openAnimeWindow) );
//HERE abrir a janela

tuner.signal_onTunerHide().connect ( sigc::mem_fun ( *this, &Main::onTunerHide ) );


//m_adjustment_digits->signal_value_changed().connect( sigc::mem_fun(*this,
  //            &ExampleWindow::on_spinbutton_digits_changed) );
//m_button1.signal_clicked().connect(sigc::bind<Glib::ustring>(
  //            sigc::mem_fun(*this, &HelloWorld::on_button_clicked), "button 1"));
//start.signal_clicked().connect( sigc::mem_fun(metronome, &Metronome::start) );


    // :::: Options events :::: //

optionsPage.signal_onNormalFrequencyChange().connect ( sigc::mem_fun ( *this, &Main::setFrequency ) );
optionsPage.signal_onStrongFrequencyChange().connect ( sigc::mem_fun ( *this, &Main::setStrongFrequency ) );

optionsPage.signal_onBeatDurationChange ().connect ( sigc::mem_fun ( *this, &Main::setDuration ) );


this->add(mainTable);

this->set_title ("Metronome");

this->set_resizable(false);

this->set_border_width(10);

this->show_all_children();


    //HERE por isto num try() catch() --just in case
loadConfigurations();


//Metronome metronome;
Metronome::start();
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
        openOptions();
        }

        // :::: Tuner window :::: //

    getline (config, line);

    value = getPropertyValue(line, "tuner");


    if (value != 0)
        {
        openTuner();
        }

        // :::: Animation window :::: //


    getline (config, line);


    value = getPropertyValue(line, "animation");


    if (value != 0)
        {
        openAnimeWindow();
        }


        // :::: Options :::: //

    getline (config, line);
    getline (config, line);

        // :::: Bpm :::: //

    getline (config, line);

    number = getPropertyValue(line, "bpm");


    setBpm (number);

//HERE melhorar a ordem disto...

    changeTempo.set_value (number);


        // :::: Strong beat :::: //

    getline (config, line);


    number = getPropertyValue(line, "strong-beats");


    if (number == 1)
        {
        oneBeat.set_active();
        }

    else if (number == 2)
        {
        twoBeats.set_active();
        }

    else if (number == 3)
        {
        threeBeats.set_active();
        }

    else if (number == 4)
        {
        fourBeats.set_active();
        }

    else
        {
        //HERE the Gtk::Entry otherBeat
        }



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

    config << "\nOptions\n";
    config << "    bpm: " << getBpm() << "\n";
    config << "    strong-beats: " << getStrongBeats() << "\n";


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
