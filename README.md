# Design & Implementation of a Small-Scale Capacitive Discharge Spot Welder
### !! Some Foreword !!
- Project is open to improvements (mentioned later)

## 1. Introduction
- So basically, my project is (was) to design a spot welder for home or small industry usage. If you check the internet for similar devices, you will see thousands of products and projects.
- This project is to make one with spending less than purchasing one, while evaluating and fixing the common design faults on devices that are available online.
- If you have no idea what a capacitive discharge spot welder, or concept of welding in general, go do some lookup online.

## 2. Background
- It usually takes from 40 to 80 mJ of energy to melt down the nickel welding strip into the battery
- Commercially available spot welders generally have setting button to have somewhat degree of control on the device. These settings change the length of the pulse signal.
- ![resim](https://github.com/AlperenYilmz/Senior_Design_Project/assets/99748681/c89d29fe-198c-45c6-b758-2c76fea19531)

  On the figure above, we inspected a sample product we bought online, with 5 different modes. Setting button changes the pulse duration from 3 ms to 16 ms.

## 3. Our Plan
### 3.1 Power Section
- We decided to build the power storage compartment with a capacitor bank formed of 15x10mF 35V rated capacitors, charged up to 12 Volts from an old adapter, thus having a 150 mF total capacitance with energy stored of 21.6 Joules.
- It is also fairly important to put a current limiting resistor between capacitor bank and power source, since ESR of the capacitors are 15 times smaller when wired parallel. No resistance in between will cause short circuit and overheating in power source (and even explosion).

### 3.2 Switching
