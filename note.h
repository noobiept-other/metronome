#ifndef NOTE_GUARD
#define NOTE_GUARD

#include <iostream>

using std::cout;
using std::endl;

class Note
{
    public:

            //construct with a 'normal' note (in western music, at least)
            //default: A4 (440 Hz)
        Note(std::string note, int octave);

            //or with a frequency (keep in mind that the frequency may not match a named note)
            //default: A4 (440 Hz)
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


        //int getNotePosition () const;


            //adds one note (as in, if current note is C, then it goes C#)
        void operator ++ (int);

        void operator -- (int);

    private:

        void findPosition ();

        void calculateFrequency();

        bool calculateNote();


        const static int numberOfNotes_obj;    //12 notes

        const static std::string allNotes_obj[12];



        std::string note_obj;

        int octave_obj;

        double frequency_obj;

            //position in the notes_obj array
        int notePosition_obj;


        bool isNamedNote_obj;

};



//const int Note::numberOfNotes_obj = 12;

//const std::string Note::allNotes_obj[] = { "A", "A+", "B", "C", "C+", "D", "D+", "E", "F", "F+", "G", "G+" };



#endif //NOTE_GUARD
