#include "animeWindow.h"

#include <sstream>


AnimeWindow::AnimeWindow(int bpm)

    : container(2, 1),
      isFullScreen(false)

{
    //sets the label of the currentBpm element with the current bpm
updateBpm(bpm);


changeFullScreen.set_label("Full screen");



normalColor.set_label("Normal beat");

selectNormalColor.set_title("Select a color");
selectNormalColor.set_rgba(animation.getColor());


strongBeatColor.set_label("Strong beat");

selectStrongColor.set_title("Select a color");
selectStrongColor.set_rgba(animation.getStrongColor());


buttonsContainer.set_spacing(10);


buttonsContainer.pack_start (currentBpm);

buttonsContainer.pack_start(normalColor);
buttonsContainer.pack_start(selectNormalColor);

buttonsContainer.pack_start(strongBeatColor);
buttonsContainer.pack_start(selectStrongColor);


buttonsContainer.pack_start(changeFullScreen);

container.attach (animation, 0, 1, 0, 1);

    //use the SHRINK on the yoption, so that the buttons don't grow in size when resizing the window
container.attach (buttonsContainer, 0, 1, 1, 2, Gtk::FILL | Gtk::EXPAND, Gtk::SHRINK);



    //set the events


selectNormalColor.signal_color_set().connect( sigc::mem_fun(*this, &AnimeWindow::onColorSet) );

selectStrongColor.signal_color_set().connect( sigc::mem_fun(*this, &AnimeWindow::onStrongColorSet) );



changeFullScreen.signal_clicked().connect( sigc::mem_fun(*this, &AnimeWindow::fullScreen) );
//openAnimation.signal_clicked().connect( sigc::mem_fun(animeWindow, &AnimeWindow::open) );


    //when closing the window
this->signal_hide().connect( sigc::mem_fun(*this, &AnimeWindow::onHide) );

//add_events(Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK);

add_events( Gdk::KEY_PRESS_MASK );

this->signal_key_release_event().connect ( sigc::mem_fun(*this, &AnimeWindow::onKeyRelease) );



set_title ("Animation");

set_default_size (400, 300);

//add_action_widget(container, 1);


add (container);

show_all_children();
}


/*
void AnimeWindow::open ()
{
isOpened_var = true;

show();
}
*/
/*
bool AnimeWindow::isOpened() const
{
return isOpened_var;
}
*/

void AnimeWindow::start()
{
    //no point in doing anything with the window closed
if (isOpened() == true)
    {
    animation.start();
    }

}



void AnimeWindow::start_strongBeat()
{
    //no point in doing anything with the window closed
if (isOpened() == true)
    {
    animation.start_strongBeat();
    }
}



void AnimeWindow::stop()
{
    //no point in doing anything with the window closed
if (isOpened() == true)
    {
    animation.stop();
    }
}


void AnimeWindow::fullScreen()
{
    //we take out the full screen
if (isFullScreen == true)
    {
    isFullScreen = false;

    unfullscreen();
    }

    //ask for full screen mode
else
    {
    isFullScreen = true;

    fullscreen();   //Gtk::Window's version
    }


}


void AnimeWindow::onHide()
{
    //reset stuff
//isOpened_var = false;

SecondaryWindow::onHide ();

    //take out the full screen (so that when opening again the animation window, it doesn't open in full screen mode)
if (isFullScreen == true)
    {
    unfullscreen();

        //when calling unfullscreen(), it leaves the window occupying the whole screen, so resize to the default values
    resize (property_default_width(), property_default_height());

    isFullScreen = false;
    }
}




bool AnimeWindow::onKeyRelease(GdkEventKey *event)
{
if (event->keyval == GDK_KEY_Escape)
    {
        //we change the window back to the dimensions it had before
    if (isFullScreen == true)
        {
        unfullscreen();

            //when calling unfullscreen(), it leaves the window occupying the whole screen, so resize to the default values
        resize (property_default_width(), property_default_height());

        isFullScreen = false;
        }

        //we close the window
    else
        {
        SecondaryWindow::onHide();

        this->hide();
        }
    }

return true;
}



void AnimeWindow::onColorSet()
{
animation.setColor(selectNormalColor.get_rgba());
}



void AnimeWindow::onStrongColorSet()
{
animation.setStrongColor(selectStrongColor.get_rgba());
}


void AnimeWindow::updateBpm (int bpm)
{
std::stringstream tempBpm;

tempBpm << bpm << " bpm";
currentBpm.set_label (tempBpm.str());
}
