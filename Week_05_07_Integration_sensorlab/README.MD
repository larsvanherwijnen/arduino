## Week 5 through 7 – Integration Sensorlab Project

## Goal

The goal for these three weeks was to apply the knowledge gained during the first four weeks to build a fully integrated system connected to the Sensorlab project backend. This system consists of:

* An MQTT data stream
* A web portal for configuration
* Multiple Arduino-based tasks working together as part of a single interactive installation

The objective was to create a modular, scalable setup where multiple Arduino devices collaborate to represent a cloud object with different behaviors.

---

## Activities

### MQTT Proof of Concept

I started this period by creating a proof-of-concept MQTT stream. Similar to my earlier API tests, I sent random RGB values through MQTT messages. These values were received by an Arduino and used to update the colors of a NeoPixel LED strip.

Unfortunately, I forgot to record a video of this specific MQTT test. To still demonstrate the result, I included a video from week 4 that shows the same visual behavior.

---

### Web Configuration Interface

After validating the MQTT communication, I started working on a web interface that allows users to configure the WiFi network of the Arduino devices. During this phase, I refactored my Arduino code by separating it into `.cpp` and `.h` files. This significantly improved readability and maintainability compared to a single large `.ino` file.

I also learned how to persist configuration data on the Arduino using EEPROM storage. This allowed WiFi credentials and configuration settings to remain available after power cycles. I followed the official Arduino EEPROM guide:
[https://docs.arduino.cc/learn/programming/eeprom-guide/](https://docs.arduino.cc/learn/programming/eeprom-guide/)

---

### Room and Job Configuration

Next, I implemented a webpage where users can assign a room and a specific job to each Arduino device. The building contains multiple rooms, which are retrieved dynamically from the backend API. On this page, users can:

* Select the room in which the cloud object is located
* Assign a specific task (job) to each Arduino

Each Arduino performs a dedicated role, such as:

* Controlling NeoPixel LEDs
* Displaying cloud emotions
* Printing or forwarding tasks to other devices

This approach allowed the system to scale across multiple devices while keeping responsibilities clearly separated.

---

### Software Architecture Improvements

To keep the codebase clean and extensible, I experimented with organizing jobs into subfolders and implementing design patterns. While I was not able to fully integrate subfolders for Arduino jobs, I successfully implemented the **Strategy Pattern**.

This allowed different Arduino behaviors to be swapped dynamically based on configuration, without duplicating large amounts of code. Although I initially aimed for a factory pattern, the strategy-based approach proved to be more practical within the constraints of the Arduino environment.

---

### OLED Display Integration

Finally, I integrated a 0.96-inch OLED display into the system. The display provides real-time feedback by showing:

* The current configuration
* The operational mode of the Arduino

The device can operate in two modes:

1. **Access Point Mode** – Used to configure WiFi credentials
2. **WiFi Connected Mode** – Normal operation with backend connectivity

This visual feedback made debugging and deployment significantly easier.

---

## Code / Project

This phase of the project focused on combining:

* WiFi communication
* JSON parsing
* MQTT and HTTP data handling
* NeoPixel LED control

Instead of relying on user input, the Arduino periodically requests a random RGB value from my API and applies it to the LEDs. This behavior mirrors the MQTT-based setup and demonstrates interchangeable communication methods.

Project links:

* [MQTT test](./mqtt-test)
* [Main cloud project](./main-cloud)

A video demonstrating the working result is included below.

---

## Pictures

### Arduino in Access Point Mode

<img src="./image/ap_mode.jpg" width="300">

### Arduino Connected to WiFi

<img src="./image/wifi_connected.jpg" width="300">

### Webpage for Room and Job Configuration

<img src="./image/webpage.png" width="300">

---

## Video

### NeoPixel color changing using my API (HTTP)

*(Same visual result as the MQTT stream)*

<video src="https://github.com/user-attachments/assets/a54fd3ed-9c3d-44af-828e-2beae56ccd38" width="350" controls></video>

---

## Reflection

These weeks went smoothly overall. Most challenges came from learning C++ in an embedded context. In particular, it took some time to understand the separation of responsibilities between files: the .h files acting as interfaces or declarations, and the .cpp files containing the actual implementations. Once this structure became clearer, the codebase was much easier to reason about and extend.

Another challenge was working with API calls and rendering the retrieved data in the browser. Developing and debugging this flow was slower than expected, mainly because the Arduino IDE offers limited tooling and because the HTML for the web interface had to be written as long strings inside the code. This made iteration and debugging less comfortable compared to standard web development.

Despite these issues, the process was a valuable learning experience. It helped me better understand how embedded software, networking, and web technologies can work together in a constrained environment.

---

## Hours Spent

| Week        | Hours    |
| ----------- | -------- |
| This period | **30**   |
| Total       | **68.5** |
