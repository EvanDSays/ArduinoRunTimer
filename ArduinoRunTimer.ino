#include <LiquidCrystal.h>

// Select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);            

int runCounter = 0;
int adc_key_in  = 0;
long runStartTime = 0;

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor 
 // The buttons when read are centered at these values: 0, 144, 329, 504, 741
 // We add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 250)  return btnUP; 
 if (adc_key_in < 450)  return btnDOWN; 
 if (adc_key_in < 650)  return btnLEFT; 
 if (adc_key_in < 850)  return btnSELECT;  
 return btnNONE;  // when all others fail, return this
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
    s = mil/1000 - (m*60);
    if(s>9) return (String)h + ":" + m + ":" + s;  
    else    return (String)h + ":" + m + ":0" + s;  
  }
}

void setup() {
  // set up the LCDs number of columns and rows
  lcd.begin(16, 2);
  runCounter = 0;
}

void loop() {

  lcd.setCursor(0, 0);
  lcd.print((String)"Run#" + (runCounter+1));
  
  String currentRunDuration = (String)" C-" + formatMilli(millis() - runStartTime);
  lcd.setCursor(16 - currentRunDuration.length(), 0);
  lcd.print(currentRunDuration);
  
  String totalTime = (String)" T-" + formatMilli(millis());
  lcd.setCursor(16 - totalTime.length(),1);
  lcd.print(totalTime);
  
  int buttonNum = read_LCD_buttons();

  //once any button (other than reset) has been clicked
  if (buttonNum < 5) {
    runCounter++;
    
    //Reset current run time
    runStartTime = millis();

    //Recalculate average run time and print to screen
    lcd.setCursor(0, 1);
    String averageTime = (String)"A-" + formatMilli(millis()/runCounter);
    lcd.print(averageTime);
    delay(500);
  }
  
}
