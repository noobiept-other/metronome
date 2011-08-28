#ifndef ANIME_WINDOW_GUARD
#define ANIME_WINDOW_GUARD

#include <gtkmm.h>


#include <iostream>
using std::cout;
using std::endl;

#include "animation.h"



class AnimeWindow : public Gtk::Window  //HERE por aqui a Animation
{
  public:

    AnimeWindow();


    void open();


    void start();
    void start_strongBeat();


    void stop();





  private:

    void onHide();

    bool onKeyRelease(GdkEventKey *event);

        //override function from Gtk::Widget
    //virtual bool on_key_release_event (GdkEventKey* event);

    void onColorSet();

    void onStrongColorSet();


    Gtk::Table container;

        Animation animation;

        Gtk::HBox buttonsContainer;

            Gtk::Label normalColor;
            Gtk::ColorButton selectNormalColor;

            Gtk::Label strongBeatColor;
            Gtk::ColorButton selectStrongColor;

            Gtk::Button changeFullScreen;



    void fullScreen();
    bool isFullScreen;


    bool isOpened;
};




#endif //ANIME_WINDOW_GUARD