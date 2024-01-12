
# CASA0019: Building the Sea Ice Extent Gauge#
## Group 6 - Ice Ice Baby (Mark Foster, Satria Mitra Utama, Qingyao Tang)##
## University College London ##
## 12th January 2024 ##


## Overview
This guide provides step-by-step instructions for building the Sea Ice Extent Gauge, a device designed to visualize changes in polar sea ice. This project, part of the CASA0019 course at University College London, aims to raise awareness about sea ice's importance and the impact of climate change.

## Table of Contents
1. Introduction
2. Components Required
3. Assembly Instructions
4. Software Setup
5. Using the Device
6. Additional Resources
7. References
8. Contributors

## 1. Introduction
The Sea Ice Extent Gauge visualizes real-time changes in Arctic and Antarctic sea ice coverage. It combines a physical device with an interactive digital twin, highlighting the urgency of environmental protection.

## 2. Components Required
- Raspberry Pico W microcontroller
- MG90S servos (2)
- 0.91-inch OLED display
- Metal Push Button LED
- Various electronic components (resistors, wires, etc.)

## 3. Assembly Instructions
### 3.1 Building the Hardware
Assemble the physical gauge using the Raspberry Pico W as the control center, connect the servos, OLED display, and LED push button according to the pin configuration provided.

### 3.2 Crafting the Physical Display
Create two semicircular charts to represent sea ice cover in the Arctic and Antarctic. Use shades of blue to indicate changes in ice coverage.

## 4. Software Setup
### 4.1 Programming the Raspberry Pi
Set up the Raspberry Pi to run a Python script that collects data from NOAA and publishes it to MQTT topics. Install necessary libraries like `paho.mqtt.client`.

### 4.2 Unity Augmented Reality Integration
Develop an AR version using Unity to mimic the physical device. Include additional functionalities like displaying videos and extra data on sea ice changes.

## 5. Using the Device
### 5.1 Interacting with the Gauge
The device uses servos to indicate sea ice extent and an OLED display to show dates. Press the LED button to toggle between historical and current data.

### 5.2 Exploring the Digital Twin
Use the Unity AR interface to access more detailed information and visualizations about sea ice changes.

## 6. Additional Resources
- [GitHub Repository](https://github.com/mfoster0/DataVis-GrpProj)
- Assembly diagrams and schematics

## 7. References
(Include a list of referenced works here)

## 8. Contributors
- Mark Foster
- Satria Mitra Utama
- Qingyao Tang

---

*This README was created for the Sea Ice Extent Gauge project, part of the CASA0019 course at University College London by Group 6, Ice Ice Baby.*
