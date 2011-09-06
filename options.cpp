#include "options.h"


extern Configurations CONFIGURATIONS;


Options::Options()

    : //isOpened_var (false),
      container (3, 1)

{
    // :::: Beat duration :::: //

beatDurationLabel.set_label ("Beat duration");


    //  //HERE
Glib::RefPtr<Gtk::Adjustment> beatDurationAdjustment (Gtk::Adjustment::create(200, 50, 300, 1, 5, 0));

changeBeatDuration.set_adjustment(beatDurationAdjustment);

changeBeatDuration.set_numeric (true);
changeBeatDuration.set_digits (3);


milisecondsLabel.set_label ("ms");


beatDurationContainer.pack_start(beatDurationLabel);
beatDurationContainer.pack_start(changeBeatDuration);
beatDurationContainer.pack_start(milisecondsLabel);

beatDurationContainer.set_spacing(10);



    // :::: Normal beat frequency :::: //

normalLabel.set_label ("Normal beat frequency");


    //  //HERE
Glib::RefPtr<Gtk::Adjustment> normalFreqAdjustment (Gtk::Adjustment::create(440, 20, 20000, 1, 10, 0));

changeNormalFrequency.set_adjustment(normalFreqAdjustment);

changeNormalFrequency.set_numeric (true);
changeNormalFrequency.set_digits (3);


normalHz.set_label ("Hz");


normalFreqContainer.pack_start(normalLabel);
normalFreqContainer.pack_start(changeNormalFrequency);
normalFreqContainer.pack_start(normalHz);

normalFreqContainer.set_spacing(10);


    // :::: Strong beat frequency :::: //


strongLabel.set_label ("Strong beat frequency");


    //  //HERE
Glib::RefPtr<Gtk::Adjustment> strongFreqAdjustment (Gtk::Adjustment::create(440, 20, 20000, 1, 10, 0));

changeStrongFrequency.set_adjustment(strongFreqAdjustment);

changeStrongFrequency.set_numeric (true);
changeStrongFrequency.set_digits (3);


strongHz.set_label ("Hz");


strongFreqContainer.pack_start(strongLabel);
strongFreqContainer.pack_start(changeStrongFrequency);
strongFreqContainer.pack_start(strongHz);


strongFreqContainer.set_spacing(10);

    // :::: Container :::: //


container.set_col_spacings(40);
container.set_row_spacings(20);

container.attach (beatDurationContainer, 0, 1, 0, 1);
container.attach (normalFreqContainer, 0, 1, 1, 2);
container.attach (strongFreqContainer, 0, 1, 2, 3);

    // :::: Window :::: //

this->add (container);

this->set_title("Options");

this->set_resizable(false);

this->set_border_width(10);

this->show_all_children();



    // :::: Events :::: //

changeNormalFrequency.signal_value_changed().connect ( sigc::mem_fun ( *this, &Options::onNormalFrequencyChange ) );
changeStrongFrequency.signal_value_changed().connect ( sigc::mem_fun ( *this, &Options::onStrongFrequencyChange ) );

changeBeatDuration.signal_value_changed().connect ( sigc::mem_fun ( *this, &Options::onBeatDurationChange ) );

//add_events( Gdk::KEY_PRESS_MASK );

//this->signal_key_release_event().connect ( sigc::mem_fun(*this, &Options::onKeyRelease) );


    //when closing the window
//this->signal_hide().connect( sigc::mem_fun(*this, &Options::onHide) );
}




void Options::loadConfigurations ()
{
changeBeatDuration.set_value ( CONFIGURATIONS.beatDuration );

changeNormalFrequency.set_value ( CONFIGURATIONS.normalFrequency );

changeStrongFrequency.set_value ( CONFIGURATIONS.strongFrequency );
}
/*
void Options::open()
{
isOpened_var = true;

show();
}
*/
/*

bool Options::isOpened() const
{
return isOpened_var;
}
*/

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
the_signal_onNormalFrequencyChange.emit ( changeNormalFrequency.get_value_as_int() );
}



void Options::onStrongFrequencyChange ()
{
the_signal_onStrongFrequencyChange.emit ( changeStrongFrequency.get_value_as_int() );
}



void Options::onBeatDurationChange ()
{
the_signal_onBeatDurationChange.emit ( changeBeatDuration.get_value_as_int() );
}



//HERE nao funciona, pq a window n ganha focus (esta nos spinbuttons)
/*
bool Options::onKeyRelease(GdkEventKey *event)
{
if (event->keyval == GDK_KEY_Escape)
    {
    isOpened_var = false;

    hide();
    }

return true;
}
*/

/*
void Options::onHide ()
{
isOpened_var = false;
}
*/
