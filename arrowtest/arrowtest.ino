#include <CapPin.h>
#include <Keyboard.h>
#define THRESH 5
 
CapPin cPin_10 = CapPin(10);    // read pin 10 (D10 on Flora) - connect to NES B
CapPin cPin_9  = CapPin(9);     // read pin 9 (D9 on Flora)   - connect to NES A

CapPin pins[] = {cPin_10, cPin_9};
char Keys[] = {KEY_RIGHT_ARROW, KEY_LEFT_ARROW};
boolean currentPressed[] = {false, false};
float smoothed;

void setup()
{
  Serial.begin(115200);
  Serial.println("start");
  Keyboard.begin();
}

void loop()                    
{ 
  for (int i=0;i<2;i++) {
    delay(1);
    //long total1 = 0;
    long start = millis();
    long total = pins[i].readPin(2000);
    Serial.println(total);

    smoothed = smooth(total, .8, smoothed);  
 
    // check if we are sensing that a finger is touching the pad 
    // and that it wasnt already pressed
    if ((total > THRESH) && (! currentPressed[i])){
      Serial.print("Key pressed #"); 
      Serial.print(" ("); Serial.print(Keys[i]); Serial.println(")");
      currentPressed[i] = true;
 
      Keyboard.press(Keys[i]);
    } 
    else if ((total <= THRESH) && (currentPressed[i])) {
      // key was released (no touch, and it was pressed before)
      Serial.print(total);
      Serial.print("Key released #"); 
      Serial.print(" ("); Serial.print(Keys[i]); Serial.println(")");
      currentPressed[i] = false;
      
      Keyboard.release(Keys[i]);
    }
    delay(5);
  }
}
 
int smooth(int data, float filterVal, float smoothedVal){

  if (filterVal > 1){      // check to make sure param's are within range
    filterVal = .999999;
  }
  else if (filterVal <= 0){
    filterVal = 0;
  }

  smoothedVal = (data * (1 - filterVal)) + (smoothedVal  *  filterVal);

  return (int)smoothedVal;
}
