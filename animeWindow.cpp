#include "animeWindow.h"




AnimeWindow::AnimeWindow()

    : container(2, 1),
      isFullScreen(false),
      isOpened (false)

{
changeFullScreen.set_label("Full screen");



normalColor.set_label("Normal beat");

selectNormalColor.set_title("Select a color");
selectNormalColor.set_rgba(animation.getColor());


strongBeatColor.set_label("Strong beat");

selectStrongColor.set_title("Select a color");
selectStrongColor.set_rgba(animation.getStrongColor());


buttonsContainer.set_spacing(10);


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

//this->signal_key_release_event().connect ( sigc::mem_fun(*this, &AnimeWindow::onKeyRelease) );



set_title ("Animation");

set_default_size (400, 300);

//add_action_widget(container, 1);


add (container);

show_all_children();
}



void AnimeWindow::open ()
{
isOpened = true;

show();
}



void AnimeWindow::start()
{
    //no point in doing anything with the window closed
if (isOpened == true)
    {
    animation.start();
    }

}



void AnimeWindow::start_strongBeat()
{
    //no point in doing anything with the window closed
if (isOpened == true)
    {
    animation.start_strongBeat();
    }
}



void AnimeWindow::stop()
{
    //no point in doing anything with the window closed
if (isOpened == true)
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
isOpened = false;
}

/*
bool on_key_release_event (GdkEventKey* event)
{
    cout << event->keyval << endl;

//if (event->keyval == GDK_Escape)
   // {
   // cout << "esc key" << endl;
  //  }
return true;
}
*/

/*
void AnimeWindow::onKeyRelease(GdkEventButton *event)
{
cout << "key" << endl;
}*/



void AnimeWindow::onColorSet()
{
animation.setColor(selectNormalColor.get_rgba());
}



void AnimeWindow::onStrongColorSet()
{
animation.setStrongColor(selectStrongColor.get_rgba());
}
