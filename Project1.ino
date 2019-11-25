#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

String byte1 = "00000000";
String byte2 = "00000000";
String result ="";
int curScreen =0;
int switch1 = 0;
int switch2 =0;
int prevSwitch1 =0;
int prevSwitch2 =0;
int index = 0;
int num = 0;
int i = 0;
int contrast = 50;

void setup() {
  
  lcd.begin(16,2);
  lcd.print("    Welcome!");
  lcd.setCursor(0,1);
  lcd.print("  Binary Adder");

  //button input pins
  pinMode(9, INPUT);
  pinMode(13, INPUT);
  
  //set initial contrast
  analogWrite(6,50);
  Serial.begin(9600);
  }
       
void loop() {
  //read buttons 
  switch1 = digitalRead(9);
  switch2 = digitalRead(13);

  //Welcome Screen
  if (curScreen == 0){
    if(switch1!= prevSwitch1 && switch2!= prevSwitch2){
      if(switch1==HIGH && switch2 == HIGH){

        switch1 = 0;
        switch2=0;
        curScreen++;
        delay(1000);
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Byte 1:");
        lcd.setCursor(0,1);
        lcd.print(byte1);
      }
      prevSwitch1 = switch1;
      prevSwitch2 = switch2;
    }
    
  }//Byte 1 Screen
  if (curScreen == 1){
    
    if(switch1 != prevSwitch1){
      if (switch1 == HIGH && index <byte1.length()){
        

        if (i ==0){
          
          lcd.setCursor(0,0);
          lcd.print("Byte 1:");
          byte1.setCharAt(index, '1');
          i=1;
          Serial.print(" byte1: "+byte1);
          lcd.setCursor(0,1);
          lcd.print(byte1);
        }
        else{
          lcd.setCursor(0,0);
          lcd.print("Byte 1:");
          byte1.setCharAt(index, '0');
          i=0;
          Serial.print(" byte1: "+byte1);
          lcd.setCursor(0,1);
          lcd.print(byte1);
        }
        
      }
    }
    prevSwitch1 = switch1;
    
    if(switch2 != prevSwitch2){
      if(switch2 == HIGH && index<byte1.length()){
        index++;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Byte 1:");
        lcd.setCursor(0,1);
        lcd.print(byte1);
        i=0; 
        delay(1000);
        if(index>=byte1.length()){
          curScreen++;
        }
      }
    }
  }



  //Byte 2 screen
  if (curScreen == 2){
    
    if(switch1 != prevSwitch1){
      if (switch1 == HIGH && index <byte1.length()){
        

        if (i ==0){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Byte 2:");
          byte2.setCharAt(index, '1');
          i=1;
          Serial.print(" byte2: "+byte2);
          lcd.setCursor(0,1);
          lcd.print(byte2);
        }
        else{
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Byte 2:");
          byte2.setCharAt(index, '0');
          i=0;
          Serial.print(" byte2: "+byte2);
          lcd.setCursor(0,1);
          lcd.print(byte2);
        }
        prevSwitch1 = switch1;
        
      }
    }
    if(switch2 != prevSwitch2){
      if(switch2 == HIGH && index<byte2.length()){
        index++;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Byte 2:");
        lcd.setCursor(0,1);
        lcd.print(byte2);
        
        prevSwitch2 = switch2;
        
      //calculation
        if(index==byte2.length()){
        //add each digit of both bytes and total sum
        for (int i =0;i<byte1.length();i++){
          if (byte1.substring(i,i+1)=="1"){
            num = num +pow(2,byte1.length()-i-1);
          }
          if(byte2.substring(i,i+1)=="1"){
            num = num+pow(2,byte2.length()-i-1);
          }
        }
        //convert sum to binary 
        int binaryNum[9]; 
  
    // counter for binary array 
       int k = 0; 
       while (num > 0) { 
  
        // storing remainder in binary array 
          binaryNum[k] = num % 2; 
          num = num / 2; 
          i++; 
    } 
  
    // printing binary array in reverse order 
    for (int j = i - 1; j >= 0; j--) 
        result += "" + binaryNum[j]; 
        
          
        curScreen++;
        }
      }
    }
}
  //solution screen
  if(curScreen == 3){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Byte1 + Byte2:");
    lcd.setCursor(0,1);
    lcd.print(result);

    if(switch1!= prevSwitch1 && switch2!= prevSwitch2){
        if(switch1==HIGH && switch2 == HIGH){
          
          switch1 = 0;
          switch2=0;
          curScreen++;
          delay(1000);
        
          lcd.clear();
    
        }
        prevSwitch1 = switch1;
        prevSwitch2 = switch2;
    }
  }
  //contrast screen
  if(curScreen == 4){
    //back to start screen
    if(switch1!= prevSwitch1 && switch2!= prevSwitch2){
        if(switch1==HIGH && switch2 == HIGH){
          curScreen = 0;
          switch1 = 0;
          switch2= 0 ;
          prevSwitch1 = 0;
          prevSwitch2 = 0;
          index =0;
          i =0;
          
          lcd.clear();
          delay(1000);
        }
    }
    if(switch1 != prevSwitch1){
      if (switch1 == HIGH){
        contrast-= 10;
        prevSwitch1 = switch1;
      }
    }
    if(switch2 != prevSwitch2){
      if(switch2 == HIGH){
        contrast+= 10;
        
        prevSwitch2 = switch2;
      }
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Contrast -  +");
    lcd.setCursor(0,1);
    lcd.print(contrast);
    analogWrite(6,contrast);

    
  }

    
  
  Serial.println(" Current Screen: "+ curScreen);
  Serial.println(switch1);
  delay(1000);
}
  
  
