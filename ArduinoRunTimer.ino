#include <LiquidCrystal.h>

// Select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);            

int runCounter = 0; //Keeps track of the total number of runs
bool paused = false; //Holds the state of device (paused or unpaused)
int adc_key_in  = 0; //Holds button value from sensor
long runStartTime = 0; //Keeps track of when each run starts
long pauseStartTime = 0; //Keeps track of when the device is paused
long pauseMillis = 0; //The amount of milliseconds that the device has been paused

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
int read_LCD_buttons()
{
 adc_key_in = analogRead(0); //Read the value from the sensor 
 if (adc_key_in > 1000) return btnNONE; // First option for speed reasons since it will be the most likely result
 if (adc_key_in < 60)   return btnRIGHT;  
 if (adc_key_in < 200)  return btnUP; 
 if (adc_key_in < 400)  return btnDOWN; 
 if (adc_key_in < 600)  return btnLEFT; 
 if (adc_key_in < 800)  return btnSELECT;  
 return btnNONE;  // When all others fail, return this
}

//Formats milliseconds into a H:M:S string
String formatMilli(long mil){
  long s = 0; //seconds
  int m = 0;  //minutes
  int h = 0;  //hours
  
  //less than 1 minute, return 0:seconds
  if (mil < 60000){
    s = mil/1000;
    if(s>9) return (String)"0:" + s;
    else    return (String)"0:0" + s;
  }
  
  //less than 1 hour, return minutes:seconds
  else if (mil < 3600000){
    m = mil/1000/60;
    s = mil/1000 - (m*60);
    if(s>9) return (String)m + ":" + s;
    else    return (String)m + ":0" + s;  
  }
  
  //greater than 1 hour, return hours:minutes:seconds
  else{
    h = mil/1000/60/60;
    m = mil/1000/60 - (h*60);
    s = mil/1000 - (m*60) - (h*60*60);
    if(s>9) return (String)h + ":" + m + ":" + s;  
    else    return (String)h + ":" + m + ":0" + s;  
  }
}

//runs at startup
void setup() {
  lcd.begin(16, 2); //Sets up the LCDs number of columns and rows
  lcd.setCursor(0, 0);
  lcd.print("Run#1"); //Print Run#1 to top left of screen
}

void loop() {

  //If the device is not paused, continue to print information to screen
  if(not paused){
    //print current run duration
    String currentRunDuration = (String)" C-" + formatMilli(millis() - pauseMillis - runStartTime);
    lcd.setCursor(16 - currentRunDuration.length(), 0);
    lcd.print(currentRunDuration);

    //print total time
    String totalTime = (String)" T-" + formatMilli(millis() - pauseMillis);
    lcd.setCursor(16 - totalTime.length(),1);
    lcd.print(totalTime);
  }
  
  //See if any buttons have been pressed
  int buttonNum = read_LCD_buttons(); 

  //If DOWN or UP are pressed, pause or unpause the device
  if (buttonNum == btnDOWN or buttonNum == btnUP){
    if(paused){
      //add the amount of paused time to the pause counter
      pauseMillis = pauseMillis + (millis() - pauseStartTime);
      paused = false;
    }
    else{ //if not paused
      paused = true;
      //keep track of when pause was pressed
      pauseStartTime = millis();
    }
    //prevent multiple clicks
    delay(500);
  }
  
  //If SELECT or LEFT are pressed and it is not paused, start a new run
  else if (not paused and (buttonNum == btnSELECT or buttonNum == btnLEFT)) {
    runCounter++;

    //print run number
    lcd.setCursor(0, 0);
    lcd.print((String)"Run#" + (runCounter+1));
    
    //Reset current run time
    runStartTime = millis() - pauseMillis;

    //Recalculate average run time and print to screen
    lcd.setCursor(0, 1);
    String averageTime = (String)"A-" + formatMilli((millis()-pauseMillis)/runCounter);
    lcd.print(averageTime);

    //prevent multiple clicks
    delay(500);
  }
  
}
