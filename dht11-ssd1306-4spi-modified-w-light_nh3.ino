#include "U8glib.h"
#include "dht.h"

#define DHT11_PIN 7

dht DHT;

U8GLIB_SH1106_128X64 u8g(13, 11, 10, 9, 8);  // D0=13, D1=11, CS=10, DC=9, Reset=8

String lightmeter;
String NH3p;
 


void draw(void) {
  
  u8g.setFont(u8g_font_unifont);  // select font
  u8g.drawStr(0, 26, "Temp: ");  // put string of display at position X, Y
  u8g.drawStr(0, 40, "Hum: ");
  u8g.setPrintPos(44, 26);  // set position
  u8g.print(((DHT.temperature)*1.8+32), 0);  // display temperature from DHT11
  u8g.drawStr(60, 26, "F ");
  u8g.setPrintPos(44, 40);
  u8g.print(DHT.humidity, 0);  // display humidity from DHT11
  u8g.drawStr(60, 40, "% ");
  u8g.setPrintPos(0, 11); // draws a bar-graph-style light meter at top
  u8g.print(lightmeter);
  u8g.drawStr(0, 54, "NH3%: ");
  u8g.setPrintPos(44, 54);
  u8g.print(NH3p); // displays Ammonia gas "percentage" (not really to scale) 
  u8g.drawStr(60, 54, "% ");
}

void setup(void) {
   Serial.begin(9600);
   //5v thru D4
   pinMode(4, OUTPUT);
   digitalWrite(4, HIGH);
}

void loop(void) {
 int chk = DHT.read11(DHT11_PIN);  // Read ll on DHT11
   //ocode below prints out humidity and temp to serial
  Serial.print("Temperature = ");
  Serial.println((DHT.temperature)*1.8+32);//convert to Farenheit
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  
  int lux;
  int luxp;
  lux=analogRead(0); //read analog pin 0 (light sensor output pin)
  luxp=(int(float(lux)/1024*100)); //convert it into a percent
  int luxb;
  luxb=(int(float(luxp/20))); //convert to a scale of 0..5
  Serial.print("Light% = "); // make serial output human-readable
  //Serial.print(luxb); // print the 0..5 value
  //Serial.print(", "); // a space
  Serial.println(luxp); // print light sensor value to serial
  lightmeter=String("");//zero this global variable each loop

  for (int i = 0; i<luxb; i++) {
    lightmeter=String(lightmeter + "/");
    };

  int nh3 = analogRead(A5); //read MQ137, plugged into A1
  int nh3p=(int(float(nh3)/1024*100)); //convert it into a percent
  Serial.print("NH3 % = "); // make serial output human-readable
  Serial.println(nh3p);
  NH3p=nh3p;
   
  
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
  delay(5000);  // Delay of 5sec before accessing DHT11 (min - 2sec)
}
