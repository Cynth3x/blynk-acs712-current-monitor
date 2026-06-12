# ⚡ ACS712 & Blynk IoT Smart Current Monitor

An Internet of Things (IoT) project designed to monitor the current consumption and power usage of electrical appliances in real-time, using the **ACS712 Current Sensor** and the **Blynk IoT** platform.

## ✨ Features
* **Real-Time Monitoring:** Track live current (Amperage) via the Blynk mobile app or web dashboard.
* **Power Calculation:** Calculates active power consumption (Watts) based on local voltage supply.
* **Data Visualization:** Built-in charts and historical data tracking through the Blynk interface.
* **Hardware Agnostic:** Fully compatible with popular Wi-Fi microcontrollers like ESP8266 and ESP32.

## 🛠️ Hardware Requirements
* **Microcontroller:** ESP8266 (NodeMCU) or ESP32
* **Sensor:** ACS712 Hall-Effect Current Sensor (5A, 20A, or 30A variant)
* **Other:** Jumper wires, breadboard, and AC/DC load source

## 💻 Setup and Installation

### 1. Blynk Cloud Configuration
* Create a new template on the [Blynk Console](https://blynk.cloud/).
* Configure your Virtual Pins (e.g., `V1` for Current, `V2` for Power).
* Copy your `BLYNK_TEMPLATE_ID` and `BLYNK_TEMPLATE_NAME`.

### 2. Software Setup
* Open the project in **Arduino IDE** or **PlatformIO**.
* Install the required libraries via Library Manager:
  * `Blynk`
  * `Filters` (or any ACS712 library you prefer for RMS calculation)
* Update the credentials in the source code with your Wi-Fi SSID, Password, and Blynk Auth Token.
* Flash the code to your microcontroller.

## 🔌 Circuit Diagram
*(Add your circuit diagram image or schematics here to help other developers)*

## 📜 License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
