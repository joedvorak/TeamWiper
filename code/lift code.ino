
#include <SparkFun_TB6612.h>   //Using the library for the Sparkfun H-Bridge to run the motor

#define POWDET 13   //Pin that will detect if the car is on
#define PWMA 3      //PWM of motor
#define AIN1 7      //Motor Input 1
#define AIN2 4      //Motor Input 2
#define STBY 8      //Standby

const int offsetA = 1;

Motor motor = Motor(AIN1, AIN2, PWMA, offsetA, STBY);

void setup() {
  Serial.begin(9600);       //Begins Serial Output
  pinMode(A0, INPUT);       //Sets pin A0 input to read the temperature
  pinMode(POWDET, INPUT);   //Sets the power detection pin as an input

}

void loop() {
  float reading;   //defines a float variable we will use for the readings from the thermistor
  float tempC;     //A variable to hold the converted resistance in Celcius
  float tempF;     //Variable that will hold the converted Celcius temperature in Fahrenheit
  int PowerIn = digitalRead(POWDET);  //Variable to hold the value for whether the car is on or not

  reading = analogRead(A0);   //Gives a reading based on voltage between 0-1023

  Serial.print("Analog Reading: "); Serial.println(reading);

  reading = (1023 / reading) - 1;   //Converts the reading into a resistance
  reading = 10000 / reading;        //using a voltage divider
  Serial.print("Thermistor Resistance: "); Serial.println(reading);

  tempC = -25.91 * log(reading) + 264;
  Serial.print("Temperature in Celcius: "); Serial.println(tempC);

  tempF = tempC * 1.8 + 32;
  Serial.print("Temperature in Fahrenheit: "); Serial.println(tempF);
  Serial.println(" ");
  delay(1000);

  if (PowerIn == LOW && tempF < 40)   //Checks if the car is off and the temperature is below a certain value
  {
    motor.drive(150, 1000);   //Runs the motor to lift the windshield
    motor.brake();            //Brakes the motor
    delay(2500);
    int x = 0;   //Defines a variable we will use to escape the loop coming up

    while (x == 0)
    {
      int PowerOn = digitalRead(POWDET);   
      if (PowerOn == HIGH)   //Checks to see if the car is turned on
      {
        x = 1;   //Escapes the loop if the car is on
      }
      delay(100);
    }
    
    motor.drive(150, 1500);   //Lowers the windshield wiper by running it forward again
    motor.brake();            //and escaping the physical lock on the windshield
    delay(1000);
  }



}
