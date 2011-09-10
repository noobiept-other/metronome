#include "tuner.h"


#include "configurations.h"

extern Configurations CONFIGURATIONS;



Tuner::Tuner()

    : container_gui (3, 2)

{
    // :::: Notes :::: //

     a_gui.set_label("A" );
a_plus_gui.set_label("A#");
     b_gui.set_label("B" );
     c_gui.set_label("C" );
c_plus_gui.set_label("C#");
     d_gui.set_label("D" );
d_plus_gui.set_label("D#");
     e_gui.set_label("E" );
     f_gui.set_label("F" );
f_plus_gui.set_label("F#");
     g_gui.set_label("G" );
g_plus_gui.set_label("G#");


Gtk::RadioButton::Group group = a_gui.get_group ();

a_plus_gui.set_group (group);
     b_gui.set_group (group);
     c_gui.set_group (group);
c_plus_gui.set_group (group);
     d_gui.set_group (group);
d_plus_gui.set_group (group);
     e_gui.set_group (group);
     f_gui.set_group (group);
f_plus_gui.set_group (group);
     g_gui.set_group (group);
g_plus_gui.set_group (group);

a_gui.set_active();


notesContainer_gui.pack_start (a_gui);
notesContainer_gui.pack_start (a_plus_gui);
notesContainer_gui.pack_start (b_gui);
notesContainer_gui.pack_start (c_gui);
notesContainer_gui.pack_start (c_plus_gui);
notesContainer_gui.pack_start (d_gui);
notesContainer_gui.pack_start (d_plus_gui);
notesContainer_gui.pack_start (e_gui);
notesContainer_gui.pack_start (f_gui);
notesContainer_gui.pack_start (f_plus_gui);
notesContainer_gui.pack_start (g_gui);
notesContainer_gui.pack_start (g_plus_gui);



    // :::: Octave :::: //

octave_gui.set_label ("Octave");

    //default 4 (for the A4 note)
Glib::RefPtr<Gtk::Adjustment> octaveAdjustment (Gtk::Adjustment::create(4, 1, 8, 1, 2, 0));

chooseOctave_gui.set_adjustment (octaveAdjustment);
chooseOctave_gui.set_numeric (true);


octaveContainer_gui.pack_start (octave_gui);
octaveContainer_gui.pack_start (chooseOctave_gui);



    // :::: Frequency :::: //

frequency_gui.set_label ("Frequency");

    //440 Hz (A4 note)
Glib::RefPtr<Gtk::Adjustment> freqAdjustment (

      Gtk::Adjustment::create(CONFIGURATIONS.noteFrequency_tuner,
                              CONFIGURATIONS.frequencyLowerLimit,
                              CONFIGURATIONS.frequencyUpperLimit, 1, 10, 0)

                                             );


chooseFrequency_gui.set_adjustment (freqAdjustment);

chooseFrequency_gui.set_numeric (true);
chooseFrequency_gui.set_digits (3);


frequencyContainer_gui.pack_start (frequency_gui);
frequencyContainer_gui.pack_start (chooseFrequency_gui);

hertz_gui.set_label ("Hz");


    // :::: Play :::: //

startPlaying_gui.set_label ("Play");
 stopPlaying_gui.set_label ("Stop");


playContainer_gui.pack_start (startPlaying_gui);
playContainer_gui.pack_start (stopPlaying_gui);


    // :::: Container :::: //

container_gui.set_col_spacings (40);
container_gui.set_row_spacings (20);

container_gui.attach (notesContainer_gui, 0, 2, 0, 1);
container_gui.attach (octaveContainer_gui, 0, 1, 1, 2);
container_gui.attach (frequencyContainer_gui, 1, 2, 1, 2);
container_gui.attach (playContainer_gui, 0, 2, 2, 3);

    // :::: Window :::: //

this->set_title ("Tuner");

this->set_resizable (false);

this->set_border_width (10);

this->add (container_gui);

this->show_all_children();


    // :::: Events :::: //


     a_gui.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "A"  ) );
a_plus_gui.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "A+" ) );
     b_gui.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "B"  ) );
     c_gui.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "C"  ) );
c_plus_gui.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "C+" ) );
     d_gui.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "D"  ) );
d_plus_gui.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "D+" ) );
     e_gui.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "E"  ) );
     f_gui.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "F"  ) );
f_plus_gui.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "F+" ) );
     g_gui.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "G"  ) );
g_plus_gui.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "G+" ) );



chooseOctave_gui.signal_value_changed().connect ( sigc::mem_fun (*this, &Tuner::onOctaveChange) );


chooseFrequency_connection = chooseFrequency_gui.signal_value_changed().connect ( sigc::mem_fun (*this, &Tuner::onFrequencyChange) );


startPlaying_gui.signal_clicked().connect ( sigc::mem_fun (*this, &Tuner::play) );
 stopPlaying_gui.signal_clicked().connect ( sigc::mem_fun (*this, &Tuner::stopPlaying) );

}


void Tuner::open()
{
SecondaryWindow::open();

    //start playing from the beginning
play();
}



void Tuner::play()
{
Sound::setFrequency (note_var.getFrequency());

Sound::play();
}



/*
    Changes the named note, not the octave

    So from A4 to B4 or F#4
 */

void Tuner::changeNote (std::string noteLetter)
{
     a_gui.set_inconsistent (false);
a_plus_gui.set_inconsistent (false);
     b_gui.set_inconsistent (false);
     c_gui.set_inconsistent (false);
c_plus_gui.set_inconsistent (false);
     d_gui.set_inconsistent (false);
d_plus_gui.set_inconsistent (false);
     e_gui.set_inconsistent (false);
     f_gui.set_inconsistent (false);
f_plus_gui.set_inconsistent (false);
     g_gui.set_inconsistent (false);
g_plus_gui.set_inconsistent (false);


int octave = chooseOctave_gui.get_value_as_int ();

note_var.newNote (noteLetter, octave);


double frequency = note_var.getFrequency();


    //so that it doesn't trigger another event, when changing the value
chooseFrequency_connection.disconnect ();

    //update the value of the Gtk::SpinButton, showing the current frequency
chooseFrequency_gui.set_value (frequency);

    //restore the event
chooseFrequency_connection = chooseFrequency_gui.signal_value_changed().connect ( sigc::mem_fun (*this, &Tuner::onFrequencyChange) );

play ();
}



//HERE um bug - por a nota D#, e ir trocando a oitava.. ele passa para a nota E !!

void Tuner::onOctaveChange()
{
     a_gui.set_inconsistent (false);
a_plus_gui.set_inconsistent (false);
     b_gui.set_inconsistent (false);
     c_gui.set_inconsistent (false);
c_plus_gui.set_inconsistent (false);
     d_gui.set_inconsistent (false);
d_plus_gui.set_inconsistent (false);
     e_gui.set_inconsistent (false);
     f_gui.set_inconsistent (false);
f_plus_gui.set_inconsistent (false);
     g_gui.set_inconsistent (false);
g_plus_gui.set_inconsistent (false);

std::string noteLetter = note_var.getNote();


note_var.newNote(noteLetter, chooseOctave_gui.get_value_as_int());



double frequency = note_var.getFrequency();


    //cancel the event, so that it isn't called when changing the value below
chooseFrequency_connection.disconnect ();

    //update the value of the Gtk::SpinButton, showing the current frequency
chooseFrequency_gui.set_value (frequency);

chooseFrequency_connection = chooseFrequency_gui.signal_value_changed().connect ( sigc::mem_fun (*this, &Tuner::onFrequencyChange) );


play();
}




void Tuner::onFrequencyChange()
{
freeNote_var.newNote (chooseFrequency_gui.get_value());


     a_gui.set_inconsistent (true);
a_plus_gui.set_inconsistent (true);
     b_gui.set_inconsistent (true);
     c_gui.set_inconsistent (true);
c_plus_gui.set_inconsistent (true);
     d_gui.set_inconsistent (true);
d_plus_gui.set_inconsistent (true);
     e_gui.set_inconsistent (true);
     f_gui.set_inconsistent (true);
f_plus_gui.set_inconsistent (true);
     g_gui.set_inconsistent (true);
g_plus_gui.set_inconsistent (true);


Sound::setFrequency(freeNote_var.getFrequency());
Sound::play();
}




/*
    Stop the metronome's sound when closing the window
 */

void Tuner::on_hide()
{
this->stopPlaying();

SecondaryWindow::on_hide();
}




void Tuner::setNoteFrequency (double frequency)
{
note_var.newNote (frequency);

Sound::setFrequency (frequency);

chooseFrequency_gui.set_value (frequency);
}




void Tuner::loadConfigurations ()
{
setNoteFrequency ( CONFIGURATIONS.noteFrequency_tuner );

    //when changing the note frequency, it triggers an event which starts the tuner
stopPlaying ();

std::string noteName = note_var.getNote ();
}
