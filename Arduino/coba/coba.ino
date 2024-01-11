#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Wifi at home
const char* ssid = "VM9486848";
const char* password = "5rfzxumhPkya8nxA";

const char* mqttServer = "mqtt.cetools.org";
const int mqttPort = 1884;
const char* mqttUser = "student";
const char* mqttPassword = "ce2021-mqtt-forget-whale";
const char* stateTopic = "student/CASA0019/ucfnmut/state";

WiFiClient espClient;
PubSubClient client(espClient);

const int ledbutton = 8; // ESP8266's built-in LED pin
//const int ledPin = LED_BUILTIN; // ESP8266's built-in LED pin
const int buttonPin = 7;
int buttonState = 0;
int lastButtonState = 0;
int state = 0;

void setup() {
  pinMode(buttonPin, INPUT);
  //pinMode(ledPin, OUTPUT); // Set LED pin as an output
  pinMode(ledbutton, OUTPUT); // Set LED pin as an output

  Serial.begin(9600);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback); // Set the callback function for subscription
  client.subscribe(stateTopic); // Subscribe to the stateTopic
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  buttonState = digitalRead(buttonPin);

  if (buttonState != lastButtonState) {
    delay(50);
    buttonState = digitalRead(buttonPin);

    if (buttonState == HIGH) {
      Serial.println("Button Pressed");
      state = 1 - state;
      Serial.print("Current State: ");
      Serial.println(state);
      sendStateViaMQTT();
    }

    lastButtonState = buttonState;
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  // Convert the incoming payload to integer
  int incomingState = atoi((char *)payload);

  if (incomingState == 0 || incomingState == 1) {
    state = incomingState; // Update the state based on the received payload

    // Control the LED based on the updated state
    if (state == 1) {
      //digitalWrite(ledPin, HIGH); // Set LED high when state is 1
      digitalWrite(ledbutton, HIGH); // Set LED high when state is 1

    } else {
      //digitalWrite(ledPin, LOW); // Set LED low when state is 0
      digitalWrite(ledbutton, LOW); // Set LED low when state is 0

    }

    Serial.print("New State: ");
    Serial.println(state);
  } else {
    Serial.println("Invalid payload");
  }
}

void sendStateViaMQTT() {
  char msg[10];
  snprintf(msg, 10, "%d", state);
  client.publish(stateTopic, msg);
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP8266Client", mqttUser, mqttPassword)) {
      Serial.println("Connected to MQTT");
      client.subscribe(stateTopic); // Resubscribe after reconnection
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}
