#include "SecondaryWindow.h"

#include <iostream>
using std::cout;
using std::endl;

SecondaryWindow::SecondaryWindow ()

    : isOpened_var (false)

{
get_position (x_position, y_position);  //HERE hmmm como inicializar isto

    // :::: Events :::: //

this->add_events( Gdk::KEY_PRESS_MASK );

this->signal_key_release_event().connect ( sigc::mem_fun( *this, &SecondaryWindow::onKeyRelease ) );
}



void SecondaryWindow::open ()
{
isOpened_var = true;


this->move (x_position, y_position);

this->show();
}



void SecondaryWindow::on_hide ()
{
this->get_position (x_position, y_position);

isOpened_var = false;

Gtk::Window::on_hide ();
}








bool SecondaryWindow::isOpened () const
{
return isOpened_var;
}




bool SecondaryWindow::onKeyRelease(GdkEventKey *event)
{
if (event->keyval == GDK_KEY_Escape)
    {
    on_hide();

    //this->hide();
    }

return true;
}
