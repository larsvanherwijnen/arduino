## Week 9 – Gyroscope & WebSerial

## Goal

The goal for this week was to build a Yatzee-like interaction using only a gyroscope sensor and a web interface. The focus was on reading motion data from the gyroscope and sending it to the browser in real time using WebSerial.

---

## Activities

* Connected and tested the gyroscope sensor.
* Read and processed gyroscope values on the Arduino.
* Built a webpage that connects to the Arduino using WebSerial.
* Used the incoming gyroscope data to drive the Yatzee-like interaction in the browser.

---

## Code / Project

This week’s project focused on a minimal but clear setup:

* **Gyroscope Input**: The Arduino continuously reads motion data from the gyro.
* **WebSerial Communication**: Sensor data is sent directly to the browser over WebSerial.
* **Frontend Logic**: The webpage interprets the gyro data and updates the game state.

No WiFi, API calls, or LEDs were used in this project. The emphasis was on reliable sensor input and real-time communication between hardware and the browser.

Project links:

* [Gyroscope Code](./gyro/gyro.ino)
* [Webpage](./yatzee/index.html)

A video demonstrating the working result is included below.

---

## Video

### Gyroscope-controlled Yatzee interaction

<video src="https://github.com/user-attachments/assets/35107e8c-d3ca-4c9e-a286-3d94672abd4f" width="350" controls></video>

---

## Reflection

This week went quite smoothly. I spent most of my time working on the frontend logic and the WebSerial connection. Initially, the WebSerial connection did not work, even after trying different baud rates. Eventually, I discovered that the issue was caused by the Arduino IDE Serial Monitor being open at the same time, which blocked the WebSerial connection. Closing it resolved the problem.

This project helped me better understand how sensor data can be streamed directly from Arduino to a browser and used for interactive applications without relying on networking or cloud services.

---

## Hours Spent

| Week      | Hours    |
| --------- | -------- |
| This week | **6**    |
| Total     | **82.5** |
