#include "note.h"

#include <cmath>

const int Note::numberOfNotes_obj = 12;

const std::string Note::allNotes_obj[] = { "A", "A+", "B", "C", "C+", "D", "D+", "E", "F", "F+", "G", "G+" };


Note::Note(std::string note, int octave)

    : note_obj (note),
      octave_obj (octave)

{
findPosition();
calculateFrequency();
}


Note::Note(double frequency)

    : frequency_obj (frequency)

{
calculateNote();
//findPosition();
}


    //similar to the constructor
void Note::newNote(double frequency)
{
frequency_obj = frequency;

calculateNote();
}



    //similar to the constructor
void Note::newNote (std::string note, int octave)
{
note_obj = note;
octave_obj = octave;


findPosition();
calculateFrequency();

cout << "endOf_newNote: note " << note_obj << " notePosition " << notePosition_obj << " freq " << frequency_obj << endl;
}


void Note::findPosition ()
{
for (int i = 0 ; i < numberOfNotes_obj ; i++)
    {
        cout << "note " << note_obj << " allNotes " << allNotes_obj[i] << endl;

        //find the note
    if (note_obj == allNotes_obj[i])
        {
        notePosition_obj = i;

        //note_obj = allNotes_obj[i];

        return;
        }
    }
}


void Note::calculateFrequency()
{
    /*
        we're calculating the difference of notes between our note and the A4 note
        (so if our note is B4, then the difference is 2 - A4, A+4, B4.. two steps)

        and we have to consider the octave as well, so if our note is B3, then
        we have the 2 plus the octave (there are 12 notes in total)
        so we get 10 as the difference (2 - 12)
    */





int diffOfNotes = notePosition_obj - 12 * (4 - octave_obj);

    //I just got this formula off wikipedia so... :)
    //in theory, you can use any frequency for music.. although in western music we're 'limited' to a set of notes (calculated with this formula)
frequency_obj = 440 * std::pow(2, diffOfNotes / 12.0);

cout << "calcFreq: note position " << notePosition_obj << " freq " << frequency_obj << endl;
}



/*
    calculates the note and octave from a frequency (as close as possible - it may not be the exact note)
 */

void Note::calculateNote ()
{
    //do the same formula in the calculateFrequency() function
    //but now we're looking for the diffOfNotes, and have the frequency_obj
    //diff = 12 * log2 (freq / 440)
double diffOfNotes_temp = 12.0 * (std::log10(frequency_obj / 440) / std::log10(2));


int diffOfNotes = diffOfNotes_temp;


    //round to the closest integer
if (diffOfNotes_temp - diffOfNotes > 0.5)
    {
    diffOfNotes++;
    }


    //now we need the notePosition_obj and the octave_obj
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
    while (diffOfNotes > 12)
        {
        octave++;

        diffOfNotes -= 12;
        }
    }

octave_obj = octave;

    //after we remove all the octaves, whats left is the notePosition
notePosition_obj = diffOfNotes;



    //now get the string representing the note
note_obj = allNotes_obj[notePosition_obj];
}



int Note::getOctave () const
{
return octave_obj;
}



std::string Note::getNote () const
{
return note_obj;
}


double Note::getFrequency() const
{
return frequency_obj;
}


void Note::operator ++ (int a)
{
notePosition_obj++;

    //we're past the length of the array, start from the beginning (and 1 more octave)
if (notePosition_obj == numberOfNotes_obj)
    {
    notePosition_obj = 0;

    octave_obj++;
    }

note_obj = allNotes_obj[notePosition_obj];


calculateFrequency();
}


void Note::operator -- (int a)
{
notePosition_obj--;

if (notePosition_obj < 0)
    {
    notePosition_obj = numberOfNotes_obj - 1;

    octave_obj--;
    }

note_obj = allNotes_obj[notePosition_obj];

calculateFrequency();
}
