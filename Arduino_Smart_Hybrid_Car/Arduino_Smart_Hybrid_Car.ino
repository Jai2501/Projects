// Ultrasonic Sensor
#define trigPin 12
#define echoPin 13
long duration ;
int distance ;

// Colour Sensor
/*#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6
int Red = 0 ;
int Green = 0 ;
int Blue = 0 ;
*/

//Infrared Sensor
#define Right_Infrared_Sensor A4 // Right Infrared Sensor
#define Left_Infrared_Sensor A5 // Left Infrared Sensor
int Right_Infrared_Sensor_Value ; //To Hold The Value of Right IR Sensor
int Left_Infrared_Sensor_Value ; //To Hold The Value of Left IR Sensor

//L293 Connection   
#define motorA A0  // Pin A0 of Arduino (PWM of MotorA)
#define motorA1 8  // Pin 2 RIGHT MOTOR
#define motorA2 9  // Pin 7 RIGHT MOTOR
#define motorB A1  // Pin A1 of Arduino (PWM of MotorB)
#define motorB1 10  // Pin 10 LEFT MOTOR
#define motorB2 11  // Pin 14 LEFT MOTOR
  
//Leds connected to Arduino UNO Pin 12
#define lights A3
  
//Buzzer/Speaker to Arduino UNO Pin 3
#define buzzer 7   
  
//Bluetooth (HC-06 JY-MCU) State pin on pin 2 of Arduino
//#define BTState = 11 ;

//Calculate Battery Level
/*
const float maxBattery = 8.0 ;// Change value to your max battery voltage level! 
int perVolt ;                 // Percentage variable 
float voltage = 0.0 ;         // Read battery voltage
int level ;
//Use it to make a delay... without delay() function!
long previousMillis = -1000*10 ;// -1000*10=-10sec. to read the first value. If you use 0 then you will take the first value after 10sec.  
long interval = 1000*10 ;       // interval at which to read battery voltage, change it if you want! (10*1000=10sec)//  
unsigned long currentMillis ;   
//Useful Variables
int i=0 ;
int j=0 ;
int state ; 
*/
// Photo-Resistor
#define Photo_Resistor A2
int Photo_Cell_Input = 0 ;

void setup() 
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(lights, OUTPUT); // Sets the Lights as an Output

// Set pins as Outputs:
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);  
  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);
//  pinMode(S0, OUTPUT);
//  pinMode(S1, OUTPUT);
//  pinMode(S2, OUTPUT);
//  pinMode(S3, OUTPUT);
  
// Set Pins as Inputs
//  pinMode(sensorOut, INPUT);
  pinMode(Right_Infrared_Sensor,INPUT) ;
  pinMode(Left_Infrared_Sensor,INPUT) ;
//  pinMode(BTState, INPUT);  
  
// Setting Red-scaling to 20%
//  digitalWrite(S0,HIGH);
//  digitalWrite(S1,LOW);

  SET() ; // To Know That Car has Initialed all Variables and is Set-Up
  
  Serial.begin(9600);
}

void loop() 
{
// Interpreting Data for Vehicle Movement
VEHICLE_CONTROL();

// To Display Values
DISP();
}

void SET() // Car is Set-Up
{
  tone(buzzer, 2000);
  digitalWrite(lights, HIGH); 
  delay(100);
  digitalWrite(lights, LOW);
  noTone(buzzer) ;
  delay(100);
  tone(buzzer, 2000) ;
  digitalWrite(lights, HIGH); 
  delay(100);
  digitalWrite(lights, LOW); 
  noTone(buzzer);
}

void VEHICLE_CONTROL()  // Moving Vehicle W.R.T Distance and Colour
{
  // Calling Ultrasonic Sensor to Calculate Distance (in CM)
  ULTRA_SONIC_SENSOR();  

  // Colour Sensor Detecting The Colours for Traffic Light Purpose
  //COLORSENSOR();

  //LIGHTS
  LIGHTS();

  // To Detect any Obstacle according to Distance
  OBSTACLE_DETECTION();
}

void ULTRA_SONIC_SENSOR()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance (for ultrasonc sensor)
  distance = duration*0.034472/2;
}
/*
void COLORSENSOR()
{
  // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output Red
  Red = pulseIn(sensorOut, LOW);
  Red = map(Red, 25,72,255,0);
  // Printing the value on the serial monitor
  Serial.print("\nR= ");//printing name
  Serial.print(Red);//printing frequency of red
  Serial.print("  ");
  delay(100);

// Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output Red
  Green = pulseIn(sensorOut, LOW);
  Green = map(Green, 30,90,255,0);
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(Green);//printing frequency of green
  Serial.print("  ");
  delay(100);

// Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output Red
  Blue = pulseIn(sensorOut, LOW);
  Blue = map(Blue, 25,70,255,0);
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(Blue);//printing frequency of blue
  Serial.println("  ");
  delay(100);
}
*/
void LIGHTS()
{
  Photo_Cell_Input = (analogRead(Photo_Resistor)/4); // Divides input 0-1023 to resemble to 0-255
  if( Photo_Cell_Input >= 11)
  {
      digitalWrite(lights, HIGH);
  }
  else
  {
      digitalWrite(lights, LOW);
  }
}

void OBSTACLE_DETECTION()  // Obstacle Detecting Function
{
  if ( distance <= 20)
    {
      REV();
      delay(10);
      TURNAROUND();
      delay(80);
    }
  else
  {
    //TRAFFIC_LIGHT();
    IR();
  }
}
/*
void TRAFFIC_LIGHT()
{
  if( Red >= 220 && Green <= 180 && Blue <= 170) // Checking The RGB Values For Understanding Red/Green Light
  {
    Serial.print("\nDetected Red Light: Stopping.");
    analogWrite(motorA, 0);
    digitalWrite(motorA1, LOW);      digitalWrite(motorA2, LOW);
    analogWrite(motorB, 0);
    digitalWrite(motorB1, LOW);      digitalWrite(motorB2, LOW); 
    STOP();
  }
  else
  {
   // Calling IR Sensor for Values
   if( Green <= 255 && Green >= 230 && Red <= 10 && Blue <= 10)
   {
     Serial.print("\nDetected Green Light: Moving Forward.");
   }
   else
   {
     Serial.print("\nDetected Light Not Red/Green: Moving Forward.");
   }
   IR();
  } 
}
*/

void IR()
{
  Right_Infrared_Sensor_Value=analogRead(Right_Infrared_Sensor);
  Left_Infrared_Sensor_Value=analogRead(Left_Infrared_Sensor);
  if( Right_Infrared_Sensor_Value < 500 && Left_Infrared_Sensor_Value < 500)
  {
    FORW();
  }
  if( Right_Infrared_Sensor_Value < 500 && Left_Infrared_Sensor_Value > 500)
  {
    RIG();
  }
  if( Right_Infrared_Sensor_Value > 500 && Left_Infrared_Sensor_Value < 500)
  {
    LEF();
  }
  if( Right_Infrared_Sensor_Value > 500 && Left_Infrared_Sensor_Value > 500)
  {
    ST();
  }
}

void FORW()
{
    Serial.print("\nMoving Forward.");
    analogWrite(motorA, 160);
    digitalWrite(motorA1, HIGH);     digitalWrite(motorA2, LOW); 
    analogWrite(motorB, 160); 
    digitalWrite(motorB1, HIGH);     digitalWrite(motorB2, LOW);
}

void LEF()
{
    Serial.print("\nTurning Left.");
    analogWrite(motorA, 200);
    digitalWrite(motorA1, HIGH);       digitalWrite(motorA2, LOW);
    analogWrite(motorB, 0);
    digitalWrite(motorB1, LOW);        digitalWrite(motorB2, LOW);  
}

void RIG()
{
    Serial.println("\nTurning Right");
    analogWrite(motorA, 0);
    digitalWrite(motorA1, LOW);      digitalWrite(motorA2, LOW);
    analogWrite(motorB, 200);
    digitalWrite(motorB1, HIGH);     digitalWrite(motorB2, LOW); 
}

void ST()
{
    analogWrite(motorA, 0);
    Serial.print("\nStopping.");
    digitalWrite(motorA1, LOW);      digitalWrite(motorA2, LOW);
    analogWrite(motorB, 0);
    digitalWrite(motorB1, LOW);      digitalWrite(motorB2, LOW); 
    HAULT() ;
}

void REV()
{
    Serial.print("\nMoving Backward.");
    analogWrite(motorA, 200);
    digitalWrite(motorA1, LOW);     digitalWrite(motorA2, HIGH); 
    analogWrite(motorB, 200); 
    digitalWrite(motorB1, LOW);     digitalWrite(motorB2, HIGH);
    STOP();
}

void TURNAROUND()
{
    Serial.print("\nTurning Around.");
    analogWrite(motorA, 225);
    digitalWrite(motorA1, LOW);      digitalWrite(motorA2, HIGH);
    analogWrite(motorB, 225);
    digitalWrite(motorB1, HIGH);     digitalWrite(motorB2, LOW); 
}


void STOP() // When Car Comes to a hault due to any object, Buzzer and all lights will flash
{
  /*Serial.print("\nSTOP Due to Object.");
  analogWrite(motorA, 0);
  digitalWrite(motorA1, LOW);      digitalWrite(motorA2, LOW);
  analogWrite(motorB, 0);
  digitalWrite(motorB1, LOW);      digitalWrite(motorB2, LOW); 
  */
  tone(buzzer, 2000);//Speaker on
  digitalWrite(lights, HIGH);
  delay(200);
  digitalWrite(lights, LOW);
  delay(200);
  digitalWrite(lights, HIGH);
  delay(200);
  digitalWrite(lights, LOW);
  delay(200);
  digitalWrite(lights, HIGH);
  delay(200);
  digitalWrite(lights, LOW);
  noTone(buzzer);
}

void HAULT()
{
  digitalWrite(lights, HIGH);
  delay(720);
  digitalWrite(lights, LOW);
  delay(720);
  digitalWrite(lights, HIGH);
  delay(720);
  digitalWrite(lights, LOW); 
  delay(720);
  digitalWrite(lights, HIGH);
  delay(720);
  digitalWrite(lights, LOW);
}

void DISP() // To Display Values
{
    Serial.print("\n");
    Serial.print("\nDistance from Nearest Object:");
    Serial.print(distance); // to print the dsitance from the object
    Serial.print("\nPhotoResistor:");
    Serial.print(Photo_Cell_Input); // to print the value for photo resistance
    Serial.print("\nRight Infrared Sensor Value:");
    Serial.print(Right_Infrared_Sensor_Value); // to print the value for Right Infrared Sensor
    Serial.print("\nLeft Infrared Sensor Value:");
    Serial.print(Left_Infrared_Sensor_Value); // to print the value for Left Infared Sensor
    //BATTERY_LEVEL();  // To Display Battery Level
}

/*void BATTERY_LEVEL()
{
  //Read battery voltage every 10sec.
    currentMillis = millis();
    if(currentMillis - (previousMillis) > (interval)) {
       previousMillis = currentMillis; 
       //Read voltage from analog pin A0 and make calibration:
       voltage = (analogRead(A0)*5.015 / 1024.0)*11.132;
       //Calculate percentage...
       perVolt = (voltage*100)/ maxBattery;
       if      (perVolt<=75)               { level=0; }
       else if (perVolt>75 && perVolt<=80) { level=1; }    //        Battery level
       else if (perVolt>80 && perVolt<=85) { level=2; }    //Min ------------------------   Max
       else if (perVolt>85 && perVolt<=90) { level=3; }    //    | 0 | 1 | 2 | 3 | 4 | 5 | >
       else if (perVolt>90 && perVolt<=95) { level=4; }    //    ------------------------
       else if (perVolt>95)                { level=5; }   
       Serial.print("\nBattery Level : ");
       Serial.print(level);    
    }
}
*/
