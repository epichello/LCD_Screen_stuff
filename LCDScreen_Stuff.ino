#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int button_pin = 2;

int button_state = 0;
int button_count = 0;
int button_count_memory = 0;

LiquidCrystal_I2C lcd(0x27, 16,2); //16 wide 2 lines

void pressed(int &button_count, int &button_count_memory)
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
if(button_state == LOW)
{
  button_count++;
  // pressed(button_count, button_count_memory);
  Serial.println(button_count);
  Serial.println("bing");

}
}
