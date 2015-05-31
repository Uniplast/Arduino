This library allows users to control the BlinkM RGB LEDs with relative ease. 
This library should be compatible with all Arsuino boards, including the Due. 

To use this library, declare a BlinkM control object like this:

   BlinkM lights;

You do not need to create a BlinkM object for every light you have because these lights
operate using the I2C protocol, and use addressing as a way to control individual lights
connected to the same bus. For example, you can control individual lights like this:

   lights.setRGB(<address>,<Red>,<Green>,<Blue>);

Replace <address> with the address of the light you wish to control, and use 0 to control
all of the lights at once. The following three arguments will set the RGB values of the light
at address <address>. 
