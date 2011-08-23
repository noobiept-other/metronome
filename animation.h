#ifndef ANIMATION_GUARD
#define ANIMATION_GUARD

#include <gtkmm.h>

class Animation : public Gtk::DrawingArea
{
    public:

        Animation();


            //opens the window
        void open();

            //starts the animation
        void show();

            //ends it
        void hide();


    protected:

        virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);



    private:

        //Gtk::Window animationWindow;
        //Gtk::DrawingArea animation;
};



#endif //ANIMATION_GUARD
