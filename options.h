#ifndef OPTIONS_GUARD
#define OPTIONS_GUARD


#include <gtkmm.h>

#include "SecondaryWindow.h"

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

        Gtk::Table container_gui;

            Gtk::HBox beatDurationContainer_gui;

                Gtk::Label beatDurationLabel_gui;
                Gtk::SpinButton changeBeatDuration_gui;
                Gtk::Label milisecondsLabel_gui;

            Gtk::HBox normalFreqContainer_gui;

                Gtk::Label normalLabel_gui;
                Gtk::SpinButton changeNormalFrequency_gui;
                Gtk::Label normalHz_gui;

            Gtk::HBox strongFreqContainer_gui;

                Gtk::Label strongLabel_gui;
                Gtk::SpinButton changeStrongFrequency_gui;
                Gtk::Label strongHz_gui;


};



#endif //OPTIONS_GUARD
