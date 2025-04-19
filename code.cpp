// Pin Definitions
#define LEFT_SENSOR_PIN A0  // Analog pin for left sensor
#define RIGHT_SENSOR_PIN A1 // Analog pin for right sensor
#define BACK_LEFT_MOTOR_PIN 9   // PWM pin for back left motor
#define BACK_RIGHT_MOTOR_PIN 10 // PWM pin for back right motor
#define FRONT_LEFT_ENABLE 5     // Enable pin for front left motor
#define FRONT_LEFT_IN1 6        // Input pin 1 for front left motor
#define FRONT_LEFT_IN2 7        // Input pin 2 for front left motor
#define FRONT_RIGHT_ENABLE 8    // Enable pin for front right motor
#define FRONT_RIGHT_IN1 3       // Input pin 1 for front right motor
#define FRONT_RIGHT_IN2 4       // Input pin 2 for front right motor

// Threshold for line detection (adjust based on lighting)
#define LINE_THRESHOLD 500

// Motor Structure
struct Motor {
  int enablePin;
  int in1Pin;
  int in2Pin;
};

// Function Prototypes
void setupMotors(struct Motor *motor, int enable, int in1, int in2);
void setMotorSpeed(struct Motor *motor, int speed);
void turnLeft(struct Motor *leftMotor, struct Motor *rightMotor);
void turnRight(struct Motor *leftMotor, struct Motor *rightMotor);
void moveForward();
void stopMotors();

struct Motor frontLeftMotor, frontRightMotor; // Front motors through L293D

void setup() {
  Serial.begin(9600);

  // Back motors (direct connection)
  pinMode(BACK_LEFT_MOTOR_PIN, OUTPUT);
  pinMode(BACK_RIGHT_MOTOR_PIN, OUTPUT);

  // Front motors through L293D motor driver
  setupMotors(&frontLeftMotor, FRONT_LEFT_ENABLE, FRONT_LEFT_IN1, FRONT_LEFT_IN2);
  setupMotors(&frontRightMotor, FRONT_RIGHT_ENABLE, FRONT_RIGHT_IN1, FRONT_RIGHT_IN2);

  // Line sensors
  pinMode(LEFT_SENSOR_PIN, INPUT);
  pinMode(RIGHT_SENSOR_PIN, INPUT);
}

void loop() {
  int leftSensor = analogRead(LEFT_SENSOR_PIN);
  int rightSensor = analogRead(RIGHT_SENSOR_PIN);

  // Decide movement based on sensor readings
  if (leftSensor < LINE_THRESHOLD && rightSensor < LINE_THRESHOLD) {
    moveForward();
  } else if (leftSensor < LINE_THRESHOLD) {
    turnRight(&frontLeftMotor, &frontRightMotor);
  } else if (rightSensor < LINE_THRESHOLD) {
    turnLeft(&frontLeftMotor, &frontRightMotor);
  } else {
    stopMotors();
  }
}

// Motor Setup Function
void setupMotors(struct Motor *motor, int enable, int in1, int in2) {
  motor->enablePin = enable;
  motor->in1Pin = in1;
  motor->in2Pin = in2;

  pinMode(motor->enablePin, OUTPUT);
  pinMode(motor->in1Pin, OUTPUT);
  pinMode(motor->in2Pin, OUTPUT);
}

// Set Motor Speed
void setMotorSpeed(struct Motor *motor, int speed) {
  analogWrite(motor->enablePin, speed);
}

// Move Forward
void moveForward() {
  analogWrite(BACK_LEFT_MOTOR_PIN, 150);  // Back motors direct connection
  analogWrite(BACK_RIGHT_MOTOR_PIN, 150);

  setMotorSpeed(&frontLeftMotor, 150);   // Front motors
  digitalWrite(frontLeftMotor.in1Pin, HIGH);
  digitalWrite(frontLeftMotor.in2Pin, LOW);

  setMotorSpeed(&frontRightMotor, 150);
  digitalWrite(frontRightMotor.in1Pin, HIGH);
  digitalWrite(frontRightMotor.in2Pin, LOW);
}

// Turn Left
void turnLeft(struct Motor *leftMotor, struct Motor *rightMotor) {
  setMotorSpeed(leftMotor, 0);
  setMotorSpeed(rightMotor, 150);
  digitalWrite(rightMotor->in1Pin, HIGH);
  digitalWrite(rightMotor->in2Pin, LOW);
}

// Turn Right
void turnRight(struct Motor *leftMotor, struct Motor *rightMotor) {
  setMotorSpeed(leftMotor, 150);
  setMotorSpeed(rightMotor, 0);
  digitalWrite(leftMotor->in1Pin, HIGH);
  digitalWrite(leftMotor->in2Pin, LOW);
}

// Stop Motors
void stopMotors() {
  analogWrite(BACK_LEFT_MOTOR_PIN, 0);
  analogWrite(BACK_RIGHT_MOTOR_PIN, 0);

  setMotorSpeed(&frontLeftMotor, 0);
  setMotorSpeed(&frontRightMotor, 0);
} 
