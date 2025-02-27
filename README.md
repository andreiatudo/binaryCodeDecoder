# How It Works

At startup, the system initializes, and the message "Hello" appears on the screen. Depending on the ambient light level detected by the photoresistor, we determine whether we are in an emergency situation or not. If this value is below 200 (indicating an emergency), we can enter signals. Otherwise, the screen displays "Bright light".

If the value is below 200, we can input observed signals using the button as follows:

- Press and hold for less than one second to enter a `.`
- Press and hold between one and two seconds to enter a `-`
- Press and hold between two and three seconds to check the entered letter. If it is a valid letter, the blue LED turns on; otherwise, the message "Invalid code!" is displayed on the screen.
- Press and hold for at least three seconds to display all entered letters so far, and the red LED will turn on.

## Short Code Explanation

### setup Function

The `setup` function configures the photoresistor and button as inputs, sets the LEDs as outputs, and initializes the LCD by turning on the backlight and displaying the message "Hello!" for 3 seconds before clearing the screen.

### loop Function

The `loop` function reads the photoresistor value and button state, then follows this logic:

- If the photoresistor value is `< 200`:
  - If the button is pressed for the first time, the timer starts.
  - If the button remains pressed, the elapsed time is displayed on the LCD.
  - If the button is released, the elapsed time is checked, and the appropriate action is taken based on the rules described in the "How It Works" section.
- Otherwise, the LCD backlight turns off, and "Bright light!" is displayed.

### convertToAscii Function

The `convertToAscii` function handles the conversion process.
