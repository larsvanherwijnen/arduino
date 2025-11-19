## Resistors and Color Codes

### What I Did
I researched what resistors do, how to identify their values using color codes, and why they are important in circuits.  
Using the [Digi-Key Color Code Calculator](https://www.digikey.com/en/resources/conversion-calculators/conversion-calculator-resistor-color-code), I practiced reading resistor color bands from my Arduino kit and double-checked that I was interpreting them correctly.  
Then, I applied this knowledge by building a simple LED test circuit both with and without a resistor to observe the difference in brightness.

### What I Learned
Resistors limit the amount of current flowing through a circuit. Without them, components like LEDs can receive too much current and get damaged.  
Each resistor has color bands that represent its value and tolerance.  
For example:
- Red, Red, Brown, Gold → 220 Ω ±5%
- Orange, Orange, Brown, Gold → 330 Ω ±5%
- Brown, Black, Red, Gold → 1 kΩ ±5%

When I ran the blinking LED test, I noticed that the LED was brighter without a resistor, but I also learned that this is unsafe for the long term.  
The resistor slightly reduced brightness but protected both the LED and the Arduino board.

### Reflection
I always saw resistors as small, unimportant components, but now I understand they play a key role in protecting circuits.  
Being able to identify resistor values by color is also really useful — it makes setting up circuits faster and more accurate.  
This experiment helped me actually see what current limitation does in practice.

---

### Sources
- [Digi-Key – Resistor Color Code Calculator](https://www.digikey.com/en/resources/conversion-calculators/conversion-calculator-resistor-color-code)
- [SparkFun – Resistor Color Codes](https://learn.sparkfun.com/tutorials/resistor-color-codes/all)
- [All About Circuits – Understanding Resistors](https://www.allaboutcircuits.com/textbook/direct-current/chpt-2/resistors/)
- [Adafruit – LED Basics and Resistors](https://learn.adafruit.com/all-about-leds/current-limiting)
