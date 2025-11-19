## Arduino UNO R4 

### What I Did
I researched the layout and purpose of the different  on the Arduino UNO R4.  
To do this, I used official documentation and several pinout diagrams to better understand what each section of the board does.  
I also compared the diagrams to my actual board to see where everything is physically located and made small notes to help me remember their functions later.

### What I Learned
The Arduino UNO R4 has multiple types of , each designed for specific functions:

- **Digital  (0–13):** Used for input or output. They can read button states or control components like LEDs.  marked with `~` can output PWM signals for things like LED dimming or controlling motors.  
- **Analog  (A0–A5):** These can read varying voltages, making them ideal for sensors like potentiometers or light sensors.  
- **Power :** The 5V and 3.3V  provide power to external components, GND completes the circuit, and VIN can power the board with an external source.  
- **Communication :** These include Serial (0–1), I²C (A4–A5), and SPI (10–13) connections for communicating with other modules or sensors.

I learned how important **ground (GND)** is — it completes the circuit and provides a safe return path for current.  
Understanding the power and communication  will help me later when I start using sensors or external components.

### Reflection
Before researching this, I only knew that components connected to “,” but not why certain ones were used.  
Now, I have a much clearer idea of what each pin is for and what to avoid (like using RX/TX  for regular I/O).  
This will make wiring and planning circuits much easier in the coming weeks.

---

### Sources
- [Arduino Documentation – UNO R4 Pinout](https://docs.arduino.cc/hardware/uno-r4-wifi)
- [SparkFun – What is an Arduino?](https://learn.sparkfun.com/tutorials/what-is-an-arduino/all)
- [Electronics Hub – PWM on Arduino](https://www.electronicshub.org/pwm-in-arduino/)
- [Adafruit – Arduino Basics](https://learn.adafruit.com/adafruit-arduino-lesson-2-leds/overview)
