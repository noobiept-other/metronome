#ifndef SECONDARY_WINDOW_GUARD
#define SECONDARY_WINDOW_GUARD


#include <gtkmm.h>


class SecondaryWindow : public Gtk::Window
{
    public:

        SecondaryWindow ();

        virtual void open();

        bool isOpened() const;


        sigc::signal<void> signal_onHide() const;


    protected:

            //when the window is closed
        void onHide();

        sigc::signal<void> the_signal_onHide;


    private:


            // :::: Events :::: //

        bool onKeyRelease(GdkEventKey *event);


            // :::: Variables :::: //

        bool isOpened_var;


}



#endif //SECONDARY_WINDOW_GUARD
