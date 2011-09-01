#include "SecondaryWindow.h"


SecondaryWindow::SecondaryWindow ()

    : isOpened_var (false)

{
    // :::: Events :::: //

    //when closing the window
this->signal_hide().connect( sigc::mem_fun(*this, &SecondaryWindow::onHide) );


this->add_events( Gdk::KEY_PRESS_MASK );

this->signal_key_release_event().connect ( sigc::mem_fun(*this, &SecondaryWindow::onKeyRelease) );

}



void SecondaryWindow::open ()
{
isOpened_var = true;

this->show();
}




bool SecondaryWindow::isOpened () const
{
return isOpened_var;
}



sigc::signal<void> SecondaryWindow::signal_onHide () const
{
return the_signal_onHide;
}



void SecondaryWindow::onHide ()
{
isOpened_var = false;


    //emit our custom signal, that tells the window was closed
the_signal_onHide.emit();
}



bool SecondaryWindow::onKeyRelease(GdkEventKey *event)
{
if (event->keyval == GDK_KEY_Escape)
    {
    onHide();

    this->hide();
    }

return true;
}
