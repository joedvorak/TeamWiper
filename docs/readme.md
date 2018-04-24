Welcome to the Team Wiper's Design Page!
# Automated Windshield Wiper Lift
Built by:
* #### Scrum master: Lucy Nieymeyer
* #### Product Owner: Erica Kevnick
* Rebecca Buchanan 
* Nick Armendarez
* Joel Martin
* Jameson Hunter
# Summary
The goal of our design was to create a product that would automatically lift windshield wiper blades up and off the windshield when outside temperatures went below freezing. The purpose was to prevent the windshield wiper blades from getting frozen and stuck to one’s windshield in the event that the owner forgot, was too lazy, or was unaware of inclement weather to lift their blades preemptively. With the Automated Windshield Wiper Lift, a microcontroller senses when the car battery is off and the temperature is below freezing to then activate a mounted motor. The motor along with a gearbox lifts the wiper blades off the windshields and holds them in the up position until manually lowered. Our project resulted in a device that works to lift one wiper blade for proof of principle. With more funds and time we could have purchased a higher torque motor and got rid of the need for a gearbox but for our purposes this product accomplishes its design criteria in that it automatically lifts the blade. 
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



Next, we set up the motor. We are controlling the motor using an H-bridge. The inputs on the H-bridge, AIN1 and AIN2, are going into pins 7 and 4, respectively. The PWMA pin is attached to pin 3 and the standby is on pin 8. The motors are connected to the two output pins. Using the regulated permanent voltage, we powered the logic for the H-bridge (pin Vcc). On pin Vm, which powers the motor, we are using a 9V battery. The 5V from the permanent will go to the Vin for powering the Arduino and the ground for the Arduino and the voltage regulator was created by attaching a wire to metal inside the car.

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
Not Provided.
# Test Procedures
Not Provided.
# Test Results
No text provided

![](https://github.com/joedvorak/BAE305Example/blob/master/Design%20File%20Images/Graph.png)

# Discussion
## Design Decisions
Not Provided
## Test Results Discussion
The Peltier Live Well Cooler allows the user to select the desired maintenance temperature of the water in the live well using 2 pushbuttons and will then automatically cycle the system on and off while giving the user a real time readout of the current live well water temperature
# References
The OLED was connected with help from this instructable: http://www.instructables.com/id/Monochrome-096-i2c-OLED-display-with-arduino-SSD13/
After finding the correct i2c address for the display using the i2c scanner, an example sketch from the Adafruit SSD1306 library was uploaded to the Arduino. After verification that the OLED was working, code from the example sketch was reworked into the code needed to display our data.
Similarly, code to run the temperature probe was borrowed from the OneWire library example sketch and modified to meet the needs of the project.
