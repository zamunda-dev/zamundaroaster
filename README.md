# zamundaroaster
Building a fulll automated coffee roaster from a popcorn popper

Based on the included sketch, I did some roasting with batches of 100gram. I think the result comes out quite nice, from Artisan I can control heat and air conveniently. I mounted the roaster on a wooden box which I can open later to check wirings etc. Bluetooth also works well.
Also built a simple chaff collector which sits on top of the roaster which can be emptied from time to time.

BTW: I disabled the "slew-function" withing the sketch for now since this "messed up" de loop-functionality within Arduino. So far, I did not experience overload problems (which was something this function should help to prevent)

Obviously there is much room for improvement but this was/is an (exciting) learning-by-doing-and-falling process.

Hardware used in this build:
- Princess Popcorn popper (1200W/220V)
- MAX6675 sensor for temp readings
- Arduino UNO (3)
- (Manual) DC voltage adapter for fan
- L298N DC-Motor Controller for slider-controlling the fan from Artisan
- Solid state relay for controlling the heat element
- Bluetooth module HC06 for wireless connection from Artisan to roaster
- DC-adapter iPhone for Arduino
