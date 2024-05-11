# Design & Implementation of a Small-Scale Capacitive Discharge Spot Welder
### !! Some Foreword !!
- Project is open to improvements (mentioned later)
- Big thanks to our project instructor, [Asst. Prof. Gokhan Dindis](https://avesis.ogu.edu.tr/gdindis/) for all his contribution and guidance along the way.
- Also thanks to VasilKalchev for [LiquidMenu](https://github.com/VasilKalchev/LiquidMenu) library for Arduino. 

## 1. Introduction
- So basically, our project is (was) to design a spot welder for home or small industry usage. If you check the internet for similar devices, you will see thousands of products and projects.
- This project is to make one with spending less than purchasing one, while evaluating and fixing the common design faults on devices that are available online.
- If you have no idea what a capacitive discharge spot welder, or concept of welding in general, go do some lookup online.

## 2. Background
- It usually takes from 40 to 80 mJ of energy to melt down the nickel welding strip into the battery
- Commercially available spot welders generally have setting button to have somewhat degree of control on the device. These settings change the length of the pulse signal.
- ![resim](https://github.com/AlperenYilmz/Senior_Design_Project/assets/99748681/c89d29fe-198c-45c6-b758-2c76fea19531)

  On the figure above, we inspected a sample product we bought online, with 5 different modes. Setting button changes the pulse duration from 3 ms to 16 ms.

## 3. Our Plan
### 3.1 Power Section
- We decided to build the power storage compartment with a capacitor bank formed of 15x10mF 35V rated capacitors, charged up to 12 Volts from an old adapter, thus having a **150 mF** total capacitance with energy stored of **21.6 Joules**.
- It is also fairly important to put a current limiting resistor between capacitor bank and power source, since ESR of the capacitors are 15 times smaller when wired parallel. No resistance in between will cause short circuit and overheating in power source (and even explosion).
- Also, a diode between capacitor bank and power source would be useful to prevent leakage to power source once the capacitor bank is full.

### 3.2 Switching
- For the switching, we decided to use 4xIRFZ48N n-channel mosfets, each for dividing the high discharge current (150 to 600 Amperes) into 4.
- Initially, discharge signal is tought to be supplied with a push button, taken as input to Arduino (mentioned at 3.3).
- When button pushed, Arduino sends a pulse train to the IR2101.
- Since IRFZ48N's are not logic level devices, we also incorporated a mosfet driver, IR2101, to have 5 volts from Arduino and supply 12 volts to mosfet gates. First schematic is as below:
- ![Scheme-it-export-driver-2024-01-18-19-35](https://github.com/AlperenYilmz/Senior_Design_Project/assets/99748681/1d22dcf7-486e-4a13-86c3-01c19563b771)

### 3.3 Control
- Accesibility, feedback, LCD screen and all controls are handled in Arduino UNO.
- There are 2 versions of code: First version has the LCD menu feature. Weld signal is controlled with a push button.
Second version employs a voltage sense logic, determines the potential drop and waits for an adjustable delay, then shoots. Feedback is supported via serial monitor. Some LCD snapshots are below:

![resim](https://github.com/AlperenYilmz/Senior_Design_Project/assets/99748681/b0d34fb5-dc9e-4091-ae62-4607d62aecfa)
![resim](https://github.com/AlperenYilmz/Senior_Design_Project/assets/99748681/57d12a11-15c2-4e77-bdc1-5e06f7ceb60f)


## 4. Revisions
- We scrapped the first version due to the lack of ability to control. Schematic for second version is below:
- ![final_schematic](https://github.com/AlperenYilmz/Senior_Design_Project/assets/99748681/c934a258-0db9-4b7a-a95f-ff40ce51fddf)

## 5. Conclusion and possible tweaks
### 5.1 Faults
- Due to the immediate, high-current switching, there is a large inductive voltage spike happening at mosfet gates, which results in burning of the IR2101 mosfet driver. Oscilloscope snapshots of these spikes are below:
![resim](https://github.com/AlperenYilmz/Senior_Design_Project/assets/99748681/fc7b8328-f1ec-435d-9d41-314bbf70cf31)
- These spikes rate up to 20 to 30 volts, which is enough to roast the driver high-side output pin.
- Most logical and economic solution for this problem is isolating the mosfets with a optocoupler.

### 5.2 Photos
![WhatsApp Image 2024-01-21 at 21 21 52](https://github.com/AlperenYilmz/Senior_Design_Project/assets/99748681/8ae46ffb-e447-435b-a5fe-8fa31d203e15)
![WhatsApp Image 2024-01-21 at 21 21 59](https://github.com/AlperenYilmz/Senior_Design_Project/assets/99748681/bb3164d5-00e4-4b0c-b8cb-bbd152a5dd9a)
