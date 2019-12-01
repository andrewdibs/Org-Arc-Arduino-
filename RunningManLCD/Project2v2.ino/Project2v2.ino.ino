#include <LiquidCrystal.h>;
#include <math.h>;
LiquidCrystal lcd(5,6,8,9,10,11);

const byte interruptPin = 2;                    

int joyPin1 = 0;                 // slider variable connecetd to analog pin 0
int joyPin2 = 1;                 // slider variable connecetd to analog pin 1
int joyValue= 0;
int score = 0;
boolean isJumping = false;
boolean isDucking = false;
boolean isRunning = true;
boolean isDead = false;
int delayTime= 300;
int sw = 1;
boolean upperTerrain[16] = {false,false,false,false,false,false,false,false,false,false,
                            false,false,false,true,false,false};
boolean lowerTerrain[16] = {false,false,false,false,false,false,false,false,false,false,
                            false,false,false,false,false,true};
static byte highSpike[8] = {    
    B11111,
    B11111,
    B11111,
    B01110,
    B01110,
    B00100,
    B00100,
    B00000,
};
static byte jumping[8] = {   
    B01100,
    B01100,
    B00000,
    B01110,
    B11100,
    B01100,
    B11010,
    B10011,
};
static byte alternateJump[8] = {    
    B01100,
    B01100,
    B00000,
    B01100,
    B01100,
    B01100,
    B01100,
    B01110,
};

static byte lowSpike[8] = {    
    B00000,
    B00100,
    B00100,
    B01110,
    B01110,
    B11111,
    B11111,
    B11111,
};
static byte upperHalf[8] = {    
    B00000,
    B01100,
    B01100,
    B00000,
    B01100,
    B01101,
    B01111,
    B11100,
};
static byte lowerHalf[8] = {   
    B11100,
    B11100,
    B01100,
    B01100,
    B01010,
    B11010,
    B10011,
    B00000,
};
static byte alternateLower[8] = {   
    B01100,
    B01100,
    B01100,
    B01100,
    B01100,
    B01100,
    B01110,
    B00000,
};
static byte alternateUpper[8] = {    
    B00000,
    B01100,
    B01100,
    B00000,
    B01100,
    B01100,
    B01100,
    B01100,
};

//SETUP
void setup() {
  analogWrite(4,20);
  lcd.begin(16,2);
  lcd.createChar(0,jumping);
  lcd.createChar(1,alternateLower);
  lcd.createChar(2,upperHalf);
  lcd.createChar(3,lowerHalf);
  lcd.createChar(4,highSpike);
  lcd.createChar(5,lowSpike);
  lcd.createChar(6,alternateUpper);
  lcd.createChar(7,alternateJump);
  pinMode(interruptPin, INPUT);
  attachInterrupt(0, resetGame, RISING);

  Serial.begin(9600);
}
//LOOP
void loop() {            
  // reads the value of the variable resistor and outputs readable value 
  joyValue = getJoyValue(analogRead(joyPin2));

  //sets runners current state
  if (joyValue> 53){
    isJumping = true;
    isDucking = false;
    isRunning = false;
  }
  if(joyValue<51){
    isJumping = false;
    isDucking = true;
    isRunning = false;
  }
  if(joyValue> 50 && joyValue<54){
    isJumping = false;
    isDucking = false;
    isRunning = true;
  }
  //if still alive continue game
  if(!isDead){
    shiftArrays();
    printScreen();

    //increment score counter every loop and display
    score++;
    lcd.setCursor(14,0);
    lcd.print(int(score/2));
  }
  else{//if death then print menu with last score
    lcd.setCursor(0,0);
    lcd.print("Press Button!");
    lcd.setCursor(0,1);
    lcd.print("Last Run:");
    lcd.setCursor(10,1);
    lcd.print(int(score/2));
  }
   //checks death 
  if((upperTerrain[0]&& (isRunning||isJumping))||(lowerTerrain[0]&&(isRunning||isDucking))){
    isDead= true;
  }
  //delay needed for loops to run slow enough
  delay(delayTime);
  if (delayTime>100)delayTime--;
  lcd.clear();
}//end loop

void printScreen(){

  //print character with running motion
  if(isJumping){
    if(sw== 1){
      lcd.setCursor(0,0);
      lcd.write(byte(0));
      sw=0;
    }else{
      lcd.setCursor(0,0);
      lcd.write(byte(7));
      sw=1;
    }
  }
  else if(isDucking){
    if(sw== 1){
      lcd.setCursor(0,1);
      lcd.write(byte(0));
      sw=0;
    }else{
      lcd.setCursor(0,1);
      lcd.write(byte(7));
      sw=1;
    }   
  }
  else{
    if(sw==1){
      lcd.setCursor(0,0);
      lcd.write(byte(2));
      lcd.setCursor(0,1);
      lcd.write(byte(3));
      sw = 0;
    }else{
      lcd.setCursor(0,0);
      lcd.write(byte(6));
      lcd.setCursor(0,1);
      lcd.write(byte(1));
      sw = 1;
    }
    
  }
  //print terrain
  for (int c = 0; c<15;c++){
    if (upperTerrain[c]){
      lcd.setCursor(c,0);
      lcd.write(byte(4));
    }
    if(lowerTerrain[c]){
      lcd.setCursor(c,1);
      lcd.write(byte(5));
    }
  }
}

//function gets readable joystick value
int getJoyValue(int data) {
  return (data * 9 / 1024) + 48;
 }

void shiftArrays(){
  
  for (int i=0;i<16;i++){
    upperTerrain[i] = upperTerrain[i+1];
    lowerTerrain[i] = lowerTerrain[i+1];
  }
  //Create random terrain
  if (upperTerrain[14]||upperTerrain[15]){
     lowerTerrain[14] = false;
     lowerTerrain[15] = false;
     int x = int(rand()%10);
     if (x>4){
      upperTerrain[15] = true;
     }
     else {
      upperTerrain[15] = false;
      lowerTerrain[15]=true;
     }
  }
  if (lowerTerrain[14]|| lowerTerrain[15]){
     upperTerrain[14] = false;
     upperTerrain[15] = false;
     int y = int(rand()%10);
     if (y>4){
      lowerTerrain[15] = true;
     }
     else {
      lowerTerrain[15] = false;
     }
  }
}
void resetGame(){
  isJumping = false;
  isDucking = false;
  isRunning = true;
  isDead = false;
  delayTime = 400;
  for (int i =0;i<16;i++){
    upperTerrain[i] = false;
    lowerTerrain[i]=false;
  }
  score = 0;
}
