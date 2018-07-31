//센서와 연결된 아날로그 핀 설정
int flexpin = A5; 
int  led = 13;

void setup() {
  // 시리얼 통신을 열고 속도를 9600로 설정한다.
    Serial.begin(9600); 
    pinMode(led, OUTPUT);
}

void loop() {
  //센서값을 저장할 변수 설정
  int flexVal; 
  // 센서로 부터 보내오는 값을 입력 받는다.(0-1023)
  flexVal = analogRead(flexpin); 
  Serial.print("sensor: ");
  // sensor:XXX 로 출력한다(XXX값은 센서로 부터 읽어 온 값)
  Serial.println(flexVal); 
  if(flexVal > 980){
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led,LOW);    
  }
  
  delay(1000);
}
