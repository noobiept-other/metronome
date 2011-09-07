#ifndef SECONDARY_WINDOW_GUARD
#define SECONDARY_WINDOW_GUARD


#include <gtkmm.h>


class SecondaryWindow : public Gtk::Window
{
    public:

        SecondaryWindow ();

        virtual void open();

        bool isOpened() const;

        void setPosition (int x, int y);

        void getPosition (int& x, int& y);

    protected:

            // :::: Events :::: //


            //override function, that is called when the window is hidden (or closed)
        virtual void on_hide ();


        virtual bool onKeyRelease(GdkEventKey *event);


    private:


            // :::: Variables :::: //


        bool isOpened_var;

            //position in the screen of the window
        int x_position;
        int y_position;

};



#endif //SECONDARY_WINDOW_GUARD
