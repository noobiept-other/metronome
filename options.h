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


};



#endif //OPTIONS_GUARD
