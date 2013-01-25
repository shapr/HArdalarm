
/*
The code below is a slightly modified version of http://www.earthshineelectronics.com/files/ASKManualRev5.pdf
with a bit of http://arduino.cc/en/Tutorial/Tone mixed in.
*/
// Project 10 - Serial controlled RGB Lamp

#include "pitches.h"

char buffer[18];
int red, green, blue;
int RedPin = 6;
int GreenPin = 10;
int BluePin = 9;
int GroundPin = 8;


int tonePin = 11;
// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };


void setup() 
{ 
  Serial.begin(9600);
  Serial.flush();
  pinMode(RedPin, INPUT);
  pinMode(GreenPin, INPUT);
  pinMode(BluePin, INPUT);
  pinMode(GroundPin, OUTPUT);
} 
void loop()
{ 
  if (Serial.available() > 0) {
    int index=0;
    delay(100); // let the buffer fill up
    int numChar = Serial.available();
    if (numChar>15) {
      numChar=15;
    }
    while (numChar--) {
      buffer[index++] = Serial.read();
    }
    splitString(buffer);
  }
}
void splitString(char* data) {
  Serial.print("Data entered: ");
  Serial.println(data);
  char* parameter; 
  parameter = strtok (data, " ,");
  while (parameter != NULL) {
    setLED(parameter);
    parameter = strtok (NULL, " ,");
  }
  // Clear the text and serial buffers
for (int x=0; x<16; x++) {
    buffer[x]='\0';
  }
  Serial.flush();
}

void setLED(char* data) {
  if ((data[0] == 'r') || (data[0] == 'R')) {
    int Ans = strtol(data+1, NULL, 10);
    Ans = constrain(Ans,0,255);
    analogWrite(RedPin, Ans);
Serial.print("Red is set to: ");
    Serial.println(Ans);
  }
  if ((data[0] == 'g') || (data[0] == 'G')) {
    int Ans = strtol(data+1, NULL, 10);
    Ans = constrain(Ans,0,255);
    analogWrite(GreenPin, Ans);
Serial.print("Green is set to: ");
    Serial.println(Ans);
  }
  if ((data[0] == 'b') || (data[0] == 'B')) {
    int Ans = strtol(data+1, NULL, 10);
    Ans = constrain(Ans,0,255);
    analogWrite(BluePin, Ans);
Serial.print("Blue is set to: ");
    Serial.println(Ans);
  }
  if ((data[0] == 't') || (data[0] == 'T')) {
    int Ans = strtol(data+1, NULL, 10);
    Ans = constrain(Ans,0,255);
    //analogWrite(BluePin, Ans);
Serial.println("Playing alarm ");
    //Serial.println(Ans);
    playAlarm();
  }  
}
void playAlarm(){
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(tonePin, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(tonePin);
  }
}
