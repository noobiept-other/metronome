#include "options.h"

#include "configurations.h"

extern Configurations CONFIGURATIONS;


Options::Options()

    : container_gui (3, 1)

{
    // :::: Beat duration :::: //

beatDurationLabel_gui.set_label ("Beat duration");


Glib::RefPtr<Gtk::Adjustment> beatDurationAdjustment (

          Gtk::Adjustment::create(CONFIGURATIONS.beatDuration,
                                  CONFIGURATIONS.beatDurationLowerLimit,
                                  CONFIGURATIONS.beatDurationUpperLimit, 1, 5, 0)

                                                     );

changeBeatDuration_gui.set_adjustment (beatDurationAdjustment);

changeBeatDuration_gui.set_numeric (true);
changeBeatDuration_gui.set_digits (3);


milisecondsLabel_gui.set_label ("ms");


beatDurationContainer_gui.pack_start (beatDurationLabel_gui);
beatDurationContainer_gui.pack_start (changeBeatDuration_gui);
beatDurationContainer_gui.pack_start (milisecondsLabel_gui);

beatDurationContainer_gui.set_spacing (10);



    // :::: Normal beat frequency :::: //

normalLabel_gui.set_label ("Normal beat frequency");



Glib::RefPtr<Gtk::Adjustment> normalFreqAdjustment (

    Gtk::Adjustment::create (CONFIGURATIONS.normalFrequency,
                             CONFIGURATIONS.frequencyLowerLimit,
                             CONFIGURATIONS.frequencyUpperLimit, 1, 10, 0)

                                                   );

changeNormalFrequency_gui.set_adjustment (normalFreqAdjustment);

changeNormalFrequency_gui.set_numeric (true);
changeNormalFrequency_gui.set_digits (3);


normalHz_gui.set_label ("Hz");


normalFreqContainer_gui.pack_start (normalLabel_gui);
normalFreqContainer_gui.pack_start (changeNormalFrequency_gui);
normalFreqContainer_gui.pack_start (normalHz_gui);

normalFreqContainer_gui.set_spacing (10);


    // :::: Strong beat frequency :::: //


strongLabel_gui.set_label ("Strong beat frequency");



Glib::RefPtr<Gtk::Adjustment> strongFreqAdjustment (

    Gtk::Adjustment::create(CONFIGURATIONS.strongFrequency,
                            CONFIGURATIONS.frequencyLowerLimit,
                            CONFIGURATIONS.frequencyUpperLimit, 1, 10, 0)

                                                   );

changeStrongFrequency_gui.set_adjustment (strongFreqAdjustment);

changeStrongFrequency_gui.set_numeric (true);
changeStrongFrequency_gui.set_digits (3);


strongHz_gui.set_label ("Hz");


strongFreqContainer_gui.pack_start (strongLabel_gui);
strongFreqContainer_gui.pack_start (changeStrongFrequency_gui);
strongFreqContainer_gui.pack_start (strongHz_gui);


strongFreqContainer_gui.set_spacing (10);

    // :::: Container :::: //


container_gui.set_col_spacings (40);
container_gui.set_row_spacings (20);

container_gui.attach (beatDurationContainer_gui, 0, 1, 0, 1);
container_gui.attach (normalFreqContainer_gui, 0, 1, 1, 2);
container_gui.attach (strongFreqContainer_gui, 0, 1, 2, 3);

    // :::: Window :::: //

this->add (container_gui);

this->set_title ("Options");

this->set_resizable (false);

this->set_border_width (10);

this->show_all_children ();



    // :::: Events :::: //

changeNormalFrequency_gui.signal_value_changed().connect ( sigc::mem_fun ( *this, &Options::onNormalFrequencyChange ) );
changeStrongFrequency_gui.signal_value_changed().connect ( sigc::mem_fun ( *this, &Options::onStrongFrequencyChange ) );

changeBeatDuration_gui.signal_value_changed().connect ( sigc::mem_fun ( *this, &Options::onBeatDurationChange ) );

}




void Options::loadConfigurations ()
{
changeBeatDuration_gui.set_value ( CONFIGURATIONS.beatDuration );

changeNormalFrequency_gui.set_value ( CONFIGURATIONS.normalFrequency );

changeStrongFrequency_gui.set_value ( CONFIGURATIONS.strongFrequency );
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
the_signal_onNormalFrequencyChange.emit ( changeNormalFrequency_gui.get_value_as_int() );
}



void Options::onStrongFrequencyChange ()
{
the_signal_onStrongFrequencyChange.emit ( changeStrongFrequency_gui.get_value_as_int() );
}



void Options::onBeatDurationChange ()
{
the_signal_onBeatDurationChange.emit ( changeBeatDuration_gui.get_value_as_int() );
}

