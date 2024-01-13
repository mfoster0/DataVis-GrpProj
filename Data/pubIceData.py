import pandas as pd
import numpy as np
import time
import paho.mqtt.client as mqtt


# Callback when the client connects to the broker
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

def keepPublishing():
    while(True):
        # loop through the rows using iterrows()
        for index, row in data.iterrows():
            #if connection drops, reconnect
            """
            if  (client.is_connected() != True):
                client.connect("mqtt.cetools.org", 1884, 60)
                #allow time for connection to be set up
                time.sleep(0.2)
            """
            #for testing
            #print(row['year'].astype(np.int64), row['mo'].astype(np.int64), row['extent_north'], row['extent_south'])
            
            client.publish("student/CASA0019/G6/data/north", row['extent_north'])
            client.publish("student/CASA0019/G6/data/south", row['extent_south'])
            client.publish("student/CASA0019/G6/data/month", str(row['mo'].astype(np.int64)))
            client.publish("student/CASA0019/G6/data/year", str(row['year'].astype(np.int64)))
            time.sleep(1)

def on_publish(client,userdata,result):          
    #print("data published \n")
    pass

# Create an MQTT client
client = mqtt.Client()

client.on_publish = on_publish

# Set the username and password for authentication
client.username_pw_set("", password="") ######## grab from secrets

# Set the callback functions
client.on_connect = on_connect

# Connect to the MQTT broker
client.connect("mqtt.cetools.org", 1884, 60)  # Replace "broker_address" with the address of your MQTT broker

# get data
initialData = 'MonthlyData.csv'
data = pd.read_csv(initialData)

keepPublishing()