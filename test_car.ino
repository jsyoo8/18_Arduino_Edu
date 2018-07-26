#include <SoftwareSerial.h>
int LED =3 ;//LED를 3번핀에 연결합니다.
int mySwitch = 0;
String myString=""; //받는 문자열
SoftwareSerial mySerial(4, 5); //블루투스의 Tx, Rx핀을 2번 3번핀으로 설정
void setup ()
{
  Serial.begin(9600);
  while (!Serial) {
    ; //시리얼통신이 연결되지 않았다면 코드 실행을 멈추고 무한 반복
  }
  Serial.println("Hello World!");

  //블루투스와 아두이노의 통신속도를 9600으로 설정
  mySerial.begin(9600);
  pinMode(LED,OUTPUT);//3번핀에 연결된 LED를 출력으로 설정합니다.
}
void loop()
{
  int analogInput = 0;
  int brightness = 0;
  while(Serial.available())  //mySerial 값이 있으면
  {
    char myChar = (char)Serial.read();  //mySerial int형식의 값을 char형식으로 변환
    myString+=myChar;   //수신되는 문자열을 myString에 모두 붙임 (1바이트씩 전송되는 것을 모두 붙임)
    delay(5);           //수신 문자열 끊김 방지
  }
  
  if(!myString.equals(""))  //myString 값이 있다면
  {
    Serial.println("input value: "+myString); //시리얼모니터에 myString값 출력
 
      if(myString.equals("on"))  //myString 값이 'on' 이라면
      {
        mySwitch = 1;
    Serial.println(mySwitch);
      } else {
        mySwitch = 0;
    Serial.println(mySwitch);
      }
      
    myString="";  //myString 변수값 초기화
  }
  if(mySwitch == 0){
    digitalWrite(LED,HIGH);
  }
  else {
    analogInput = analogRead(A0);//가변저항을 아날로그 0번핀에 연결하고 이를 입력으로 설정합니다.
    brightness = analogInput /4;// 가변저항의 입력값(0-1023사이의 값)을 LED의밝기값(0-255)의 값으로 변경해줍니다.
    analogWrite(LED, brightness);//가변저항의 값을 LED로 보내 출력합니다.
  }
}
