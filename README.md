# STM32 OTA Firmware Update System with TFT Menu

📌 Overview
-----------------------------------------------------------------------------------------------------------------------------
This project implements a Firmware Over-The-Air (OTA) update system for an STM32 microcontroller, combined with a graphical TFT menu interface for running various applications.

It enables:

- 📤 Uploading new firmware via a web interface

- 📡 Transmitting it wirelessly through an ESP Wi-Fi module

- 💾 Programming it into the STM32 Flash (via bootloader)

The TFT menu provides access to interactive apps such as:

- 🔢 Digital counter (count up/down)

- 🟩 LED matrix shape display

- 🎵 Buzzer control

🚀 System Workflow
-----------------------------------------------------------------------------------------------------------------------------
## 🌐 Web Interface

- 🖋 Built using HTML & JSON

- 📂 Allows user to upload .hex firmware file

- 🔗 Integrated with Node-RED for backend processing

## 🖧 Node-RED Backend
- 📥 Handles file reception and parsing

- 📤 Sends firmware line-by-line to the ESP Wi-Fi module

- ✅ Implements ACK/NACK with timeout for reliability

## 📶 ESP Wi-Fi Module
- 📡 Receives firmware from Node-RED

- 🔌 Sends data to STM32 via UART

- 🔁 Retransmits lines upon NACK or timeout

## 🔲 STM32 MCU
- 📥 Receives firmware lines via UART

- 🗃 Parsing is already implemented — firmware is stored as bytes

- 🛠 (Planned) Bootloader will write parsed bytes into Flash memory

- 🖥 Runs TFT menu for selecting applications

🖥️ TFT Menu Features
-----------------------------------------------------------------------------------------------------------------------------

## The STM32 firmware includes a menu-driven interface allowing the user to:

- 🎯 Select Application Mode to run apps

- 📡 Choose Update Mode to initiate OTA update process

- ↩ Exit or return to main menu

## Available Applications:
- 🔢 Counter App – count up or down

- 🟩 LED Matrix App – display various shapes

- 🎵 Buzzer App – turn buzzer on/off

🔧 Hardware Used
-----------------------------------------------------------------------------------------------------------------------------

- 🖥 STM32F4 Series MCU

- 📶 ESP Wi-Fi Module

- 🖼 TFT LCD Display

- 🟩 LED Matrix

- 🎵 Passive Buzzer

- 🔘 Push buttons for navigation

📍 Project Status
-----------------------------------------------------------------------------------------------------------------------------

- ✅ Website upload & transfer to ESP complete
  
- ✅ ESP ↔ STM32 UART communication with ACK/NACK & retry done
  
- ✅ TFT menu system functional
  
- ✅ Firmware parsing implemented on STM32
  
- 🟡 Bootloader pending — will take parsed bytes and write to Flash

