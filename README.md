# Word Clock

![Test Bench](/TestBench.jpeg)

## Overview

This project uses a matrix of indiviually controllable letters to spell out time. You can set a custom birthday and anniversary and an entire row of 11 letters is left free for customization. Setting the time, date, color, brightness, and even anniversary / birthdays can be done from the back of the device. Unless you are adding a custom name, no hardcoding is necessary.

## Technical Details

### Specs
- **Display Technology**: Individually addressable WS2812B RGB LEDs illuminate each letter. 
- **Microcontroller**: Driven by the high-performance STM32F4 Microcontroller.
- **Real-Time Clock (RTC)**: The RTC is kept on the STM32 with an external 32.768 kHz crystal for accuracy.
- **User Interface**: A 4-digit 7-segment display coupled with a pushable rotary encoder allows adjustments for time, color, date, etc.
- **Power Source**: Powered through a USB-C cable as this is my favorite cable.
- **Enclosure**: Designed to snugly fit a 9x9 shadow box from Michaels.

### Tools
- **Software Environment**: STM32 Cube IDE
- **Hardware Environment**: Altium Designer

## Assembly and Setup

### Building the Clock

1. **Manufacture the Clock**: You'll find the Gerber, BOM, and CPL files for sending to your preferred PCB manufacturer.
2. **Microcontroller Programming**: A 6 pin J link adapter is necessary for programming the microcontroller. Refer to the SWD on the board for the programming interface.
3. **3D Printing**: Certain components are to be 3D printed and assembled using M6 nuts and bolts.
4. **Letter Mask**: Included is a vector file for the mask — these letters cater to my specific requirements, yet the design permits custom text display through full customization of a row of letters. This design can be sent to a company specializing in making vinyl stickers. This sticker should be applied from the inside of the glass so consider how you will have to (or not have to) mirror your file before sending. This mask can then be applied carefully so each letter is in front of it's respective LED.
5. **Film**: Adding a one-way film to the glass front makes the unlit letters harder to see.
6. **Prepare Back Panel**: To accommodate the 7 segment display, the rotary encoder, and the USB-C, the back panel requires laser cutting. I will provide the SVG file used for this purpose shortly.
7. **Assemble**: Commence with a 9x9 diffusion paper layer, followed by the PCB with letters facing the glass, and finally secure the back panel in place.

![Assembled Clock](/Assembled.jpeg)

### Operation

- **Setting the Time**: Utilize the dial to cycle through hours and minutes, pressing it to alternate between selections. The current setting is displayed on the 7-segment display.
- **Powering the Clock**: Simply connect the clock to a power outlet using a USB-C cable, and it will start showcasing the current time.

## Contact

Should you have any inquiries, feel free to contact me at d.savag1@gmail.com.

This project is duly licensed under GNU General Public License v3.0 to allow both personal and commercial use, provided due attribution is made.
