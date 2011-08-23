#include <gtkmm.h>

#include "metronome.h"

#include "animation.h"


/*

    To doo:

        ver como se consegue mudar o layout (estilo css.. style dos elementos)

 */





//HERE pensar noutra maneira de fazer isto

void update_tempo (Metronome* metro, Gtk::SpinButton* button)
{
int value = button->get_value_as_int();

metro->setBpm (value);
}


int main(int argc, char *argv[])
{
Gtk::Main kit(argc, argv);

Gst::init (argc, argv);



Gtk::Window window;


    //2 row and 2 columns
Gtk::Table mainTable (2, 2);




Gtk::Table tempoContainer (2, 2);

Gtk::Label tempoName;
tempoName.set_label("Tempo: ");


Gtk::Label tempoValue;
tempoValue.set_label ("60 bpm");


    //start at 60, with limits from 30 to 300 - step is 1
Glib::RefPtr<Gtk::Adjustment> tempoAdjustment (Gtk::Adjustment::create(60, 30, 300, 1, 5, 0));

Gtk::SpinButton changeTempo(tempoAdjustment);
changeTempo.set_numeric (true);


tempoContainer.attach(tempoName, 0, 1, 0, 1);
tempoContainer.attach(tempoValue, 1, 2, 0, 1);
tempoContainer.attach(changeTempo, 0, 2, 1, 2);




Gtk::Table strongBeat(2, 5);

Gtk::Label strongBeatLabel;
strongBeatLabel.set_label("Strong beat");

Gtk::Label oneBeat;
oneBeat.set_label("1");

Gtk::Label twoBeats;
twoBeats.set_label("2");

Gtk::Label threeBeats;
threeBeats.set_label("3");

Gtk::Label fourBeats;
fourBeats.set_label("4");

Gtk::Entry otherBeat;


strongBeat.attach (strongBeatLabel, 0, 5, 0, 1);
strongBeat.attach (oneBeat, 0, 1, 1, 2);
strongBeat.attach (twoBeats, 1, 2, 1, 2);
strongBeat.attach (threeBeats, 2, 3, 1, 2);
strongBeat.attach (fourBeats, 3, 4, 1, 2);
strongBeat.attach (otherBeat, 4, 5, 1, 2);




Gtk::HBox startStopContainer;


Gtk::Button start;
start.set_label("start");


Gtk::Button stop;
stop.set_label("stop");

startStopContainer.pack_start(start);
startStopContainer.pack_start(stop);



Gtk::VBox tunerContainer;


Gtk::Button tuner;
tuner.set_label("tuner");

Gtk::Button openAnimation;
openAnimation.set_label("animation");

tunerContainer.pack_start(tuner);
tunerContainer.pack_start(openAnimation);


mainTable.attach(tempoContainer, 0, 1, 0, 1);
mainTable.attach(strongBeat, 1, 2, 0, 1);
mainTable.attach(startStopContainer, 0, 1, 1, 2);
mainTable.attach(tunerContainer, 1, 2, 1, 2);



Metronome metronome;
metronome.start();






    //set the events

start.signal_clicked().connect( sigc::mem_fun(metronome, &Metronome::start) );
stop.signal_clicked().connect( sigc::mem_fun(metronome, &Metronome::stop) );





changeTempo.signal_value_changed().connect (
                        sigc::bind<Metronome*, Gtk::SpinButton*>(
                                sigc::ptr_fun(update_tempo), &metronome, &changeTempo
                                       ));



Animation anime;


Gtk::Window animeWindow;
animeWindow.add (anime);

//openAnimation.signal_clicked().connect( sigc::mem_fun(anime, &Animation::open) );
openAnimation.signal_clicked().connect( sigc::mem_fun(animeWindow, &Gtk::Window::show) );
//HERE abrir a janela



//m_adjustment_digits->signal_value_changed().connect( sigc::mem_fun(*this,
  //            &ExampleWindow::on_spinbutton_digits_changed) );
/*m_button1.signal_clicked().connect(sigc::bind<Glib::ustring>(
              sigc::mem_fun(*this, &HelloWorld::on_button_clicked), "button 1"));
start.signal_clicked().connect( sigc::mem_fun(metronome, &Metronome::start) );
*/

window.add(mainTable);

window.show_all_children();


Gtk::Main::run(window);

return EXIT_SUCCESS;
}
