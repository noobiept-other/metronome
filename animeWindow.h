#ifndef ANIME_WINDOW_GUARD
#define ANIME_WINDOW_GUARD

#include <gtkmm.h>


#include "SecondaryWindow.h"
#include "animation.h"



class AnimeWindow : public SecondaryWindow
{
    public:

        AnimeWindow(int bpm);


        void loadConfigurations ();


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

            // :::: Event functions :::: //

            //override base function
        virtual void on_hide();

        virtual bool onKeyRelease(GdkEventKey *event);


    private:


        void onColorSet();

        void onStrongColorSet();


        void fullScreen ();

        bool isFullScreen_var;

            // :::: Layout stuff :::: //


        Gtk::Table container_gui;

            Animation animation_gui;

            Gtk::HBox buttonsContainer_gui;

                Gtk::Label currentBpm_gui;

                Gtk::Label normalColor_gui;
                Gtk::ColorButton selectNormalColor_gui;

                Gtk::Label strongBeatColor_gui;
                Gtk::ColorButton selectStrongColor_gui;

                Gtk::Button changeFullScreen_gui;

};




#endif //ANIME_WINDOW_GUARD
