#include <Servo.h>
#include "pitch.h"
Servo servo;

int angle;

const int switchPin = 13;
unsigned long previousTime;

int switchState = 0;
int prevState = 0;

int led = 7;
long interval = 2000;

int notes[] = {NOTE_CS4,NOTE_AS4,NOTE_G4,NOTE_AS4,NOTE_CS4,NOTE_AS4,NOTE_G4,NOTE_AS4,
                NOTE_C4,NOTE_GS4,NOTE_F4,NOTE_GS4,NOTE_C4,NOTE_GS4,NOTE_F4,NOTE_GS4,NOTE_C4,
                NOTE_GS4,NOTE_F4,NOTE_GS4,NOTE_C4,NOTE_GS4,NOTE_DS4,NOTE_GS4,NOTE_D4,NOTE_GS4,NOTE_F4
                  };
void setup() {
  servo.attach(9);

  for (int i =7; i>3;i--){
    pinMode(i,OUTPUT);
  }
  pinMode(switchPin,INPUT);
  
  Serial.begin(9600);
}

void loop() {
  

  unsigned long currentTime = millis();

  if(currentTime- previousTime >interval){
    previousTime = currentTime;

    digitalWrite(led, HIGH);
    led--;

    if (led== 3){

    for(int i=0;i<27;i++){
      tone(8,notes[i],400);
      if (i%2==0){
        digitalWrite(4,HIGH);
        digitalWrite(5,LOW);
        digitalWrite(6,LOW);
        digitalWrite(7,HIGH);
      }
      else{
        digitalWrite(4,LOW);
        digitalWrite(5,HIGH);
        digitalWrite(6,HIGH);
        digitalWrite(7,LOW);
      }
      delay(400);
    }
    tone(8,NOTE_DS4,2000);
    delay(2000);
    
    tone(8, NOTE_AS4,1000);
    digitalWrite(4,HIGH);
    digitalWrite(5,HIGH);
    digitalWrite(6,HIGH);
    digitalWrite(7,HIGH);
    delay(1000);
    
    tone(8, NOTE_CS5,400 );
    digitalWrite(4,LOW);
    digitalWrite(5,HIGH);
    digitalWrite(6,HIGH);
    digitalWrite(7,HIGH);
    delay(400);
    
    tone(8, NOTE_C5,400 );
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,HIGH);
    digitalWrite(7,HIGH);
    delay(400);
    
    tone(8, NOTE_DS5,400);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,HIGH);
    delay(400);
    
    tone(8, NOTE_GS4,400);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
    delay(400);
    
    tone(8, NOTE_FS4,400);
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,HIGH);
    delay(400);
    
    tone(8, NOTE_F4,2000);
    digitalWrite(4,LOW);
    digitalWrite(5,HIGH);
    digitalWrite(6,HIGH);
    digitalWrite(7,LOW);
    delay(2000);



    tone(8, NOTE_AS4,1000);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
    delay(1000);
    
    tone(8, NOTE_CS5,400 );
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,HIGH);
    delay(400);
    
    tone(8, NOTE_C5,400 );
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,HIGH);
    digitalWrite(7,HIGH);
    delay(400);
    
    tone(8, NOTE_DS5,400);
    digitalWrite(4,LOW);
    digitalWrite(5,HIGH);
    digitalWrite(6,HIGH);
    digitalWrite(7,HIGH);
    delay(400);
    
    tone(8, NOTE_GS5,400);
    digitalWrite(4,HIGH);
    digitalWrite(5,HIGH);
    digitalWrite(6,HIGH);
    digitalWrite(7,HIGH);
    delay(400);
    
    tone(8, NOTE_FS5,400);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
    delay(400);
    
    tone(8, NOTE_F5,2000);
    digitalWrite(4,HIGH);
    digitalWrite(5,HIGH);
    digitalWrite(6,HIGH);
    digitalWrite(7,HIGH);
    delay(2000);

    noTone(8);
    
    servo.write(300);
    delay(1500);
    servo.write(50);
    delay(1500);
    servo.write(300);
    delay(1500);
    servo.write(50);

      
    }
  }

  switchState= digitalRead(switchPin);

  if (switchState!= prevState){
    for (int x = 2;x<8;x++){
      digitalWrite(x,LOW);
    }
    led = 7;
    previousTime =currentTime;
  }
  prevState = switchState;
  //0-4000 //milliseconds



  

}
