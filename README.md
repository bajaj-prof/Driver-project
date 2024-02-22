# UART Driver for MSP430 Launchpad

## Overview
This project involves the development of a software suite for embedded systems, focusing on the MSP430 microcontroller. The centerpiece is a Universal Asynchronous Receiver-Transmitter (UART) driver that enables communication between the MSP430 launchpad and a PC terminal. Alongside the UART driver, the project includes an ASSERT function for improved debugging, trace functions for outputting strings, and a custom toolchain setup using the GCC compiler.

**Software Architecture**
![Untitled presentation](https://github.com/bajaj-prof/Driver-project/assets/85208079/0e17f7dc-6a2d-4f24-9824-1c954f261228)


## Features
- **UART Communication**: Establishes serial communication with a PC terminal, allowing for data exchange and debugging information output.
- **Trace Function**: Utilizes the UART driver to print strings, facilitating the monitoring and debugging of the application.
- **ASSERT Function**: A powerful debugging tool that breaks execution and prints the file name and line number where it is called, aiding in faster and more effective debugging.
- **Custom GCC Toolchain**: Tailored development environment setup to meet the specific needs of the project and to gain hands-on experience with embedded toolchain configuration.

## Getting Started
1. Clone the repository to your local machine.
2. Ensure you have the MSP430 toolchain and GCC installed and properly configured.
3. Connect your MSP430 Launchpad to the PC using a USB cable.
4. Compile the project using the provided Makefile.
5. Flash the compiled firmware onto your MSP430 Launchpad.
6. Open a terminal on your PC and connect to the appropriate COM port at 9600 baud rate (or the configured baud rate).

## Usage
- To send data to the PC terminal, use the trace function embedded within your application.
- Implement ASSERT statements in your code to check for conditions and aid in debugging.

**Functional Diagram**
![Untitled presentation (1)](https://github.com/bajaj-prof/Driver-project/assets/85208079/1cbada73-8920-4080-8f5b-a902d2a14b67)
## Development Environment
- MSP430 Launchpad
- Custom GCC toolchain
- PC terminal for output display

## Learning Resources
For those new to embedded system programming or firmware development, check out the excellent video series by Niklas from Artful Bytes: [Embedded System Programming Series](https://lnkd.in/gNQhTkKS).

## Acknowledgments
A special thanks to the open-source community and the creators of the tools used in this project. Your work and dedication make projects like this possible.

## Author
- Vishal



---

**Functional Diagram**
![Untitled presentation (1)](https://github.com/bajaj-prof/Driver-project/assets/85208079/1cbada73-8920-4080-8f5b-a902d2a14b67)


