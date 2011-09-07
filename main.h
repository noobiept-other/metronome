#ifndef MAIN_GUARD
#define MAIN_GUARD

/*

    To doo:


        window.set_icon() ou .set_icon_from_file()
            (e fazer o icon)



        gravar a posicao da janela no monitor e dps ao iniciar o programa mover para essa posicao
            convem verificar se essa posicao nao fica fora do monitor (por exemplo usar as mesmas configuracoes
                                                                        em 2 pcs com monitores diferentes)
                ver o tamanho maximo, e se passar esse limite ajustar os valores



        reorganizar o codigo...

        a configurations, ter uma funcao friend das classes, em vez de ter set/get functions (e n ter global a variavel)


 */


#include <gtkmm.h>
#include <gstreamermm.h>

#include <iostream>
#include <string>
#include <fstream>


using std::cout;
using std::endl;

using std::string;

#include "metronome.h"
#include "tuner.h"
#include "note.h"
#include "configurations.h"



class Main : public Gtk::Window, public Metronome
{
    public:

        Main();

            //saves the state of the program (which windows were open, the options, etc)
        ~Main();

        virtual void start();

        void openOptions();


        void openTuner();

bool test();
        //Configurations configurations;

    protected:


        virtual void updateTempo();

            //called when the tuner is closed
        void onTunerHide();

        //void test();

    private:

            // :::: Functions :::: //

        void loadConfigurations();

       // double getPropertyValue (string line, string property);


        virtual void setStrongBeats (Gtk::RadioButton* widget, int beat);

        void setStrongBeats_fromSpinButton ();

        //HERE hack - to cancel multiple events when changing the strong beats
        bool changingStrongBeats;


            // :::: Variables :::: //


        Options optionsPage;

        Tuner tuner;
        //Metronome metronome;
            //when we open the tuner, we save in this variable whether the metronome was playing, so that when
            //closing the tuner window, we can restart the metronome
        bool wasPlaying_var;

            // :::: Layout :::: //

            //2 row and 2 columns
        Gtk::Table mainTable;

            Gtk::Table tempoContainer;

                Gtk::Label tempoName;
                Gtk::SpinButton changeTempo;
                Gtk::Label tempoBpm;

            Gtk::Table strongBeat;

                Gtk::Label strongBeatLabel;

                Gtk::RadioButton oneBeat;
                Gtk::RadioButton twoBeats;
                Gtk::RadioButton threeBeats;
                Gtk::RadioButton fourBeats;
                Gtk::SpinButton otherBeat;

            Gtk::HBox startStopContainer;

                Gtk::Button start_gui;
                Gtk::Button stop;

            Gtk::HBox otherContainer;

                Gtk::Button openOptions_gui;
                Gtk::Button openTuner_gui;
                Gtk::Button openAnimation;

};


#endif
