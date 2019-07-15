# fire-detector
Goal of this project was to develop a simple prototype which is working smoothly!
Used HW: Arduino Uno, Microphone sensor KY-038, RGB, Vibration Motor, Joystick
Prototype realizes the following uses cases: Microphone sensor recognizes and differentiates three acoustic sounds: standard fire alarm, # doorbell and random environmental noises.

Output:
- In case of fire -> red RGB + constant vibration -> press joystick required to stop vibration and set RGB back to white
- In case of doorbell -> green LED + 3x vibration -> RGB is set back to white
- nothing is happening -> LED is white and nothing is happening

Further development including an SIM shield will be committed soon.
How? Using a DC/DC Converter, SIM800L, Prepaid Sim Card to send an sms to any phone number in case of a fire alarm
