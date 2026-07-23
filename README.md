# 🕷️ Spider Horus – Real-Time Industrial Vibration Monitoring System

A real-time industrial vibration monitoring system designed to detect abnormal machine vibrations using an **ESP32** and **MPU6050** accelerometer. The system streams vibration data wirelessly to a Python desktop application through **UDP over Wi-Fi**, where the data is visualized in real time and abnormal vibration events trigger visual and audible alarms.

---

## 📌 Overview

Industrial machines often suffer from excessive vibration before mechanical failures occur. Early vibration detection helps reduce maintenance costs and prevents unexpected downtime.

Spider Horus continuously measures vibration intensity, filters sensor noise, visualizes live data, and alerts the operator whenever the vibration exceeds a predefined safety threshold.

---

## ✨ Features

- 📡 Real-time vibration monitoring
- 📶 Wi-Fi communication using ESP32
- 📤 UDP data transmission
- 📈 Live Python visualization using Matplotlib
- 🚨 Automatic alarm using LED and buzzer
- ⚙️ Auto-calibration at startup
- 🔍 Noise filtering for stable readings
- 📊 Real-time vibration graph
- 🏭 Designed for industrial predictive maintenance applications

---

# 📷 Project Gallery

## Hardware Prototype

![Prototype](images/prototype.jpeg)

---

## Complete Setup

![Setup](images/setup.jpeg)

---

## Circuit Wiring

![Circuit](images/circuit_wiring.png)

---

## Live Vibration Graph

![Graph](images/graph.png)

---

## Second Prototype Version

![Prototype 2](images/prototype1.jpeg)

---

# 🛠 Hardware Components

- ESP32 Development Board
- MPU6050 Accelerometer & Gyroscope
- Active Buzzer
- Red LED
- Breadboard
- Jumper Wires
- Power Supply

---

# 💻 Software Stack

- Arduino IDE
- Python 3
- ESP32 Arduino Framework
- Matplotlib
- Socket Programming
- UDP Communication
- Wi-Fi Networking

---

# 📂 Project Structure

```
Spider-Horus-Vibration-Monitoring
│
├── firmware/
│   └── spider_horus.ino
│
├── python/
│   └── monitor.py
│
├── images/
│   ├── prototype.jpeg
│   ├── prototype1.jpeg
│   ├── setup.jpeg
│   ├── circuit_wiring.png
│   └── graph.png
│
├── docs/
│
├── requirements.txt
├── README.md
└── LICENSE
```

---

# ⚙️ System Workflow

```
MPU6050 Sensor
        │
        ▼
ESP32 reads acceleration
        │
        ▼
Auto Calibration
        │
        ▼
Noise Filtering
        │
        ▼
Wi-Fi UDP Transmission
        │
        ▼
Python Desktop Application
        │
        ▼
Live Graph + Alarm Detection
```

---

# 🚀 Getting Started

## Clone Repository

```bash
git clone https://github.com/Mahmoud20005/Spider-Horus-Vibration-Monitoring.git
```

---

## Install Python Requirements

```bash
pip install -r requirements.txt
```

---

## Upload ESP32 Firmware

1. Open Arduino IDE
2. Install ESP32 Board Package
3. Open `firmware/spider_horus.ino`
4. Configure your Wi-Fi credentials
5. Upload the firmware

---

## Run Desktop Monitor

```bash
python python/monitor.py
```

---

# 📊 Results

The system successfully:

- Streams vibration data over Wi-Fi
- Detects abnormal vibration events
- Displays live vibration intensity
- Generates real-time graphical analysis
- Activates LED and buzzer alarms when the threshold is exceeded

---

# 🔧 Future Improvements

- MQTT Cloud Integration
- Node-RED Dashboard
- Predictive Maintenance using Machine Learning
- Data Logging to Database
- Mobile Application
- FFT Frequency Analysis
- Edge AI Anomaly Detection

---

# 👨‍💻 Author

**Mahmoud Ibrahim**

Mechatronics Engineering Student

Embedded Systems • Industrial IoT • Robotics • Python • ESP32

LinkedIn:
https://www.linkedin.com/in/mahmoud20005

GitHub:
https://github.com/Mahmoud20005

---

## ⭐ If you like this project, don't forget to leave a Star!
