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
The goal of our design was to create a product that would automatically lift windshield wiper blades up and off the windshield when outside temperatures went below freezing. The purpose was to prevent the windshield wiper blades from getting frozen and stuck to one’s windshield in the event that the owner forgot, was too lazy, or was unaware of inclement weather to lift their blades preemptively. With the Automated Windshield Wiper Lift, a microcontroller senses when the car battery is off and the temperature is below freezing to then activate a mounted motor. The motor along with a gearbox lifts the wiper blades off the windshields and holds them in the up position until the car is turned on. Then it is lowered. Our project resulted in a device that works to lift one wiper blade for proof of principle. With more funds and time we could have purchased a higher torque motor and got rid of the need for a gearbox but for our purposes this product accomplishes its design criteria in that it automatically lifts the blade. 
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

## Schematics
Red wire= positive, Green wire= negative, Blue wire= analog/digital outputs

![](https://github.com/joedvorak/BAE305Example/blob/master/Design%20File%20Images/Tundra%203000_schem.gif)

## Engineering Drawings
Not Provided.
## Programming Code
See this repository for the Arduino Code.
This code reads the temperature sensor on the OneWire interface and converts it to Fahrenheit and Celsius
```C
for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
    Serial.print(" ");
  }
  Serial.println();
  // Convert the data to actual temperature

  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;
  fahrenheit = celsius * 1.8 + 32.0;
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
<img width="399" alt="temperature and resistance test" src="https://user-images.githubusercontent.com/35348092/39217730-4a182f16-47ef-11e8-8734-c1ac164545b8.png">

For another test we simulated our code in TinkerCad. We put our completed code into the program to test if the motor turned on when the temperature sensor sensed temperatures below freezing and the car was off. To do this we had to input made up temperatures and make up the input voltages from the car. This procedure just tested for the code involving starting and stopping the motor when the car battery was on (in theory) and the temperature was freezing (in theory). 
# Test Results
We used Arduino to print the temperature values every second and then created an Excel graph to display the temperature against the time. This shows that the temperature sensor started at 70°F and ended at 36.87°F. 

The simulation showed that our code was correct and working before we hooked it up to the car.

# Discussion
## Design Decisions
Not Provided
## Test Results Discussion
Since we were comparing it to known temperatures, this test proved the accuracy of our sensor and code. Therefore, we felt comfortable using it for our project.
The simulation provided a safe way to test the code without risk of frying any of the circuit components or doing damage to fuses in the car.
# References
We used the Sparkfun library to get our motor running.
https://learn.sparkfun.com/tutorials/tb6612fng-hookup-guide

We used the gear box manual for calculations when creating the motor arm and power needed
https://www.greatplanes.com/motors/gearboxes.php

