# IRComputerRemote


## Objective

Control my living room light (IR remote controlled light) using a computer.

Control computer from an IR remote control.

## Electronics

IR receiver: VS1838

IR transmitter: TODO

MCU board: Arduino UNO/NANO

Room light: idual Jedi light

## IDual remote codes

ON: 407F807F

OFF: 407F40BF

Darker: 40708F7

Brighter: 407F906F

## Source Code

Arduino receive computer command via serial interface, and control light bulb via IR led.
Arduino receive IR remote control commands, and control the computer sound volume via serial interface.

#### Arduino

Install Arduino-IRremote library.
https://github.com/z3t0/Arduino-IRremote

#### Computer

