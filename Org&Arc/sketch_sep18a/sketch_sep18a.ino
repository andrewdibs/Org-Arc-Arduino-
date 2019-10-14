  //Variables
const int sensorPin = A0;
const float baseTemp = 20.0;
 
const int redPin = 10;
const int bluePin = 11; 

int redValue = 0;
int blueValue = 0;

int values[10];      
int valueIndex = 0;              
int total = 0;                  
int average = 0;                

int minValue = 50.78;
int maxValue = 70.66;
int threshold = 0;
void setup() {
  Serial.begin(9600);

  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  for (int pinNum = 2;pinNum<5;pinNum++){
    pinMode(pinNum, OUTPUT);
    digitalWrite(pinNum, LOW);
  }
  for (int thisValue = 0; thisValue < 10; thisValue++) {
    values[thisValue] = 0;
  }
}

void loop() {
  //smoothing: takes the last 10 values and outputs average
  total = total - values[valueIndex];
  values[valueIndex] = analogRead(sensorPin);
  
  total = total + values[valueIndex];
  valueIndex = valueIndex + 1;

  if (valueIndex >= 10) {
    valueIndex = 0;
  }

  average = total / 10;
  
  Serial.print(" Sensor Value: ");
  Serial.println(average);

  
  
  //calculates voltage
  float voltage = (average/1024.0)*5;
  Serial.print(", Volts: ");
  Serial.print(voltage);
  //converts to C
  Serial.print(", Degrees C: ");
  float temp = (voltage - .5)*100;
  Serial.print(temp);

  
  threshold = (temp - minValue)/(maxValue-minValue)*(510)-255;
  Serial.print(" Threshold: ");
  Serial.print(threshold);


  if(threshold>255){
    digitalWrite(redPin,HIGH);
    digitalWrite(bluePin,LOW);
  }
  else if(threshold<-255){
    digitalWrite(bluePin,HIGH);
    digitalWrite(redPin,LOW);
  }
  else if(threshold == 0){
    digitalWrite(bluePin,127.5);
    digitalWrite(redPin,127.5);
  }
  else if (threshold<0){
    blueValue = threshold*-1.5;
    redValue = threshold/-1.5;
    digitalWrite(bluePin,blueValue);
   digitalWrite(redPin,redValue);
 }
    else if(threshold>0){
    blueValue = threshold/1.5;
    redValue = threshold*1.5;
    digitalWrite(bluePin,blueValue);
    digitalWrite(redPin,redValue);
 }

  
  delay(1);
}
