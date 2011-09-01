#include "tuner.h"

#include "note.h"



Tuner::Tuner()

    : //isOpened_obj (false),

      note(440),    //A4 - 440 Hz
      container(3, 2)

{
    // :::: Notes :::: //

     a.set_label("A" );
a_plus.set_label("A#");
     b.set_label("B" );
     c.set_label("C" );
c_plus.set_label("C#");
     d.set_label("D" );
d_plus.set_label("D#");
     e.set_label("E" );
     f.set_label("F" );
f_plus.set_label("F#");
     g.set_label("G" );
g_plus.set_label("G#");


Gtk::RadioButton::Group group = a.get_group ();

a_plus.set_group(group);
     b.set_group(group);
     c.set_group(group);
c_plus.set_group(group);
     d.set_group(group);
d_plus.set_group(group);
     e.set_group(group);
     f.set_group(group);
f_plus.set_group(group);
     g.set_group(group);
g_plus.set_group(group);

a.set_active();


notesContainer.pack_start(a);
notesContainer.pack_start(a_plus);
notesContainer.pack_start(b);
notesContainer.pack_start(c);
notesContainer.pack_start(c_plus);
notesContainer.pack_start(d);
notesContainer.pack_start(d_plus);
notesContainer.pack_start(e);
notesContainer.pack_start(f);
notesContainer.pack_start(f_plus);
notesContainer.pack_start(g);
notesContainer.pack_start(g_plus);



    // :::: Octave :::: //

octave.set_label("Octave");

    //start at 60, with limits from 30 to 300 - step is 1   //HERE
Glib::RefPtr<Gtk::Adjustment> octaveAdjustment (Gtk::Adjustment::create(4, 1, 8, 1, 5, 0));

chooseOctave.set_adjustment(octaveAdjustment);
chooseOctave.set_numeric (true);


octaveContainer.pack_start(octave);
octaveContainer.pack_start(chooseOctave);



    // :::: Frequency :::: //

frequency.set_label("Frequency");

    //   //HERE
Glib::RefPtr<Gtk::Adjustment> freqAdjustment (Gtk::Adjustment::create(440, 20, 20000, 1, 10, 0));

chooseFrequency.set_adjustment(freqAdjustment);

chooseFrequency.set_numeric (true);
chooseFrequency.set_digits (3);


frequencyContainer.pack_start(frequency);
frequencyContainer.pack_start(chooseFrequency);

hertz.set_label("Hz");


    // :::: Play :::: //

startPlaying.set_label("Play");
stopPlaying.set_label("Stop");

playContainer.pack_start(startPlaying);
playContainer.pack_start(stopPlaying);


    // :::: Container :::: //

container.set_col_spacings(40);
container.set_row_spacings(20);

container.attach (notesContainer, 0, 2, 0, 1);
container.attach (octaveContainer, 0, 1, 1, 2);
container.attach (frequencyContainer, 1, 2, 1, 2);
container.attach (playContainer, 0, 2, 2, 3);

    // :::: Window :::: //

this->set_title("Tuner");

this->set_resizable(false);

this->set_border_width(10);

this->add (container);

this->show_all_children();


    // :::: Events :::: //

    //when closing the window
this->signal_hide().connect( sigc::mem_fun(*this, &Tuner::onHide) );


//window.add_events( Gdk::KEY_PRESS_MASK );

//window.signal_key_release_event().connect ( sigc::mem_fun(*this, &Tuner::onKeyRelease) );


     a.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "A"  ) );
a_plus.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "A+" ) );
     b.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "B"  ) );
     c.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "C"  ) );
c_plus.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "C+" ) );
     d.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "D"  ) );
d_plus.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "D+" ) );
     e.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "E"  ) );
     f.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "F"  ) );
f_plus.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "F+" ) );
     g.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "G"  ) );
g_plus.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "G+" ) );



chooseOctave.signal_value_changed().connect ( sigc::mem_fun (*this, &Tuner::onOctaveChange) );

    //HERE alguma maneira de nao ter a funcao a ser chamada constantemente... esperar k o utilizador pare de mudar os valores
    //e soh depois chamar
chooseFrequency.signal_value_changed().connect ( sigc::mem_fun (*this, &Tuner::onFrequencyChange) );


startPlaying.signal_clicked().connect ( sigc::mem_fun (*this, &Tuner::play) );
stopPlaying.signal_clicked().connect ( sigc::mem_fun(*this, &Tuner::stop) );

}


void Tuner::open()
{
//isOpened_obj = true;    //HERE isto eh tudo mt igual.. ter uma classe base?..

//window.show();

SecondaryWindow::open();

    //HERE stop the metronome

    //start playing from the beginning
play();
}



void Tuner::play()
{
sound.setFrequency(note.getFrequency());

sound.play();
}



void Tuner::stop()
{
sound.stopPlaying();
}



void Tuner::changeNote (std::string noteLetter)
{
int octave = note.getOctave();

note.newNote (noteLetter, octave);


cout << "note " << noteLetter << " freq " << note.getFrequency() << endl;

double frequency = note.getFrequency();

    //update the value of the Gtk::SpinButton, showing the current frequency
chooseFrequency.set_value (frequency);

sound.setFrequency(frequency);
sound.play();
}


/*
bool Tuner::isOpened() const
{
return isOpened_obj;
}
*/

//HERE um bug - por a nota D#, e ir trocando a oitava.. ele passa para a nota E !!

void Tuner::onOctaveChange()
{
std::string noteLetter = note.getNote();

cout << "onOctaveChange: noteLetter " << noteLetter;

cout << " chooseOctave value " << chooseOctave.get_value_as_int() << endl;

note.newNote(noteLetter, chooseOctave.get_value_as_int());



double frequency = note.getFrequency();

    //update the value of the Gtk::SpinButton, showing the current frequency
chooseFrequency.set_value (frequency);


sound.setFrequency(frequency);
sound.play();
}




void Tuner::onFrequencyChange()
{
note.newNote(chooseFrequency.get_value());

//HERE selecionar a nota mais perto desta frequencia?...

sound.setFrequency(note.getFrequency());
sound.play();
}

/*
sigc::signal<void> Tuner::signal_onTunerHide()
{
return the_signal_onTunerHide;
}
*/



/*
bool Tuner::onKeyRelease(GdkEventKey *event)
{
if (event->keyval == GDK_KEY_Escape)
    {
    onTunerHide();

    window.hide();
    }

return true;
}
*/



void Tuner::onHide()
{
//isOpened_obj = false;

this->stop();

SecondaryWindow::onHide();

    //emit our custom signal, that tells the window was closed
//the_signal_onTunerHide.emit();
}
