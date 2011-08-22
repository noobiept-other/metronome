#include "sound.h"



Sound::Sound(int frequency)

	: frequency_obj (frequency)

{
m_pipeline = Gst::Pipeline::create("note");     //HERE ter que passar estes nomes como argumento, senao n consigo ter + k 1 objecto da classe

m_source = Gst::ElementFactory::create_element("audiotestsrc", "source");
m_sink = Gst::ElementFactory::create_element ("autoaudiosink", "output");

m_pipeline->add(m_source);
m_pipeline->add(m_sink);
m_source->link(m_sink);

m_source->set_property("freq", frequency);
}



void Sound::play ()
{
m_pipeline->set_state(Gst::STATE_PLAYING);
}



void Sound::stop()
{
m_pipeline->set_state(Gst::STATE_NULL);
}



void Sound::setFrequency (int frequency)
{
    //see if its within the audible range (maybe I can reduce this range?... //HERE )
if (frequency < 20 || frequency > 20000)
    {
    return;
    }


frequency_obj = frequency;

m_source->set_property("freq", frequency);
}
