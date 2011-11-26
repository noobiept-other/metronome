#include "tuner.h"


#include "configurations.h"

extern Configurations CONFIGURATIONS;



Tuner::Tuner()

    : container_ui (3, 2)

{
    // :::: Notes :::: //

     a_ui.set_label("A" );
a_plus_ui.set_label("A#");
     b_ui.set_label("B" );
     c_ui.set_label("C" );
c_plus_ui.set_label("C#");
     d_ui.set_label("D" );
d_plus_ui.set_label("D#");
     e_ui.set_label("E" );
     f_ui.set_label("F" );
f_plus_ui.set_label("F#");
     g_ui.set_label("G" );
g_plus_ui.set_label("G#");


Gtk::RadioButton::Group group = a_ui.get_group ();

a_plus_ui.set_group (group);
     b_ui.set_group (group);
     c_ui.set_group (group);
c_plus_ui.set_group (group);
     d_ui.set_group (group);
d_plus_ui.set_group (group);
     e_ui.set_group (group);
     f_ui.set_group (group);
f_plus_ui.set_group (group);
     g_ui.set_group (group);
g_plus_ui.set_group (group);

a_ui.set_active();


notesContainer_ui.pack_start (a_ui);
notesContainer_ui.pack_start (a_plus_ui);
notesContainer_ui.pack_start (b_ui);
notesContainer_ui.pack_start (c_ui);
notesContainer_ui.pack_start (c_plus_ui);
notesContainer_ui.pack_start (d_ui);
notesContainer_ui.pack_start (d_plus_ui);
notesContainer_ui.pack_start (e_ui);
notesContainer_ui.pack_start (f_ui);
notesContainer_ui.pack_start (f_plus_ui);
notesContainer_ui.pack_start (g_ui);
notesContainer_ui.pack_start (g_plus_ui);



    // :::: Octave :::: //

octave_ui.set_label ("Octave");

    //default 4 (for the A4 note)
Glib::RefPtr<Gtk::Adjustment> octaveAdjustment (Gtk::Adjustment::create(4, 1, 8, 1, 2, 0));

chooseOctave_ui.set_adjustment (octaveAdjustment);
chooseOctave_ui.set_numeric (true);


octaveContainer_ui.pack_start (octave_ui);
octaveContainer_ui.pack_start (chooseOctave_ui);



    // :::: Frequency :::: //

frequency_ui.set_label ("Frequency");

    //440 Hz (A4 note)
Glib::RefPtr<Gtk::Adjustment> freqAdjustment (

      Gtk::Adjustment::create(CONFIGURATIONS.noteFrequency_tuner,
                              CONFIGURATIONS.frequencyLowerLimit,
                              CONFIGURATIONS.frequencyUpperLimit, 1, 10, 0)

                                             );


chooseFrequency_ui.set_adjustment (freqAdjustment);

chooseFrequency_ui.set_numeric (true);
chooseFrequency_ui.set_digits (3);


frequencyContainer_ui.pack_start (frequency_ui);
frequencyContainer_ui.pack_start (chooseFrequency_ui);

hertz_ui.set_label ("Hz");


    // :::: Play :::: //

startPlaying_ui.set_label ("Play");
 stopPlaying_ui.set_label ("Stop");


playContainer_ui.pack_start (startPlaying_ui);
playContainer_ui.pack_start (stopPlaying_ui);


    // :::: Container :::: //

container_ui.set_col_spacings (40);
container_ui.set_row_spacings (20);

container_ui.attach (notesContainer_ui, 0, 2, 0, 1);
container_ui.attach (octaveContainer_ui, 0, 1, 1, 2);
container_ui.attach (frequencyContainer_ui, 1, 2, 1, 2);
container_ui.attach (playContainer_ui, 0, 2, 2, 3);

    // :::: Window :::: //

this->set_title ("Tuner");

this->set_resizable (false);

this->set_border_width (10);

this->add (container_ui);

this->show_all_children();


    // :::: Events :::: //


     a_ui.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "A"  ) );
a_plus_ui.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "A+" ) );
     b_ui.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "B"  ) );
     c_ui.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "C"  ) );
c_plus_ui.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "C+" ) );
     d_ui.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "D"  ) );
d_plus_ui.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "D+" ) );
     e_ui.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "E"  ) );
     f_ui.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "F"  ) );
f_plus_ui.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "F+" ) );
     g_ui.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "G"  ) );
g_plus_ui.signal_clicked().connect ( sigc::bind<std::string>( sigc::mem_fun (*this, &Tuner::changeNote), "G+" ) );



chooseOctave_ui.signal_value_changed().connect ( sigc::mem_fun (*this, &Tuner::onOctaveChange) );


chooseFrequency_connection = chooseFrequency_ui.signal_value_changed().connect ( sigc::mem_fun (*this, &Tuner::onFrequencyChange) );


startPlaying_ui.signal_clicked().connect ( sigc::mem_fun (*this, &Tuner::play) );
 stopPlaying_ui.signal_clicked().connect ( sigc::mem_fun (*this, &Tuner::stopPlaying) );

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
     a_ui.set_inconsistent (false);
a_plus_ui.set_inconsistent (false);
     b_ui.set_inconsistent (false);
     c_ui.set_inconsistent (false);
c_plus_ui.set_inconsistent (false);
     d_ui.set_inconsistent (false);
d_plus_ui.set_inconsistent (false);
     e_ui.set_inconsistent (false);
     f_ui.set_inconsistent (false);
f_plus_ui.set_inconsistent (false);
     g_ui.set_inconsistent (false);
g_plus_ui.set_inconsistent (false);


int octave = chooseOctave_ui.get_value_as_int ();

note_var.newNote (noteLetter, octave);


double frequency = note_var.getFrequency();



    //so that it doesn't trigger another event, when changing the value
chooseFrequency_connection.disconnect ();

    //update the value of the Gtk::SpinButton, showing the current frequency
chooseFrequency_ui.set_value (frequency);

    //restore the event
chooseFrequency_connection = chooseFrequency_ui.signal_value_changed().connect ( sigc::mem_fun (*this, &Tuner::onFrequencyChange) );

play ();
}



//HERE um bug - por a nota D#, e ir trocando a oitava.. ele passa para a nota E !!

void Tuner::onOctaveChange()
{
     a_ui.set_inconsistent (false);
a_plus_ui.set_inconsistent (false);
     b_ui.set_inconsistent (false);
     c_ui.set_inconsistent (false);
c_plus_ui.set_inconsistent (false);
     d_ui.set_inconsistent (false);
d_plus_ui.set_inconsistent (false);
     e_ui.set_inconsistent (false);
     f_ui.set_inconsistent (false);
f_plus_ui.set_inconsistent (false);
     g_ui.set_inconsistent (false);
g_plus_ui.set_inconsistent (false);

std::string noteLetter = note_var.getNote();


note_var.newNote(noteLetter, chooseOctave_ui.get_value_as_int());



double frequency = note_var.getFrequency();


    //cancel the event, so that it isn't called when changing the value below
chooseFrequency_connection.disconnect ();

    //update the value of the Gtk::SpinButton, showing the current frequency
chooseFrequency_ui.set_value (frequency);

chooseFrequency_connection = chooseFrequency_ui.signal_value_changed().connect ( sigc::mem_fun (*this, &Tuner::onFrequencyChange) );


play();
}




void Tuner::onFrequencyChange()
{
freeNote_var.newNote (chooseFrequency_ui.get_value());


     a_ui.set_inconsistent (true);
a_plus_ui.set_inconsistent (true);
     b_ui.set_inconsistent (true);
     c_ui.set_inconsistent (true);
c_plus_ui.set_inconsistent (true);
     d_ui.set_inconsistent (true);
d_plus_ui.set_inconsistent (true);
     e_ui.set_inconsistent (true);
     f_ui.set_inconsistent (true);
f_plus_ui.set_inconsistent (true);
     g_ui.set_inconsistent (true);
g_plus_ui.set_inconsistent (true);


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

chooseFrequency_ui.set_value (frequency);
}




void Tuner::loadConfigurations ()
{
setNoteFrequency ( CONFIGURATIONS.noteFrequency_tuner );

    //when changing the note frequency, it triggers an event which starts the tuner
stopPlaying ();

std::string noteName = note_var.getNote ();
}
