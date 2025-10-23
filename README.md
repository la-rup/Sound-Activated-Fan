# Sound-Activated-Fan

## Elevator Pitch
On blistering summer days, the last thing you should have to do is over-exert yourself just to turn on a fan. With this handheld sound-activated fan system, all you need to do is snap your fingers and cool air comes your way! This ‘cool’ product features a fan powered by a DC brushed motor, a sound sensor, and an LED that visually indicates sound intensity and fan speed.

## Components Used
| Component | Description | 
| :--- | :--- | 
| LM393 Sound Sensor Module | Captures sound and converts it into voltage signals | 
| Brushed DC Motor | Drives the fan | 
| Red LED + 220Ω Resistor | Indicates sound intensity and fan speed visually | 
| Power Supply Module | Powers the motor and sensor system | 

These components were selected to meet the functional requirements of a responsive, sound-triggered fan. The brushed motor is ideal for simple driven functions, while the LM393 module reliably detects sound levels. The LED adds a layer of user feedback by reflecting system state.

## Signal Conditioning
To reduce noise and improve system reliability, a Simple Moving Average (SMA) filter was implemented. This filter smooths out short-term fluctuations in the sound signal, preventing erratic behavior and ensuring that only sustained sound levels trigger the fan.

SMA Benefits:
- Reduces high-frequency noise
- Stabilizes voltage threshold
- Improves activation consistency

## System Behavior
The system operates in three distinct states based on sound intensity:
- State 0: Fan off, LED off
- State 1: Fan at half speed, LED at half brightness
- State 2: Fan at full speed, LED at full brightness
  
These states are displayed via the serial monitor and visually represented by the LED.

## Challenges & Solutions

#### Problem: Sensor Sensitivity
Despite debouncing code, the sound sensor often picked up multiple states in rapid succession, causing inconsistent fan behavior.

#### Solution:
- Introduced a cooldown period of 500 milliseconds to prevent rapid state switching
- Implemented a toggle mechanism to maintain state stability until cooldown expires

<!--## How to Use
- Connect the LM393 sensor, DC motor, LED, and power supply as per the schematic.
- Upload the Arduino sketch to your microcontroller.
- Power the system and give a snap to watch the fan respond!-->

## Notes
- Adjust the SMA window size for different environments.
- Cooldown time can be tuned for responsiveness vs. stability.
- Ensure proper power ratings for motor and LED components.
