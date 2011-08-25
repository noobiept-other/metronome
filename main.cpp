#include <gtkmm.h>

#include "metronome.h"

#include "animeWindow.h"


/*

    To doo:

        ver como se consegue mudar o layout (estilo css.. style dos elementos)


        esc key para sair do fullscreen


        ter os bpm actuais na animacao


        gravar o estado das janelas (se a animacao estava aberta... etc)

 */





//HERE pensar noutra maneira de fazer isto

void update_tempo (Metronome* metro, Gtk::SpinButton* button)
{
int value = button->get_value_as_int();

metro->setBpm (value);
}



void test()
{
    cout << "test" << endl;
}


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


/*
Gdk::RGBA color("Blue");
start.override_background_color(color);
*/
//start.override_background_color(blue);

Gtk::Button stop ("stop");


startStopContainer.pack_start(start);
startStopContainer.pack_start(stop);



//Gtk::VBox tunerContainer;
Gtk::HBox otherContainer;


Gtk::Button openOptions ("options");


Gtk::Button tuner ("tuner");


Gtk::Button openAnimation ("animation");


otherContainer.pack_start(openOptions);
otherContainer.pack_start(tuner);
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

//openAnimation.signal_clicked().connect( sigc::mem_fun(anime, &Animation::open) );
openAnimation.signal_clicked().connect( sigc::mem_fun(metronome, &Metronome::openAnimeWindow) );
//HERE abrir a janela



//m_adjustment_digits->signal_value_changed().connect( sigc::mem_fun(*this,
  //            &ExampleWindow::on_spinbutton_digits_changed) );
/*m_button1.signal_clicked().connect(sigc::bind<Glib::ustring>(
              sigc::mem_fun(*this, &HelloWorld::on_button_clicked), "button 1"));
start.signal_clicked().connect( sigc::mem_fun(metronome, &Metronome::start) );
*/

window.add(mainTable);

window.set_title ("Metronome");

window.set_resizable(false);

window.set_border_width(10);

window.show_all_children();


Gtk::Main::run(window);

return EXIT_SUCCESS;
}
