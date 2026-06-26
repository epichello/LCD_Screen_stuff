#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int button_pin = 2;

int button_state = HIGH;  //initial state
int button_count = 0;

int button_state_previous = HIGH;

unsigned long last_debounce_time = 0; //unsigned long since we're counting in milliseconds
unsigned long debounce_delay = 200;   //which would fill up super fast with int type

LiquidCrystal_I2C lcd(0x27, 16,2); //16 wide 2 lines

bool lever_function(int &button_state_current, int &button_state_previous, int&button_count)
{
  if(button_state_current == LOW && button_state_previous == HIGH)  //checks for edge case 
  {
    if ((millis() - last_debounce_time) > debounce_delay) //millis returns the ms since arduino started
    {                                                     //minus the last time it was activated 
    last_debounce_time = millis(); 
    return true;
    }
  }
  return false;
}

void update_lcd(int &button_count)
{
  if(button_count%2 == 1)
  {
    lcd.backlight();
    return;
  } else
  {
    lcd.noBacklight();
    return;
  }
}

void setup() 
{
Serial.begin(9600);
pinMode(button_pin, INPUT_PULLUP); //sets input to up
lcd.init();
lcd.noBacklight(); //initialise with no backlight

lcd.setCursor(0, 0);             
lcd.print("  (*(*(*-*)*)*)");      // Print text to the first line
lcd.setCursor(0, 1);             // Move the cursor to column 0, row 1 (Second line)
lcd.print("   MEEP MEEP");    // Print text to the second line

}

void loop()
{
button_state_previous = button_state;
button_state = digitalRead(button_pin); //returns 1 (up) or 0 (down)
if(lever_function(button_state, button_state_previous, button_count))
{
  button_count++;
  update_lcd(button_count);
}
}
