# STM32 OTA Firmware Update System with TFT Menu

📌 Overview
-----------------------------------------------------------------------------------------------------------------------------
This project implements a Firmware Over-The-Air (OTA) update system for an STM32 microcontroller, combined with a graphical TFT menu interface for running various applications.

It allows uploading new firmware via a web interface, transmitting it wirelessly through an ESP Wi-Fi module, and finally programming it onto the STM32.

The TFT menu provides access to interactive apps such as:

Digital counter (count up/down)

LED matrix shape display

Buzzer control

🚀 System Workflow
-----------------------------------------------------------------------------------------------------------------------------
Web Interface

Built using HTML & JSON.

User uploads the firmware (.hex) file.

The interface is connected to Node-RED for backend processing.

Node-RED Backend

Handles file reception and parsing.

Sends the file line-by-line to the ESP Wi-Fi module.

Implements ACK/NACK with timeout to ensure reliable transmission.

ESP Wi-Fi Module

Receives firmware from Node-RED.

Sends data to the STM32 via UART.

Retransmits any line upon NACK or timeout.

STM32 MCU

Receives firmware lines via UART.

(Planned) Bootloader will take parsed firmware bytes and program them into Flash memory.

Runs the TFT menu system for application selection.

🖥️ TFT Menu Features
-----------------------------------------------------------------------------------------------------------------------------

The STM32 firmware includes a menu-driven interface allowing the user to:

Select “Application” mode to run different apps.

Choose “Update” mode to initiate OTA update process.

Exit or return to main menu.

Available Applications:

Counter App – count up or down.

LED Matrix App – display various shapes.

Buzzer App – turn buzzer on/off.

🔧 Hardware Used
-----------------------------------------------------------------------------------------------------------------------------

STM32F4 Series MCU

ESP Wi-Fi Module

TFT LCD Display

LED Matrix

Passive Buzzer

Push buttons for navigation
