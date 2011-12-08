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


#include "options.h"

#include "configurations.h"

extern Configurations CONFIGURATIONS;


Options::Options()

    : container_ui (3, 1)

{
    // :::: Beat duration :::: //

beatDurationLabel_ui.set_label ("Beat duration");


Glib::RefPtr<Gtk::Adjustment> beatDurationAdjustment (

          Gtk::Adjustment::create(CONFIGURATIONS.beatDuration,
                                  CONFIGURATIONS.beatDurationLowerLimit,
                                  CONFIGURATIONS.beatDurationUpperLimit, 1, 5, 0)

                                                     );

changeBeatDuration_ui.set_adjustment (beatDurationAdjustment);

changeBeatDuration_ui.set_numeric (true);
changeBeatDuration_ui.set_digits (3);


milisecondsLabel_ui.set_label ("ms");


beatDurationContainer_ui.pack_start (beatDurationLabel_ui);
beatDurationContainer_ui.pack_start (changeBeatDuration_ui);
beatDurationContainer_ui.pack_start (milisecondsLabel_ui);

beatDurationContainer_ui.set_spacing (10);



    // :::: Normal beat frequency :::: //

normalLabel_ui.set_label ("Normal beat frequency");



Glib::RefPtr<Gtk::Adjustment> normalFreqAdjustment (

    Gtk::Adjustment::create (CONFIGURATIONS.normalFrequency,
                             CONFIGURATIONS.frequencyLowerLimit,
                             CONFIGURATIONS.frequencyUpperLimit, 1, 10, 0)

                                                   );

changeNormalFrequency_ui.set_adjustment (normalFreqAdjustment);

changeNormalFrequency_ui.set_numeric (true);
changeNormalFrequency_ui.set_digits (3);


normalHz_ui.set_label ("Hz");


normalFreqContainer_ui.pack_start (normalLabel_ui);
normalFreqContainer_ui.pack_start (changeNormalFrequency_ui);
normalFreqContainer_ui.pack_start (normalHz_ui);

normalFreqContainer_ui.set_spacing (10);


    // :::: Strong beat frequency :::: //


strongLabel_ui.set_label ("Strong beat frequency");



Glib::RefPtr<Gtk::Adjustment> strongFreqAdjustment (

    Gtk::Adjustment::create(CONFIGURATIONS.strongFrequency,
                            CONFIGURATIONS.frequencyLowerLimit,
                            CONFIGURATIONS.frequencyUpperLimit, 1, 10, 0)

                                                   );

changeStrongFrequency_ui.set_adjustment (strongFreqAdjustment);

changeStrongFrequency_ui.set_numeric (true);
changeStrongFrequency_ui.set_digits (3);


strongHz_ui.set_label ("Hz");


strongFreqContainer_ui.pack_start (strongLabel_ui);
strongFreqContainer_ui.pack_start (changeStrongFrequency_ui);
strongFreqContainer_ui.pack_start (strongHz_ui);


strongFreqContainer_ui.set_spacing (10);

    // :::: Container :::: //


container_ui.set_col_spacings (40);
container_ui.set_row_spacings (20);

container_ui.attach (beatDurationContainer_ui, 0, 1, 0, 1);
container_ui.attach (normalFreqContainer_ui, 0, 1, 1, 2);
container_ui.attach (strongFreqContainer_ui, 0, 1, 2, 3);

    // :::: Window :::: //

this->add (container_ui);

this->set_title ("Options");

this->set_resizable (false);

this->set_border_width (10);

this->show_all_children ();


this->set_icon_from_file("images/options.png");


    // :::: Events :::: //

changeNormalFrequency_ui.signal_value_changed().connect ( sigc::mem_fun ( *this, &Options::onNormalFrequencyChange ) );
changeStrongFrequency_ui.signal_value_changed().connect ( sigc::mem_fun ( *this, &Options::onStrongFrequencyChange ) );

changeBeatDuration_ui.signal_value_changed().connect ( sigc::mem_fun ( *this, &Options::onBeatDurationChange ) );
}




void Options::loadConfigurations ()
{
changeBeatDuration_ui.set_value ( CONFIGURATIONS.beatDuration );

changeNormalFrequency_ui.set_value ( CONFIGURATIONS.normalFrequency );

changeStrongFrequency_ui.set_value ( CONFIGURATIONS.strongFrequency );
}




sigc::signal<void, int> Options::signal_onNormalFrequencyChange()
{
return the_signal_onNormalFrequencyChange;
}


sigc::signal<void, int> Options::signal_onStrongFrequencyChange()
{
return the_signal_onStrongFrequencyChange;
}


sigc::signal<void, int> Options::signal_onBeatDurationChange()
{
return the_signal_onBeatDurationChange;
}




void Options::onNormalFrequencyChange ()
{
the_signal_onNormalFrequencyChange.emit ( changeNormalFrequency_ui.get_value_as_int() );
}



void Options::onStrongFrequencyChange ()
{
the_signal_onStrongFrequencyChange.emit ( changeStrongFrequency_ui.get_value_as_int() );
}



void Options::onBeatDurationChange ()
{
the_signal_onBeatDurationChange.emit ( changeBeatDuration_ui.get_value_as_int() );
}

