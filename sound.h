#ifndef _SOUND_H_
#define _SOUND_H_


#include <gstreamermm.h>


class Sound
{
	public:

		Sound(double normalFrequency = 440); //440 Hz - A4


        void setFrequency (int frequency);


        void play();
        void play_strongBeat();

        void play (double frequency);

		void stopPlaying();


		bool isPlaying() const;


	private:

		Glib::RefPtr<Gst::Pipeline> m_pipeline;
		Glib::RefPtr<Gst::Element> m_source;
		Glib::RefPtr<Gst::Element> m_sink;


		double normalFrequency_obj;
		double strongFrequency_obj;

            //the difference in the above frequencies
        const int diffFrequency_obj;


        bool isPlaying_obj;

};


#endif // _SOUND_H_
