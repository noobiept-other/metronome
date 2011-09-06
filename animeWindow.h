#ifndef ANIME_WINDOW_GUARD
#define ANIME_WINDOW_GUARD

#include <gtkmm.h>


#include <iostream>
using std::cout;
using std::endl;

#include "SecondaryWindow.h"
#include "animation.h"



class AnimeWindow : public SecondaryWindow
{
    public:

        AnimeWindow(int bpm);


        void loadConfigurations ();
    //void open();

   // bool isOpened() const;

        void start();
        void start_strongBeat();


        void stop();



        void updateBpm (int bpm);


            //hmmm - isto ja existe no animation.h
        Gdk::RGBA getColor() const;

        Gdk::RGBA getStrongColor() const;

        void setColor (Gdk::RGBA newColor);

        void setStrongColor (Gdk::RGBA newColor);


    protected:

        virtual void onHide();

        virtual bool onKeyRelease(GdkEventKey *event);


    private:


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

};




#endif //ANIME_WINDOW_GUARD
