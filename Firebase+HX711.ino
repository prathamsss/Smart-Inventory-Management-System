#include "HX711.h"


// HX711 circuit wiring
const int LOADCELL_DOUT_PIN1 = 16;//D0
const int LOADCELL_SCK_PIN1 = 5;//D1


const int  LOADCELL_DOUT_PIN2 = 12;//D6
const int LOADCELL_SCK_PIN2 = 13;//D7
 const int  LOADCELL_DOUT_PIN3 = 2;//D4
const int LOADCELL_SCK_PIN3 = 14;//D5
HX711 scale1;
HX711 scale2;
HX711 scale3;


#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>


#define WIFI_SSID "pratha"
#define WIFI_PASSWORD "dada123123"
#define FIREBASE_HOST "pratham-2307.firebaseio.com"
#define FIREBASE_AUTH "S4CFJ9ZjJTsZEAUckIOwyZIox7Ed15B4hgNAgsyQ"

void setup() {
  Serial.begin(38400);
  Serial.println("HX711 Demo");

  Serial.println("Initializing the scale");

  // Initialize library with data output pin, clock input pin and gain factor.
  // Channel selection is made by passing the appropriate gain:
  // - With a gain factor of 64 or 128, channel A is selected
  // - With a gain factor of 32, channel B is selected
  // By omitting the gain factor parameter, the library
  // default "128" (Channel A) is used here.
  scale1.begin(LOADCELL_DOUT_PIN1, LOADCELL_SCK_PIN1);

  Serial.println("Before setting up the scale1:");
  Serial.print("read: \t\t");
  Serial.println(scale1.read());      // print a raw reading from the ADC

  Serial.println("read average: \t\t");
  Serial.println(scale1.read_average(20));   // print the average of 20 readings from the ADC

  Serial.println("get value: \t\t");
  Serial.println(scale1.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale1.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight (not set) divided
            // by the SCALE parameter (not set yet)

  scale1.set_scale(470.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale1.tare();               // reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale1.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale1.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale1.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale1.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
            // by the SCALE parameter set with set_scale
scale2.begin(LOADCELL_DOUT_PIN2, LOADCELL_SCK_PIN2);

  Serial.println("Before setting up the scale1:");
  Serial.print("read: \t\t");
  Serial.println(scale2.read());      // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale2.read_average(20));   // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale2.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale2.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight (not set) divided
            // by the SCALE parameter (not set yet)

  scale2.set_scale(470.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale2.tare();               // reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale2.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale2.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale2.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale2.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
            // by the SCALE parameter set with set_scale

scale3.begin(LOADCELL_DOUT_PIN3, LOADCELL_SCK_PIN3);

  Serial.println("Before setting up the scale3:");
  Serial.print("read: \t\t");
  Serial.println(scale3.read());      // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale3.read_average(20));   // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale3.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale3.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight (not set) divided
            // by the SCALE parameter (not set yet)

  scale3.set_scale(470.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale3.tare();               // reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale3.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale3.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale3.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale3.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
            // by the SCALE parameter set with set_scale


  Serial.println("Readings:");
  Serial.begin(9600);
  delay(1000);                
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                              // connect to firebase
  
}

void loop() {
  Serial.print("one reading:\t");
  Serial.print(scale1.get_units(), 1);
  int t1 =scale1.get_units(10);
      Serial.print("\t| average:\t");
      Serial.println("Wt if i_1");
      Serial.println(scale1.get_units(10), 1);
  String fire1 = String(t1);                                                     //convert integer temperature to string temperature

  scale1.power_down();             // put the ADC in sleep mode
  delay(5000);
  scale1.power_up();
      Serial.print("one reading:\t");
      Serial.print(scale2.get_units(), 1);
  int t2 =scale2.get_units(10);
  String fire2 = String(t2);                                                     //convert integer temperature to string temperature

  Serial.print("\t| average:\t");
    Serial.println("Wt Of i_2");

  Serial.println(scale2.get_units(10), 1);
  scale2.power_down();             // put the ADC in sleep mode
  delay(5000);
  scale2.power_up();
  Serial.print("one reading:\t");
  Serial.print(scale3.get_units(), 1);

  Serial.print("\t| average:\t");
    Serial.println("Wt Of i_3");

  Serial.println(scale3.get_units(10), 1);
    int t3 =scale3.get_units(10);
  String fire3 = String(t3);                                                     //convert integer temperature to string temperature



  scale3.power_down();             // put the ADC in sleep mode
  delay(5000);
  scale3.power_up();
Firebase.setString("i_1", fire1);
Serial.println("FireBASE UPLOADED");//setup path and send readings
  Firebase.setString("i_2", fire2);
    Firebase.setString("i_3", fire3);                                //setup path and send readings
  
}
