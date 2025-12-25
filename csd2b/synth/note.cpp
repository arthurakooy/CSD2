//
// Created by Ciska Vriezenga on 01/12/2025.
//

#include "note.h"

Note::Note(int midiNoteNumber, float quarterNoteDuration, float quarterNoteToNext) :
 midiNoteNumber(midiNoteNumber), quarterNoteDuration(quarterNoteDuration), quarterNoteToNext(quarterNoteToNext)
{}

int Note::getMidiNoteNumber() {
  return midiNoteNumber;
}

float Note::getQuarterNoteDuration() {
  return quarterNoteDuration;
}

float Note::getQuarterNoteToNext() {
  return quarterNoteToNext;
}

float Note::getPitch() {
  return mtof(midiNoteNumber);
}

float Note::mtof(int midiNoteNumber)
{
  return 440.0 * pow (2.0, (midiNoteNumber - 69.0f) / 12.0f);
}