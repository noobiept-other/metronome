#ifndef ANIMATION_GUARD
#define ANIMATION_GUARD

#include <gtkmm.h>


#include <iostream>

using std::cout;
using std::endl;

class Animation : public Gtk::DrawingArea
{
    public:

        Animation();


            //starts the animation
        void start();

        void start_strongBeat();

            //ends it
        void stop();


        Gdk::RGBA getColor() const;

        Gdk::RGBA getStrongColor() const;


        void setColor (Gdk::RGBA newColor);

            //values from 0 to 1
        void setColor (int red, int green, int blue, int alpha);


        void setStrongColor (Gdk::RGBA newColor);


    protected:

        virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);



    private:


        void forceReDraw();

            //when we're on the tempo, change to this color
        Gdk::RGBA activeColor;

            //or this, when its the strong beat
        Gdk::RGBA strongBeatColor;

            //otherwise, just draw the black color
        const Gdk::RGBA black;

        Gdk::RGBA tempColor;

};



#endif //ANIMATION_GUARD
