# Problem 1

### Goal : Write code for MPC4922 12-bit DAC module using Shunya Interfaces on Raspberry Pi 4

### Description

Convert Arduino API's into Shunya Interfaces API's for MPC4922 DAC Arduino library. 
Write code to interface MPC4922 DAC with RPI 4 over I2C and generate 0-5V output when given 
respective 12-bit Input.

Please use Arduino MPC4922 library as reference. 

- [MPC4922 Arduino library](https://github.com/michd/Arduino-MCP492X)


### For Example: 

Lets say 
#### Given (Input)
that the  MPC4922 module is connected to the RPI4 using I2C, the example code when run
#### Then (output)
should loop and generate 0-5V with 0.02 V steps and a delay of 100 ms between
each loop iteration.


### Acceptance Criteria 
This is the criteria to accept the assignment.
- The code must be divided into functions 
- **Must** have documentation for using the program.
- Code **Must** follow the Coding Standards.
- Code must be in C.
- Code must be compiled in the Shunya OS docker container.

#### Note: Documentation of the whole program is a must criteria for the completion of the Assignment.