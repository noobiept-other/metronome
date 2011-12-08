#ifndef OPTIONS_GUARD
#define OPTIONS_GUARD


#include <gtkmm.h>

#include "SecondaryWindow.h"
#include "mySpinButton.h"

/*
    The options window - when a value is changed, we emit a signal with the value, so that
    that change can be set (on Main)
 */

class Options : public SecondaryWindow
{
    public:

        Options();

        void loadConfigurations ();



        sigc::signal<void, int> signal_onNormalFrequencyChange();
        sigc::signal<void, int> signal_onStrongFrequencyChange();

        sigc::signal<void, int> signal_onBeatDurationChange();


    protected:


        sigc::signal<void, int> the_signal_onNormalFrequencyChange;
        sigc::signal<void, int> the_signal_onStrongFrequencyChange;

        sigc::signal<void, int> the_signal_onBeatDurationChange;

    private:


            //events functions

        void onNormalFrequencyChange ();
        void onStrongFrequencyChange ();

        void onBeatDurationChange ();



            //layout stuff

        Gtk::Table container_ui;

            Gtk::HBox beatDurationContainer_ui;

                Gtk::Label beatDurationLabel_ui;
                MySpinButton changeBeatDuration_ui;
                Gtk::Label milisecondsLabel_ui;

            Gtk::HBox normalFreqContainer_ui;

                Gtk::Label normalLabel_ui;
                MySpinButton changeNormalFrequency_ui;
                Gtk::Label normalHz_ui;

            Gtk::HBox strongFreqContainer_ui;

                Gtk::Label strongLabel_ui;
                MySpinButton changeStrongFrequency_ui;
                Gtk::Label strongHz_ui;


};



#endif //OPTIONS_GUARD
