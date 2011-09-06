#include "SecondaryWindow.h"

#include <iostream>
using std::cout;
using std::endl;

SecondaryWindow::SecondaryWindow ()

    : isOpened_var (false)

{
//x_position = 10;
//y_position = 10;

int x, y;
this->get_position (x, y);
this->get_position (x_position, y_position);
//x_position =
//y_position = //default position
//x_position = 10;
//y_position = 10;
cout << "CONSTRUCTOR x " << x << " y " << y << endl;
cout << "CONSTRUCTOR x " << x_position << " y " << y_position << endl;

    // :::: Events :::: //

    //when closing the window
this->signal_hide().connect( sigc::mem_fun(*this, &SecondaryWindow::onHide) );


this->add_events( Gdk::KEY_PRESS_MASK );

this->signal_key_release_event().connect ( sigc::mem_fun( *this, &SecondaryWindow::onKeyRelease ) );

}



void SecondaryWindow::open ()
{
isOpened_var = true;

cout << "OPEN x " << x_position << " y " << y_position << endl;

this->move (x_position, y_position);

this->show();
}




bool SecondaryWindow::isOpened () const
{
return isOpened_var;
}


/*
sigc::signal<void> SecondaryWindow::signal_onHide () const
{
return the_signal_onHide;
}
*/


void SecondaryWindow::onHide ()
{
isOpened_var = false;

    //get the current position of the window
this->get_position (x_position, y_position);    //HERE eh sempre 0..

cout << "ONHIDE x " << x_position << " y " << y_position << endl;
    //emit our custom signal, that tells the window was closed
//the_signal_onHide.emit();
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
