Welcome to the Team Wiper's Design Page!
# Automated Windshield Wiper Lift
Built by:
* #### Scrum master: Lucy Niemeyer
* #### Product Owner: Erica Kevnick
* Rebecca Buchanan 
* Nick Armendarez
* Joel Martin
* Jameson Hunter
# Summary
The goal of our design was to create a product that would automatically lift windshield wiper blades up and off the windshield when outside temperatures went below freezing. The purpose was to prevent the windshield wiper blades from getting frozen and stuck to one’s windshield in the event that the owner forgot, was too lazy, or was unaware of inclement weather to lift their blades preemptively. With the Automated Windshield Wiper Lift, a microcontroller senses when the car battery is off and the temperature is below freezing to then activate a mounted motor. The motor along with a gearbox should lift the wiper blades off the windshields and holds them in the up position until the car is turned on. Our project resulted in a device which is not powerful enough to lift a blade. While the mechanics were lacking, the code and circuit programming works to power the motor when the specifications are met and lower the blade when the car is turned on. With more funds and time we could have purchased a higher torque motor and got rid of the need for a gearbox but for our purposes this product demonstrates the design criteria but does not actually lift the wiper blade.
# Video
# Materials
## Materials
* Electrifly GD-600 Electric Flight Gear Drive 
* Arduino Uno microcontroller
* RC4WD 80t motor
* Sparkfun Motor Driver Dual TB
* L7805 voltage regulator
* 2 1KOhm resistor
* Semitec 103AT-11 thermistor
* 2 ATM fuse taps
## Tools and Supplies
* solder
* soldering iron 
* 3D printer 
* laser cutter
* wire cutters
* wire
* breadboard 
* wire strippers
* electrical tape
# Assembly Procedures
Our assembly involved coding each component to communicate with the microcontroller individually before setting it up to work all together.

First, we set up our temperature sensors using a temporary breadboard with the sensors connected to A0. The temperature sensor acts as a thermistor which increases resistance as the temperature decreases. To measure what the temperature was we created a voltage divider using a 10kOhm resistor. Once we have it as a resistance we use the values given by the manufacturer to create an equation which converts the resistance into temperature in Celsius. 

![tempresisstance](https://user-images.githubusercontent.com/35348092/39151307-d622e204-4712-11e8-8dcc-31338e3fa0b0.jpg)

The car has two types of fuses. The ignition fuses only have a voltage output when the car is on. Permanent fuses always have a voltage output. For our project we are going to use an ignition fuse to signal when the car is on and a permanent fuse to power the Arduino. However, the voltage output of the car ranges from 10-14V and the Arduino can only handle voltage inputs of up to 5V, so we used voltage regulators to maintain a steady output of 5V. 

![fuses](https://user-images.githubusercontent.com/35348092/39213435-8c42e7a6-47df-11e8-9007-9be438cdfd7f.jpg)

Next, we set up the motor. We are controlling the motor using an H-bridge. The inputs on the H-bridge, AIN1 and AIN2, are going into pins 7 and 4, respectively. The PWMA pin is attached to pin 3 and the standby is on pin 8. The motors are connected to the two output pins. Using the regulated permanent voltage, we powered the logic for the H-bridge (pin Vcc). On pin Vm, which powers the motor, we are using a 9V battery. The 5V from the permanent will go to the Vin for powering the Arduino and the ground for the Arduino and the voltage regulator was created by attaching a wire to metal inside the car.

![inkedmicrocontroller_li](https://user-images.githubusercontent.com/35348092/39213188-e020cb96-47de-11e8-83c7-63a4c9eb21c4.jpg)

Magenta = senses if the car is on, lime = temperature sensor, blue = power supply for arduino and motor 


![h bridge](https://user-images.githubusercontent.com/35348092/39212541-0532d7e6-47dd-11e8-9669-3c7737306411.jpg)

More specifically, for our H-bridge:
* Vm was connected to the positive terminal of our 9V battery
* Vcc was wired to our breadboard and powered from the car
* GND was ground from car, on breadboard
* A01 is the red wire of the motor
* A02 is the black wire of the motor
* PWMA is Pin 3
* AIN2 is Pin 4
* AIN1 is Pin 7
* STBY is Pin 8
* GND (right side) is negative terminal of the 9V battery

The arm and locking mechanism for lifting the wiper blade and holding it in place until the car is turned on was designed with the motor only running in one direction. The design consisted of a two-prong lever which lifted the blade and a catch system which would roll over itself to catch the blade in the up position and also release it when the motor was turned on. These pieces were 3D printed in poor quality and required some filing to get the pieces to fit together. But with a better 3D printer these design files made in Inventor should work properly when attached to the motor.
(The engineering drawings are provided below.)

## Schematics
![screenshot 60](https://user-images.githubusercontent.com/35348092/39266163-349477c8-4897-11e8-83d1-9faeca16b425.png)

## Engineering Drawings

Arm
![arm](https://user-images.githubusercontent.com/35348092/39279182-7bba5a9a-48c5-11e8-911e-34165f1874a2.PNG)

Lock
![lock](https://user-images.githubusercontent.com/35348092/39279224-ac474c5e-48c5-11e8-81db-f62cf0ff936b.PNG)

House
![house](https://user-images.githubusercontent.com/35348092/39279280-091065ce-48c6-11e8-89fc-ee1f25860dfd.PNG)

Assembly
![assembly](https://user-images.githubusercontent.com/35348092/39279296-247802cc-48c6-11e8-95db-eb4d28a6cf69.PNG)

Freebody
![freebody](https://user-images.githubusercontent.com/35348092/39279330-5296c378-48c6-11e8-92d4-fa5f5d7b679a.PNG)
## Programming Code
See this repository for the Arduino Code. It is labeled "Lift Code" in the code folder.


This code converts the resistance given by the thermistor into a value in degrees Fahrenheit and prints the values.
```C
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
```
# Test Equipment
* temperature sensor 
* Arduino uno
* wire
* 2 1KOhm resistors 
* Excel
* TinkCAD
# Test Procedures
We tested the accuracy of our temperature sensor to ensure that it would be able to sense freezing outdoor temperatures within a reasonable time frame. We used our setup for the thermistor as descirbed previously with the other components (the power supply and voltage sensor) removed. This was done by taking our thermistor from an indoor temperature of 70°F into a walk-in freezer at a known temperature of 36°F. 

![temperature serial](https://user-images.githubusercontent.com/35348092/39217593-bd6a3d8e-47ee-11e8-95d8-8c4493cdd78c.PNG)
<img width="399" alt="temperature and resistance test" src="https://user-images.githubusercontent.com/35348092/39217548-8991a2b8-47ee-11e8-8e69-671b5731767f.png">
<img width="398" alt="timevtemp" src="https://user-images.githubusercontent.com/35348092/39265649-d0ae5748-4895-11e8-907c-88ba4fd0c241.png">


For another test we simulated our code in TinkerCad. We put our completed code into the program to test if the motor turned on when the temperature sensor sensed temperatures below freezing and the car was off. To do this we had to input made up temperatures and make up the input voltages from the car. This procedure just tested for the code involving starting and stopping the motor when the car battery was on (in theory) and the temperature was freezing (in theory). 
# Test Results
We used Arduino to print the temperature values every second and then created an Excel graph to display the temperature against the time. This shows that the temperature sensor started at 70°F and ended at 36.87°F. 

The simulation showed that our code was correct and working before we hooked it up to the car.

# Discussion
## Design Decisions
In our design we discovered too late that we did not have the mechanics properly calculated so that our motor actually lifted the blade. Part of our misstep was due to misinformation when buying the motor. We were under the impression that it could operate at a higher torque with 9V. If we were to go back to the production stage we would redesign to use a stepper motor or pulley locking mechanism to achieve the force needed to lift the blade. This was problem that could have been mitigated with better time management and more funds. Originally, we planned to use the ESP32 from Sparkfun but later switched to the Arduino Uno. This is why we got the voltage to under 3.3V for signaling when the car is on. With the Uno we could’ve regulated it to 5V but we decided not to change it. We also decided to wire out the car window as we were using a fellow classmate’s car and were unsure of how to get through the car to under the hood. We didn’t want to risk any harm being done to his car. In production this could more confidently be fixed with more time to wire the fuses to the motor internally. 
## Test Results Discussion
Since we were comparing it to known temperatures, this test proved the accuracy of our sensor and code. Therefore, we felt comfortable using it for our project.
The simulation provided a safe way to test the code without risk of frying any of the circuit components or doing damage to fuses in the car.
# References
We used the Sparkfun library to get our motor running.
https://learn.sparkfun.com/tutorials/tb6612fng-hookup-guide

We used the gear box manual for calculations when creating the motor arm and power needed
https://www.greatplanes.com/motors/gearboxes.php

