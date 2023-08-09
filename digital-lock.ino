#include <Keypad.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
#define Password_Lenght 7 
char Data[Password_Lenght]; 
char master[Password_Lenght];
byte data_count = 0, master_count = 0;

char customKey;
char setKey;
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
bool door = true;
byte rowPins[ROWS] = {1, 2, 3, 4}; 
byte colPins[COLS] = {5, 6, 7}; 
Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); 
Keypad setKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); 
void setup()
{
  pinMode(8,OUTPUT);
  digitalWrite(8,LOW);
  lcd.begin(16, 2);
  lcd.print("     Welcome");
  lcd.setCursor(0, 1);
  lcd.print("  LOCK YOURSELF");
  delay(1000);
  lcd.clear();
  setpass();
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("     *****");
  delay(1000);
  
}


void loop()
{
  if (door == 0)
  {
    customKey = customKeypad.getKey();
    if (customKey == '#')
    {
      lcd.clear();
      
      lcd.print("  LOCKED AGAIN");
      digitalWrite(8,LOW);
      delay(800);
      door = 1;
    }
  }
  else Open();
}

void setpass()
{
  lcd.setCursor(0, 0);
  lcd.print("    Set PIN");
  
  int chk=1;
  while(chk)
  {
    setKey = setKeypad.getKey();
    if (setKey) 
    {
    master[master_count] = setKey; 
    lcd.setCursor(master_count, 1); 
    lcd.print(master[master_count]); 
    master_count++; 
  }
  if (master_count == Password_Lenght - 1)
  {
    
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Your PIN IS SET");
    chk=0;
  }
     
}
}


void clearData()
{
  while (data_count != 0)
  {
    Data[data_count--] = 0; 
  }
  return;
}

void Open()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   Enter PIN");
  
  int chk=1;
  while(chk)
  {
    customKey = customKeypad.getKey();
    if (customKey) 
    {
    Data[data_count] = customKey; 
    lcd.setCursor(data_count, 1); 
    lcd.print(Data[data_count]); 
    data_count++; 
  }
  if (data_count == Password_Lenght - 1) 
  {
    if (!strcmp(Data, master)) 
    {
      lcd.clear();
     
      lcd.print("    UNLOCKED");
      digitalWrite(8,HIGH);
      door = 0;
    }
    else
    {
      lcd.clear();
      lcd.print("SORRY WRONG PIN!");
      delay(800);
      door = 1;
    }
    chk=0;
  }
   
  }
  
    clearData();
}
