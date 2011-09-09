#include "animeWindow.h"

#include <sstream>

#include "configurations.h"
extern Configurations CONFIGURATIONS;



AnimeWindow::AnimeWindow(int bpm)

    : isFullScreen_var (false),
      container_gui    (2, 1)

{
    // :::: Show current bpm :::: //

    //sets the label of the currentBpm element with the current bpm
updateBpm(bpm);


    // :::: Change to full screen :::: //

changeFullScreen_gui.set_label("Full screen");



    // :::: Change normal color :::: //

normalColor_gui.set_label("Normal beat");

selectNormalColor_gui.set_title ("Select a color");
selectNormalColor_gui.set_rgba  (animation_gui.getColor());


    // :::: Change strong color :::: //

strongBeatColor_gui.set_label("Strong beat");

selectStrongColor_gui.set_title("Select a color");

selectStrongColor_gui.set_rgba(animation_gui.getStrongColor());


    // :::: Buttons container :::: //

buttonsContainer_gui.set_spacing(10);


buttonsContainer_gui.pack_start (currentBpm_gui);

buttonsContainer_gui.pack_start(normalColor_gui);
buttonsContainer_gui.pack_start(selectNormalColor_gui);

buttonsContainer_gui.pack_start(strongBeatColor_gui);
buttonsContainer_gui.pack_start(selectStrongColor_gui);


buttonsContainer_gui.pack_start(changeFullScreen_gui);

container_gui.attach (animation_gui, 0, 1, 0, 1);

    //use the SHRINK on the yoption, so that the buttons don't grow in size when resizing the window
container_gui.attach (buttonsContainer_gui, 0, 1, 1, 2, Gtk::FILL | Gtk::EXPAND, Gtk::SHRINK);


    // :::: Window :::: //


this->set_title ("Animation");

this->set_default_size (400, 300);



this->add (container_gui);

this->show_all_children();


    // :::: Set the events :::: //


selectNormalColor_gui.signal_color_set().connect( sigc::mem_fun(*this, &AnimeWindow::onColorSet) );

selectStrongColor_gui.signal_color_set().connect( sigc::mem_fun(*this, &AnimeWindow::onStrongColorSet) );


changeFullScreen_gui.signal_clicked().connect( sigc::mem_fun(*this, &AnimeWindow::fullScreen) );



    // keyboard events

this->add_events( Gdk::KEY_PRESS_MASK );

this->signal_key_release_event().connect ( sigc::mem_fun(*this, &AnimeWindow::onKeyRelease) );
}



/*
    Is only called in the beginning of the program
 */

void AnimeWindow::loadConfigurations ()
{
setColor (CONFIGURATIONS.normalColor);
selectNormalColor_gui.set_rgba (CONFIGURATIONS.normalColor);

setStrongColor (CONFIGURATIONS.strongColor);
selectStrongColor_gui.set_rgba (CONFIGURATIONS.strongColor);
}




void AnimeWindow::start()
{
    //no point in doing anything with the window closed
if (isOpened() == true)
    {
    animation_gui.start();
    }

}



void AnimeWindow::start_strongBeat()
{
    //no point in doing anything with the window closed
if (isOpened() == true)
    {
    animation_gui.start_strongBeat();
    }
}



void AnimeWindow::stop()
{
    //no point in doing anything with the window closed
if (isOpened() == true)
    {
    animation_gui.stop();
    }
}


void AnimeWindow::fullScreen()
{
    //we take out the full screen
if (isFullScreen_var == true)
    {
    isFullScreen_var = false;

    this->unfullscreen();
    }

    //ask for full screen mode
else
    {
    isFullScreen_var = true;

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
        SecondaryWindow::on_hide();
        }
    }

return true;
}



void AnimeWindow::onColorSet()
{
animation_gui.setColor(selectNormalColor_gui.get_rgba());
}



void AnimeWindow::onStrongColorSet()
{
animation_gui.setStrongColor(selectStrongColor_gui.get_rgba());
}



void AnimeWindow::updateBpm (int bpm)
{
std::stringstream tempBpm;

    //convert to string
tempBpm << bpm << " bpm";

currentBpm_gui.set_label (tempBpm.str());
}



Gdk::RGBA AnimeWindow::getColor() const
{
return animation_gui.getColor ();
}



Gdk::RGBA AnimeWindow::getStrongColor() const
{
return animation_gui.getStrongColor();
}


void AnimeWindow::setColor (Gdk::RGBA newColor)
{
animation_gui.setColor (newColor);
}


void AnimeWindow::setStrongColor (Gdk::RGBA newColor)
{
animation_gui.setStrongColor (newColor);
}
