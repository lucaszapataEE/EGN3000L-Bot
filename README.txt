This code runs the robot. Standard funcitonality allows the robot to pick up an item, then follow
a person or moving object. After stopping for 10 seconds, it drops the object.
The code has been made readable enough to be able to be adjusted and modified.
The functions included and their functionality are as follows.
TurnRight(): Turns the robot right for an amount of milliseconds equal to the variable turnDelay.
TurnLeft(): Turns the robot left for an amount of milliseconds equal to the variable turnDelay.
Lower(): Lowers the servo arm.
Lift(): Raises the servo arm.
Forward(): Moves the robot directly forward.
Reverse(): Moves the robot directly backwards.
Stop(): Stops the robot.
ReadDistance(): Lets the robot read how far it is from the object ahead of it.
New functionality can be added by putting those functions together as building blocks.