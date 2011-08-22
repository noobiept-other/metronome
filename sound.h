

#ifndef _SOUND_H_
#define _SOUND_H_


#include <gstreamermm.h>

class Sound
{
	public:
		Sound(int frequency = 440); //440 Hz - A4

		void play();
		void stop();

        void setFrequency (int frequency);

	private:

		Glib::RefPtr<Gst::Pipeline> m_pipeline;
		Glib::RefPtr<Gst::Element> m_source;
		Glib::RefPtr<Gst::Element> m_sink;

		double frequency_obj;

};


#endif // _SOUND_H_
