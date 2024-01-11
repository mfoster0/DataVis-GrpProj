#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

//wifi CE lab
const char* ssid = "CE-Hub-Student";
const char* password = "casa-ce-gagarin-public-service";

//wifi home
// const char* ssid = "VM9486848";
// const char* password = "5rfzxumhPkya8nxA";

const char* mqtt_server = "mqtt.cetools.org";
const int mqtt_port = 1884;
const char* mqtt_user = "student";
const char* mqtt_password = "ce2021-mqtt-forget-whale";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
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
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int randomNumber1 = random(0, 181);
  int randomNumber2 = random(0, 181);
  const char* curmonth = "December";
  int curyear = 2023;


  // Publish JSON messages to separate topics
  char jsonString1[10];
  char jsonString2[10];
  char jsonString3[10];
  char jsonString4[10];
    char jsonString5[10];



  snprintf(jsonString1, sizeof(jsonString1), "%d", randomNumber1);
  snprintf(jsonString2, sizeof(jsonString2), "%d", randomNumber2);
  snprintf(jsonString3, sizeof(jsonString3), "%d", 15);
  snprintf(jsonString4, sizeof(jsonString4), "%s", curmonth);
  snprintf(jsonString5, sizeof(jsonString4), "%d", curyear);



  client.publish("student/CASA0016/ucfnmut/random1", jsonString1);
  client.publish("student/CASA0016/ucfnmut/random2", jsonString2);
  client.publish("student/CASA0016/ucfnmut/curData", jsonString3);
  client.publish("student/CASA0016/ucfnmut/curMonth", jsonString4);
  client.publish("student/CASA0016/ucfnmut/curyear", jsonString5);



  Serial.println(jsonString1);
  Serial.println(jsonString2);
  Serial.println(jsonString3);
  Serial.println(jsonString4);
  Serial.println(jsonString5);




  delay(10000);
}
