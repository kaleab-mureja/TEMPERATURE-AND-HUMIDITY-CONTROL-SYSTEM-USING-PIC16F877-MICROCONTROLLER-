# TEMPERATURE-AND-HUMIDITY-CONTROL-SYSTEM-USING-PIC16F877-MICROCONTROLLER-

# Temperature and Humidity Control System using PIC16F877 Microcontroller

A compact, energy-efficient, and adaptable microcontroller-based system designed for real-time monitoring and display of environmental temperature and humidity.

## Table of Contents
- [Project Overview](#project-overview)
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Circuit Diagram](#circuit-diagram)
- [Setup and Wiring](#setup-and-wiring)
- [Flashing the Microcontroller](#flashing-the-microcontroller)
- [Usage](#usage)
- [Code Structure](#code-structure)
- [Future Enhancements](#future-enhancements)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgments](#acknowledgments)

## Project Overview

This project implements a precise environmental monitoring system using the PIC16F877 microcontroller. It interfaces with a DHT11 sensor to acquire temperature and humidity data and displays this information on an LM046L Liquid Crystal Display (LCD). The system aims to provide a robust and user-friendly solution, offering a modern alternative to traditional analog systems that are often bulky and less flexible.

## Features

* **Real-time Monitoring:** Continuously displays current temperature and humidity.
* **Sensor Interface:** Utilizes the DHT11 digital temperature and humidity sensor.
* **LCD Output:** Presents data clearly on an LM046L LCD.
* **Microcontroller Core:** Powered by the reliable PIC16F877 microcontroller.
* **Compact Design:** Built for efficiency and adaptability.
* **Error Handling:** Includes basic checksum error detection for DHT11 readings.

## Hardware Requirements

To build and run this project, you will need the following components:

* **Microcontroller:** PIC16F877A
* **Temperature & Humidity Sensor:** DHT11
* **Liquid Crystal Display (LCD):** LM046L (commonly 16x2 or 20x4 character LCD)
* **Crystal Oscillator:** 8 MHz
* **Capacitors:** 2 x 22pF (for crystal)
* **Resistors:**
    * 330 Ohm (for LCD backlight/current limiting, if required by your specific LCD)
    * 4.7 kOhm (pull-up for DHT11 data line)
* **Breadboard / PCB**
* **Connecting Wires**
* **Power Supply:** 5V DC

## Software Requirements

* **IDE:** MPLAB X IDE (or equivalent PIC development environment)
* **Compiler:** XC8 Compiler (or compatible C compiler for PIC microcontrollers)
* **Simulation Software (Optional):** Proteus 8.14 (or similar for circuit simulation)

## Circuit Diagram

(You should ideally include an image of your circuit diagram here, e.g., `circuit_diagram.png`)

Alternatively, describe the connections:
* **PIC16F877A Connections:**
    * VCC and GND connected to 5V power supply.
    * MCLR pin (Pin 1) connected to VCC through a pull-up resistor (e.g., 10kOhm) or dedicated reset circuit.
    * RA0 connected to DHT11 Data Pin.
    * RB0, RB1, RB2 connected to LCD Data pins D4, D5, D6.
    * RB3, RB4, RB5 connected to LCD Data pins D7, RS, E.
    * RC0 connected to LCD Data pin D0. (Note: The provided code uses RB0-RB5 for LCD, but implies 8-bit mode in some functions. Verify your exact LCD connection from your final circuit.)
    * RC1 connected to LCD Data pin D1.
    * RC2 connected to LCD Data pin D2.
    * RC3 connected to LCD Data pin D3.
    * Oscillator pins OSC1, OSC2 connected to 8MHz crystal and 22pF capacitors to ground.
* **DHT11 Sensor Connections:**
    * VCC connected to 5V.
    * GND connected to Ground.
    * Data pin connected to PIC16F877A's RA0 with a 4.7kOhm pull-up resistor to VCC.
* **LM046L LCD Connections:**
    * VSS to Ground, VDD to 5V.
    * VO (contrast) to potentiometer or suitable voltage divider.
    * RS (Register Select) to PIC pin (e.g., RB5).
    * RW (Read/Write) to Ground.
    * E (Enable) to PIC pin (e.g., RB4).
    * D4-D7 (Data pins) to PIC pins (e.g., RB0-RB3 or similar, as per your code's configuration).
    * A (LED Anode) to 5V through 330 Ohm resistor (if applicable).
    * K (LED Cathode) to Ground.

## Setup and Wiring

1.  Assemble the components on a breadboard or custom PCB according to the circuit diagram.
2.  Ensure all power and ground connections are secure.
3.  Double-check the data line connections for the DHT11 and LCD to the PIC microcontroller.

## Flashing the Microcontroller

1.  Open the project in MPLAB X IDE.
2.  Build the project to generate the `.hex` file.
3.  Connect your PIC programmer (e.g., PICkit 3, PICkit 4) to your computer and the PIC16F877A microcontroller.
4.  Use the programmer software (e.g., MPLAB IPE) to load the generated `.hex` file onto the PIC16F877A.

## Usage

Once the microcontroller is programmed and the circuit is powered on, the system will immediately start monitoring.
* The LM046L LCD will display the current temperature (in Celsius) and humidity (in percentage).
* If a checksum error occurs during DHT11 reading, an "Check sum error" message will be displayed.

## Code Structure

The core logic resides primarily in a `main.c` file. This file contains:

* **Initialization routines:** For PIC ports, LCD, and DHT11.
* **DHT11 communication protocol:** Functions to send commands and read data from the sensor.
* **Data parsing and validation:** Logic to extract temperature and humidity and perform checksum verification.
* **LCD display functions:** To format and show data on the LCD.
* **Main loop:** Continuously reads sensor data and updates the display.

(You might list other `.h` or `.c` files if your project is structured into multiple files.)

## Future Enhancements

* **Active Control Mechanisms:** Implement logic to control external devices (e.g., fans, heaters, humidifiers) based on predefined temperature and humidity thresholds. The software architecture already includes commented-out logic for this.
* **Data Logging:** Add functionality to store historical sensor data (e.g., to an SD card or EEPROM).
* **User Interface Improvements:** Add buttons for settings or mode changes.
* **Wireless Connectivity:** Integrate Wi-Fi (e.g., ESP8266) or Bluetooth modules for remote monitoring.
* **Calibration:** Implement a calibration routine for sensor accuracy.
* **Power Optimization:** Further optimize code and hardware for lower power consumption.

## Contributing

Contributions are welcome! If you have suggestions for improvements, new features, or bug fixes, please open an issue or submit a pull request.

## License

This project is open-source and available under the [Choose a License, e.g., MIT License, Apache 2.0 License, etc.]. See the `LICENSE` file for more details.

## Acknowledgments

* Addis Ababa Science and Technology University for resources.

---
*README.md generated by Kaleab Mureja*
