# "Byggern" on Linux

When you work on Linux rather than Windows, you have much more freedom in terms of how you write your code, compile it, and flash it. The flipside of this is that Linux does not "hold your hand" as much as e.g. Atmel Studio does - so starting to use Linux might seem overwhelming at first. Fear not, however; this short document should get you up and running in no time :)

## Set up the toolchain
A toolchain is a set of tools that allow you to compile, assemble, link, and flash your program. It should already be installed on the lab computers, but if you encounter issues, run the following command to install it:

```bash
sudo apt install avr-libc avrdude gcc-avr
```
If you are new to Linux, you can press `Ctrl + Alt + T` on Ubuntu to open a new terminal.

## Connect the ICE debugger
The ICE debugger is the "white box" that you connect by USB to the host computer. The debugger has two additional ports - one marked AVR, and one marked SAM. You will be using the AVR port during this course.

Before you connect the debugger to the ATmega162, you must decide on a protocol to flash the microcontroller with - JTAG or SPI. By default, the supplied *Makefile* uses SPI, but you are free to change this by editing the Makefile, if you prefer JTAG.

Instructions for connecting the debugger to the microcontroller can be found in the ICE Debugger manual (http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-ICE_UserGuide.pdf):
  * See table 3-1 for JTAG connection instructions.
  * See table 3-6 for SPI connection instructions.

## Write code
I will leave this step up to you. When you have something that you want to flash to the ATmega162 - read on ;)
### Notes
On Linux, there is no predefined development environment that you have to use. You are free to select whichever editor that you want. Sublime text, Visual Studio code, and Atom are all good alternatives and are easy to start with.

## Compile and flash
When you have written your code, you can use the supplied Makefile to automatically build the files that you want. This is best described with an example: Suppose I have written some code in, and have the following folder content:
```
.
├── led.c
├── led.h
├── main.c
└── Makefile
```

Both "led.c" and "main.c" are source files - so they will need to be compiled, but "led.h" is just a header file `#include`d by "main.c". To instruct make to build "led.c" and "main.c", we must open up the Makefile. In the top lines, you will see:
```make
# List all source files to be compiled; separate with space
SOURCE_FILES := main.c led.c

# Set this flag to "yes" (no quotes) to use JTAG; otherwise ISP (SPI) is used
PROGRAM_WITH_JTAG := no
```
As the comments in the Makefile describe, we simply write "main.c led.c" after the `SOURCE_FILES :=` declarator to specify our compile files.

If you opted to use JTAG instead of SPI, you would also change `PROGRAM_WITH_JTAG` from "no" to "yes".

### Compile
To compile the code, simply call `make` from the directory that contains your code and Makefile. This will compile and link your code, and you will end up with something that looks like this:
```
.
├── build
│   ├── a.out
│   ├── led.o
│   ├── main.hex
│   └── main.o
├── led.c
├── led.h
├── main.c
└── Makefile

```
As you will see, make creates a directory called "build" and places all the compilation artifacts there. This is simply to keep your code directory clean.

### Flash
To flash the target, simply call `make flash`.

### For the lazy
Actually, calling `make flash` will automatically recompile all your code if it has changed since the last compilation - so this is really the only command you need.

## What can the Makefile do?
The supplied Makefile supports four commands by default, they are:
  * make (no arguments): Compile all code that has changed
  * make flash: Compile code if necessary, then flash to executable to the microcontroller
  * make clean: Purge all compiled artifacts
  * make erase: Kill the contents of the microcontroller

## I found an error, or I can't understand what you mean, Kolbjørn!
Please do not hesitate about asking for help. Linux can be a lot to chew through at first - and my explanations ~~might not be~~ are not perfect. Also keep in mind that this is the first time we are running the lab on Linux, so expect to run into issues that I did not consider. That being said, reach me at kolbjora.austreng(at)ntnu.no, or just go to B445 and knock on my door.
