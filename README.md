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
3. Install the [Arduino IDE](https://www.arduino.cc/en/software) and upload the code I provided in this repo
4. If the LCD screen doesn't display any text, adjust the potentiometer as shown [in this video](https://www.youtube.com/watch?v=hsJOVG_5pMI) (use a screwdriver and turn the potentiometer screw about 10 times clockwise)
