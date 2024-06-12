# ENGR103 Game
Bob-it inspired game desinged for and on the adafruit circuit playground

--------------------------OVERVIEW---------------------------------------------

You will be ask to do a task like pressing a button or touch something to change the capacity (used a nail attached to an aligator clip on pin A1)
Each successful task will increase over all score
As you get more tasks right the amount of time you have to complete the task will decrease until the wrong task is done or you run out of time.


---------------------------RULES---------------------------------------------

At the very beginning you'll be able to select the starting difficulty
pressing the right button(pin 5) will increase difficulty
pressing the left button (pin 4) will decrease difficulty
moving the slide switch will start the game


The display will tell the next required task
If the right thing is done it will play a quick happy tune light up green and diplay you're total score
then it will display the next task

After 3 sucessful task it will increase the difficutly to the next level. This will lower the time you have to complete taskes.

If you run out of time or press the wrong button all the lights will flash red and the screen will display your score, then it will restart from the begining.



----------------The required inputs and outputs--------------------------
  
  -----------Inputs---------
  
  Left and Right buttons (pin 4 & pin 5)
  
  Contact sensor (capacity, CircuitPlayground.readCap(6);)


  -----------Outputs--------

LEDs
Serial Monitor
Speaker
