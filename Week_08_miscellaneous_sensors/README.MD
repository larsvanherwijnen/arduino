
## Week 4 – Sensor Exploration

## Goal

The goal for this week was to experiment with different types of sensors and actuators and to understand how they fall into different categories. The focus was on building several small, isolated projects to learn how each component works individually and how hardware choices affect the final result.

---

## Activities

### Ultrasonic Distance Sensor

I started with a distance sensor, also known as an ultrasonic sensor (HC-SR04). This sensor works by sending out an ultrasonic sound pulse and measuring the time it takes for the echo to return. Based on this time difference, the distance to an object can be calculated.

To get started, I followed this guide:
https://projecthub.arduino.cc/Isaac100/getting-started-with-the-hc-sr04-ultrasonic-sensor-7cabe1

After getting the basic distance readings working, I expanded the project by:

- Adding a buzzer that reacts to distance
- Displaying the measured distance on a screen

---

### LDR (Light Dependent Resistor)

Next, I worked with an LDR (Light Dependent Resistor). This sensor changes its resistance based on the amount of light it receives and is commonly used in applications such as automatic night lights.

Although the code itself was relatively simple, this sensor took the longest to get working. The analog readings constantly returned values close to 1023, which represents the maximum value of the Arduino’s 10-bit ADC (analog-to-digital converter). This indicated that the sensor was always reading a very high voltage.

Both a project member and I initially could not determine the cause. Eventually, I discovered that the issue was related to the wiring configuration. After changing the wiring and moving away from the original diagram, the sensor started working as expected.

Initially, I followed this tutorial, which did not work in my setup:
https://projecthub.arduino.cc/electronicsfan123/interfacing-arduino-uno-with-ldr-61f455

---

### Force Sensor

After that, I experimented with a force-sensitive resistor (FSR). The goal was to visualize the applied pressure on a screen.

While testing, the sensor consistently showed values around 1% and I never got it to exceeded 96%. The 1% should actually be 0 when not touching but i wasn't able to figure that out, it mostly due to having the wrong resistor value. I also implemented a progress bar on the screen that visually represented the applied force based on the measured percentage. 

---

### Servo Motor

Finally, I worked with a servo motor. The servo was programmed to rotate left or right based on a button press. This was super easy to get working.

---

## Code / Project

- [Distance sensor](./distance_sensor/distance_sensor.ino)
- [LDR](./ldr_sensor/ldr_sensor.ino)
- [Force sensor](./force_sensor/forcesensor.ino)
- [Servo motor](./servo/servo.ino)

Videos demonstrating the results are included below.

---

## Distance sensor analog
<video src="https://github.com/user-attachments/assets/ae10fd38-b17d-46c9-98be-c5a1bef9813e
" width="350" controls></video>

## Distance sensor with lights and zoomer
<video src="https://github.com/user-attachments/assets/e151df32-4172-48bf-8083-9b1b869b4a07" width="350" controls></video>


## Distance sensor analog
<video src="https://github.com/user-attachments/assets/e8e5b4bd-7a18-411a-b0b2-6ee88eda1e45" width="350" controls></video>

## Force sensor
<video src="https://github.com/user-attachments/assets/38d9417a-8f07-4e69-99d7-0e85106509f1
" width="350" controls></video>

## LDR
<video src="https://github.com/user-attachments/assets/4e2a901c-7d9d-4f99-96fa-58fcba5365d0" width="350" controls></video>


## Distance sensor analog
<video src="https://github.com/user-attachments/assets/fea9c4c1-7e60-4773-a1f4-c6f5777e388b" width="350" controls></video>

---

## Reflection

I really enjoyed experimenting with different types of sensors and exploring how they could be applied in various products. One important takeaway from this week is that the main challenge when working with Arduino is often not the programming itself, which is usually quite straightforward, but the electronics and wiring.

Debugging hardware issues such as incorrect wiring or unexpected sensor values was challenging but also the most enjoyable part of the process. It reinforced my interest in understanding how physical components behave and interact.

---

## Hours Spent

| Week      | Hours |
|-----------|-------|
| This week | **8** |
| Total     | **76.5** |

