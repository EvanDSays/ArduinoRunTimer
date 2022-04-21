# ArduinoRunTimer
Use an Arduino Uno and LED shield to track run counts and times

![ArduinoRunTimer](https://user-images.githubusercontent.com/2483481/164128789-5f9cea70-ba18-41d5-93e3-46811c47ee9f.jpg)

## What it displays
The LCD displays 4 numbers:
1. Number of runs completed (top left)
2. Current run time (top right)
3. Average run time (bottom left)
4. Total time of all runs (bottom right)

## Parts needed
You need 3 parts (~$30 USD):
1. An Arduino Uno Rev3 ([example on Amazon](https://www.amazon.com/dp/B008GRTSV6))
2. A 1602 LCD Keypad Shield ([example on Amazon](https://www.amazon.com/dp/B00OGYXN8C))
3. A cord to power the arduino (a [USB 2.0 printer cord](https://www.amazon.com/AmazonBasics-USB-2-0-Cable-Male/dp/B00NH11KIK) works fine)

## Assembly
Here are the steps to get it working:
1. Place the shield on top of the Arduino Uno and push the pins in place
2. Plug the Arduino into your computer using the USB 2.0 cable
3. Install the [Arduino IDE](https://www.arduino.cc/en/software)
4. Add the [LiquidCrystal library](https://www.arduino.cc/reference/en/libraries/liquidcrystal/) via the IDE (Sketch -> Include LIbrary -> Manage Libaries)
5. Grab the [code I provided in this repo](https://github.com/EvanDSays/ArduinoRunTimer/blob/main/ArduinoRunTimer.ino) and edit the line shown below to match your LED pin-outs for your board ([more info here](https://www.arduino.cc/reference/en/libraries/liquidcrystal/liquidcrystal/))
  ```cpp
  LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  
  ```
6. If the LCD screen doesn't display any text, adjust the potentiometer as shown [in this video](https://www.youtube.com/watch?v=hsJOVG_5pMI) (use a screwdriver and turn the potentiometer screw about 10 times clockwise)

## How it works
- Press `RST` when you start your first run (it should display Run#1 and both Current and Total clocks will start counting up)
- Press `SELECT` or `LEFT` when you complete each run
- Press `DOWN` or `UP` to pause or unpause the device
