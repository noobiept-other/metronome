/*

	Copyright - 2011 - Pedro Ferreira

	This file is part of Metronome.

    Metronome is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Metronome is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Metronome.  If not, see <http://www.gnu.org/licenses/>.

 */


#include "animeWindow.h"

#include <sstream>

#include "configurations.h"
extern Configurations CONFIGURATIONS;



AnimeWindow::AnimeWindow(int bpm)

    : isFullScreen_var (false),
      container_ui    (2, 1)

{
    // :::: Show current bpm :::: //

    //sets the label of the currentBpm element with the current bpm
updateBpm(bpm);


    // :::: Change to full screen :::: //

changeFullScreen_ui.set_label("Full screen");



    // :::: Change normal color :::: //

normalColor_ui.set_label("Normal beat");

selectNormalColor_ui.set_title ("Select a color");
selectNormalColor_ui.set_rgba  (animation_ui.getColor());


    // :::: Change strong color :::: //

strongBeatColor_ui.set_label("Strong beat");

selectStrongColor_ui.set_title("Select a color");

selectStrongColor_ui.set_rgba(animation_ui.getStrongColor());


    // :::: Buttons container :::: //

buttonsContainer_ui.set_spacing (10);
buttonsContainer_ui.set_homogeneous( true );
buttonsContainer_ui.set_orientation( Gtk::ORIENTATION_HORIZONTAL );

buttonsContainer_ui.add (currentBpm_ui);

buttonsContainer_ui.add (normalColor_ui);
buttonsContainer_ui.add (selectNormalColor_ui);

buttonsContainer_ui.add (strongBeatColor_ui);
buttonsContainer_ui.add (selectStrongColor_ui);


buttonsContainer_ui.add (changeFullScreen_ui);

container_ui.attach (animation_ui, 0, 1, 0, 1);

    //use the SHRINK on the yoption, so that the buttons don't grow in size when resizing the window
container_ui.attach (buttonsContainer_ui, 0, 1, 1, 2, Gtk::FILL | Gtk::EXPAND, Gtk::SHRINK);


    // :::: Window :::: //


this->set_title ("Animation");

this->set_default_size (400, 300);



this->add (container_ui);

this->show_all_children();


this->set_icon_from_file("images/animation.png");

    // :::: Set the events :::: //

    // buttons

selectNormalColor_ui.signal_color_set().connect( sigc::mem_fun(*this, &AnimeWindow::onColorSet) );

selectStrongColor_ui.signal_color_set().connect( sigc::mem_fun(*this, &AnimeWindow::onStrongColorSet) );


changeFullScreen_ui.signal_clicked().connect( sigc::mem_fun(*this, &AnimeWindow::fullScreen) );


    // animation

animation_ui.add_events( Gdk::BUTTON_PRESS_MASK );

animation_ui.signal_button_press_event().connect( sigc::mem_fun( *this, &AnimeWindow::animationEvents ) );


    // keyboard events

this->add_events( Gdk::KEY_RELEASE_MASK );

this->signal_key_release_event().connect ( sigc::mem_fun(*this, &AnimeWindow::onKeyRelease) );
}



/*
    Is only called in the beginning of the program
 */

void AnimeWindow::loadConfigurations ()
{
setColor (CONFIGURATIONS.normalColor);
selectNormalColor_ui.set_rgba (CONFIGURATIONS.normalColor);

setStrongColor (CONFIGURATIONS.strongColor);
selectStrongColor_ui.set_rgba (CONFIGURATIONS.strongColor);
}




void AnimeWindow::start()
{
    //no point in doing anything with the window closed
if (isOpened() == true)
    {
    animation_ui.start();
    }

}



void AnimeWindow::start_strongBeat()
{
    //no point in doing anything with the window closed
if (isOpened() == true)
    {
    animation_ui.start_strongBeat();
    }
}



void AnimeWindow::stop()
{
    //no point in doing anything with the window closed
if (isOpened() == true)
    {
    animation_ui.stop();
    }
}


void AnimeWindow::fullScreen()
{
    //we take out the full screen
if (isFullScreen_var == true)
    {
    isFullScreen_var = false;

        //show the buttons //HERE not working
    //buttonsContainer_ui.show_now();


    this->unfullscreen();
    }

    //ask for full screen mode
else
    {
    isFullScreen_var = true;

        //hide the buttons  //HERE this does though
    //buttonsContainer_ui.hide();


    this->fullscreen();   //from Gtk::Window
    }


}




void AnimeWindow::on_hide()
{
    //take out the full screen (so that when opening again the animation window, it doesn't open in full screen mode)
if (isFullScreen_var == true)
    {
    unfullscreen();

        //when calling unfullscreen(), it leaves the window occupying the whole screen, so resize to the default values
    resize (property_default_width(), property_default_height());

    isFullScreen_var = false;
    }


SecondaryWindow::on_hide ();
}




/*
    When pressing esc, it goes off fullscreen mode
    otherwise, its just the normal behaviour from SecondaryWindow
 */

bool AnimeWindow::onKeyRelease(GdkEventKey *event)
{
if (event->keyval == GDK_KEY_Escape)
    {
        //we change the window back to the dimensions it had before
    if (isFullScreen_var == true)
        {
        unfullscreen();

            //when calling unfullscreen(), it leaves the window occupying the whole screen, so resize to the default values
        resize (property_default_width(), property_default_height());

        isFullScreen_var = false;
        }

        //we close the window
    else
        {
        SecondaryWindow::hide();
        }
    }

return true;
}




/*
    When double-clicking on the animation, we open/close the fullscreen
 */

bool AnimeWindow::animationEvents( GdkEventButton *event )
{
    //when double-clicking
if ( event->type == GDK_2BUTTON_PRESS )
    {
        //open/close the fullscreen
    fullScreen();

    return true;
    }


return false;
}




void AnimeWindow::onColorSet()
{
animation_ui.setColor(selectNormalColor_ui.get_rgba());
}



void AnimeWindow::onStrongColorSet()
{
animation_ui.setStrongColor(selectStrongColor_ui.get_rgba());
}



void AnimeWindow::updateBpm (int bpm)
{
std::stringstream tempBpm;

    //convert to string
tempBpm << bpm << " bpm";

currentBpm_ui.set_label (tempBpm.str());
}



Gdk::RGBA AnimeWindow::getColor() const
{
return animation_ui.getColor ();
}



Gdk::RGBA AnimeWindow::getStrongColor() const
{
return animation_ui.getStrongColor();
}


void AnimeWindow::setColor (Gdk::RGBA newColor)
{
animation_ui.setColor (newColor);
}


void AnimeWindow::setStrongColor (Gdk::RGBA newColor)
{
animation_ui.setStrongColor (newColor);
}
