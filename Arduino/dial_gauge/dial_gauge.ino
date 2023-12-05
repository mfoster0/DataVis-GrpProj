#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>


char receivedMessage[50]; 
// Wifi at home
// const char* ssid = "VM9486848";
// const char* password = "5rfzxumhPkya8nxA";

// CE Lab wifi
const char* ssid = "CE-Hub-Student";
const char* password = "casa-ce-gagarin-public-service";

const char* mqttuser = "student";
const char* mqttpass = "ce2021-mqtt-forget-whale";
const char* mqtt_server = "mqtt.cetools.org";

// Define topic to subscribe
const char* topic1 = "student/CASA0019/G6/data/south";
const char* topic2 = "student/CASA0016/ucfnmut/random2";

WiFiClient espClient;
PubSubClient client(espClient);

// Define servo objects
Servo servo1; 
Servo servo2;

//Define LED Panel
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0); 


void setup() {
  Serial.begin(115200);
  delay(100);

  startWifi();

  client.setServer(mqtt_server, 1884);
  client.setCallback(callback);
  subscribeToTopic(topic1);
  subscribeToTopic(topic2);

  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  servo1.attach(14, 500, 2400); // Replace D1 with the pin number for servo 1
  servo2.attach(12, 500, 2400); // Replace D2 with the pin number for servo 2
  u8g2.begin();

}

void loop() {

  client.loop();
  displayMessage(receivedMessage); // Display the received message on the OLED

}

void displayMessage(const char* message) {
  u8g2.clearBuffer(); // Clear the display buffer
  u8g2.setCursor(0, 30); // Set the cursor position
  u8g2.setFont(u8g2_font_ncenB14_tr); // Set the font for displaying text on the OLED
  u8g2.print(message); // Display the received message on the OLED
  u8g2.sendBuffer(); // Send the buffer content to the display
}


void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str(), mqttuser, mqttpass)) {
      Serial.println("connected");
      client.subscribe("student/CASA0016/ucfnmut/inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void subscribeToTopic(const char* mqttTopic) {
  if (!client.connected()) {
    reconnect();
  }

  if (client.subscribe(mqttTopic)) {
    Serial.print("Subscribed to topic: ");
    Serial.println(mqttTopic);
  } else {
    Serial.print("Failed to subscribe to topic: ");
    Serial.println(mqttTopic);
  }
}

void startWifi() {
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void moveServo(Servo& servo, int value) {
  int angle = map(value, 0, 20, 0, 180); 
  servo.write(angle); // Move the servo to the mapped angle
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived ");
  //Serial.print(topic);
  for (int i = 0; i < length; i++) {
     Serial.print((char)payload[i]);
   }
  Serial.println();

  snprintf(receivedMessage, sizeof(receivedMessage), "%.*s", length, (char*)payload);
  int value = atoi(receivedMessage); // Convert received message to an integer

  if (strcmp(topic, "student/CASA0019/G6/data/south") == 0) {
    moveServo(servo1, value); // Control servo 1 based on the received value
  } else if (strcmp(topic, "student/CASA0016/ucfnmut/random2") == 0) {
    moveServo(servo2, value); // Control servo 2 based on the received value
  }
}



