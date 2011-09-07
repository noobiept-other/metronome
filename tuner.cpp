#include "tuner.h"


Tuner::Tuner()

    : container(3, 2)

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

    //default 4 (for the A4 note)
Glib::RefPtr<Gtk::Adjustment> octaveAdjustment (Gtk::Adjustment::create(4, 1, 8, 1, 2, 0));

chooseOctave.set_adjustment(octaveAdjustment);
chooseOctave.set_numeric (true);


octaveContainer.pack_start(octave);
octaveContainer.pack_start(chooseOctave);



    // :::: Frequency :::: //

frequency.set_label("Frequency");

    //440 Hz (A4 note)  //HERE 20 a 20000 se calhar eh muito
Glib::RefPtr<Gtk::Adjustment> freqAdjustment (Gtk::Adjustment::create(440, 20, 20000, 1, 10, 0));

chooseFrequency.set_adjustment(freqAdjustment);

chooseFrequency.set_numeric (true);
chooseFrequency.set_digits (3);


frequencyContainer.pack_start(frequency);
frequencyContainer.pack_start(chooseFrequency);

hertz.set_label("Hz");


    // :::: Play :::: //

startPlaying.set_label("Play");
stopPlaying_gui.set_label("Stop");

playContainer.pack_start(startPlaying);
playContainer.pack_start(stopPlaying_gui);


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
//this->signal_hide().connect( sigc::mem_fun(*this, &Tuner::onHide) );


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
chooseFrequency_connection = chooseFrequency.signal_value_changed().connect ( sigc::mem_fun (*this, &Tuner::onFrequencyChange) );


startPlaying.signal_clicked().connect ( sigc::mem_fun (*this, &Tuner::play) );
 stopPlaying_gui.signal_clicked().connect ( sigc::mem_fun(*this,  &Tuner::stopPlaying) );

}


void Tuner::open()
{
SecondaryWindow::open();

    //start playing from the beginning
play();
}



void Tuner::play()
{
Sound::setFrequency (note.getFrequency());

Sound::play();
}


/*
void Tuner::stop()
{
sound.stopPlaying();
}
*/

/*
    Changes the named note, not the octave

    So from A4 to B4 or F#4
 */

void Tuner::changeNote (std::string noteLetter)
{
cout << "Tuner::changeNote\n";


     a.set_inconsistent (false);
a_plus.set_inconsistent (false);
     b.set_inconsistent (false);
     c.set_inconsistent (false);
c_plus.set_inconsistent (false);
     d.set_inconsistent (false);
d_plus.set_inconsistent (false);
     e.set_inconsistent (false);
     f.set_inconsistent (false);
f_plus.set_inconsistent (false);
     g.set_inconsistent (false);
g_plus.set_inconsistent (false);


int octave = chooseOctave.get_value_as_int ();

note.newNote (noteLetter, octave);


//cout << "note " << noteLetter << " freq " << note.getFrequency() << endl;

double frequency = note.getFrequency();


    //so that it doesn't trigger another event, when changing the value
chooseFrequency_connection.disconnect ();

    //update the value of the Gtk::SpinButton, showing the current frequency
chooseFrequency.set_value (frequency);

    //restore the event
chooseFrequency_connection = chooseFrequency.signal_value_changed().connect ( sigc::mem_fun (*this, &Tuner::onFrequencyChange) );

play ();
/*
setFrequency(frequency);
play();*/
}



//HERE um bug - por a nota D#, e ir trocando a oitava.. ele passa para a nota E !!

void Tuner::onOctaveChange()
{
cout << "Tuner::onOctaveChange\n";

     a.set_inconsistent (false);
a_plus.set_inconsistent (false);
     b.set_inconsistent (false);
     c.set_inconsistent (false);
c_plus.set_inconsistent (false);
     d.set_inconsistent (false);
d_plus.set_inconsistent (false);
     e.set_inconsistent (false);
     f.set_inconsistent (false);
f_plus.set_inconsistent (false);
     g.set_inconsistent (false);
g_plus.set_inconsistent (false);

std::string noteLetter = note.getNote();

//cout << "onOctaveChange: noteLetter " << noteLetter;

//cout << " chooseOctave value " << chooseOctave.get_value_as_int() << endl;

note.newNote(noteLetter, chooseOctave.get_value_as_int());



double frequency = note.getFrequency();


    //cancel the event, so that it isn't called when changing the value below
chooseFrequency_connection.disconnect ();

    //update the value of the Gtk::SpinButton, showing the current frequency
chooseFrequency.set_value (frequency);

chooseFrequency_connection = chooseFrequency.signal_value_changed().connect ( sigc::mem_fun (*this, &Tuner::onFrequencyChange) );


/*
sound.setFrequency(frequency);
sound.play();
*/
play();
}




void Tuner::onFrequencyChange()
{
cout << "Tuner::onFrequencyChange\n";

freeNote.newNote (chooseFrequency.get_value());


     a.set_inconsistent (true);
a_plus.set_inconsistent (true);
     b.set_inconsistent (true);
     c.set_inconsistent (true);
c_plus.set_inconsistent (true);
     d.set_inconsistent (true);
d_plus.set_inconsistent (true);
     e.set_inconsistent (true);
     f.set_inconsistent (true);
f_plus.set_inconsistent (true);
     g.set_inconsistent (true);
g_plus.set_inconsistent (true);


Sound::setFrequency(freeNote.getFrequency());
Sound::play();
}




/*
    Stop the metronome's sound when closing the window
 */

void Tuner::on_hide()    //HERE override
{
this->stopPlaying();

SecondaryWindow::on_hide();
}

/*
bool Tuner::isPlaying () const
{
return sound.isPlaying();
}
*/

/*
double Tuner::getNoteFrequency () const
{
return note.getFrequency ();
}
*/

void Tuner::setNoteFrequency (double frequency)
{
note.newNote(frequency);

Sound::setFrequency(frequency);

chooseFrequency.set_value (frequency);
}




void Tuner::loadConfigurations ()
{
setNoteFrequency ( CONFIGURATIONS.noteFrequency_tuner );

    //when changing the note frequency, it triggers an event which starts the tuner
stopPlaying ();

std::string noteName = note.getNote ();

//if (noteName == "A")
}
