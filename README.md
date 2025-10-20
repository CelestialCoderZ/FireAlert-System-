# 🔥 Flame Detection System with ST7789V LCD


A sophisticated flame detection system built with Arduino Uno, featuring real-time monitoring on a 2-inch ST7789V TFT LCD display with visual LED alerts.

## 🚀 Features

- **Real-time Flame Detection** using IR flame sensor
- **ST7789V TFT LCD Interface** with color-coded status display
- **Audible Buzzer Alerts** - Loud audible warnings for immediate attention
- **Serial Monitor Integration** for calibration and debugging
- **Threshold-based Detection** with customizable sensitivity
- **Professional GUI** with sensor values and status indicators

## 🛠️ Hardware Components

| Component | Specification |
|-----------|---------------|
| Microcontroller | Arduino Uno |
| Display | ST7789V 2-inch TFT LCD (240x320) |
| Sensor | IR Flame Sensor Module |
| Alert System | Buzzer (Active/Passive) |
| Power | 5V DC via USB or external supply |

## 📋 Project Specifications

- **Detection Method**: Infrared (IR) spectrum analysis
- **Response Time**: < 1 second
- **Display**: Real-time sensor values and system status
- **Alert Types**: Visual (LED blinking + LCD color changes)
- **Calibration**: Software-based threshold adjustment
- **Communication**: Serial monitor for system control

## 🎯 Applications

- **Home Safety** - Early fire detection in households
- **Laboratory Use** - Monitoring flammable experiments
- **Industrial Safety** - Machinery overheating detection
- **Educational Purpose** - Embedded systems learning
- **IoT Integration** - Can be extended with cloud connectivity

## 🔌 Circuit Connection


| ST7789V TFT LCD | ARDUINO UNO |
|-----------|---------------|
| VCC | 5V |
| GND | GND |
| SCL | D13 |
| SDA | D11 |
| RES | D8 |
| DC | D9 |
| CS | D10 |
| BL | 3.3V |

| IR FLAME SENSOR | ARDUINO UNO |
|-----------|---------------|
| VCC | 5V |
| GND | GND |
| A0 | A0 |

| BUZZER | ARDUINO UNO |
|-----------|---------------|
| + | D7 |
| - | GND |

## ⚡ Quick Start
    1. Clone the repository:
       git clone https://github.com/yourusername/FireAlert-System.git
       cd FireAlert-System

    2. Library Dependencies:
       Install via Arduino Library Manager:
            (i)  Adafruit ST7789 Library
            (ii) Adafruit GFX Library

    3. Upload Code:
        (i)   Open src/firealert_system.ino in Arduino IDE
        (ii)  Select Board: Arduino Uno
        (iii) Select Port: Appropriate COM port
        (iv)  Click Upload

    4. Calibration:
       - Open Serial Monitor (9600 baud)
       - Type 'c' for calibration mode
       - Adjust threshold in code:
             | int flameThreshold = 500; |  (Change this value)
    
## 🙏 Acknowledgments
     
- Adafruit Industries for ST7789 library
- Arduino community for continuous support
- Open-source hardware and software contributors


## Contact Me
If you have any questions, suggestions, or feedback, feel free to reach out:

 - Name: Anuprabha Bag
 - Email: [anuprabhabag2004ind@gmail.com]
 - LinkedIn: [linkedin.com/in/yourprofile](https://www.linkedin.com/in/anuprabha-bag-b98359260/)  
 - GitHub: [github.com/yourusername](https://github.com/CelestialCoderZ)  
💡 I’d love to connect and collaborate on exciting projects!


