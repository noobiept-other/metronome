/*

	Copyright - 2011 - Pedro Ferreira

	This file is part of Metronome.

    Metronome is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Metronome is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Metronome.  If not, see <http://www.gnu.org/licenses/>.

 */


#include "tuner.h"


#include "configurations.h"

extern Configurations CONFIGURATIONS;



Tuner::Tuner()

    : cancelEvents_var (false),
      container_ui (3, 2)


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


notesContainer_ui.set_orientation( Gtk::ORIENTATION_HORIZONTAL );
notesContainer_ui.set_homogeneous( true );

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


octaveContainer_ui.set_orientation( Gtk::ORIENTATION_HORIZONTAL );
octaveContainer_ui.set_homogeneous( true );


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



frequencyContainer_ui.set_orientation( Gtk::ORIENTATION_HORIZONTAL );
frequencyContainer_ui.set_homogeneous( true );

frequencyContainer_ui.pack_start (frequency_ui);
frequencyContainer_ui.pack_start (chooseFrequency_ui);

hertz_ui.set_label ("Hz");


    // :::: Play :::: //

startPlaying_ui.set_label ("Play");
 stopPlaying_ui.set_label ("Stop");


playContainer_ui.set_orientation( Gtk::ORIENTATION_HORIZONTAL );
playContainer_ui.set_homogeneous( true );

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


this->set_icon_from_file("images/tuner.png");


    // :::: Events :::: //

//HERE -- podia ser ints em vez de strings
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
    //unwanted events
if (cancelEvents_var == true)
    {
    return;
    }

int octave = chooseOctave_ui.get_value_as_int ();

Tuner::setNote( noteLetter, octave, false );


play ();
}



//HERE um bug - por a nota D#, e ir trocando a oitava.. ele passa para a nota E !!

void Tuner::onOctaveChange()
{
    //unwanted events
if (cancelEvents_var == true)
    {
    return;
    }

std::string noteLetter = note_var.getNote();

Tuner::setNote( noteLetter, chooseOctave_ui.get_value_as_int(), false );


play();
}


/*
    Called when the frequency is changed directly (in the SpinButton)
 */

void Tuner::onFrequencyChange()
{
    //unwanted events
if (cancelEvents_var == true)
    {
    return;
    }

setNote( chooseFrequency_ui.get_value(), true );

play();
}




/*
    Stop the metronome's sound when closing the window
 */

void Tuner::on_hide()
{
this->stopPlaying();

SecondaryWindow::on_hide();
}



/*

 */

void Tuner::setNote( int notePosition, int octave, bool updateUi )
{
Tuner::setNote( Note::allNotes_var[notePosition], octave, updateUi );
}



/*

 */

void Tuner::setNote( std::string noteName, int octave, bool updateUi )
{
    //cancel events that happen due to updating the ui
cancelEvents_var = true;


    //when we change to a random frequency, the RadioButton's state is changed to inconsistent
    //when we change back to a named note, we have to revert this
if (a_ui.get_inconsistent() == true)
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
    }



note_var.newNote(noteName, octave);



double frequency = note_var.getFrequency();



    //update the value of the Gtk::SpinButton, showing the current frequency
chooseFrequency_ui.set_value (frequency);



if ( updateUi == true )
    {
        //update the octave
    chooseOctave_ui.set_value( octave );

        //and the RadioButton that is selected
    switch( note_var.getPosition() )
        {
        case 0:

            a_ui.set_active();
            break;

        case 1:

            a_plus_ui.set_active();
            break;

        case 2:

            b_ui.set_active();
            break;

        case 3:

            c_ui.set_active();
            break;

        case 4:

            c_plus_ui.set_active();
            break;

        case 5:

            d_ui.set_active();
            break;

        case 6:

            d_plus_ui.set_active();
            break;

        case 7:

            e_ui.set_active();
            break;

        case 8:

            f_ui.set_active();
            break;

        case 9:

            f_plus_ui.set_active();
            break;

        case 10:

            g_ui.set_active();
            break;

        case 11:

            g_plus_ui.set_active();
            break;

        }
    }


    //back to normal
cancelEvents_var = false;
}







/*

 */

void Tuner::setNote( double frequency, bool updateUi )
{
    //cancel events that happen due to updating the ui
cancelEvents_var = true;

note_var.newNote (frequency);



    //update the value of the Gtk::SpinButton, showing the current frequency
chooseFrequency_ui.set_value (frequency);



if (updateUi == true)
    {
        //assuming its never a named note
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
    }

    //back to normal
cancelEvents_var = false;
}



/*
    returns a string in the form: "noteName octave" or an empty string if it isn't a named note
 */

std::string Tuner::getNote()
{
std::string note = note_var.getNote();

    //it isn't a named note
if (note == "")
    {
    return note;
    }

    //else, make the string and return it
std::stringstream stream;

stream << note << " " << note_var.getOctave();

return stream.str();
}


/*
    changes the arguments value to have the current note that is set
    is it isn't a named note, when it will have negative values
 */

void Tuner::getNote( int* notePosition, int* octave )
{
*notePosition = note_var.getPosition();
*octave = note_var.getOctave();
}
