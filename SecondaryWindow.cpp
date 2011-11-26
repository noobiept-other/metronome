#include "SecondaryWindow.h"

#include <iostream>
using std::cout;
using std::endl;

SecondaryWindow::SecondaryWindow ()

    : isOpened_var (false)

{

Glib::RefPtr< const Gdk::Screen > screen = get_screen ();

    //get screen dimensions
int screenWidth = screen->get_width ();
int screenHeight = screen->get_height ();

    //default position - more or less to the middle of the screen (we would need the window's dimensions to calculate properly)
    //since we don't know, we'll assume a window of 500 width and 250 height
    //it will be close enough :)
x_position_var = (screenWidth  / 2) - (500 / 2);
y_position_var = (screenHeight / 2) - (250 / 2);



    // :::: Events :::: //

this->add_events( Gdk::KEY_RELEASE_MASK );

this->signal_key_release_event().connect ( sigc::mem_fun( *this, &SecondaryWindow::onKeyRelease ) );
}



void SecondaryWindow::open ()
{
isOpened_var = true;


this->move (x_position_var, y_position_var);


this->show();
}



void SecondaryWindow::on_hide ()
{
this->get_position (x_position_var, y_position_var);


isOpened_var = false;

Gtk::Window::on_hide ();
}






bool SecondaryWindow::isOpened () const
{
return isOpened_var;
}




bool SecondaryWindow::onKeyRelease (GdkEventKey *event)
{
if (event->keyval == GDK_KEY_Escape)
    {
    hide();
    }

return true;
}



    //only for loading, the window will be moved when calling open ()
    //this has to be called first..
void SecondaryWindow::setPosition (int x, int y)
{
x_position_var = x;
y_position_var = y;
}


void SecondaryWindow::getPosition (int& x, int& y)
{
this->get_position (x, y);
}
