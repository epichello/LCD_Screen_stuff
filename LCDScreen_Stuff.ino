#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int button_pin = 2;

int button_state = 0;
int button_count = 0;
int button_count_memory = 0;

int button_state_current = 0;
int button_state_previous = 0;

bool button_was_pressed = false;

LiquidCrystal_I2C lcd(0x27, 16,2); //16 wide 2 lines

bool lever_function(int &button_state_current, int &button_state_previous, int&button_count)
{
  if(button_state_current == button_state_previous)
  {
    return false;
  }
  if(button_state_current == 1 && button_state_previous == 0)
  {
    button_count++;
    return true;
  }
}

void off_on_lcd(int &button_count, int &button_count_memory)
{
  if(button_count - button_count_memory == 1)
  {
    lcd.backlight();
    return;
  }
  if(button_count - button_count_memory == 2)
  {
    lcd.noBacklight();
    button_count_memory = button_count;
    return;
  }
}

void setup() 
{
Serial.begin(9600);
pinMode(button_pin, INPUT_PULLUP); //sets 
lcd.noBacklight(); //initialise with no backlight
}

void loop()
{
button_state = digitalRead(button_pin); //returns 1 (up) or 0 (down)
button_state_previous = button_state;
if(button_state == 0)
{
  button_state_current = button_state;
  Serial.println("hello1");
}
button_was_pressed = lever_function(button_state_current, button_state_previous, button_count) ;
if(button_was_pressed == true)
{
  off_on_lcd(button_count, button_count_memory);
  Serial.println("hello2");
}
}
