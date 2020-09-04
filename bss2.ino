#include <SoftwareSerial.h> // 0,1번핀 제외하고 Serial 통신을 하기 위해 선언
char command = 0;
bool action = false;
int Trg = 8; //초음파센서(중앙)
int Ech = 9;
long Duration = 0; //정수로 정의(딱히 상관 없을거 같기도 하지만 상관있음)
long Distance = 0;
long Durationl = 0;
long Distancel = 0;
long Durationr = 0;
long Distancer = 0;
int Trgl = 4; //초음파센서(좌측)
int Echl = 5;
int Trgr = 7; //초음파센서(우측)
int Echr = 6;
SoftwareSerial mySerial(2, 3); // HC-06 TX=2번핀 , RX=3번핀 연결 hc-06

void setup() {
  Serial.begin(9600);
  pinMode(Trg, OUTPUT); //ㅋㅋㅋㅋㅋㅋㅋㅋㅋ 하나만해놨네. 이러니까 대회장소가서 문제생기지
  pinMode(Ech, INPUT);
  pinMode(Trgl, OUTPUT); //깃허브 정리하다 수정함
  pinMode(Echl, INPUT);
  pinMode(Trgr, OUTPUT);
  pinMode(Echr, INPUT);
  mySerial.begin(9600);

}

void loop() {
  action = true; //작동 시작
  if (mySerial.available() > 0)
  {
    command = mySerial.read();
    //Serial.print("incoming command is ");
    Serial.println(command);
    //if (Serial.available())
    
    
    action = true; //개발과정에서의 테스트코드 && action = ture 시 센서 동작, 블루투스 통신 함수 
    if (command == '0'){

      action = false;
    //  Serial.println("masurement end");
    }
    else if (command == '1')
    {
      action = true;
    //  Serial.println("masurement start");
    }
    else
    {
    //  Serial.println("invaild command");
    }
  }
  else
  {
    if (action == true)
    {
//      Serial.println("not running");
//    }
//    else
//    {
      //Serial.println("running");
      hc_sr04(); //개발 과정에서 사용한 센서가 hc_sr04여서 함수 이름을 이와 같이 지정
      hc_sr04l(); //좌측센서
      hc_sr04r(); //우측센서
      sendbtserial(); //HC-06 BT Serial 통신
    }
    delay(1000); //1초마다 한번씩(이렇게 안하면 앱에서 못받아들임)
    


    
  }

}

void hc_sr04() //거리별로 값을 다르게 하려고 하였으나, 시간 문제로 제외
{
  digitalWrite(Trg, LOW);
  delayMicroseconds(2);
  digitalWrite(Trg, HIGH);
  digitalWrite(Trg, LOW);

  Duration = pulseIn(Ech, HIGH);
  Distance = (Duration/2.9)/2; //거리 = (시간/2.9)/2
  //Serial.print("Duration = ");
  //Serial.println(Duration);
  Serial.print("F");
  Serial.println(Distance); 
  //mySerial.print("F");
  //mySerial.println(Distance); //개발테스트용
  /*if((Distance > 5000) && (Distance <= 7000))
  {
    mySerial.println("F");//전면
    mySerial.println("1");//1
    //mySerial.println(Distance);
  }
  else if(Distance <= 5000)
  {
    mySerial.println("F");
    mySerial.println("2");//2
  }
  else
  {
    mySerial.println("F");
    mySerial.println("0");//감지 X
  }*/
}


void hc_sr04l() //좌측센서
{
  digitalWrite(Trgl, LOW);
  delayMicroseconds(2);
  digitalWrite(Trgl, HIGH);
  digitalWrite(Trgl, LOW);

  Durationl = pulseIn(Echl, HIGH);
  Distancel = (Durationl/2.9)/2;
  //Serial.print("Duration = ");
  //Serial.println(Duration);
  Serial.println("L");
  Serial.println(Distancel); 
  //mySerial.print("F");
  //mySerial.println(Distance);//개발 테스트용
  /*if((Distancel > 5000) && (Distance <= 7000))
  {
    mySerial.println("L");
    mySerial.println("1");
    //mySerial.println(Distancel);
  }
  else if(Distancel <=5000)
  {
    mySerial.println("L");
    mySerial.println("2");
  }
  else
  {
    mySerial.println("L");
    mySerial.println("0");
  }*/
}

void hc_sr04r() //우측센서
{
  digitalWrite(Trgr, LOW);
  delayMicroseconds(2);
  digitalWrite(Trgr, HIGH);
  digitalWrite(Trgr, LOW);

  Durationr = pulseIn(Echr, HIGH);
  Distancer = (Durationr/2.9)/2;
  //Serial.print("Duration = ");
  //Serial.println(Duration);
  Serial.println("R");
  Serial.println(Distancer); 
  //mySerial.print("F"); //개발 테스트용
  //mySerial.println(Distance);
  /*if((Distancer > 5000) && (Distancer <= 7000))
  {
    mySerial.println("R");
    mySerial.println("1");
    //mySerial.println(Distancer);
  }
  else if(Distancer <=5000)
  {
   mySerial.println("R");
   mySerial.println("2");
  }
  else
  {
   mySerial.println("R");
   mySerial.println("0");
  }*/
}

void sendbtserial() //데이터전송 - 앱에서 값을 받을때 혼선되지 않도록 전송 텍스트 간략화.
{
  if((Distance == 1) && (Distancer == 0) && (Distancel == 0)) // 중간 1, 우측 0, 좌측 0
  {
    mySerial.println("1");
  }
  else if((Distance == 0) && (Distancer == 1) && (Distancel == 0)) // 중간 0, 우측 1, 좌축 0
  {
    mySerial.println("2");
  }
  else if((Distance == 0) && (Distancer == 0) && (Distancel == 1)) // 중간 0, 우측 0, 좌측 1
  {
    mySerial.println("3");
  }
  else if((Distance == 1) && (Distancer == 1) && (Distancel == 0)) // 중간 1, 우측 1, 좌측 0
  {
    mySerial.println("4");
  }
  else if((Distance == 1) && (Distancer == 0) && (Distancel == 1)) // 중간 1, 우측 0, 좌측 1
  {
    mySerial.println("5");
  }
  else if((Distance == 0) && (Distancer == 1) && (Distancel == 1)) // 중간 0, 우측 1, 좌측 1
  {
    mySerial.println("6");
  }
  else if((Distance == 1) && (Distancer == 1) && (Distancel == 1)) // 전체 동시 감지
  {
    mySerial.println("7");
  }
  else //감지 X
  {
    mySerial.println("0");
  } //하.. 이제 앱도해야하는데....
} //2020-08-12 수정
