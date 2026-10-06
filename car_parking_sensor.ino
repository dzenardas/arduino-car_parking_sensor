// @author Dženardas Jevič
// Creative build: car parking sensor (parking assistant)

#include <LiquidCrystal_I2C.h>

// PINS
int greenLED = 6;
int yellowLED = 5;
int redLED = 4;
int sigPIN = 7;
int buzzerPIN = 8;

// LCD
LiquidCrystal_I2C lcd(0x20, 16, 2);

// Distance calculation (Found in website)
long readDistanceCM()
{
  pinMode(sigPIN, OUTPUT);
  digitalWrite(sigPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(sigPIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(sigPIN, LOW);

  pinMode(sigPIN, INPUT);
  long duration = pulseIn(sigPIN, HIGH);

  return duration * 0.034 / 2;
}

// LED bulbs
void setLEDS(bool green, bool yellow, bool red)
{
  digitalWrite(greenLED, green);
  digitalWrite(yellowLED, yellow);
  digitalWrite(redLED, red);
}

// LCD screen
void showDistanceLCD(double distance)
{
  if (distance < 25){
    lcd.setCursor(0, 0);
  	lcd.print("STOP!!         ");
    lcd.setCursor(0, 1);
  	lcd.print("               ");
  } else {
  	lcd.setCursor(0, 0);
  	lcd.print("Distance:      ");
  	lcd.setCursor(0, 1);
  	lcd.print(distance);
  	lcd.print(" cm            ");
  }
}

// Setup
void setup()
{
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  
  lcd.init();
  lcd.clear();         
  lcd.backlight();
  
  Serial.begin(9600);
}

// Loop
void loop()
{
  long distance = readDistanceCM();
  showDistanceLCD(distance);
  
  Serial.print(distance);
  Serial.print(" ");
  
  if(distance > 100){
  	setLEDS(true, false, false);
    noTone(buzzerPIN);
    delay(100);
  } else if(distance > 50){
  	setLEDS(false, true, false);
    tone(buzzerPIN, 1000);
    delay(100);
    noTone(buzzerPIN);
    delay(500);
  } else if(distance > 25){
  	setLEDS(false, false, true);
    tone(buzzerPIN, 1500);
    delay(100);
    noTone(buzzerPIN);
    delay(500);
  } else{
  	setLEDS(false, false, true);
    tone(buzzerPIN, 2000);
    delay(100);
    noTone(buzzerPIN);
    delay(200);
  }
}