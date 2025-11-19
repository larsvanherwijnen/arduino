## Ohm’s Law & Basic Circuits

### What I Did
I studied Ohm’s Law to understand how voltage, current, and resistance relate to each other.  
I read examples and watched tutorials that showed how to calculate resistor values for LEDs, then applied it to my own LED test circuit.  
I also looked into how breadboards are connected internally, which helped me understand how current flows between components.

### What I Learned
Ohm’s Law states:
> V = I × R

This formula explains how voltage (V), current (I), and resistance (R) are connected.  
I learned how to use it to calculate the right resistor value for an LED circuit.  
For example:
- Arduino output = 5V  
- LED voltage drop = 2V  
- Voltage across resistor = 3V  
- Desired current = 0.02A  
→ R = 3 / 0.02 = 150 Ω  
Since 220 Ω is a safer standard value, that’s what I used.

This calculation matched what I observed — the LED worked normally with the resistor and became brighter without it.  
It helped me understand that Ohm’s Law isn’t just theory; it explains exactly what happens in a real circuit.

### Reflection
Learning how to apply Ohm’s Law made everything else click.  
Before, I didn’t fully understand how voltage and current worked together, but now I can calculate what’s happening in a circuit before I even build it.  
It also showed me why using the right resistor value is important for protecting components and making circuits behave predictably.

---

### Sources
- [All About Circuits – Ohm’s Law](https://www.allaboutcircuits.com/textbook/direct-current/chpt-2/ohms-law/)
- [Khan Academy – Ohm’s Law](https://www.khanacademy.org/science/physics/circuits-topic/circuits-resistance/a/what-is-ohms-law)
- [Arduino – Blink Example](https://docs.arduino.cc/built-in-examples/basics/Blink)
- [Tinkercad Circuits – Arduino Simulations](https://www.tinkercad.com/circuits)
