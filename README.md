# Energy Monitoring System

This project is an IoT-based energy monitoring system designed to provide real-time monitoring of electricity consumption.

<p align="center">
  <img src="assets/output_for_electronic_management_system.png" alt="Energy Monitoring System Overview" width="500"/>
</p>

## Project Overview
Manually reading electricity meters is often time-consuming and can lead to inaccuracies in energy usage tracking. This project automates the process by using sensors and IoT technology to monitor energy consumption in real time. The data is displayed on an OLED screen and can be further developed for remote monitoring via mobile applications.

### Components Used
- **NodeMCU ESP32s (ESP32 Wroom 32) MCU Module**
- **SCT-013 Current Sensor** (Non-invasive, 30A AC)
- **ZMPT101B Voltage Sensor Module**
- **1.3 inch I2C OLED Display Module**
- **5V 1A DC Jack Adapter**
- **Resistors** (10K Ohm, 100 Ohm)
- **Electrolytic Capacitor** (10uF, 50V)
- **Breadboard and Jumper Wires**
- Additional Hardware: Breadboard power supply, solderless connectors, 9-watt bulb, holder, and plug

### Features
- **Real-Time Monitoring**: Continuously measures voltage and current to calculate power consumption.
- **OLED Display**: Shows real-time power usage data.
- **Modular Design**: Easily expandable with additional sensors or remote monitoring features (future scope).

### Setup and Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/guruyogendra/Energy-monitoring-system.git
   cd Energy-monitoring-system
