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


#ifndef _SOUND_H_
#define _SOUND_H_


#include <gstreamermm.h>


class Sound
{
	public:

		Sound(double normalFrequency = 440, double strongFrequency = 587.33); //440 Hz - A4 | 587.33 - D5


        void setFrequency (double frequency);

        void setStrongFrequency (double frequency);


        void play();
        void play_strongBeat();

        void play (double frequency);

		void stopPlaying();


		bool isPlaying() const;


        double getNormalFrequency() const;
        double getStrongFrequency() const;


	private:

		Glib::RefPtr<Gst::Pipeline> pipeline_var;
		Glib::RefPtr<Gst::Element> source_var;
		Glib::RefPtr<Gst::Element> sink_var;


		double normalFrequency_var;
		double strongFrequency_var;


        bool isPlaying_var;

};


#endif // _SOUND_H_
