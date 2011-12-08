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


#ifndef NOTE_GUARD
#define NOTE_GUARD

#include <string>

class Note
{
    public:

        /*!
            construct with a 'normal' note (in western music, at least)
            default: A4 (440 Hz)
         */

        Note(std::string note, int octave);


        /*!
            or with a frequency (keep in mind that the frequency may not match a named note)
            default: A4 (440 Hz)
         */

        Note (double frequency = 440);


            //similar to the constructors - defines a new note

            //returns true if the frequency is close to a known note
            //even if it isn't, it will still have the nearest note
        bool newNote (double frequency);

        void newNote (std::string note, int octave);



        int getOctave () const;

        std::string getNote () const;


            //returns the frequency of the note
        double getFrequency() const;

        void setFrequency (double frequency);


            //adds one note (as in, if current note is C, then it goes C#)
        void operator ++ (int);

        void operator -- (int);


            //returns the position of the note (0 -> "A", 1 -> "A#", 2 -> "B", ...)
            //or -1 is there isn't a named note that corresponds to the frequency set
        int getPosition() const;


            // :: static variables :: //

        const static int numberOfNotes_var;    //12 notes

        const static std::string allNotes_var[12];


    private:

        void findPosition ();

        void calculateFrequency();

        bool calculateNote();




        std::string note_var;

        int octave_var;

        double frequency_var;

            //position in the allNotes_var array, of the current note
        int notePosition_var;

            //if its one of the standard notes (only when we construct with a frequency, is that this may be false)
        bool isNamedNote_var;

};


#endif //NOTE_GUARD
