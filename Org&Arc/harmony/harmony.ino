#include "pitches.h";
               //    1         2       3       4         5       6       7         8       9
int notes[] = {NOTE_CS4,NOTE_AS4,NOTE_G4,NOTE_AS4,NOTE_CS4,NOTE_AS4,NOTE_G4,NOTE_AS4,
                NOTE_C4,NOTE_GS4,NOTE_F4,NOTE_GS4,NOTE_C4,NOTE_GS4,NOTE_F4,NOTE_GS4,NOTE_C4,
                NOTE_GS4,NOTE_F4,NOTE_GS4,NOTE_C4,NOTE_GS4,NOTE_DS4,NOTE_GS4,NOTE_D4,NOTE_GS4,NOTE_F4
                  };

int chorus[] = {NOTE_D5,NOTE_DS5,NOTE_F5,NOTE_G5,NOTE_DS5,NOTE_C5,NOTE_C5,NOTE_D5,};

void setup() {
  // iterate over the notes of the melody:
   
   for (int i =7; i>3;i--){
    pinMode(i,OUTPUT);
  }
    for(int i=0;i<27;i++){
      tone(8,notes[i],400);
      delay(400);
    }
    tone(8,NOTE_DS4,2000);
    delay(2000);
     for(int i=0;i<8;i++){
      tone(8,chorus[i],400);
      delay(400);
    }

    noTone(8);
 }


void loop() {
  
 
}
