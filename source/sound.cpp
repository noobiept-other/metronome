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


#include "sound.h"



Sound::Sound(double normalFrequency, double strongFrequency)

	: normalFrequency_var (normalFrequency),
      strongFrequency_var (strongFrequency),
      isPlaying_var       (false)

{
pipeline_var = Gst::Pipeline::create("sound");


source_var = Gst::ElementFactory::create_element ("audiotestsrc", "source");
sink_var   = Gst::ElementFactory::create_element ("autoaudiosink", "output");

pipeline_var->add (source_var);
pipeline_var->add (sink_var);

source_var->link (sink_var);

source_var->set_property ("freq", normalFrequency);
}



/*
    Plays the normal frequency, until stopPlaying() is called
 */

void Sound::play ()
{
source_var->set_property ("freq", normalFrequency_var);

pipeline_var->set_state (Gst::STATE_PLAYING);

isPlaying_var = true;
}



void Sound::play_strongBeat()
{
source_var->set_property ("freq", strongFrequency_var);

pipeline_var->set_state (Gst::STATE_PLAYING);

isPlaying_var = true;
}



void Sound::play (double frequency)
{
source_var->set_property ("freq", frequency);

pipeline_var->set_state (Gst::STATE_PLAYING);

isPlaying_var = true;
}



void Sound::stopPlaying()
{
pipeline_var->set_state (Gst::STATE_NULL);

isPlaying_var = false;
}



void Sound::setFrequency (double frequency)
{
normalFrequency_var = frequency;
}


void Sound::setStrongFrequency (double frequency)
{
strongFrequency_var = frequency;
}



bool Sound::isPlaying() const
{
return isPlaying_var;
}




double Sound::getNormalFrequency() const
{
return normalFrequency_var;
}


double Sound::getStrongFrequency() const
{
return strongFrequency_var;
}
