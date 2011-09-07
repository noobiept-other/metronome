#ifndef OPTIONS_GUARD
#define OPTIONS_GUARD


#include <gtkmm.h>

#include "SecondaryWindow.h"
#include "configurations.h"


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

        Gtk::Table container;

            Gtk::HBox beatDurationContainer;

                Gtk::Label beatDurationLabel;
                Gtk::SpinButton changeBeatDuration;
                Gtk::Label milisecondsLabel;

            Gtk::HBox normalFreqContainer;

                Gtk::Label normalLabel;
                Gtk::SpinButton changeNormalFrequency;
                Gtk::Label normalHz;

            Gtk::HBox strongFreqContainer;

                Gtk::Label strongLabel;
                Gtk::SpinButton changeStrongFrequency;
                Gtk::Label strongHz;


};



#endif //OPTIONS_GUARD
