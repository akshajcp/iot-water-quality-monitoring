# IoT Water Quality Monitoring System (ESP32 + Blynk)

## Overview
This project implements a real-time water quality monitoring system using ESP32 and multiple sensors. It measures temperature, turbidity, and TDS levels and provides alerts when values exceed safe thresholds. The system also integrates with the Blynk platform for remote monitoring.

## Problem Statement
Maintaining optimal water quality is critical in aquaculture and environmental monitoring. Manual checking is inefficient and delayed, which can lead to poor water conditions and potential losses.

## Objective
To design a low-cost embedded IoT system that continuously monitors water parameters and alerts users in real time.

## Components Used
- ESP32 (WiFi-enabled microcontroller)
- Temperature Sensor (DS18B20)
- Turbidity Sensor
- TDS Sensor
- OLED Display (SSD1306)
- Buzzer
- LED

## Features
- Real-time monitoring of water parameters  
- WiFi-based remote monitoring using Blynk  
- OLED display for local data visualization  
- Threshold-based alert system (LED + buzzer)  
- Continuous data acquisition  

## System Architecture
Sensors → ESP32 → Data Processing →  
→ OLED Display (local monitoring)  
→ Blynk App (remote monitoring)  
→ Alert System (LED + Buzzer)

## IoT Integration
The system uses ESP32 WiFi capabilities to send sensor data to the Blynk cloud platform. Users can monitor real-time data remotely through the Blynk mobile application.

## Working Principle
- Sensors collect environmental data (temperature, turbidity, TDS)  
- ESP32 processes sensor readings  
- If values exceed safe thresholds, alerts are triggered  
- Data is displayed locally on OLED and sent to Blynk app  

## Results
- Successfully implemented real-time monitoring system  
- Achieved stable sensor integration  
- Implemented remote monitoring and alert system  

## Note
Currently, pH value is set as a placeholder in the code and can be replaced with an actual pH sensor in future improvements.

## Future Improvements
- Integration of pH sensor  
- Cloud data logging and analytics  
- Mobile app enhancements  
- Wireless sensor expansion  

## Author
Akshaj C P  
B.Tech ECE Student  
