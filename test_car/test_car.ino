/**set control port**/
const int Right_Engine = 5;
const int Right_Motor = 4;
const int Left_Engine = 6;
const int Left_Motor = 7;
enum ToGo {
  Forward = 0,
  Backward,
  Rightward,
  Leftward,
  Stop
};

typedef struct
{
  int enginePin;
  int directionPin;
}MotorControl;

const int RightMotor = 0;
const int LeftMotor = 1;
const int MotorCount = 2;
const MotorControl MotorPin[] = { { Right_Engine,Right_Motor },{ Left_Engine,Left_Motor } };

void setup()
{
  initMotor();
}

void loop()
{
  enum ToGo togo;
  togo = Forward;
  drive(togo);
  delay(1000);
  togo = Stop;
  drive(togo);
  delay(1000);
  togo = Backward;
  drive(togo);
  delay(1000);
  togo = Stop;
  drive(togo);
  delay(1000);
  togo = Rightward;
  drive(togo);
  delay(1000);
  togo = Stop;
  drive(togo);
  delay(1000);
  togo = Leftward;
  drive(togo);
  delay(1000);
  togo = Stop;
  drive(togo);
  delay(1000);
}

void initMotor()
{
  int i;
  for (i = 0; i < MotorCount; i++)
  {
    digitalWrite(MotorPin[i].enginePin, LOW);
    pinMode(MotorPin[i].enginePin, OUTPUT);
    pinMode(MotorPin[i].directionPin, OUTPUT);
  }
}

void drive(int direction)
{
  switch (direction)
  {
  case 0:
    digitalWrite(MotorPin[RightMotor].directionPin, LOW);
    digitalWrite(MotorPin[LeftMotor].directionPin, HIGH);
    analogWrite(MotorPin[RightMotor].enginePin, 255);
    analogWrite(MotorPin[LeftMotor].enginePin, 255);
    break;
  case 1:
    digitalWrite(MotorPin[RightMotor].directionPin, HIGH);
    digitalWrite(MotorPin[LeftMotor].directionPin, LOW);
    analogWrite(MotorPin[RightMotor].enginePin, 255);
    analogWrite(MotorPin[LeftMotor].enginePin, 255);
    break;
  case 2:
    digitalWrite(MotorPin[RightMotor].directionPin, HIGH);
    digitalWrite(MotorPin[LeftMotor].directionPin, HIGH);
    analogWrite(MotorPin[RightMotor].enginePin, 0);
    analogWrite(MotorPin[LeftMotor].enginePin, 255);
    break;
  case 3:
    digitalWrite(MotorPin[RightMotor].directionPin, LOW);
    digitalWrite(MotorPin[LeftMotor].directionPin, LOW);
    analogWrite(MotorPin[RightMotor].enginePin, 255);
    analogWrite(MotorPin[LeftMotor].enginePin, 0);
    break;
  default:
    digitalWrite(MotorPin[RightMotor].directionPin, LOW);
    digitalWrite(MotorPin[LeftMotor].directionPin, HIGH);
    analogWrite(MotorPin[RightMotor].enginePin, 0);
    analogWrite(MotorPin[LeftMotor].enginePin, 0);
    break;
  }
}
