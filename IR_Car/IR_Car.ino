#include <IRremote.h>
int IR_RECV_PIN = 13; // IR 수신기와 연결된 PIN
IRrecv ir_recv(IR_RECV_PIN);
decode_results decode_data;

const int button0 = 0xFF6897;
const int button1 = 0xFF30CF;
const int button2 = 0xFF18E7;
const int button3 = 0xFF7A85;
const int button4 = 0xFF10EF;
const int button5 = 0xFF38C7;
const int button6 = 0xFF5AA5;
const int button7 = 0xFF42BD;
const int button8 = 0xFF4AB5;
const int button9 = 0xFF52AD;

int beforeSignal = 4;

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
  Serial.begin(9600);
  ir_recv.enableIRIn();
  initMotor();
}

void loop()
{
  enum ToGo togo;
  if (ir_recv.decode(&decode_data)) {
    if (decode_data.decode_type == NEC) {
      togo = IRrecvCommand(decode_data.value);
      Serial.println(togo);
      drive(togo);
      delay(300);
      togo = Stop;
      drive(togo);
    }
    ir_recv.resume();
  }
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

int IRrecvCommand(int receiveSignal) {
  Serial.println(receiveSignal);
  if (receiveSignal == -1) {
    return beforeSignal;
  }
  switch (receiveSignal)
  {
  case button2:
    beforeSignal = 0;
    return 0;
  case button8:
    beforeSignal = 1;
    return 1;
  case button6:
    beforeSignal = 2;
    return 2;
  case button4:
    beforeSignal = 3;
    return 3;
  default:
    beforeSignal = 4;
    return 4;
  }
}
