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

            // :::: Events :::: //


            //when the window is closed
        virtual void onHide();


        virtual bool onKeyRelease(GdkEventKey *event);


    private:


            // :::: Variables :::: //

        sigc::signal<void> the_signal_onHide;

        bool isOpened_var;

};



#endif //SECONDARY_WINDOW_GUARD
