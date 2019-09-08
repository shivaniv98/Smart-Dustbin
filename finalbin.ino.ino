#include<SoftwareSerial.h>
SoftwareSerial gsm(2, 3);
char str[70];
char *test="$GPGGA";       
char logitude[10];
char latitude[10];
int i,j,k;
int temp;
long duration, distance, duration1, distance1;

#define trigPin A0
#define echoPin A1

#define trigPin1 A2
#define echoPin1 A3

#define IN1 6
#define IN2 7
#define IR  A4
#define MOISTURE  A5

 void msg1()
 {
    Serial.print(latitude);
    Serial.print(latitude);
    gsm.println("AT");    //select text mode
    delay(1000);
    gsm.println("AT+CMGF=1");    //select text mode
    delay(1000);
    gsm.println("AT+CMGS=\"+917020944092\"\r");  // enter receipent number
    delay(1000);
    gsm.println("DRY GARBAGE OVERLOADED");             //enter latitude in msg
    gsm.println("LOCATION");             //enter latitude in msg
    gsm.print("Latitude(N): ");             //enter latitude in msg
    gsm.print(latitude);                  //enter latitude value in msg
    gsm.print("Longitude(E): ");            //enter Longitude in Msg
    gsm.println(logitude);                  //enter longitude value in msg
    gsm.write(0x1A);                      //send msg  Ctrl+z=26
    delay(1000);
   }

 void msg2()
 {
    Serial.print(latitude);
    Serial.print(latitude);
    gsm.println("AT");    //select text mode
    delay(1000);
    gsm.println("AT+CMGF=1");    //select text mode
    delay(1000);
    gsm.println("AT+CMGS=\"+917020944092\"\r");  // enter receipent number
    delay(1000);
    gsm.println("WET GARBAGE OVERLOADED");             //enter latitude in msg
    gsm.println("LOCATION");             //enter latitude in msg
    gsm.print("Latitude(N): ");             //enter latitude in msg
    gsm.print(latitude);                  //enter latitude value in msg
    gsm.print("Longitude(E): ");            //enter Longitude in Msg
    gsm.println(logitude);                  //enter longitude value in msg
    gsm.write(0x1A);                      //send msg  Ctrl+z=26
    delay(1000);
    }

void clockwise()
{
   digitalWrite(IN1, LOW);  // Added this line
   digitalWrite(IN2, HIGH);  // Added this line

}
void anticlockwise()
{
  digitalWrite(IN1, HIGH);  // Added this line
  digitalWrite(IN2, LOW);  // Added this line

}
void stop_motor()
{
  digitalWrite(IN1, LOW);  // Added this line
  digitalWrite(IN2, LOW);  // Added this line

}

void ultra()
{
    digitalWrite(trigPin, LOW);  // Added this line
    delayMicroseconds(2); // Added this line
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;
    Serial.println(distance);

    digitalWrite(trigPin1, LOW);  // Added this line
    delayMicroseconds(2); // Added this line
    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin1, LOW);
    duration1 = pulseIn(echoPin1, HIGH);

    distance1 = (duration1 / 2) / 29.1;
   Serial.println(distance1);

}

void setup()
{
  pinMode(IR,INPUT); // Configuring pin A1 as input
  pinMode(IN1,OUTPUT); // Configuring pin
  pinMode(IN2,OUTPUT); // Configuring pin 
  digitalWrite(IN1, LOW);  // Added this line
  digitalWrite(IN2, LOW);  // Added this line

  gsm.begin(9600);
  Serial.begin(9600);             // we agree to talk fast!
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  Serial.println("WELCOME");
  delay(1000);
}
void loop()
{

 if (temp==1) 
  {
    for(i=18;i<27;i++)          //extract latitude from string
    {
     latitude[j]=str[i];
     j++;
    }
    for(i=30;i<40;i++)          //extract longitude from string
    {
    logitude[k]=str[i];
     k++;
    }
    delay(100);
    temp=0;
    i=0;
    j=0;
    k=0;
    Serial.println("CORDI. GETTED");
    }
       ultra();
       if(distance < 7)
       {
         Serial.println("WET GARBADE FULL ");
         delay(1000);
         msg2();
       }
       if(distance1 < 7)
       {
         Serial.println("DRY GARBADE FULL ");
         delay(1000);
         msg1();
       }
      delay(1000);
    int state = digitalRead(IR);
    int state_M = digitalRead(MOISTURE);
    if (state == LOW)
    {
    Serial.println("GARBAGE DETECTED");
    delay(1000);
    int state_M = digitalRead(MOISTURE);
    if (state_M == LOW)
    {
       Serial.println("WET GARBAGE ");
       delay(1000);
       clockwise();
       delay(1400);
       stop_motor();
       delay(1000);
       ultra();
       if(distance < 7)
       {
         Serial.println("WET GARBADE FULL ");
         delay(1000);
         msg2();
       }
       if(distance1 < 7)
       {
         Serial.println("DRY GARBADE FULL ");
         delay(1000);
         msg1();
       }

    }
    if (state_M == HIGH)
    {
       Serial.println("DRY GARBAGE ");
       delay(1000);
       anticlockwise();
       delay(1400);
       stop_motor();
       ultra();
       if(distance < 7)
       {
         Serial.println("WET GARBADE FULL ");
         delay(1000);
         msg2();
       }
       if(distance1 < 7)
       {
         Serial.println("DRY GARBADE FULL ");
         delay(1000);
         msg1();
       }

    }

    }
}

void serialEvent()
{
  while (Serial.available())            //Serial incomming data from GPS 
  {
    char inChar = (char)Serial.read(); 
    str[i]= inChar;                  //store incomming data from GPS to temparary string str[]
     i++;
     if (i < 7)                       
     {
      if(str[i-1] != test[i-1])         //check for right string
      {
        i=0; 
      }
     }
    if(i >=60)
    {
     temp=1;
    } 
  }
}

