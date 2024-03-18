# Word Clock

## Overview

This project details the creation of a unique word clock, designed to display the time by illuminating letters in a word-search-esque display. The clock is a combination of hardware and software engineering, enclosed in a 9x9 shadow box frame for ease of manufacturing. 


## Technical Details

### Specs
- **Display Technology**: Each letter is illuminated by a WS2812B individually adressable RGB LEDs. 
- **Microcontroller**: Powered by an STM32F4 High Performance Microcontroller.
- **Real-Time Clock (RTC)**: The RTC logic is managed by the STM32 with the help of a 32.768 kHz external crystal.
- **User Interface**: Features a 4-digit 7-segment display and a pushable rotary encoder for adjusting the time, color, date and more.
- **Power Source**: Operates via a USB-C cable, offering convenience and modernity.
- **Enclosure**: Designed to fit perfectly within a 9x9 shadow box from Michaels, making it easy to integrate into various interior designs.

### Tools
- **Software Environment**: The firmware for the STM32F4 is developed using STM32 Cube IDE, a comprehensive tool for STM32 microcontroller programming.
- **Hardware Enviornment**: All electronic schematics and PCB designs are created in Altium Designer, ensuring professional-grade design quality and ease of manufacturing.

## Assembly and Setup

### Building the Clock

1. **Manufacture the Clock**: The Gerber, Bom, and CPL files are included to be sent to the PCB manufacturer of your choice
2. **Microcontroller Programming**: Microcontroller requires a 6 pin J link adapter to program. See SWD on the board for the programming point
3. **3D Printing**: Some parts must be 3d printed. They can be joined with M6 nuts and bolts.
4. **Letter Mask**: A vector file is provided. These are the letters that I am using for my own needs, although there is a row of letters that can be fully customized for displaying custom text. This file will need to be turned into a vinyl sticker to be applied to the front glass.
5. **Film**: A one-way film can be added to the front of the glass to make the unilluminated letters disappear.
6. **Prepare back panel**: To show the 7 segment display and to allow the rotary encoder and usb-c to stick out the back the back panel will need to be laser cut. I will soon provide the svg file I used for laser cutting.
7. **Assemble**: Layer a 9x9 sheet of diffusion paper, the pcb with the letters facing the glass, and secure the back panel into place. 

### Operation

- **Setting the Time**: Use the dial to navigate through the hours and minutes, pressing it to switch between them. The 7-segment display shows the current setting.
- **Powering the Clock**: Connect the clock to a power source using a USB-C cable. The clock will begin displaying the current time.

This project is licensed under [appropriate license], allowing for personal and commercial use with attribution.

## Contact

For any inquiries, please reach out to [Your Name] at [Your Email].
