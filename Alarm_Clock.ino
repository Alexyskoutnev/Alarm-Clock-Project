#include <RTClib.h>
#include <LiquidCrystal.h>
#include <Wire.h> 


const int buzzer = 2;
const int buttonApin = 3;
const int buttonBpin = 2;
const int buttonActivation = 13;
const int buttonAlarmPin= 4;
const int buzzerpin = 5;
int buttonAlarmState = 0;
int alarm = 0;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
float time;
unsigned int seconds = 0;
unsigned int minutes = 0;
unsigned int hours = 0;
unsigned int alarmHours = 0;
unsigned int alarmMinutes = 0;
RTC_DS3231 rtc;                     // create rtc for the DS3231 RTC module, address is fixed at 0x68

void setup() {
  // initializing the rtc
  if(!rtc.begin()) {
      Serial.println("Couldn't find RTC!");
      Serial.flush();
      abort();
  }
  if(rtc.lostPower()) {
      // this will adjust to the date and time at compilation
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  pinMode(buttonApin, INPUT_PULLUP);  
  pinMode(buttonBpin, INPUT_PULLUP);
  pinMode(buttonActivation, INPUT_PULLUP);  
  pinMode(buttonAlarmPin, INPUT);   
  pinMode(buzzerpin, OUTPUT);
  
  lcd.begin(16, 2);
  lcd.clear();
  pinMode(buzzer, OUTPUT); // Set buzzer as an output
  Serial.begin(9600); 
}

void loop() {
  //
  DisplayDateTime();
  SetAlarm();
  if (digitalRead(buttonActivation) == LOW)
  {
   lcd.clear();
   lcd.setCursor(0,0);
   if (alarmHours <= 9){
    lcd.print("0");
   }
   lcd.print(alarmHours);
   lcd.print(":");
   lcd.setCursor(3,0);
   if (alarmMinutes <= 9){
    lcd.print("0");
   }
   lcd.print(alarmMinutes);
   delay(100);

   if (digitalRead(buttonBpin) == LOW)
   {
   lcd.setCursor(0,0);
   alarmHours = alarmHours +  1;
   if (alarmHours == 60)
   {
    alarmHours = 0;
   }
   if (hours <= 9){
    lcd.print("0");
   }
   lcd.print(alarmHours);
   delay(700);
   }
   if (digitalRead(buttonApin) == LOW)
   {
   alarmMinutes = alarmMinutes +  1;
   if (alarmMinutes == 60){
    alarmMinutes = 0; 
   }
   if (minutes <= 9)
   {
    lcd.print("0");
   }
   lcd.setCursor(3,0);
   lcd.print(alarmMinutes);
   delay(300);
  }
  lcd.setCursor(0,1);
  lcd.print("Set Alarm");
  }//Alarm Set
  
  if (digitalRead(buttonApin) == LOW)
  {
   lcd.setCursor(0,1);
   lcd.print("A");
  }
  if (digitalRead(buttonBpin) == LOW)
  {
   lcd.setCursor(0,1);
   lcd.print("B");
  }
  if (digitalRead(buttonAlarmPin) == HIGH)
  {
   alarm = (alarm+1)%2;
   if (alarm == 1){
   lcd.setCursor(0,1);
   lcd.print("Alarm On");
   alarm = 1;
   }
   else{
   lcd.setCursor(0,1);
   lcd.print("Alarm Off");
   alarm = 0;
   }
   delay(2000);
   lcd.clear();
  }
}


void DisplayDateTime()
{
  DateTime rtctime = rtc.now();
  seconds = rtctime.second();
  minutes = rtctime.minute();
  hours = rtctime.twelveHour();
  lcd.setCursor(0,0);
  {
    lcd.print("0");
  }
  lcd.print(hours);
  lcd.print(":");
  if (minutes <= 9)
  {
    lcd.print("0");
  }
  lcd.print(minutes);
  lcd.print(":");
  if (seconds <= 9)
  {
    lcd.print("0");
  }
  lcd.print(seconds);
}

void SetAlarm()
{
 if (alarm == 1)
 {
  if (alarmHours == hours and alarmMinutes == minutes){
    if (alarm == 1){
      tone(buzzerpin, 1000); 
    }
    else{
      noTone(buzzerpin); 
    }

  }
  if (alarm == 0)
  {
    noTone(buzzerpin);
  }
 }
}
