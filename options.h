#ifndef OPTIONS_GUARD
#define OPTIONS_GUARD


#include <gtkmm.h>


class Options : public Gtk::Window
{
    public:

        Options();

        void open();

    private:

        bool isOpened;


            //layout stuff

        Gtk::Table container;

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
