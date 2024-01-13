#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>
#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>


char receivedMessage[5]; 
char monthReceived[5]; // Store the received month
char yearReceived[5];  // Store the received year
char stateReceived[5];  // Store the received year

// // Wifi at home
const char* ssid = "VM9486848";
const char* password = "5rfzxumhPkya8nxA";

// CE Lab wifi
// const char* ssid = "CE-Hub-Student";
// const char* password = "casa-ce-gagarin-public-service";

// // Wifi at Gintare
// const char* ssid = "4B87 Hyperoptic 1Gb Fibre 2.4Ghz";
// const char* password = "47EAgzx59EFA";

const char* mqttuser = "student";
const char* mqttpass = "ce2021-mqtt-forget-whale";
const char* mqtt_server = "mqtt.cetools.org";

// Define topic to subscribe
const char* north = "student/CASA0019/G6/data/north";

const char* south = "student/CASA0019/G6/data/south";
const char* month = "student/CASA0019/G6/data/month";
const char* year = "student/CASA0019/G6/data/year";
const char* currentyear = "student/CASA0019/G6/data/currentyear";
const char* currentmonth = "student/CASA0019/G6/data/currentmonth";
const char* northDailyExtent = "student/CASA0019/G6/data/northDailyExtent";
const char* southDailyExtent = "student/CASA0019/G6/data/southDailyExtent";

const char* stateTopic = "student/CASA0019/G6/data/displayDaily";

int currentState = 0; // Variable to hold the current state

WiFiClient espClient;
PubSubClient client(espClient);

// Define servo objects
Servo servo1;
Servo servo2;

//Define LED Panel
Adafruit_SSD1306 display(128, 32);

//Define button pin
const int ledbutton = 8; // ESP8266's built-in LED pin
const int buttonPin = 7; // Define the pin for the button
int buttonState = 0; // Initialize variable to hold the button state
int lastButtonState = 0; // Initialize variable to hold the previous button state
int state = 0;

int ledState = 0; // Initialize variable to hold the LED state
//const int ledPin = LED_BUILTIN; // Define the pin for the LED

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;   

void setup() {
  Serial.begin(115200);
  delay(500);

  servo1.attach(2, 500, 2400); // Replace D1 with the pin number for servo 1
  servo2.attach(3, 500, 2400); // Replace D2 with the pin number for servo 2
  //servo1.write(3); 
  //servo2.write(3); 

  // // Servo Sweep - Useful for Calibration - Edit for own Servo/Dial Range
  // servo1.setEasingType(EASE_LINEAR);
  // servo2.setEasingType(EASE_LINEAR);

  // servo1.setSpeed(15);
  // servo2.setSpeed(15);

  Serial.print("Moving to 0");
  servo1.write(0);
  servo2.write(0);

  
  delay (1000);
  Serial.print("Moving to 180");
  servo1.write(180);
  servo2.write(180);

  delay (1000);
  
  Serial.print("Moving to 0");
  servo1.write(0);
  servo2.write(0);

  Serial.print("Pausing for 1 seconds");
  delay (2000);

  startWifi();

  client.setServer(mqtt_server, 1884);
  client.setCallback(callback);
  subscribeToTopic(north);
  subscribeToTopic(south);
  subscribeToTopic(month);
  subscribeToTopic(year);
  subscribeToTopic(northDailyExtent);
  subscribeToTopic(currentmonth);
  subscribeToTopic(currentyear);
  subscribeToTopic(southDailyExtent);

  subscribeToTopic(stateTopic);

  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());




  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Address 0x3D for 128x32
  pinMode(buttonPin, INPUT); // Set the button pin as an input
  //pinMode(ledPin, OUTPUT); // Set LED pin as an output
  pinMode(ledbutton, OUTPUT); // Set LED pin as an output
  display.clearDisplay();

}

void loop() {
  client.loop();

  // Read the current state of the button
  int reading = digitalRead(buttonPin);

  // Check if the button state has changed
  if (reading != lastButtonState) {
    // Reset the debouncing timer
    lastDebounceTime = millis();
  }

  // If the button state has been different for longer than the debounce delay,
  // we assume that the button state has changed:
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // Only toggle the state if the new button state is HIGH
      if (buttonState == HIGH) {
        Serial.println("Button Pressed");
        state = 1 - state;
        Serial.print("Current State: ");
        Serial.println(state);
        sendStateViaMQTT();
      }
    }
  }

  // Save the reading for the next loop
  lastButtonState = reading;
}

void sendStateViaMQTT() {
  char msg[10];
  snprintf(msg, 10, "%d", state);
  client.publish(stateTopic, msg);
}

// void checkState() {
//   if (currentState == 1) {
//     performTaskB(); // Perform Task B when the state is 1
//   } else {
//     performTaskA(); // Perform Task A when the state is 0
//   }
// }

void displayMessage(const char* month, const char* year) {
  display.clearDisplay();
  display.setTextColor(WHITE);
  // display.setTextSize(1);
  // display.setCursor(0, 0); // Set the cursor position
  // display.print(" Arctic: "); // Display the received message on the OLED
  // display.setCursor(62, 0); // Set the cursor position
  // display.print("Antarctica:"); // Display the received message on the OLED
  // display.setTextSize(2);
  // display.setCursor(0, 10); // Set the cursor position
  // display.print("15"); // Display the received message on the OLED
  // display.setCursor(27, 10); // Set the cursor position
  // display.print("KM"); // Display the received message on the OLED
  // display.setCursor(48, 10); // Set the cursor position
  // display.write(252);
  // display.setCursor(67, 10); // Set the cursor position
  // display.print("20"); // Display the received message on the OLED
  // display.setCursor(94, 10); // Set the cursor position
  // display.print("KM"); // Display the received message on the OLED
  // display.setCursor(115, 10); // Set the cursor position
  // display.write(252);

  display.setTextSize(1);
  display.setCursor(0, 10); // Set the cursor position
  display.print("MONTH  :"); // Display the received message on the OLED
  display.setCursor(50, 10); // Set the cursor position
  display.print(month); // Display the received message on the OLED
  display.setCursor(0, 20); // Set the cursor position
  display.print("YEAR   :"); // Display the received message on the OLED
  display.setCursor(50, 20); // Set the cursor position
  display.print(year); // Display the received message on the OLED

  display.display(); 
}


void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str(), mqttuser, mqttpass)) {
      Serial.println("connected");
      client.subscribe("student/CASA0019/G6/data/inTopic");
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
    //Serial.print("Subscribed to topic: ");
    //Serial.println(mqttTopic);
  } else {
    //Serial.print("Failed to subscribe to topic: ");
    //Serial.println(mqttTopic);
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

void moveServo1(Servo& servo1, int value) {
  int invertedValue = 20 - value; // Invert the value from 0-20 to 20-0
  int angle = map(invertedValue, 0, 20, 0, 180);
  servo1.write(angle); // Move the servo to the mapped angle
   // Calculate the difference in angle
  //int angleDifference = abs(servo1.read() - angle);

  //if (angleDifference < 10) {
  //servo1.setSpeed(5); // Slower for small changes
  //servo1.setEasingType(EASE_LINEAR); // Linear easing for smoother small movements
  //} else {
  //servo1.setSpeed(10); // Faster for larger changes
  //servo1.setEasingType(EASE_CUBIC_IN_OUT); // Cubic easing for larger movements
  // }
  //   // Move servo to the new position
  // servo1.easeTo(angle);
  delay(10); // Allow transit time
}

void moveServo2(Servo& servo2, int value) {
  int angle = map(value, 0, 20, 0, 180); 
  servo2.write(angle); // Move the servo to the mapped angle
   // Calculate the difference in angle
  // int angleDifference = abs(servo2.read() - angle);

  // if (angleDifference < 10) {
  // //servo2.setSpeed(5); // Slower for small changes
  // //servo2.setEasingType(EASE_LINEAR); // Linear easing for smoother small movements
  // } else {
  // //servo2.setSpeed(10); // Faster for larger changes
  // //servo2.setEasingType(EASE_CUBIC_IN_OUT); // Cubic easing for larger movements
  // }
  //   // Move servo to the new position
  // servo2.easeTo(angle);
  delay(10); // Allow transit time
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived ");
  Serial.println(topic);
  
 // Ensure the payload is null-terminated
  char payloadStr[length + 1]; // Create a buffer with an extra space for the null terminator
  memcpy(payloadStr, payload, length); // Copy the payload to the buffer
  payloadStr[length] = '\0'; // Null-terminate the string

  // Convert the null-terminated payload to an integer
  int value = atoi(payloadStr);
  Serial.print("Received Value: ");
  Serial.println(value);

  if (strcmp(topic, stateTopic) == 0) {
    currentState = value; // Set the current state based on the received value
    Serial.print("Current State: ");
    Serial.println(currentState);

    // Control LED button based on currentState
    if (currentState != 0) {
      digitalWrite(ledbutton, HIGH); // Turn on LED button when currentState is 1
    } else {
      digitalWrite(ledbutton, LOW); // Turn off LED button when currentState is 0
    }
  } else {
    // Handle other topics without impacting LED button control
    if (currentState == 0) {
      if (strcmp(topic, north) == 0) {
        moveServo1(servo1, value); // Control servo 1 based on the received value from 'north'
      } else if (strcmp(topic, south) == 0) {
        moveServo2(servo2, value); // Control servo 2 based on the received value from 'south'
      } else if (strcmp(topic, month) == 0) {
        snprintf(monthReceived, sizeof(monthReceived), "%.*s", length, (char*)payload);
        displayMessage(monthReceived, yearReceived); // Display received month on OLED
      } else if (strcmp(topic, year) == 0) {
        snprintf(yearReceived, sizeof(yearReceived), "%.*s", length, (char*)payload);
        displayMessage(monthReceived, yearReceived); // Display received year on OLED
      }
    } else if (currentState == 1) {
      if (strcmp(topic, northDailyExtent) == 0) {
        moveServo1(servo1, value); // Control servo 1 based on the received value from 'northDailyExtent'
      } else if (strcmp(topic, southDailyExtent) == 0) {
        moveServo2(servo2, value); // Control servo 2 based on the received value from 'southDailyExtent'
      } else if (strcmp(topic, currentmonth) == 0) {
        snprintf(monthReceived, sizeof(monthReceived), "%.*s", length, (char*)payload);
        displayMessage(monthReceived, yearReceived); // Display received current month on OLED
      } else if (strcmp(topic, currentyear) == 0) {
        snprintf(yearReceived, sizeof(yearReceived), "%.*s", length, (char*)payload);
        displayMessage(monthReceived, yearReceived); // Display received current year on OLED
      }
    }
  }
  //value = 0;
}

