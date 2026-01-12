# Final Reflection Report - Arduino Learning Journey

## Situation

At the beginning of this learning journey, I set out to independently develop simple but functional prototypes with Arduino and expand my technical knowledge. I came from a strong software development background but had little to no experience with hardware, electronics, or microcontrollers. The learning path consisted of nine weeks in which I would complete progressively more difficult projects each week, from basic LED circuits to complex integrated systems with networking functionality.

## Task

My assignment was to work systematically toward my learning goal by completing weekly hands-on projects, sharing my knowledge and results broadly through documentation and community contributions, and reflecting on my learning process to demonstrate improvement. Specifically, I needed to learn to work with sensors and actuators, understand basic circuits, program in C/C++ for embedded systems, and ultimately realize complex integrations where hardware and software come together.

## Action

I approached the learning journey systematically with a clear progression:

**Weeks 1-2:** I started by building fundamental knowledge. I installed the Arduino IDE, studied Ohm's Law, learned to read resistor color codes, and built simple LED circuits. I created a comprehensive list of all components in my kit to understand what I would be working with.

**Week 3:** I combined input (button) with output (NeoPixel LEDs). During this week, I encountered a hardware problem where the button always indicated "pressed." Through systematic debugging, I discovered that I had placed 5V and GND in the same breadboard column. This taught me the importance of working carefully with electronics.

**Week 4:** I explored the WiFi capabilities of the Arduino UNO R4. Here I accidentally burned a potentiometer through incorrect wiring, which was a valuable lesson in checking schematics. Next, I built my own API and tried to connect it to the Arduino. After extensive debugging of SSL problems—including firmware updates and testing multiple APIs—I discovered that the Arduino UNO R4 WiFi has limitations with HTTPS. I documented this problem extensively in an Arduino forum post to help others.

**Weeks 5-7:** These were the most challenging and educational weeks. I built a fully integrated system for the Sensorlab project with:
- MQTT communication for real-time data streaming
- A web interface for WiFi configuration via Access Point mode
- Room and job configuration with dynamic API calls
- EEPROM storage for persistent data
- Code refactoring into .cpp and .h files for better structure
- Implementation of the Strategy Pattern for modular behavior
- OLED display integration for status feedback

This period required me to learn C++ in an embedded context, where I had to understand how .h files function as interfaces and .cpp files contain the implementations.

**Week 8:** I experimented with various sensors (ultrasonic, LDR, force sensor, servo motor). With the LDR sensor, I consistently got values around 1023, which after consultation with fellow students turned out to be caused by incorrect wiring. This reinforced my insight that Arduino problems are often hardware-related.

**Week 9:** I realized a gyroscope-controlled Yatzee game via WebSerial, where I streamed real-time sensor data to the browser without WiFi or cloud services.

Throughout the entire journey, I documented extensively with code, images, videos, and reflections. I actively helped fellow students with their problems and shared my knowledge via the Arduino forum.

## Result

I achieved my learning goal comprehensively. Instead of just "simple prototypes," I built a fully functional IoT system with web configuration, MQTT communication, and multiple collaborating Arduino devices.

**Concrete results:**
- 9 working projects with increasing complexity
- Mastery of C++ for embedded systems
- Understanding of hardware debugging and electronics fundamentals
- Experience with real-time communication protocols (MQTT, WebSerial)
- Successful knowledge sharing via GitHub documentation, forum posts, and helping fellow students
- 82.5 hours invested with consistently working deliverables

The most significant result was the discovery during weeks 5-7 that I find the integration between hardware and software particularly interesting—this has determined my future project direction.

## Reflection

**What went well:**
My systematic approach and software background enabled me to tackle complex problems in a structured way. Documenting failures (such as the burned potentiometer and incorrect wiring) proved more valuable for my learning process than only documenting successes. This transparency also helped others—my Arduino forum post about macOS upload problems was read by multiple people.

**What could be improved:**
Initially, I underestimated the difference between software and hardware debugging. In software, you can iterate and log quickly, but with hardware, you need to check physical connections, and often you only discover after much searching that a simple wrong wire is the problem. Week 4, for example, cost unnecessarily much time on SSL debugging while the problem was a hardware limitation. 

Additionally, I could have experimented more with design patterns for embedded systems. Although I implemented the Strategy Pattern, there was room for deeper architectural exploration.

**Key insights:**
1. **Hardware-first thinking:** With Arduino, the challenge usually lies in the electronics, not the code
2. **Documentation of failures is valuable:** My most useful documentation described what went wrong and how I solved it
3. **Integration is fascinating:** The combination of physical and digital worlds offers infinite possibilities

**Future application:**
This journey has confirmed my interest in hardware-software integration. I want to expand this further in more ambitious IoT projects, such as building a 3D-printed, remote-controllable F1 car that I have  wanted to realize. The skills in networking, real-time communication, and embedded programming form a solid foundation for this. I might even do a course/study in Electrical Engineering

---

**Total hours invested:** 82.5 hours over 9 weeks
**Key achievement:** Full-stack IoT system with web configuration, MQTT communication, and multiple collaborative Arduino devices
