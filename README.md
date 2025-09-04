Precision Line-Guided Autonomous Robot

The Precision Line-Guided Autonomous Robot is a smart, sensor-driven robotic system designed for accurate line-following and autonomous navigation. Powered by an Arduino microcontroller, this robot uses analog infrared sensors to detect and follow a predefined path with high precision.

Features

Line Following: Uses two analog IR sensors to detect black/white surfaces.

Autonomous Navigation: Follows the path without manual control.

Dual Motor System: Combination of direct-driven motors and L293D motor driver for smooth movement.

Directional Control: Capable of moving forward, turning left, turning right, and stopping based on sensor input.

Adjustable Sensitivity: Threshold values can be tuned for different lighting conditions.

Hardware Requirements

Arduino Uno (or compatible board)

2 Analog IR Sensors

2 DC Motors (back motors, direct-driven)

2 DC Motors (front motors via L293D)

L293D Motor Driver IC

Motor Driver Power Supply (Battery or DC source)

Chassis with wheels

Jumper wires and connectors

Pin Configuration

Sensors:

Left Sensor → A0

Right Sensor → A1

Back Motors (direct connection):

Back Left Motor → Pin 9 (PWM)

Back Right Motor → Pin 10 (PWM)

Front Motors (via L293D):

Front Left Enable → Pin 5

Front Left IN1 → Pin 6

Front Left IN2 → Pin 7

Front Right Enable → Pin 8

Front Right IN1 → Pin 3

Front Right IN2 → Pin 4

How It Works

The sensors continuously read surface reflectivity values.

If both sensors detect the line, the robot moves forward.

If the left sensor detects the line, the robot turns right.

If the right sensor detects the line, the robot turns left.

If no line is detected, the robot stops.

Code Explanation

Motor Struct: Stores enable and input pins for each motor.

setupMotors(): Initializes pins for the motors.

setMotorSpeed(): Controls motor speed using PWM.

moveForward(), turnLeft(), turnRight(), stopMotors(): Defines basic robot movements.

loop(): Continuously checks sensor values and decides movement.

Customization

Adjust LINE_THRESHOLD in the code to calibrate sensor sensitivity.

Modify motor speed values in moveForward(), turnLeft(), and turnRight() for better control.

Future Enhancements

PID control for smoother and more accurate line following.

Additional sensors for sharper turns and intersections.

Obstacle detection and avoidance.
