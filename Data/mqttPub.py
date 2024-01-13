# test script to publish out data to required topics
import paho.mqtt.client as mqtt
import time


# Callback when the client connects to the broker
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

def keepPublishing():
    while(True):
        if  (client.is_connected() != True):
            client.connect("mqtt.cetools.org", 1884, 60)
            time.sleep(0.2)

        client.publish("student/CASA0019/G6/data/north", "test")
        client.publish("student/CASA0019/G6/data/south", "test")
        client.publish("student/CASA0019/G6/data/month", "test")
        client.publish("student/CASA0019/G6/data/year", "test")
        time.sleep(5)
        print(".")

def on_publish(client,userdata,result):             #create function for callback
    print("data published \n")
    pass

      
# Create an MQTT client
client = mqtt.Client()

client.on_publish = on_publish

# Set the username and password for authentication
client.username_pw_set("", password="")

# Set the callback functions
client.on_connect = on_connect

# Connect to the MQTT broker
client.connect("mqtt.cetools.org", 1884, 60)  # Replace "broker_address" with the address of your MQTT broker

keepPublishing()
