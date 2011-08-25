#include "sound.h"



Sound::Sound(double normalFrequency, int strongBeats)

	: normalFrequency_obj (normalFrequency),
      diffFrequency_obj   (150)

{
    //HERE
strongFrequency_obj = normalFrequency + diffFrequency_obj;



m_pipeline = Gst::Pipeline::create("note");     //HERE ter que passar estes nomes como argumento, senao n consigo ter + k 1 objecto da classe

m_source = Gst::ElementFactory::create_element("audiotestsrc", "source");
m_sink = Gst::ElementFactory::create_element ("autoaudiosink", "output");

m_pipeline->add(m_source);
m_pipeline->add(m_sink);
m_source->link(m_sink);

m_source->set_property("freq", normalFrequency);
}



void Sound::play ()
{
m_source->set_property("freq", normalFrequency_obj);

m_pipeline->set_state(Gst::STATE_PLAYING);
}



void Sound::play_strongBeat()
{
m_source->set_property("freq", strongFrequency_obj);

m_pipeline->set_state(Gst::STATE_PLAYING);
}


void Sound::stopPlaying()
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


normalFrequency_obj = frequency;

strongFrequency_obj = frequency + diffFrequency_obj;

m_source->set_property("freq", frequency);
}
