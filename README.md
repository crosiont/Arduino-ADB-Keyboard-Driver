# Arduino-ADB-Keyboard-Driver
This is a (currently) non-working ADB to Arduino interface, used for getting input in Arduino projects. 
Some help would be appreciated in debugging and fixing the timing protocol, which I think is causing the issues. 

#IMPORTANT
An ADB plug has 4 pin holes, with a rectangular slot. If the slot is at the top of the plug, the pins go from left to right starting with the top row: GND, VCC +5v, then PSW (the power switch that tells the computer to turn on. it can be ignored in this setup), and DATA. The DATA line needs to have a 1k pullup resistor. The ADB communication protocol does not use a clock signal, so timeing is very important. The length of the low and high bits are what determine 1's and 0's. Here is a link to a website with more info: https://developer.apple.com/library/archive/documentation/mac/pdf/Devices/ADB_Manager.pdf Another: 
https://wiki.retrotechcollection.com/Apple_Desktop_Bus
