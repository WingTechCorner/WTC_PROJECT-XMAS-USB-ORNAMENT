# Wing's XMAS Ornament

* Something for the holidays.
* Made using SMT/SMD components so most/all parts on one side.
* Added header pins on revrse side for adding batteries or different UART(s).
* Added USB-A PCB top to allow plugging into a laptop or computer USB port or to power with a USB-A extension cable.

# Components

* CH340G USB-to-TTL interface chip
* AMS1117-3v3 linear voltage regulator
* QMA7981 IMU in I2C mode
* STM32F030F4 - Arm M0 MCU

# STM32 Pinouts Used

## I2C 

* PA9  - I2C SCL (connects to QMA7981's SCL)
* PA10 - I2C SDA (connects to QMA7981's SDX)

## UART

* PA2  - UART-TX (connects to CH340G's RX)
* PA3  - UART-RD (connects to CH340G's TX)

## LED Driving Lines

* PA0  - A (CharliePlexed LED Lines)
* PA1  - B (CharliePlexed LED Lines)
* PA4  - C (CharliePlexed LED Lines)
* PA5  - D (CharliePlexed LED Lines)
* PA6  - E (CharliePlexed LED Lines)
* PA7  - F (CharliePlexed LED Lines)
* PA13 - G (CharliePlexed LED Lines)
* PA14 - H (CharliePlexed LED Lines)
