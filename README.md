# Bowling_ENGR103
Bowling Game, ENGR 103 Final Project

## Inputs
SlideSwitch: Pin 7, inputs 0 or 1 (left or right)

Use: when switched it turns the game on/off.

Right Button: Pin 5, inputs 0 or 1 (pressed or not)

Use: when pressed it simulates one ball in bowling.

## Outputs
Neopixel LEDs: 10 pixels (0 to 9), outputs RGB values from 0 to 255

Use: emits white lights to represent pins left remaining after each ball.

Red LED: pin 13, outputs on or off red light

Use: Indicated whether game is on/playing or has been switched off

Serial Monitor: outputs text

Use: prints text to guide player. As the end of the game recaps all of the frames as well as total score.

## Game Description
The game simulates 1 player bowling. Player clicks the button to roll each ball. Pins hit is shown by Neopixles and Serial Monitor. There are 10 frames with 2 balls each. At game end, each frame's score is shown on serial monitor as well as a total value.

## Scoring
Each pin down = 1 point. 
Spare = 10 + next roll. 
Strike = 10 + next two roll. 
Max Points : 280 (no additional frame in this game if a strike/spare is rolled in the last frame)
