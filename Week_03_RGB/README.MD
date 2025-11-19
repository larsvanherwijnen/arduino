## Week 3 – RGB LEDs & Button Control

### Goal

Learn how to use a push button as an input on the Arduino and combine it with NeoPixel RGB LEDs.
Understand how button states work, why debouncing is needed, and how to switch between different light modes using a single button.

### Activities

* Started by wiring a push button and testing it with a basic serial-print sketch.
* Debugged an issue where the button always showed as “pressed.” This happened because I accidentally placed the 5V and GND wires in the same breadboard column.
* Rewired the button correctly (pictures below).
* Looked up which library was needed for my NeoPixel strip and installed the **Adafruit NeoPixel** library.
  → [https://github.com/adafruit/Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
* Tested the LEDs with a simple “first light test” to confirm the strip was working.
* Combined the button and NeoPixels into one program that cycles through several modes.
* Spent most of my time figuring out how to rotate through the different RGB patterns smoothly.

### Code / Project

This week’s project was a button-controlled NeoPixel system.
Pressing the button cycles through multiple modes: solid colors, rainbow, theater chase, fire flicker, sparkle, and off.

> Files used:
> • `button_test.ino`
> • `first_led_test.ino`
> • `rgb_button_modes.ino` (final combined sketch)


### Pictures

## Incorrect wiring:
<img src="./images/wiring_incorrect.jpg" width="300">

## Correct wiring:
<img src="./images/wiring_correct.jpg" width="300">

### Videos

## First LED light test
<video src="./videos/first_light_test.mp4" width="350" controls></video>

## RGB mode cycling demo
<video src="./videos/rgb_cycle_demo.mp4" width="350" controls></video>


### Reflection

This week was a mix of hardware troubleshooting and learning how to structure code around user input. At the beginning, the button kept triggering even when I wasn’t touching it, which was confusing until I realized I had accidentally placed GND and 5V in the same breadboard column. Fixing the wiring immediately solved the issue.

The NeoPixels were easier to set up once I found the correct library. The first light test confirmed the LEDs were responding, which helped me move on to the animation part. The most challenging part was combining everything so the button could cycle between animations without blocking the loop. I had to think more carefully about timing, debouncing, and how to let animations update smoothly.


### Hours spent

9 hours



