# Word Clock

## Overview

This project unveils the design and assembly of a distinctive word clock, configured to exhibit time by lighting up letters in a puzzle-like display. A fusion of hardware and software engineering encapsulated in a 9x9 shadow box frame enhances manufacturability. 

## Technical Details

### Specs
- **Display Technology**: Individually addressable WS2812B RGB LEDs illuminate each letter. 
- **Microcontroller**: Driven by the high-performance STM32F4 Microcontroller.
- **Real-Time Clock (RTC)**: STM32 employs a 32.768 kHz external crystal to fine-tune the RTC mechanics.
- **User Interface**: A 4-digit 7-segment display coupled with a pushable rotary encoder allows adjustments for time, color, date, etc.
- **Power Source**: Powered through a USB-C cable, this design merges convenience with modern trends.
- **Enclosure**: Tailored to snugly fit a 9x9 shadow box from Michaels, facilitating seamless integration into diverse decor styles.

### Tools
- **Software Environment**: Leveraging STM32 Cube IDE for the firmware development, this tool stands out for programming STM32 microcontrollers.
- **Hardware Environment**: Altium Designer was employed for all electronic schematics and PCB layouts, guaranteeing top-tier design quality and manufacturability.

## Assembly and Setup

### Building the Clock

1. **Manufacture the Clock**: You'll find the Gerber, BOM, and CPL files for sending to your preferred PCB manufacturer.
2. **Microcontroller Programming**: A 6 pin J link adapter is necessary for programming the microcontroller. Refer to the SWD on the board for the programming interface.
3. **3D Printing**: Certain components are to be 3D printed and assembled using M6 nuts and bolts.
4. **Letter Mask**: Included is a vector file for the mask — these letters cater to my specific requirements, yet the design permits custom text display through full customization of a row of letters. This design needs conversion into a vinyl sticker for the front glass application.
5. **Film**: Adding a one-way film to the glass front makes the unlit letters vanish from sight.
6. **Prepare Back Panel**: To accommodate the 7 segment display, the rotary encoder, and the USB-C, the back panel requires laser cutting. I will provide the SVG file used for this purpose shortly.
7. **Assemble**: Commence with a 9x9 diffusion paper layer, followed by the PCB with letters facing the glass, and finally secure the back panel in place.

### Operation

- **Setting the Time**: Utilize the dial to cycle through hours and minutes, pressing it to alternate between selections. The current setting is displayed on the 7-segment display.
- **Powering the Clock**: Simply connect the clock to a power outlet using a USB-C cable, and it will start showcasing the current time.

This project is duly licensed under GNU General Public License v3.0 to allow both personal and commercial use, provided due attribution is made.

## Contact

Should you have any inquiries, feel free to contact me at d.savag1@gmail.com.
