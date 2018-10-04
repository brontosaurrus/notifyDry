#include <SimpleTimer.h>
#include <Time.h>


//Libraries
#include <DHT.h>
// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"

//Constants
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor for normal 16mhz Arduino

//Variables
float hum;  //Stores humidity value
float temp; //Stores temperature value

RTC_PCF8523 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int dryState = 1;
int wetState = 2;
int currentState;
int x = 2;
int y = 0;
float b = 0;




void setup() {
  // put your setup code here, to run once:
  dht.begin();  //for temp and humidity

  pinMode(6, INPUT);  //for motion sensor
  while (!Serial) {
      delay(1);  // for Leonardo/Micro/Zero
   }
  
  Serial.begin(9600);


//rest of set up is for time
if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.initialized()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  //DateTime now = rtc.now();
  //DateTime dryTimer (now + TimeSpan(0,0,x,y));
  

}

void loop() {
  //code to start a timer
//calculate a general time for when the paint will have dried which is 0 days, 0 hours 25 mins
 b = b + 12;
float z = 0-b;


 DateTime now = rtc.now();
DateTime startTime (now + TimeSpan(0, 0, 0, 0));
DateTime dryTimer (now + TimeSpan(0,0,x,z));
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

  //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp= dht.readTemperature();

 //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");
    delay(2000); //Delay 2 sec.

    
    
    //perfect conditions
if (temp > 10){
  if (hum > 60 and hum < 80){

  DateTime dryTimer (dryTimer + TimeSpan(0, 0, x, y));
 }
 else{
 DateTime dryTimer (dryTimer + TimeSpan(0, 0,x + 5, y));
 }
}
else {
  if (hum > 60 and hum < 80){
  
  DateTime dryTimer (dryTimer + TimeSpan(0, 0,x + 5, y));
 }
 else {
    DateTime dryTimer (dryTimer + TimeSpan(0, 0,x + 10, y));
 }
  
}


if ( now.minute() >= dryTimer.minute() ){
  Serial.print("Paint is dry ");
  int currrentState = 1;
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);                       // wait for a second 
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      delay(1000);                           // wait for a second
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);                       // wait for a second
}
else {
  currentState = wetState;
}
  
 if (digitalRead(6) == HIGH) {
    Serial.println("Active");
    if (currentState == wetState){
      //code to set alarm
    }
    else{ //when motion is detected but paint is not wet the LED will flash
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);                       // wait for a second 
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      delay(1000);                           // wait for a second
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);                       // wait for a second
    }
  }
  else {
    Serial.println("Inactive");
  }
  delay(1000);


    Serial.print(dryTimer.day(), DEC);
    Serial.print(' ');
    Serial.print(dryTimer.hour(), DEC);
    Serial.print(':');
    Serial.print(dryTimer.minute(), DEC);
    Serial.print(':');
    Serial.print((dryTimer.second()), DEC);
    Serial.println();
    
    Serial.println();
    delay(3000);


  
}
