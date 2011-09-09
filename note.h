#ifndef NOTE_GUARD
#define NOTE_GUARD

#include <string>

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


            //adds one note (as in, if current note is C, then it goes C#)
        void operator ++ (int);

        void operator -- (int);

    private:

        void findPosition ();

        void calculateFrequency();

        bool calculateNote();


        const static int numberOfNotes_var;    //12 notes

        const static std::string allNotes_var[12];



        std::string note_var;

        int octave_var;

        double frequency_var;

            //position in the allNotes_var array, of the current note
        int notePosition_var;

            //if its one of the standard notes (only when we construct with a frequency, is that this may be false)
        bool isNamedNote_var;

};


#endif //NOTE_GUARD
