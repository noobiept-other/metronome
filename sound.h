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
