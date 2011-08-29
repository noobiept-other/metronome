#include "options.h"


Options::Options()

    : isOpened (false),
      container (2, 1)

{
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

container.attach (normalFreqContainer, 0, 1, 0, 1);
container.attach (strongFreqContainer, 0, 1, 1, 2);

    // :::: Window :::: //

this->add (container);

this->set_title("Options");

this->set_resizable(false);

this->set_border_width(10);

this->show_all_children();



    // :::: Events :::: //

changeNormalFrequency.signal_value_changed().connect ( sigc::mem_fun ( *this, &Options::onNormalFrequencyChange ) );
changeStrongFrequency.signal_value_changed().connect ( sigc::mem_fun ( *this, &Options::onStrongFrequencyChange ) );
}


void Options::open()
{
isOpened = true;

show();
}



void Options::onNormalFrequencyChange ()
{
//HERE como actualizar o metronomo....
}



void Options::onStrongFrequencyChange ()
{

}
