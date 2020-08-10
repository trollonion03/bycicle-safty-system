#include <SoftwareSerial.h> // 0,1번핀 제외하고 Serial 통신을 하기 위해 선언
char command = 0;
bool action = false;
int Trg = 8;
int Ech = 9;
long Duration = 0;
long Distance = 0;
long Durationl = 0;
long Distancel = 0;
long Durationr = 0;
long Distancer = 0;
int Trgl = 4;
int Echl = 5;
int Trgr = 7;
int Echr = 6;
SoftwareSerial mySerial(2, 3); // HC-06 TX=2번핀 , RX=3번핀 연결

void setup() {
  Serial.begin(9600);
  pinMode(Trg, OUTPUT);
  pinMode(Ech, INPUT);
  mySerial.begin(9600);

}

void loop() {
  action = true; 
  if (mySerial.available() > 0)
  {
    command = mySerial.read();
    //Serial.print("incoming command is ");
    Serial.println(command);
    //if (Serial.available())
    
    
    action = true;
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
      hc_sr04();
      hc_sr04l();
      hc_sr04r();
      sendbtserial();
    }
    delay(1000);
    


    
  }

}

void hc_sr04()
{
  digitalWrite(Trg, LOW);
  delayMicroseconds(2);
  digitalWrite(Trg, HIGH);
  digitalWrite(Trg, LOW);

  Duration = pulseIn(Ech, HIGH);
  Distance = (Duration/2.9)/2;
  //Serial.print("Duration = ");
  //Serial.println(Duration);
  Serial.print("F");
  Serial.println(Distance); 
  //mySerial.print("F");
  //mySerial.println(Distance);
  /*if((Distance > 5000) && (Distance <= 7000))
  {
    mySerial.println("F");
    mySerial.println("1");
    //mySerial.println(Distance);
  }
  else if(Distance <= 5000)
  {
    mySerial.println("F");
    mySerial.println("2");
  }
  else
  {
    mySerial.println("F");
    mySerial.println("0");
  }*/
}


void hc_sr04l()
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
  //mySerial.println(Distance);
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

void hc_sr04r()
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
  //mySerial.print("F");
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

void sendbtserial()
{
  if((Distance == 1) && (Distancer == 0) && (Distancel == 0))
  {
    mySerial.println("1");
  }
  else if((Distance == 0) && (Distancer == 1) && (Distancel == 0))
  {
    mySerial.println("2");
  }
  else if((Distance == 0) && (Distancer == 0) && (Distancel == 1))
  {
    mySerial.println("3");
  }
  else if((Distance == 1) && (Distancer == 1) && (Distancel == 0))
  {
    mySerial.println("4");
  }
  else if((Distance == 1) && (Distancer == 0) && (Distancel == 1))
  {
    mySerial.println("5");
  }
  else if((Distance == 0) && (Distancer == 1) && (Distancel == 1))
  {
    mySerial.println("6");
  }
  else if((Distance == 1) && (Distancer == 1) && (Distancel == 1))
  {
    mySerial.println("7");
  }
  else
  {
    mySerial.println("0");
  }
}
