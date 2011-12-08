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


#include "note.h"

#include <cmath>

    //Note's static variables
const int Note::numberOfNotes_var = 12;

const std::string Note::allNotes_var[] = { "A", "A+", "B", "C", "C+", "D", "D+", "E", "F", "F+", "G", "G+" };



/*
    Constructing a note with a standard note ( A4, D2 , ...)
 */

Note::Note (std::string note, int octave)

    : note_var (note),
      octave_var (octave),
      isNamedNote_var (true)

{
findPosition();
calculateFrequency();
}



/*
    Constructing a note with a sound frequency
    It will probably not match a standard note (not that there's any problem with that)
 */

Note::Note(double frequency)

    : frequency_var (frequency)

{
calculateNote();
}



    //similar to the constructor
bool Note::newNote (double frequency)
{
frequency_var = frequency;

return calculateNote();
}



    //similar to the constructor
void Note::newNote (std::string note, int octave)
{
note_var = note;
octave_var = octave;
isNamedNote_var = true;


findPosition();
calculateFrequency();
}



/*
    Finds the note position in the allNotes_var array
    So, if our note is A, then the position is 0, if its B its the position 2
 */

void Note::findPosition ()
{
for (int i = 0 ; i < numberOfNotes_var ; i++)
    {
        //find the note
    if (note_var == allNotes_var[i])
        {
        notePosition_var = i;

        return;
        }
    }
}



/*
    Get the frequency of the note, from knowing the letter of the note, and the octave (for standard notes only)
    (we also have a valid notePosition_var)
 */

void Note::calculateFrequency()
{
    /*
        we're calculating the difference of notes between our note and the A4 note
        (so if our note is B4, then the difference is 2 - A4, A+4, B4.. two steps)

        and we have to consider the octave as well, so if our note is B3, then
        we have the 2 minus the octave (there are 12 notes in total)
        so we get -10 as the difference (2 - 12)
    */



int diffOfNotes = notePosition_var - 12 * (4 - octave_var);

    //I just got this formula off wikipedia so... :)
    //in theory, you can use any frequency for music.. although in western music we're 'limited' to a set of notes (calculated with this formula)
frequency_var = 440 * std::pow(2, diffOfNotes / 12.0);
}




/*
    calculates the note and octave from a frequency (as close as possible - it may not be the exact note)
 */

bool Note::calculateNote ()
{
    //do the same formula in the calculateFrequency() function
    //but now we're looking for the diffOfNotes, and have the frequency_var
    //diff = 12 * log2 (freq / 440)
double diffOfNotes_temp = 12.0 * (std::log10(frequency_var / 440) / std::log10(2));


int diffOfNotes = diffOfNotes_temp;


    //see if this is a named note (if the diffOfNotes_temp is an integer, it means it is)
    //since there may be some calculation errors, we're giving it a range, not doing a equality check
if ((diffOfNotes_temp - diffOfNotes) < 0.1)
    {
    isNamedNote_var = true;
    }

else
    {
    isNamedNote_var = false;
    }


    //round to the closest integer
if (diffOfNotes_temp - diffOfNotes > 0.5)
    {
    diffOfNotes++;
    }


    //now we need the notePosition_var and the octave_var
    //since we have the difference of notes, we can get these values
    //we know that to get from one note to the octave, there's 12 steps (notes)
    //so just substract 12 to get the number of octaves, and the rest is the notePosition

    //our base is A4 - 440 Hz
int octave = 4;

    //its a note 'lower' than A4
if (diffOfNotes < 0)
    {
    while (diffOfNotes < 0)
        {
        octave--;

        diffOfNotes += 12;
        }
    }

    //its a note 'higher' than A4
else
    {
    while (diffOfNotes >= 12)
        {
        octave++;

        diffOfNotes -= 12;
        }
    }

octave_var = octave;

    //after we remove all the octaves, whats left is the notePosition
notePosition_var = diffOfNotes;


    //now get the string representing the note
note_var = allNotes_var[notePosition_var];


return isNamedNote_var;
}



int Note::getOctave () const
{
if (isNamedNote_var == true)
    {
    return octave_var;
    }

return -1;
}



std::string Note::getNote () const
{
if (isNamedNote_var == true)
    {
    return note_var;
    }

return "";
}


double Note::getFrequency() const
{
return frequency_var;
}


void Note::operator ++ (int a)
{
notePosition_var++;

    //we're past the length of the array, start from the beginning (and 1 more octave)
if (notePosition_var == numberOfNotes_var)
    {
    notePosition_var = 0;

    octave_var++;
    }

note_var = allNotes_var[notePosition_var];


calculateFrequency();
}


void Note::operator -- (int a)
{
notePosition_var--;

    //one less octave
if (notePosition_var < 0)
    {
        //last note in the array
    notePosition_var = numberOfNotes_var - 1;

    octave_var--;
    }

note_var = allNotes_var[notePosition_var];

calculateFrequency();
}


/*
    Returns the position of the note (considering: 0 -> "A", 1 -> "A#", ...)
 */

int Note::getPosition() const
{
if (isNamedNote_var == true)
    {
    return notePosition_var;
    }

return -1;
}
