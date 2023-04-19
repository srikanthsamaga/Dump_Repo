#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <WiFiEspUdp.h>
//#include "SoftwareSerial.h"
#include <PubSubClient.h>


#define OUTPUT_LED 13
#define OUTPUT_HIGH digitalWrite(OUTPUT_LED, HIGH)
#define OUTPUT_LOW digitalWrite(OUTPUT_LED, LOW)


IPAddress server(52, 31, 15, 152);
//char ssid[] = "Alemari's";           // your network SSID (name)
//char pass[] = "1921681123456";           // your network password

char ssid[] = "DLink";           // your network SSID (name)
char pass[] = "1921681123456";           // your network password

unsigned long looptimer_prev = 0;
unsigned long looptimer_curr = 0;

//char ssid[] = "Dheeraj Rao";           // your network SSID (name)
//char pass[] = "9986503762";           // your network password
int status = WL_IDLE_STATUS;   // the Wifi radio's status

// Initialize the Ethernet client object
WiFiEspClient espClient;

void callback(char* topic, byte* payload, unsigned int length);

//PubSubClient client(espClient);
PubSubClient client(server, 19257, callback, espClient);

//SoftwareSerial soft(2,3); // RX, TX

void setup() {

  //Initialize Output
  pinMode(OUTPUT_LED,OUTPUT);
  OUTPUT_LOW;
  
  // initialize serial for debugging
  Serial.begin(9600);
  // initialize serial for ESP module
  Serial3.begin(115200);
  // initialize ESP module
  WiFi.init(&Serial3);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  // you're connected now, so print out the data
  Serial.println("You're connected to the network");

  //connect to MQTT server
  if (client.connect("arduinoClient", "TestArduino", "password")) {
    client.publish("testtopic1","hello MQTT");
    client.subscribe("testtopic");
  }
}

//print any message received for subscribed topic
void callback(char* topic, byte* payload, unsigned int length) {
  volatile unsigned int payload_int;
  static char res[2];
  //String str;
  
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();



  payload_int = (((payload[0]-48)*10)+(payload[1]-48));

  
  Serial.println((payload[0]-48));
  Serial.println((payload[1]-48));

  Serial.println(payload_int);
  
  //payload_int++;
  
  Serial.println(payload_int);
  //str.toCharArray(payload_int,2);

  //Limit to 2 digits
  payload_int = payload_int%100;
  //MSB
  res[0] = (payload_int/10)+48;
  //LSB
  res[1] = (payload_int%10)+48;
    
  //res[1] = (payload_int&0x0F)+48;
  //res[0] = ((payload_int&0xF0)>>4)+48;

  Serial.print(res[0]);
  Serial.println(res[1]);
  
  //client.publish("testtopic1",res,2,false);

  if(payload_int>=50)
  {
    OUTPUT_HIGH;
    client.publish("testtopic1","Output ON");
  }
  else
  {
    OUTPUT_LOW;
    client.publish("testtopic1","Output OFF");
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  

  looptimer_curr = millis();

  //Serial.print("....millis : ");
  //Serial.print(loopvar);

  if((looptimer_curr-looptimer_prev)>10000)
  {
    if (!client.connected()) {
      reconnect();
    }
    
    looptimer_prev = looptimer_curr;
  }
    
    client.loop();

   
 /* }
  else
  {
    //delay(1);
  }*/
  //loopvar++;

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect, just a name to identify the client
    if (client.connect("arduinoClient", "TestArduino", "password")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("testtopic1","reconnected");
      // ... and resubscribe
      client.subscribe("testtopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
