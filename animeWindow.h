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

    AnimeWindow(int bpm);


    void open();

    bool isOpened() const;

    void start();
    void start_strongBeat();


    void stop();



    void updateBpm (int bpm);



  private:

    void onHide();

    bool onKeyRelease(GdkEventKey *event);



    void onColorSet();

    void onStrongColorSet();


    Gtk::Table container;

        Animation animation;

        Gtk::HBox buttonsContainer;

            Gtk::Label currentBpm;

            Gtk::Label normalColor;
            Gtk::ColorButton selectNormalColor;

            Gtk::Label strongBeatColor;
            Gtk::ColorButton selectStrongColor;

            Gtk::Button changeFullScreen;



    void fullScreen();
    bool isFullScreen;


    bool isOpened_var;
};




#endif //ANIME_WINDOW_GUARD
