/*

	Copyright - 2011 - Pedro Ferreira

	This file is part of Metronome.

    Metronome is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Metronome is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Metronome.  If not, see <http://www.gnu.org/licenses/>.

 */


#ifndef MAIN_GUARD
#define MAIN_GUARD

/*

    Naming conventions:

        Global variables:

            All characters capitalized
                (like, EXAMPLE)

        class name:

            First character capitalized
                (like, Example)

        gtkmm related class variables (for the buttons, containers, etc):

            ending in _ui (from, user interface)
                (like example_ui)

        normal class variables (that don't conform with anything above):

            ending in _var (from, variable)
                (like, example_var)



    To doo:


        - ter a possibilidade de ter diferentes tipos de som (ver audiotestsrc - gstreamer)

        - Nos Gtk::ColorButton, ele fecha a janela on_key_press, e depois ao largar-se a tecla (on_key_release)
            fecha de seguida a AnimeWindow... por a fechar apenas on_key_release os Gtk::ColorButton


        - passar os setStrongBeats() do Main para o Metronome


        - a configurations, ter uma funcao friend das classes, em vez de ter set/get functions (e n ter global a variavel)

        - passar o loadConfigurations() do Main para o Configurations (tem os erros ao compilar.. nao encontra as classes..)
            (e ter Main como friend class)


        - gravar no ficheiro: property="value" ?..
		    ou estilo json


        - double-click na Animation para ir para fullscreen (n esta a funcionar)

        - esconder os butoes qd a Animation esta em fullscreen, e voltar a por qd sai (tb n)

		- melhorar o icon

 */


#include <gtkmm.h>

#include <iostream>
#include <string>
#include <fstream>



#include "metronome.h"
#include "options.h"
#include "tuner.h"


class Main : public Gtk::Window, public Metronome
{
    public:

        Main();

            //saves the state of the program (which windows were open, the options, etc)
        virtual ~Main();

        virtual void start();

        void openOptions();


        void openTuner();


    protected:

            //override from Gtk::Window
        virtual void on_hide ();

        virtual void updateTempo();

            //called when the tuner_var is closed
        void onTunerHide();


    private:

            // :::: Functions :::: //

        void loadConfigurations();

        bool bringTunerToFront();



        virtual void setStrongBeats (Gtk::RadioButton* widget, int beat);

        void setStrongBeats_fromSpinButton ();

            //hack - to cancel multiple events when changing the strong beats
        bool changingStrongBeats_var;


            // :::: Variables :::: //


        Options optionsPage_var;

        Tuner tuner_var;


            //when we open the tuner_var, we save in this variable whether the metronome was playing, so that when
            //closing the tuner window, we can restart the metronome
        bool wasPlaying_var;

            // :::: Layout :::: //

            //2 row and 2 columns
        Gtk::Table mainTable_ui;

            Gtk::Table tempoContainer_ui;

                Gtk::Label tempoName_ui;
                Gtk::SpinButton changeTempo_ui;
                Gtk::Label tempoBpm_ui;

            Gtk::Table strongBeat_ui;

                Gtk::Label strongBeatLabel_ui;

                Gtk::RadioButton oneBeat_ui;
                Gtk::RadioButton twoBeats_ui;
                Gtk::RadioButton threeBeats_ui;
                Gtk::RadioButton fourBeats_ui;
                Gtk::SpinButton otherBeat_ui;

            Gtk::Box startStopContainer_ui;

                Gtk::Button start_ui;
                Gtk::Button stop_ui;

            Gtk::Box otherContainer_ui;

                Gtk::Button openOptions_ui;
                Gtk::Button openTuner_ui;
                Gtk::Button openAnimation_ui;

};


#endif
