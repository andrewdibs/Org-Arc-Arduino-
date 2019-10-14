  //Variables
const int sensorPin = A0;
const float baseTemp = 20.0;
 
const int redPin = 10;
const int bluePin = 11; 

int redValue = 0;
int blueValue = 0;

int values[10];      
int valueIndex = 0;              
float total = 0;                  
int average = 0;                

float minValue = 22.00;
float maxValue = 32.00;
float threshold = 0;
void setup() {
  Serial.begin(9600);

  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);


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
  Serial.print(analogRead(sensorPin));
  Serial.print(" Normalized Sensor Value: ");
  Serial.print(average);

  
  
  //calculates voltage
  float voltage = (average/1024.0)*5;
  Serial.print(" Volts: ");
  Serial.print(voltage);
  //converts to C
  Serial.print(", Degrees C: ");
  float temp = (voltage - .5)*100;
  Serial.print(temp);

  
  threshold = (temp - minValue)/(maxValue-minValue);//percent value 0.00-1.00
  Serial.print(" Threshold: ");
  Serial.print(threshold);

  redValue = threshold *255;//percent between 0 and 255
  blueValue = 255 - redValue;
  analogWrite(bluePin,blueValue);
  analogWrite(redPin,redValue);
  
  Serial.print(" Blue: ");
  Serial.print(blueValue);
  Serial.print(" Red: ");
  Serial.println(redValue);
  delay(1);
}
